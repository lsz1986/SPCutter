#include "StdAfx.h"
#include "Global.h"
#include "HpglFile.h"
#include "Thread.h"
int gPackSumPlotOnly = 0;

int WaitWorkNone();
int DoWork();
int DoPlot(int PackNo); //喷墨过程
int DoCut(void); //切割过程
void PreparePlotData(int nPlotPackNum);

void PreparePlotData(int nPlotPackNum)
{
	if (gSet.getSpType() == 1)
	{
		IUT308_SetSpDataZero();
		GetOnePackOrgData(nPlotPackNum); //获取一包喷墨数据，存入 g_SpDataOrg 中
		IUT308_ConvertOrgDataToSendData(nPlotPackNum); //将原始数据格式转换成打印数据 存入 g_IUT308_SpDataSend中
		IUT308_ZipSpSendData();
	}
	else
	{
		HP45_SetSpDataZero();
		GetOnePackOrgData(nPlotPackNum); //获取一包喷墨数据，存入 g_SpDataOrg 中
		HP45_ConvertOrgDataToSendData(nPlotPackNum); //将原始数据格式转换成打印数据 存入 g_HP45_SpDataSend中
		HP45_ZipSpSendData();
	}
}

int WaitWorkNone(void)
{
	while(1)
	{
		if (0 == gCommu.OnCmd0(CMD0_GET_STAT)) 
		{
			if (THREAD_MESSAGE_CANCEL == gSet.getThreadMessage())
			{
				Sleep(10);
				gCommu.OnCmd0(CMD0_WCANCEL);
				gSet.setThreadMessage(THREAD_MESSAGE_NONE);
				return ERROR_CANCEL_FILE;
			}
			else if (THREAD_MESSAGE_RESUME == gSet.getThreadMessage())
			{
				gCommu.OnCmd0(CMD0_WRESUME);
				gSet.setThreadMessage(THREAD_MESSAGE_NONE);
			}
			else if (THREAD_MESSAGE_PAUSE == gSet.getThreadMessage())
			{
				gCommu.OnCmd0(CMD0_WPAUSE);
				gSet.setThreadMessage(THREAD_MESSAGE_NONE);
			}
			if ( ( WORKING != (gSysState&0x0f) ) &&( WORK_PAUSE != (gSysState & 0x0f)) )
			{
//				return ERROR_CANCEL_FILE; //20170104
				return ERROR_NONE;
			}
			if(WORKING == gSysState)
			{
				break;
			}
		}
		Sleep(10);
	}
	return 0;
}

int DoPlot(int PackNo) //开始喷墨
{
	int rev;
	u8 PlotDir;

	if (PackNo<gPackSumPlotOnly)
	{
		PreparePlotData(PackNo);
		if ((0 == PackNo % 2)
			|| (FALSE == gSet.getBiDir())) //喷墨方向TO (Y+)
		{
			PlotDir = 0;
		}
		else //喷墨方向TO (Y-)
		{
			PlotDir = 1;
		}

		if(gCommu.WriteBulk( (char*)(&(g_ZippedSpDataSend[0])),g_iSpdataSizeZipped ) == g_iSpdataSizeZipped ) //数据包发送成功
		{
			u8 sbuf[64];
			u8 rbuf[64];
			*((int*)(&sbuf[0])) = PackNo; //包号，
			sbuf[4] = PlotDir;	//喷墨距离

			rev = gCommu.OnCmd1(CMD1_PLOT, 5, sbuf, 1, rbuf);
			if (0 == rev)
			{
				return 0;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	return 0;
}

UINT ThreadWork(LPVOID pParam)
{
	int rev=0;
	u8 rbuf[64];
	u8 sbuf[64];
	CalcPlotPackSum(); //计算喷墨数据的包数
//TODO 判断是否超过幅宽

	*((int*)(&sbuf[0])) = (int)(gWorkingPage.m_nXmax / 40.0*gSet.getPPMMX());//PLT文件X
	*((int*)(&sbuf[4])) = g_iMacPixelY;//BMPY像素

	if( (gSet.getWorkStartPause() ) || ( gSet.getFirstPageConfirm() ) )
	{
		rev = gCommu.OnCmd1(CMD1_NEWF_PAUSE, 8, sbuf, 1, rbuf);
	}
	else
	{
		rev = gCommu.OnCmd1(CMD1_NEWF_RUN, 8, sbuf, 1, rbuf);
	}
	gSet.setWorkStartPause(FALSE);

	if (rev !=0)
	{
		if (gDispSet.getLanguage() == 0){
			AfxMessageBox("发送命令失败,请重试");
		}else{
			AfxMessageBox("Send Command failed,Please retry!");
		}

		g_pMainfrm->SendMessage(USER_END_WTHREAD,1,0); //删除线程并删除表头
		return 0;
	}

 	rev = DoWork();
	if (ERROR_NONE == rev)
	{
//		gCommu.OnCmd0(CMD0_WEND);
		g_pMainfrm->SendMessage(USER_END_WTHREAD, 1, 0); //删除线程并删除表头
	}
	else if (ERROR_CANCEL_FILE == rev)
	{
		gCommu.OnCmd0(CMD0_WCANCEL);
		g_pMainfrm->SendMessage(USER_END_WTHREAD, 2, 0); //删除线程并将第一个文件状态设置为手动
	}
	else
	{
		gCommu.OnCmd0(CMD0_WCANCEL);
		g_pMainfrm->SendMessage(USER_END_WTHREAD, 1, 0); //删除线程并删除表头
	}
	return 0;
}

int DoWork()
{
	int rev;
	int iPackNum; //当前的喷墨包号
	iPackNum = 0;
	while (1)
	{
		rev = WaitWorkNone();
		if (gSet.getParaUpdateFlag())
		{
			WritePlotPara();
			gSet.setParaUpdateFlag(FALSE);
		}
		if (rev != ERROR_NONE)
		{
			return rev;
		}
		if (iPackNum > gPackSumPlotOnly)
		{
			break;
		}

		gPlotPackNo = iPackNum; //更新显示
		rev = DoPlot(iPackNum);
		if (rev != 0)
		{
			return rev;
		}
		iPackNum++;
	}
	if (DoCut() != 0)
	{
		return ERROR_CANCEL_FILE; //待修改
	}
	return ERROR_NONE;
}

int DoCut(void)
{
	int nCncSize;
	int rev;
	u8 sbuf[64];
	u8 rbuf[64];

	nCncSize = g_ptrCncList.GetSize();

	if (SendCncData() == 0)
	{
		*((int*)(&sbuf[0])) = nCncSize;
		rev = gCommu.OnCmd1(CMD1_CUT, 4, sbuf, 1, rbuf);
		if (rev != 0)
			return rev;
		Sleep(1);
	}
	rev = WaitWorkNone();
	return rev;
}
