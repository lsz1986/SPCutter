#if !defined(AFX_DLGABOUTGM_H__186B9E5A_997D_4E8B_AF09_2C95B4DE2FDC__INCLUDED_)
#define AFX_DLGABOUTGM_H__186B9E5A_997D_4E8B_AF09_2C95B4DE2FDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAboutGm.h : header file
//
#include "HyperLink.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgAboutGm dialog

class CDlgAboutGm : public CDialog
{
// Construction
public:
	CDlgAboutGm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAboutGm)
	enum { IDD = IDDLG_ABOUTGM };
	CHyperLink	m_urlGmWebSite;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAboutGm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAboutGm)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGABOUTGM_H__186B9E5A_997D_4E8B_AF09_2C95B4DE2FDC__INCLUDED_)
