#if !defined(AFX_MYDLGBAR_H__738B742C_2175_40F0_BDFD_CF7013F9C443__INCLUDED_)
#define AFX_MYDLGBAR_H__738B742C_2175_40F0_BDFD_CF7013F9C443__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDlgBar.h : header file
//
#include "HyperLink.h"
/////////////////////////////////////////////////////////////////////////////
// CMyDlgBar dialog

class CMyDlgBar : public CDialogBar
{
// Construction
public:
	BOOL DirIsEmpty(CString strDir);
	CString m_strTempDataDir;
	CMyDlgBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlgBar)
	enum { IDD = IDDLG_BAR };
	CHyperLink	m_hyperLinkDataDir;
	BOOL	m_bJobAutoStart;
	BOOL	m_bOnlyPlot;
	BOOL	m_bAutoCleanOn;
	int		m_nYBlankMm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDlgBar)
	afx_msg void OnSetAutoDir();
	virtual LRESULT OnInitDialog(UINT wParam,LONG lParam);
	afx_msg void OnOnlyplot();
	afx_msg void OnAutoWork();
	afx_msg void OnAutoCleansp();
	afx_msg void OnApplyBlankMm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLGBAR_H__738B742C_2175_40F0_BDFD_CF7013F9C443__INCLUDED_)
