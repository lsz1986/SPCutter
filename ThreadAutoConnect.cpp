#include "StdAfx.h"
#include "Thread.h"

CWinThread* gThreadAutoConnect;
CWinThread* gThrdWork;
CWnd* g_pMainfrm;

int gCarCurPosX;
int gCarCurPosY;

UINT ThreadAutoConnect(LPVOID pParam) //自动连接机器并开始服务
{
	static int kk = 0;
	u8 sbuf[64];
	u8 rbuf[64];
	while (1)
	{
		Sleep(100);
		if (gSet.getAppExitFlag()) //程序关闭前先关闭线程
		{
			gThreadAutoConnect = NULL;
			return 0;
		}
		if (gSet.getQueryEnable()) //允许查询
		{
			if (FALSE == g_bParaRead)
			{
				ReadMacPara(); //定时检测，未读取则读取一次参数
				continue;
			}
			if (gCommu.OnCmd0(CMD0_GET_STAT) != 0)
			{
				kk++;
				if (kk >= 3)
				{
					kk = 0;
					g_bParaRead = FALSE;
					gSysState = 0xff;
				}
			}
			else
			{
				kk = 0;
			}
			if ((NULL == gThrdWork) && (READY == (gSysState & 0x0f)))
			{
				g_pMainfrm->SendMessage(USER_AUTO_START, 0, 0);
			}
		}

		g_pMainfrm->SendMessage(USER_SEARCH_PLT, 0, 0);

		Sleep(100);
		if ((gSysState & 0x0f) == READY)
		{
			sbuf[0] = 8;
			gCommu.OnCmd1(CMD1_GET_CAR_POS, 1, sbuf, 8, rbuf);
			gCarCurPosX = *(int*)(&rbuf[0]);
			gCarCurPosY = *(int*)(&rbuf[4]);
			Sleep(10);
		}
	}
}
