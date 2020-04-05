#include "StdAfx.h"
#include "Global.h"

CWinThread* gThreadAutoConnect;
ST_THREAD_PARA gParaAutoConnect;

CWinThread* gThrdWork;
ST_THREAD_PARA gParaWork;

UINT ThreadAutoConnect(LPVOID pParam) //�Զ����ӻ�������ʼ����
{
	CWnd *pParent;
	pParent = (CWnd *) ((ST_THREAD_PARA *)pParam)->m_pWnd;
	static int kk=0;
	while(1)
	{
		if(gMacSet.getQueryEnable()) //�����ѯ
		{
			if (!g_bParaRead)
			{
				ReadMacPara(); //��ʱ��⣬δ��ȡ���ȡһ�β���
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

			if(gMacSet.getJobAutoStart()==TRUE) //�Զ���ʼ����
			{
				if( (NULL == gThrdWork) && (READY == gSysState) )
				{
					pParent->SendMessage(USER_AUTO_START,0,0);
				}
 			}

		}
		if(gMacSet.getJobAutoStart()==TRUE) //�Զ���ʼ����
		{
			pParent->SendMessage(USER_SEARCH_PLT,0,0);
		}
		Sleep(400);
	}		
}

