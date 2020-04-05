#include "StdAfx.h"
#include "Global.h"
#include "HpglFile.h"
#include "Thread.h"
int gnPackSum=0;

int WaitWorkNone(CWnd* pParent,BOOL bIsPlot);

UINT DoPlot(CWnd* pParent); //喷墨过程
UINT DoCut(CWnd* pParent); //切割过程

int WaitWorkNone(CWnd* pParent,BOOL bIsPlot)
{
	while(1)
	{
		if( 0 == gUSB.OnGetMacState() )
		{
			if (THREAD_MESSAGE_CANCEL == gMacSet.getThreadMessage())
			{
				gUSB.OnWorkCtrl(WORKCMD_CANCEL);
				gMacSet.setThreadMessage(THREAD_MESSAGE_NONE);
				return ERROR_CANCEL_FILE;
			}
			else if (THREAD_MESSAGE_RESUME == gMacSet.getThreadMessage())
			{
				gUSB.OnWorkCtrl(WORKCMD_RESUME);
				gMacSet.setThreadMessage(THREAD_MESSAGE_NONE);
			}
			else if (THREAD_MESSAGE_PAUSE == gMacSet.getThreadMessage())
			{
				gUSB.OnWorkCtrl(WORKCMD_PAUSE);
				gMacSet.setThreadMessage(THREAD_MESSAGE_NONE);
			}
			if ( ( WORKING != gSysState) &&( WORK_PAUSE != gSysState) )
			{
				return ERROR_CANCEL_FILE;
			}
			if( (WORKING == gSysState) && (gWorkType == WT_NONE) )
			{
				break;
			}
			if( (!bIsPlot)||(WORK_PAUSE == gSysState) )
			{
				pParent->SendMessage(USER_DISP_STAT,0,0);
			}
		}
		Sleep(10);
	}
	return 0;
}

UINT DoPlot(CWnd* pParent) //开始喷墨
{
	int rev;
	int nCurPackNo;
	u8 PlotDir;
	if (0 == gnPackSum) //没有打印数据
	{
		return 0; //成功完成
	}

	for (nCurPackNo =0; nCurPackNo<gnPackSum; )
	{
		if (gMacSet.getSpType() == 1)
		{
			IUT308_SetSpDataZero(); 
			GetOnePackOrgData(nCurPackNo); //获取一包喷墨数据，存入 g_SpDataOrg 中
			IUT308_ConvertOrgDataToSendData(nCurPackNo); //将原始数据格式转换成打印数据 存入 g_SpDataSend中
			IUT308_ZipSpSendData();
		}
		else
		{
			HP45_SetSpDataZero(); 
			GetOnePackOrgData(nCurPackNo); //获取一包喷墨数据，存入 g_SpDataOrg 中
			HP45_ConvertOrgDataToSendData(nCurPackNo); //将原始数据格式转换成打印数据 存入 g_SpDataSend中
			HP45_ZipSpSendData();
		}

		rev = WaitWorkNone(pParent,TRUE);
		if( rev !=0 ) 
			return rev;

		if(gUSB.WriteBulk( (char*)(&(g_ZippedSpDataSend[0])),g_iSpdataSizeZipped ) == g_iSpdataSizeZipped ) //数据包发送成功
		{
			Sleep(10);
			if ( (gMacSet.getBiDir())&&(nCurPackNo%2 == 1) )
			{
				PlotDir = 1;
			}
			else
			{
				PlotDir = 0;
			}
			gUSB.OnWorkCmdPlot(nCurPackNo,PlotDir);
			gWorkType = WT_PLOTTING;
			pParent->SendMessage(USER_DISP_STAT,nCurPackNo,gnPackSum); //显示打印进度
			nCurPackNo++;
		}
		else
		{
			gUSB.OnResetRcvAddr(); //重置接收地址
			Sleep(10);
		}

		if (THREAD_MESSAGE_CANCEL == gMacSet.getThreadMessage())
		{
			gUSB.OnWorkCtrl(WORKCMD_CANCEL);
			gMacSet.setThreadMessage(THREAD_MESSAGE_NONE);
			return ERROR_CANCEL_FILE;
		}

		if (THREAD_MESSAGE_RESUME == gMacSet.getThreadMessage())
		{
			gUSB.OnWorkCtrl(WORKCMD_RESUME);
			gMacSet.setThreadMessage(THREAD_MESSAGE_NONE);
		}
		if (THREAD_MESSAGE_PAUSE == gMacSet.getThreadMessage())
		{
			gUSB.OnWorkCtrl(WORKCMD_PAUSE);
			gMacSet.setThreadMessage(THREAD_MESSAGE_NONE);
		}
	}

	rev = WaitWorkNone(pParent,TRUE);
	if( rev !=0 ) 
		return rev;
	return 0;
}

UINT ThreadWork(LPVOID pParam)
{
	int rev=0;
	CWnd* pParent = (CWnd *) ((ST_THREAD_PARA *)pParam)->m_pWnd;
	CalcPlotPackSum(); //计算喷墨数据的包数

	if( (gMacSet.getWorkStartPause() ) || ( gMacSet.getFirstPageConfirm() ) )
	{
		rev = gUSB.OnWorkCmdStart(gnCncXMax,gnCncYMax,gnPackSum,g_iMacPixelY,1);
	}
	else
	{
		rev = gUSB.OnWorkCmdStart(gnCncXMax,gnCncYMax,gnPackSum,g_iMacPixelY,0);
	}
	gMacSet.setWorkStartPause(FALSE);

	if (rev !=0)
	{
		switch (rev)
		{
		case -1:
			AfxMessageBox("USB Error!");
			break;
			
		case ERROR_XYSIZE:
			if (gDispSet.getLanguage() == 0){
				AfxMessageBox("超出切割范围！请重设原点或检查文件尺寸。");
			}else{
				AfxMessageBox("Out Of Size!");
			}
			break;
			
		case ERROR_NOTREADY:
			AfxMessageBox("Not Ready");
			break;
		}
		pParent->SendMessage(USER_END_WTHREAD,1,0); //删除线程并删除表头
		return 0;
	}

	rev = DoPlot(pParent);
	if (rev != 0 )
	{
		if (ERROR_CANCEL_FILE == rev)
		{
			pParent->SendMessage(USER_END_WTHREAD,2,0); //删除线程并删除全部
		}
		else
		{
			pParent->SendMessage(USER_END_WTHREAD,1,0); //删除线程并删除表头
			gUSB.OnWorkCtrl(WORKCMD_CANCEL);
		}
		return 0;
	}
	rev = DoCut(pParent);
	if (ERROR_CANCEL_FILE == rev)
	{
		pParent->SendMessage(USER_END_WTHREAD,2,0); //删除线程并删除全部
		return 0;
	}
	if (g_ptrCncList.GetSize() == 0)
	{
		gUSB.OnWorkCtrl(WORKCMD_CANCEL);
	}
	else
	{
		gUSB.OnWorkCtrl(WORKCMD_END);
	}
	pParent->SendMessage(USER_END_WTHREAD,1,0); //删除线程并删除表头
	return 0;
}

UINT DoCut(CWnd* pParent)
{
	int rev;
	rev = WaitWorkNone(pParent,FALSE);
	if( rev !=0 ) 
		return rev;

	rev = SendCncData();
	if (rev != 0)
		return rev;

	int nCncSize = g_ptrCncList.GetSize();
	rev = gUSB.OnWorkCmdCut(nCncSize);
	if (rev != 0)
		return rev;
	rev = WaitWorkNone(pParent,FALSE);
	return 0;
}
