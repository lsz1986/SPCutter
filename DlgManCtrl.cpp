// DLgManCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "SpCutter.h"
#include "DLgManCtrl.h"
#include "Global.h"
#include "Thread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgManCtrl dialog
static int USBkeyVal=0;

CDlgManCtrl::CDlgManCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgManCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgManCtrl)
	m_nKPwm = 0;
	m_bCutDown = FALSE;
	m_bPumpOn = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgManCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgManCtrl)
	DDX_Text(pDX, IDCE_K_PWM, m_nKPwm);
	DDV_MinMaxUInt(pDX, m_nKPwm, 0, 90);
	DDX_Check(pDX, IDCHK_CUT_DOWN, m_bCutDown);
	DDX_Check(pDX, IDCHK_PUMPON, m_bPumpOn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgManCtrl, CDialog)
	//{{AFX_MSG_MAP(CDlgManCtrl)
	ON_BN_CLICKED(IDCB_BAK_ORG, OnBtnManOrg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCHK_CUT_DOWN, OnCutDown)
	ON_BN_CLICKED(IDCHK_PUMPON, OnPumpon)
	ON_BN_CLICKED(IDCB_SET_ZP, OnSetZp)
	ON_BN_CLICKED(IDCB_XN, OnXn)
	ON_BN_CLICKED(IDCB_XP, OnXp)
	ON_BN_CLICKED(IDCB_YN, OnYn)
	ON_BN_CLICKED(IDCB_YP, OnYp)
	ON_BN_CLICKED(IDCB_STOP, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgManCtrl message handlers

BOOL CDlgManCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_nKPwm = gMacSet.getPwmKStart();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgManCtrl::OnDestroy() 
{
	CDialog::OnDestroy();
	gUSB.OnSendUsbKeyValue(0);
	Sleep(10);	
	if(m_bCutDown)
	{
		gUSB.OnCutDown(0);
		Sleep(10);
	}
}

void CDlgManCtrl::OnCutDown() 
{
	u8 rev;
	UpdateData();

	if (m_bCutDown)	{
		rev=gUSB.OnCutDown(m_nKPwm);
	}else{
		rev=gUSB.OnCutDown(0);
	}
	if (rev != 0)
	{
		if (gDispSet.getLanguage() == 0) {
			AfxMessageBox("∑¢ÀÕ√¸¡Ó ß∞‹");
		} else {
			AfxMessageBox("Send Command Failed");
		}
	}
}

void CDlgManCtrl::OnPumpon() 
{
	u8 rev;
	UpdateData();
	rev = gUSB.OnPumpCtrl(m_bPumpOn); //πÿ±’∆¯±√
	if (rev != 0)
	{
		if (gDispSet.getLanguage() == 0) {
			AfxMessageBox("∑¢ÀÕ√¸¡Ó ß∞‹");
		}else {
			AfxMessageBox("Send Command Failed");
		}
	}
}

void CDlgManCtrl::OnBtnManOrg() 
{
	u8 rev = gUSB.OnToDefZp();
	if (rev != 0)
	{
		if (gDispSet.getLanguage() == 0){
			AfxMessageBox("∑¢ÀÕ√¸¡Ó ß∞‹");
		}else{
			AfxMessageBox("Send Command Failed");
		}
	}
}

void CDlgManCtrl::OnSetZp() 
{
	if (gThrdWork != NULL)
	{
		if (gDispSet.getLanguage() == 0){
			AfxMessageBox("∑¢ÀÕ√¸¡Ó ß∞‹");
		}else{
			AfxMessageBox("Send Command Failed");
		}
		return;
	}
	u8 rev = gUSB.OnSetZp();
	if (rev != 0)
	{
		if (gDispSet.getLanguage() == 0){
			AfxMessageBox("∑¢ÀÕ√¸¡Ó ß∞‹");
		}else{
			AfxMessageBox("Send Command Failed");
		}
	}
	else
	{
		if (gDispSet.getLanguage() == 0){
			AfxMessageBox("…Ë∂®‘≠µ„≥…π¶");
		}else{
			AfxMessageBox("Failed To Set Start Point");
		}
		CDialog::OnOK();
	}
}

#define Key_Left		0xEE
#define Key_Right		0xFA
#define Key_Down		0xBE
#define Key_Up			0x01
// 
void CDlgManCtrl::OnXn() 
{
	if (USBkeyVal == 0)
	{
		USBkeyVal = Key_Left;
		gUSB.OnSendUsbKeyValue(USBkeyVal);
	}
	else
	{
		USBkeyVal = 0;
		gUSB.OnSendUsbKeyValue(USBkeyVal);
	}
}

void CDlgManCtrl::OnXp() 
{
	if (USBkeyVal == 0)
	{
		USBkeyVal = Key_Right;
		gUSB.OnSendUsbKeyValue(USBkeyVal);
	}
	else
	{
		USBkeyVal = 0;
		gUSB.OnSendUsbKeyValue(USBkeyVal);
	}
}

void CDlgManCtrl::OnYn() 
{
	if (USBkeyVal == 0)
	{
		USBkeyVal = Key_Down;
		gUSB.OnSendUsbKeyValue(USBkeyVal);
	}
	else
	{
		USBkeyVal = 0;
		gUSB.OnSendUsbKeyValue(USBkeyVal);
	}
}

void CDlgManCtrl::OnYp() 
{
	if (USBkeyVal == 0)
	{
		USBkeyVal = Key_Up;
		gUSB.OnSendUsbKeyValue(USBkeyVal);
	}
	else
	{
		USBkeyVal = 0;
		gUSB.OnSendUsbKeyValue(USBkeyVal);
	}
}

void CDlgManCtrl::OnStop() 
{
	USBkeyVal = 0;
	gUSB.OnSendUsbKeyValue(USBkeyVal);
}
