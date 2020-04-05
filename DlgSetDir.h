#if !defined(AFX_DLGSETDIR_H__F1A8D3E4_F848_4C71_96CE_3048A75C199B__INCLUDED_)
#define AFX_DLGSETDIR_H__F1A8D3E4_F848_4C71_96CE_3048A75C199B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetDir.h : header file
//
#include "SpCutter.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSetDir dialog

class CDlgSetDir : public CDialog
{
// Construction
public:
	CDlgSetDir(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetDir)
	enum { IDD = IDDLG_SET_SOFT };
	BOOL	m_bAutoDelPlt;
	BOOL	m_bFirstPageConfirm;
	int		m_nPltScale;
	BOOL	m_bMoveToLeft;
	BOOL	m_bMoveToBottom;
	UINT	m_nPltPageLen;
	UINT	m_nY1000Scale;
	UINT	m_nX1000Scale;
	BOOL	m_bFindOutline;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetDir)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetDir)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETDIR_H__F1A8D3E4_F848_4C71_96CE_3048A75C199B__INCLUDED_)
