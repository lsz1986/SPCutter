// DlgProtectPrar.cpp : implementation file
//

#include "stdafx.h"
#include "SpCutter.h"
#include "DlgProtectPara.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProtectPara dialog


CDlgProtectPara::CDlgProtectPara(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProtectPara::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProtectPara)
	m_sPPW = _T("");
	m_dPPMMX = 104.16;
	m_dPPMMY = 104.16;
	m_nSpAccStep = 4000;
	m_nMacSizeX = 1200;
	m_nMacSizeY = 900;
	m_nSpdCut = 3;
	m_nSpdMove = 3;
	m_bJamDetectOn = FALSE;
	m_nSdPercent = 0;
	//}}AFX_DATA_INIT
}


void CDlgProtectPara::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProtectPara)
	DDX_Text(pDX, IDCEP_PW, m_sPPW);
	DDX_Text(pDX, IDCEP_PPMM_X, m_dPPMMX);
	DDX_Text(pDX, IDCEP_PPMM_Y, m_dPPMMY);
	DDX_Text(pDX, IDCEP_ACCSTEP, m_nSpAccStep);
	DDV_MinMaxUInt(pDX, m_nSpAccStep, 2500, 6000);
	DDX_Text(pDX, IDCEP_MACSIZE_X, m_nMacSizeX);
	DDV_MinMaxUInt(pDX, m_nMacSizeX, 1200, 4000);
	DDX_Text(pDX, IDCEP_MACSIZE_Y, m_nMacSizeY);
	DDV_MinMaxUInt(pDX, m_nMacSizeY, 900, 3000);
	DDX_Text(pDX, IDCEP_SPD_CUT, m_nSpdCut);
	DDV_MinMaxUInt(pDX, m_nSpdCut, 1, 5);
	DDX_Text(pDX, IDCEP_SPD_MOVE, m_nSpdMove);
	DDV_MinMaxUInt(pDX, m_nSpdMove, 1, 5);
	DDX_Check(pDX, IDCHK_JAMDETEC, m_bJamDetectOn);
	DDX_Text(pDX, IDCEP_SD_PERCENT, m_nSdPercent);
	DDV_MinMaxUInt(pDX, m_nSdPercent, 0, 4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProtectPara, CDialog)
	//{{AFX_MSG_MAP(CDlgProtectPara)
	ON_BN_CLICKED(IDCB_CONFIRM, OnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProtectPara message handlers

BOOL CDlgProtectPara::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_PTXT2)->ShowWindow(FALSE);
	GetDlgItem(IDC_PTXT3)->ShowWindow(FALSE);
	GetDlgItem(IDC_PTXT4)->ShowWindow(FALSE);
	GetDlgItem(IDC_PTXT5)->ShowWindow(FALSE);
	GetDlgItem(IDC_PTXT6)->ShowWindow(FALSE);
	GetDlgItem(IDC_PTXT7)->ShowWindow(FALSE);
	GetDlgItem(IDC_PTXT8)->ShowWindow(FALSE);
	GetDlgItem(IDC_PTXT9)->ShowWindow(FALSE);

	GetDlgItem(IDCEP_PPMM_X)->ShowWindow(FALSE);
	GetDlgItem(IDCEP_PPMM_Y)->ShowWindow(FALSE);
	GetDlgItem(IDCEP_MACSIZE_X)->ShowWindow(FALSE);
	GetDlgItem(IDCEP_MACSIZE_Y)->ShowWindow(FALSE);
	GetDlgItem(IDCEP_ACCSTEP)->ShowWindow(FALSE);
	GetDlgItem(IDCEP_SPD_CUT)->ShowWindow(FALSE);
	GetDlgItem(IDCEP_SPD_MOVE)->ShowWindow(FALSE);
	GetDlgItem(IDCEP_SD_PERCENT)->ShowWindow(FALSE);
	GetDlgItem(IDCHK_JAMDETEC)->ShowWindow(FALSE);

	GetDlgItem(IDCB_CONFIRM)->ShowWindow(FALSE);
	GetDlgItem(IDCANCEL)->ShowWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgProtectPara::OnOK() 
{
	UpdateData(TRUE);

	if(m_sPPW == _T("gm"))
	{
		GetDlgItem(IDC_PTXT1)->ShowWindow(FALSE);
		GetDlgItem(IDCEP_PW)->ShowWindow(FALSE);
		GetDlgItem(IDOK)->ShowWindow(FALSE);
		
		GetDlgItem(IDC_PTXT4)->ShowWindow(TRUE);
		GetDlgItem(IDC_PTXT5)->ShowWindow(TRUE);
		GetDlgItem(IDC_PTXT6)->ShowWindow(TRUE);
		GetDlgItem(IDC_PTXT7)->ShowWindow(TRUE);
		GetDlgItem(IDC_PTXT8)->ShowWindow(TRUE);
		GetDlgItem(IDC_PTXT9)->ShowWindow(TRUE);
		
		GetDlgItem(IDCEP_MACSIZE_X)->ShowWindow(TRUE);
		GetDlgItem(IDCEP_MACSIZE_Y)->ShowWindow(TRUE);
		GetDlgItem(IDCEP_ACCSTEP)->ShowWindow(TRUE);
		GetDlgItem(IDCEP_SPD_CUT)->ShowWindow(TRUE);
		GetDlgItem(IDCEP_SPD_MOVE)->ShowWindow(TRUE);
		GetDlgItem(IDCEP_SD_PERCENT)->ShowWindow(TRUE);
		GetDlgItem(IDCHK_JAMDETEC)->ShowWindow(TRUE);

		GetDlgItem(IDCB_CONFIRM)->ShowWindow(TRUE);
		GetDlgItem(IDCANCEL)->ShowWindow(TRUE);	

		m_dPPMMX = gMacSet.getPPMMX();
		m_dPPMMY = gMacSet.getPPMMY();

		m_nMacSizeX = gMacSet.getMacSizeX();
		m_nMacSizeY = gMacSet.getMacSizeY();

		m_nSpAccStep = gMacSet.getSpAccStep();
		m_nSpdCut = gMacSet.getSpdCut();
		m_nSpdMove = gMacSet.getSpdMove();
		m_bJamDetectOn = gMacSet.getJamDetect();
		m_nSdPercent = gMacSet.getSpdDownType();
		UpdateData(FALSE);
	}else if (m_sPPW == _T("gmtest"))
	{
		GetDlgItem(IDC_PTXT1)->ShowWindow(FALSE);
		GetDlgItem(IDCEP_PW)->ShowWindow(FALSE);
		GetDlgItem(IDOK)->ShowWindow(FALSE);
		
		GetDlgItem(IDC_PTXT2)->ShowWindow(TRUE);
		GetDlgItem(IDC_PTXT3)->ShowWindow(TRUE);
		GetDlgItem(IDC_PTXT4)->ShowWindow(TRUE);
		GetDlgItem(IDC_PTXT5)->ShowWindow(TRUE);
		GetDlgItem(IDC_PTXT6)->ShowWindow(TRUE);
		GetDlgItem(IDC_PTXT7)->ShowWindow(TRUE);
		GetDlgItem(IDC_PTXT8)->ShowWindow(TRUE);
		GetDlgItem(IDC_PTXT9)->ShowWindow(TRUE);
		
		GetDlgItem(IDCEP_PPMM_X)->ShowWindow(TRUE);
		GetDlgItem(IDCEP_PPMM_Y)->ShowWindow(TRUE);
		GetDlgItem(IDCEP_MACSIZE_X)->ShowWindow(TRUE);
		GetDlgItem(IDCEP_MACSIZE_Y)->ShowWindow(TRUE);
		GetDlgItem(IDCEP_ACCSTEP)->ShowWindow(TRUE);
		GetDlgItem(IDCEP_SPD_CUT)->ShowWindow(TRUE);
		GetDlgItem(IDCEP_SPD_MOVE)->ShowWindow(TRUE);
		GetDlgItem(IDCEP_SD_PERCENT)->ShowWindow(TRUE);
		GetDlgItem(IDCHK_JAMDETEC)->ShowWindow(TRUE);

		GetDlgItem(IDCB_CONFIRM)->ShowWindow(TRUE);
		GetDlgItem(IDCANCEL)->ShowWindow(TRUE);	
		
		m_dPPMMX = gMacSet.getPPMMX();
		m_dPPMMY = gMacSet.getPPMMY();
		
		m_nMacSizeX = gMacSet.getMacSizeX();
		m_nMacSizeY = gMacSet.getMacSizeY();
		
		m_nSpAccStep = gMacSet.getSpAccStep();
		m_nSpdCut = gMacSet.getSpdCut();
		m_nSpdMove = gMacSet.getSpdMove();
		m_bJamDetectOn = gMacSet.getJamDetect();
		m_nSdPercent = gMacSet.getSpdDownType();
		UpdateData(FALSE);
	}
}

void CDlgProtectPara::OnConfirm() 
{
	UpdateData(TRUE);
	gMacSet.setPPMMX(m_dPPMMX);
	gMacSet.setPPMMY(m_dPPMMY);

	gMacSet.setMacSizeX(m_nMacSizeX);
	gMacSet.setMacSizeY(m_nMacSizeY);

	gMacSet.setSpAccStep(m_nSpAccStep);
	gMacSet.setSpdCut(m_nSpdCut);
	gMacSet.setSpdMove(m_nSpdMove);
	gMacSet.setJamDetect(m_bJamDetectOn);
	gMacSet.setSpdDownType(m_nSdPercent);

	CDialog::OnOK();
}
