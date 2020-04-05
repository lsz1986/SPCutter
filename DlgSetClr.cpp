// DlgSetClr.cpp : implementation file
//

#include "stdafx.h"
#include "DlgSetClr.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetClr dialog


CDlgSetClr::CDlgSetClr(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetClr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetClr)
	m_bDisplayDirection = FALSE;
	m_bDisplaySequence = FALSE;
	m_bListDispLeft = FALSE;
	m_nDispSizeX = 1200;
	m_nDispSizeY = 900;
	//}}AFX_DATA_INIT
}


void CDlgSetClr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetClr)
	DDX_Control(pDX, IDCB_CLR_BG, m_btnBG);
	DDX_Control(pDX, IDCB_CLR_FR, m_btnFR);
	DDX_Control(pDX, IDCB_CLR_PEN, m_btnPen);
	DDX_Control(pDX, IDCB_CLR_BLADE, m_btnBlade);
	DDX_Check(pDX, IDCHK_DISPLAY_DIR, m_bDisplayDirection);
	DDX_Check(pDX, IDCHK_DISPLAY_NUM, m_bDisplaySequence);
	DDX_Check(pDX, IDCHK_DISPLIST_LEFT, m_bListDispLeft);
	DDX_Text(pDX, IDCE_DISP_SIZEX, m_nDispSizeX);
	DDV_MinMaxUInt(pDX, m_nDispSizeX, 1200, 4000);
	DDX_Text(pDX, IDCE_DISP_SIZEY, m_nDispSizeY);
	DDV_MinMaxUInt(pDX, m_nDispSizeY, 900, 3000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetClr, CDialog)
	//{{AFX_MSG_MAP(CDlgSetClr)
	ON_BN_CLICKED(IDCB_CLR_BG, OnClrBg)
	ON_BN_CLICKED(IDCB_CLR_FR, OnClrFr)
	ON_BN_CLICKED(IDCB_CLR_PEN, OnClrPen)
	ON_BN_CLICKED(IDCB_CLR_BLADE, OnClrBlade)
	ON_BN_CLICKED(IDCB_CLR_DEFAULT, OnClrDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetClr message handlers

BOOL CDlgSetClr::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnBG.SetActiveBgColor(gDispSet.getClrBG());
	m_btnBG.SetInactiveBgColor(gDispSet.getClrBG());

	m_btnFR.SetActiveBgColor(gDispSet.getClrFR());
	m_btnFR.SetInactiveBgColor(gDispSet.getClrFR());

	m_btnPen.SetActiveBgColor(gDispSet.getClrPen());
	m_btnPen.SetInactiveBgColor(gDispSet.getClrPen());

	m_btnBlade.SetActiveBgColor(gDispSet.getClrCut());
	m_btnBlade.SetInactiveBgColor(gDispSet.getClrCut());

	m_bDisplayDirection = gMacSet.getDisplayStartAndDir();
	m_bDisplaySequence = gMacSet.getDisplaySequence();

	m_bListDispLeft = gMacSet.getListDispLeft();

	m_nDispSizeX = gDispSet.getDispSizeX();
	m_nDispSizeY = gDispSet.getDispSizeY();

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSetClr::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	gDispSet.setClrBG(m_btnBG.GetActiveBgColor());
	gDispSet.setClrFR(m_btnFR.GetActiveBgColor());
	gDispSet.setClrPen(m_btnPen.GetActiveBgColor());
	gDispSet.setClrCut(m_btnBlade.GetActiveBgColor());

	gMacSet.setDisplayStartAndDir(m_bDisplayDirection);
	gMacSet.setDisplaySequence(m_bDisplaySequence);

	gDispSet.setDispSizeX(m_nDispSizeX);
	gDispSet.setDispSizeY(m_nDispSizeY);

	if( gMacSet.getListDispLeft() != m_bListDispLeft )
	{
		gMacSet.setListDispLeft(m_bListDispLeft);
		if (gDispSet.getLanguage() == 0){
			AfxMessageBox("你已改变了列表的显示位置，需要重启程序才能生效");
		}else{
			AfxMessageBox("Restart Application To Change List Display position");
		}
	}
	CDialog::OnOK();
}

void CDlgSetClr::OnClrBg() 
{
	CColorDialog dlg(m_btnBG.GetActiveBgColor());
	if (IDOK == dlg.DoModal())
	{
		m_btnBG.SetActiveBgColor(dlg.GetColor(),TRUE);
		m_btnBG.SetInactiveBgColor(dlg.GetColor(),TRUE);
	}
}

void CDlgSetClr::OnClrFr() 
{
	CColorDialog dlg(m_btnFR.GetActiveBgColor());
	if (IDOK == dlg.DoModal())
	{
		m_btnFR.SetActiveBgColor(dlg.GetColor(),TRUE);
		m_btnFR.SetInactiveBgColor(dlg.GetColor(),TRUE);
	}	
}

void CDlgSetClr::OnClrPen() 
{
	CColorDialog dlg(m_btnPen.GetActiveBgColor());
	if (IDOK == dlg.DoModal())
	{
		m_btnPen.SetActiveBgColor(dlg.GetColor(),TRUE);
		m_btnPen.SetInactiveBgColor(dlg.GetColor(),TRUE);
	}
}

void CDlgSetClr::OnClrBlade() 
{
	CColorDialog dlg(m_btnBlade.GetActiveBgColor());
	if (IDOK == dlg.DoModal())
	{
		m_btnBlade.SetActiveBgColor(dlg.GetColor(),TRUE);
		m_btnBlade.SetInactiveBgColor(dlg.GetColor(),TRUE);
	}	
}

void CDlgSetClr::OnClrDefault() 
{
	m_btnBG.SetActiveBgColor(RGB(0,0,0));
	m_btnBG.SetInactiveBgColor(RGB(0,0,0));
	
	m_btnFR.SetActiveBgColor(RGB(0,255,0));
	m_btnFR.SetInactiveBgColor(RGB(0,255,0));
	
	m_btnPen.SetActiveBgColor(RGB(0,0,255));
	m_btnPen.SetInactiveBgColor(RGB(0,0,255));
	
	m_btnBlade.SetActiveBgColor(RGB(255,0,0));
	m_btnBlade.SetInactiveBgColor(RGB(255,0,0));
	Invalidate(TRUE);
}
