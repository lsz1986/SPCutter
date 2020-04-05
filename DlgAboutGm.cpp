// DlgAboutGm.cpp : implementation file
//

#include "stdafx.h"
#include "spcutter.h"
#include "DlgAboutGm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAboutGm dialog


CDlgAboutGm::CDlgAboutGm(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAboutGm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAboutGm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAboutGm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAboutGm)
	DDX_Control(pDX, IDC_WEBSITE, m_urlGmWebSite);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAboutGm, CDialog)
	//{{AFX_MSG_MAP(CDlgAboutGm)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAboutGm message handlers
