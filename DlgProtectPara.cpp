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
	m_dPPMMX = 104.16;
	m_dPPMMY = 104.16;
	m_nSpAccDistmm = 40;
	m_nMacSizeX = 1200;
	m_nMacSizeY = 900;
	m_nSpdCut = 3;
	m_nSpdMove = 3;
	m_nSecLen = 40;
	m_bJamDetectOn = FALSE;
	m_nCurveSpd = 8;
	//}}AFX_DATA_INIT
}


void CDlgProtectPara::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProtectPara)
	DDX_Text(pDX, IDCEP_PPMM_X, m_dPPMMX);
	DDX_Text(pDX, IDCEP_PPMM_Y, m_dPPMMY);
	DDX_Text(pDX, IDCEP_ACCMM, m_nSpAccDistmm);
	DDV_MinMaxUInt(pDX, m_nSpAccDistmm, 25, 60);
	DDX_Text(pDX, IDCEP_MACSIZE_X, m_nMacSizeX);
	DDV_MinMaxUInt(pDX, m_nCurveSpd, 5, 50);
	DDX_Text(pDX, IDCEP_CURVE_SPD, m_nCurveSpd);
	DDV_MinMaxUInt(pDX, m_nMacSizeX, 500, 4000);
	DDX_Text(pDX, IDCEP_MACSIZE_Y, m_nMacSizeY);
	DDV_MinMaxUInt(pDX, m_nMacSizeY, 500, 3000);
	DDX_Text(pDX, IDCEP_SPD_CUT, m_nSpdCut);
	DDV_MinMaxUInt(pDX, m_nSpdCut, 1, 5);
	DDX_Text(pDX, IDCEP_SPD_MOVE, m_nSpdMove);
	DDV_MinMaxUInt(pDX, m_nSpdMove, 1, 5);
	DDX_Check(pDX, IDCHK_JAMDETEC, m_bJamDetectOn);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDCEP_SEC_LEN, m_nSecLen);
}


BEGIN_MESSAGE_MAP(CDlgProtectPara, CDialog)
	//{{AFX_MSG_MAP(CDlgProtectPara)
	ON_BN_CLICKED(IDCB_CONFIRM, OnConfirm)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCB_CHANGE_RATE, &CDlgProtectPara::OnBnClickedChangeRate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProtectPara message handlers

BOOL CDlgProtectPara::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_nMacSizeX = gSet.getMacSizeX();
	m_nMacSizeY = gSet.getMacSizeY();

	m_nSpAccDistmm = gSet.getSpAccDistmm();
	m_nSpdCut = gSet.getSpdCut();
	m_nSpdMove = gSet.getSpdMove();
	m_bJamDetectOn = gSet.getJamDetect();
	m_nSecLen = gSet.getSecLen();
	m_nCurveSpd = gSet.getCurveSpd();

	m_dPPMMX = gSet.getPPMMX();
	m_dPPMMY = gSet.getPPMMY();
	GetDlgItem(IDCEP_PPMM_X)->EnableWindow(FALSE);
	GetDlgItem(IDCEP_PPMM_Y)->EnableWindow(FALSE);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgProtectPara::OnConfirm() 
{
	UpdateData(TRUE);
	gSet.setMacSizeX(m_nMacSizeX);
	gSet.setMacSizeY(m_nMacSizeY);

	gSet.setSpAccDistmm(m_nSpAccDistmm);
	gSet.setSpdCut(m_nSpdCut);
	gSet.setSpdMove(m_nSpdMove);
	gSet.setJamDetect(m_bJamDetectOn);
	gSet.setSecLen(m_nSecLen);
	gSet.setCurveSpd(m_nCurveSpd);

	gSet.setPPMMX(m_dPPMMX);
	gSet.setPPMMY(m_dPPMMY);
	CDialog::OnOK();
}


void CDlgProtectPara::OnBnClickedChangeRate()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDCEP_PPMM_X)->EnableWindow(TRUE);
	GetDlgItem(IDCEP_PPMM_Y)->EnableWindow(TRUE);
}
