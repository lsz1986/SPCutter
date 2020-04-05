// MyDlgBar.cpp : implementation file
//

#include "stdafx.h"
#include "spcutter.h"
#include "MyDlgBar.h"
#include "Global.h"
#include "Thread.h"
#define TIMER_ID_REFRESH (10)

int gPlotPackNo;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBar dialog


CMyDlgBar::CMyDlgBar(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CMyDlgBar)
	//}}AFX_DATA_INIT
}


void CMyDlgBar::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CMyDlgBar)
	DDX_Control(pDX, IDCB_AR_LEFT, m_btnArLeft);
	DDX_Control(pDX, IDCB_AR_RIGHT, m_btnArRight);
	DDX_Control(pDX, IDCB_AR_UP, m_btnArUp);
	DDX_Control(pDX, IDCB_AR_DOWN, m_btnArDown);
	DDX_Control(pDX, IDCB_WORK_START, m_btnWorkStart);
	DDX_Control(pDX, IDCB_WORK_PAUSE, m_btnWorkPause);
	DDX_Control(pDX, IDCB_WORK_CANCEL, m_btnWorkCancel);
	DDX_Control(pDX, IDCB_SPCLEAN, m_btnSpClean);
	DDX_Control(pDX, IDCB_SET_ZP, m_btnZpSet);
	DDX_Control(pDX, IDCB_TO_DEFZP, m_btnZpToDef);
	DDX_Check(pDX, IDCHK_CUT_DOWN, m_bCutDown);
	DDX_Check(pDX, IDCHK_PUMPON, m_bPumpOn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlgBar, CDialogBar)
	//{{AFX_MSG_MAP(CMyDlgBar)
	ON_MESSAGE(WM_INITDIALOG,OnInitDialog)
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(IDCB_AR_DOWN, &CMyDlgBar::OnUpdateAr)
	ON_UPDATE_COMMAND_UI(IDCB_AR_LEFT, &CMyDlgBar::OnUpdateAr)
	ON_UPDATE_COMMAND_UI(IDCB_AR_RIGHT, &CMyDlgBar::OnUpdateAr)
	ON_UPDATE_COMMAND_UI(IDCB_AR_UP, &CMyDlgBar::OnUpdateAr)
	ON_UPDATE_COMMAND_UI(IDCB_TO_DEFZP, &CMyDlgBar::OnUpdateIdcbToDefZp)
	ON_UPDATE_COMMAND_UI(IDCB_WORK_CANCEL, &CMyDlgBar::OnUpdateIdcbWorkCancel)
	ON_UPDATE_COMMAND_UI(IDCB_WORK_PAUSE, &CMyDlgBar::OnUpdateIdcbWorkPause)
	ON_UPDATE_COMMAND_UI(IDCB_WORK_START, &CMyDlgBar::OnUpdateIdcbWorkStart)
	ON_UPDATE_COMMAND_UI(IDCB_SPCLEAN, &CMyDlgBar::OnUpdateIdcbSpClean)
	ON_UPDATE_COMMAND_UI(IDCB_SET_ZP, &CMyDlgBar::OnUpdateIdcbSetZp)
	ON_BN_CLICKED(IDCB_SPCLEAN, &CMyDlgBar::OnBnClickedSpclean)
	ON_BN_CLICKED(IDCB_SET_ZP, &CMyDlgBar::OnBnClickedSetZp)
	ON_BN_CLICKED(IDCB_TO_DEFZP, &CMyDlgBar::OnBnClickedToDefzp)
	ON_BN_CLICKED(IDCHK_CUT_DOWN, &CMyDlgBar::OnBnClickedCutDown)
	ON_BN_CLICKED(IDCHK_PUMPON, &CMyDlgBar::OnBnClickedPumpon)
	ON_UPDATE_COMMAND_UI(IDCHK_CUT_DOWN, &CMyDlgBar::OnUpdateIdchkCutDown)
	ON_UPDATE_COMMAND_UI(IDCHK_PUMPON, &CMyDlgBar::OnUpdateIdchkPumpon)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBar message handlers


LRESULT CMyDlgBar::OnInitDialog(UINT wParam,LONG lParam) 
{
	short	shBtnColor = 30;
	BOOL bRet = HandleInitDialog(wParam,lParam);
	if (!UpdateData(FALSE))
	{
		TRACE("InitCDataStatus Failed！");
	}
	m_btnArLeft.SetIcon(IDI_AR_LEFT);
	m_btnArLeft.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnArLeft.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

	m_btnArRight.SetIcon(IDI_AR_RIGHT);
	m_btnArRight.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnArRight.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

	m_btnArUp.SetIcon(IDI_AR_UP);
	m_btnArUp.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnArUp.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

	m_btnArDown.SetIcon(IDI_AR_DOWN);
	m_btnArDown.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnArDown.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

	m_btnWorkStart.SetIcon(IDI_WSTART);
	m_btnWorkStart.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnWorkStart.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

	m_btnWorkPause.SetIcon(IDI_WPAUSE);
	m_btnWorkPause.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnWorkPause.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

	m_btnWorkCancel.SetIcon(IDI_WCANCEL);
	m_btnWorkCancel.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnWorkCancel.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

	m_btnSpClean.SetIcon(IDI_WSPCLEAN);
	m_btnSpClean.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnSpClean.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

	m_btnZpSet.SetIcon(IDI_ZP_SET);
	m_btnZpSet.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnZpSet.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

	m_btnZpToDef.SetIcon(IDI_ZP_TO_DEF);
	m_btnZpToDef.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	m_btnZpToDef.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	
	m_bCutDown = FALSE;
	m_bPumpOn = FALSE;

	SetTimer(TIMER_ID_REFRESH, 300, NULL);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyDlgBar::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString strText;
	static int kkk = 0;
	if (g_bParaRead)
	{
		switch (gSysState & 0x0f)
		{
		case SYS_INIT:
			strText.Format("Init...");
			break;

		case SEEK_ZP:
			if (gDispSet.getLanguage() == 0)
			{
				strText.Format("正在寻找原点...");
			}
			else
			{
				strText.Format("Seek ZP...");
			}
			break;

		case READY:
			if (gDispSet.getLanguage() == 0)
			{
				strText.Format("准备就绪 X%.1fmm Y%.1fmm", (gCarCurPosX / gSet.getPPMMX()), (gCarCurPosY / gSet.getPPMMY()));
			}
			else
			{
				strText.Format("READY X%.1fmm Y%.1fmm", (gCarCurPosX / gSet.getPPMMX()), (gCarCurPosY / gSet.getPPMMY()));
			}
			break;

		case PRT_TEST:
			if (gDispSet.getLanguage() == 0)
			{
				strText.Format(_T("清洗喷头..."));
			}
			else
			{
				strText.Format(_T("Plot Test..."));
			}
			break;

		case PROCESSING:
			if (gDispSet.getLanguage() == 0)
			{
				strText.Format(_T("处理中..."));
			}
			else
			{
				strText.Format(_T("Processing..."));
			}
			break;

		case WORKING:
			if( (gSysState & 0xf0) == WT_NONE)
			{
				if(kkk++ < 5)
				break;
				if (gDispSet.getLanguage() == 0)
				{
					strText.Format(_T("等待数据..."));
				}
				else
				{
					strText.Format(_T("等待数据..."));
				}
				break;
			}
			kkk = 0;
			switch(gSysState & 0xf0)
			{
			case WT_PLOTTING:
				if (gDispSet.getLanguage() == 0)
				{
					strText.Format(_T("绘图中...%d/%d"), gPlotPackNo,gPackSumPlotOnly);
				}
				else
				{
					strText.Format(_T("Plotting..."));
				}
				break;
			case WT_CUTTING:
				if (gDispSet.getLanguage() == 0)
				{
					strText.Format(_T("切割中..."));
				}
				else
				{
					strText.Format(_T("Plotting..."));
				}
				break;
			default:
				break;
			}
			break;

		case WORK_PAUSE:
 			if (gDispSet.getLanguage() == 0)
 			{
 				strText.Format(_T("暂停中.."));
 			}
 			else
 			{
 				strText.Format(_T("Paused.."));
 			}
			break;

		case ERROR_SRAM:
			if (gDispSet.getLanguage() == 0)
			{
				strText.Format(_T("内存错误..."));
			}
			else
			{
				strText.Format(_T("MEM ERROR..."));
			}
			break;

		default:
			strText.Format(_T("未连接..."));
			break;
		}
	}
	else
	{
		if (gDispSet.getLanguage() == 0)
		{
			strText.Format("未连接...");
		}
		else
		{
			strText.Format("Disconnected...");
		}
	}
	GetDlgItem(ID_TXT_MAC_STA)->SetWindowText(strText);
	CDialogBar::OnTimer(nIDEvent);
}


BOOL CMyDlgBar::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (9999 == message)
	{
		switch (wParam)
		{
		case IDCB_AR_UP:
			if (lParam)
			{
				gCommu.OnCmd0(CMD0_DIR_UP);
			}
			else
			{
				gCommu.OnCmd0(CMD0_DIR_NONE);
			}
			break;

		case IDCB_AR_DOWN:
			if (lParam)
			{
				gCommu.OnCmd0(CMD0_DIR_DOWN);
			}
			else
			{
				gCommu.OnCmd0(CMD0_DIR_NONE);
			}
			break;

		case IDCB_AR_LEFT:
			if (lParam)
			{
				gCommu.OnCmd0(CMD0_DIR_LEFT);
			}
			else
			{
				gCommu.OnCmd0(CMD0_DIR_NONE);
			}
			break;

		case IDCB_AR_RIGHT:
			if (lParam)
			{
				gCommu.OnCmd0(CMD0_DIR_RIGHT);
			}
			else
			{
				gCommu.OnCmd0(CMD0_DIR_NONE);
			}
			break;
		}
	}
	return CDialogBar::OnWndMsg(message, wParam, lParam, pResult);
}



void CMyDlgBar::OnUpdateAr(CCmdUI *pCmdUI)
{
	if (((gSysState & 0x0f) == READY) || ((gSysState & 0x0f) == WORK_PAUSE))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMyDlgBar::OnUpdateIdcbWorkStart(CCmdUI *pCmdUI)
{
	if ((READY == (gSysState & 0x0f)) || (WORK_PAUSE == (gSysState & 0x0f)))
	{
		pCmdUI->Enable(TRUE);
		return;
	}
	pCmdUI->Enable(FALSE);
	return;
}

void CMyDlgBar::OnUpdateIdcbWorkPause(CCmdUI *pCmdUI)
{
	if (WORKING == (gSysState & 0x0f))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMyDlgBar::OnUpdateIdcbWorkCancel(CCmdUI *pCmdUI)
{
	if ((gThrdWork != NULL)
		|| ((gSysState & 0x0f) == WORK_PAUSE)
		|| ((gSysState & 0x0f) == WORKING)
		)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMyDlgBar::OnUpdateIdcbSpClean(CCmdUI *pCmdUI)
{
	if ((gSysState & 0x0f) == READY)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMyDlgBar::OnUpdateIdcbSetZp(CCmdUI *pCmdUI)
{
	if ((gSysState & 0x0f) == READY)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMyDlgBar::OnUpdateIdcbToDefZp(CCmdUI *pCmdUI)
{
	if ((gSysState & 0x0f) == READY)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}


void CMyDlgBar::OnUpdateIdchkCutDown(CCmdUI *pCmdUI)
{
	if ( ((gSysState & 0x0f) == READY) || ((gSysState & 0x0f) == WORK_PAUSE) )
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}


void CMyDlgBar::OnUpdateIdchkPumpon(CCmdUI *pCmdUI)
{
	if (((gSysState & 0x0f) == READY) || ((gSysState & 0x0f) == WORK_PAUSE))
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}


void CMyDlgBar::OnBnClickedSpclean()
{
	gSet.setQueryEnable(FALSE);
	gCommu.OnCmd0(CMD0_SPCLEAN);
	gSet.setQueryEnable(TRUE);
}

void CMyDlgBar::OnBnClickedSetZp()
{
	gSet.setQueryEnable(FALSE);
	if (0 == gCommu.OnCmd0(CMD0_ZP_SET))
	{
		if (gDispSet.getLanguage() == 0)
		{
			AfxMessageBox("设置起点成功");
		}
		else
		{
			AfxMessageBox("Set Start Point OK");
		}
	}
	else
	{
		if (gDispSet.getLanguage() == 0)
		{
			AfxMessageBox("设置起点失败");
		}
		else
		{
			AfxMessageBox("Command Failed");
		}
	}
	gSet.setQueryEnable(TRUE);
}


void CMyDlgBar::OnBnClickedToDefzp()
{
	gSet.setQueryEnable(FALSE);
	gCommu.OnCmd0(CMD0_ZP_TODEF);
	gSet.setQueryEnable(TRUE);
}


void CMyDlgBar::OnBnClickedCutDown()
{
	UpdateData();
	gSet.setQueryEnable(FALSE);
	if (m_bCutDown) {
		gCommu.OnCmd0(CMD0_CUT_DOWN);
	}else{
		gCommu.OnCmd0(CMD0_CUT_UP);
	}
	gSet.setQueryEnable(TRUE);
}


void CMyDlgBar::OnBnClickedPumpon()
{
	UpdateData();
	gSet.setQueryEnable(FALSE);
	if (m_bPumpOn) {
		gCommu.OnCmd0(CMD0_PUMP_ON);
	}
	else {
		gCommu.OnCmd0(CMD0_PUMP_OFF);
	}
	gSet.setQueryEnable(TRUE);
}

