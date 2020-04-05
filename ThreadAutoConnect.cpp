#include "StdAfx.h"
#include "Global.h"

CWinThread* gThreadAutoConnect;
ST_THREAD_PARA gParaAutoConnect;

CWinThread* gThrdWork;
ST_THREAD_PARA gParaWork;

UINT ThreadAutoConnect(LPVOID pParam) //自动连接机器并开始服务
{
	CWnd *pParent;
	pParent = (CWnd *) ((ST_THREAD_PARA *)pParam)->m_pWnd;
	static int kk=0;
	while(1)
	{
		if(gMacSet.getQueryEnable()) //允许查询
		{
			if (!g_bParaRead)
			{
				ReadMacPara(); //定时检测，未读取则读取一次参数
			}
			if (gUSB.OnGetMacState() != 0 )
			{
				kk++;
				if (kk > 4)
				{
					kk = 0;
					g_bParaRead = FALSE;
				}
			}
			else
			{
				kk = 0;
			}
			pParent->SendMessage(USER_DISP_STAT,0,0);

			if(gMacSet.getJobAutoStart()==TRUE) //自动开始工作
			{
				if( (NULL == gThrdWork) && (READY == gSysState) )
				{
					pParent->SendMessage(USER_AUTO_START,0,0);
				}
 			}

		}
		if(gMacSet.getJobAutoStart()==TRUE) //自动开始工作
		{
			pParent->SendMessage(USER_SEARCH_PLT,0,0);
		}
		Sleep(400);
	}		
}

