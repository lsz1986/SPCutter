// DlgSetDir.cpp : implementation file
//

#include "stdafx.h"
#include "DlgSetDir.h"
#include "Global.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetDir dialog


CDlgSetDir::CDlgSetDir(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetDir::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetDir)
	m_bAutoDelPlt = FALSE;
	m_bFirstPageConfirm = FALSE;
	m_nPltScale = 1000;
	m_bMoveToLeft = FALSE;
	m_bMoveToBottom = FALSE;
	m_nPltPageLen = 0;
	m_nMaxCurveLen = 0;
	m_nY1000Scale = 1000;
	m_nX1000Scale = 1000;
	m_bFindOutline = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgSetDir::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetDir)
	DDX_Check(pDX, IDCHK_AUTO_DEL_PLT, m_bAutoDelPlt);
	DDX_Check(pDX, IDCHK_AUTO_PAUSE, m_bFirstPageConfirm);
	DDX_Text(pDX, IDCE_PLT_SCALE, m_nPltScale);
	DDV_MinMaxInt(pDX, m_nPltScale, 900, 1100);
	DDX_Check(pDX, IDCHK_IG_BLANK_LEFT, m_bMoveToLeft);
	DDX_Check(pDX, IDCHK_IG_BLANK_BOTTOM, m_bMoveToBottom);
	DDX_Text(pDX, IDCE_PLT_SEC_LEN, m_nPltPageLen);
	DDV_MinMaxUInt(pDX, m_nPltPageLen, 0, 3000);
	DDX_Text(pDX, IDCE_CURVE_LEN, m_nMaxCurveLen);
	DDV_MinMaxUInt(pDX, m_nMaxCurveLen, 1, 8);
	DDX_Text(pDX, IDCE_YSCALE, m_nY1000Scale);
	DDV_MinMaxUInt(pDX, m_nY1000Scale, 100, 10000);
	DDX_Text(pDX, IDCE_XSCALE, m_nX1000Scale);
	DDV_MinMaxUInt(pDX, m_nX1000Scale, 100, 10000);
	DDX_Check(pDX, IDCHK_SEARCHOUTLINE, m_bFindOutline);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetDir, CDialog)
	//{{AFX_MSG_MAP(CDlgSetDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetDir message handlers

void CDlgSetDir::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	gMacSet.setAutoDelPlt(m_bAutoDelPlt);
	gMacSet.setFirstPageConfirm(m_bFirstPageConfirm);
	gMacSet.setPltScale(m_nPltScale);
	gMacSet.setAutoMoveToLeft(m_bMoveToLeft);
	gMacSet.setAutoMoveToBottom(m_bMoveToBottom);
	gMacSet.setPltPageLen(m_nPltPageLen);
	gMacSet.setCurveLen(m_nMaxCurveLen);

	gMacSet.setPltSaveScaleX(m_nX1000Scale);
	gMacSet.setPltSaveScaleY(m_nY1000Scale);
	gMacSet.setFindOutLine(m_bFindOutline);
	CDialog::OnOK();
}

BOOL CDlgSetDir::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_bAutoDelPlt = gMacSet.getAutoDelPlt();
	m_bFirstPageConfirm = gMacSet.getFirstPageConfirm();
	m_nPltScale = gMacSet.getPltScale();
	m_bMoveToLeft = gMacSet.getAutoMoveToLeft();
	m_bMoveToBottom = gMacSet.getAutoMoveToBottom();
	m_nPltPageLen = gMacSet.getPltPageLen();
	m_nMaxCurveLen = gMacSet.getCurveLen();

	m_nX1000Scale = gMacSet.getPltSaveScaleX();
	m_nY1000Scale = gMacSet.getPltSaveScaleY();

	m_bFindOutline = gMacSet.getFindOutLine();
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

