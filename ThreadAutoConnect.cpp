#include "StdAfx.h"
#include "Thread.h"

CWinThread* gThreadAutoConnect;
CWinThread* gThrdWork;
CWnd* g_pMainfrm;

int gCarCurPosX;
int gCarCurPosY;

UINT ThreadAutoConnect(LPVOID pParam) //�Զ����ӻ�������ʼ����
{
	static int kk = 0;
	u8 sbuf[64];
	u8 rbuf[64];
	while (1)
	{
		Sleep(100);
		if (gSet.getAppExitFlag()) //����ر�ǰ�ȹر��߳�
		{
			gThreadAutoConnect = NULL;
			return 0;
		}
		if (gSet.getQueryEnable()) //�����ѯ
		{
			if (FALSE == g_bParaRead)
			{
				ReadMacPara(); //��ʱ��⣬δ��ȡ���ȡһ�β���
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
