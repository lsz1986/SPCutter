#if !defined(AFX_MYDLGBAR_H__738B742C_2175_40F0_BDFD_CF7013F9C443__INCLUDED_)
#define AFX_MYDLGBAR_H__738B742C_2175_40F0_BDFD_CF7013F9C443__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDlgBar.h : header file
//

#include "BtnST.h"
/////////////////////////////////////////////////////////////////////////////
// CMyDlgBar dialog

class CMyDlgBar : public CDialogBar
{
// Construction
public:
	CString m_strTempDataDir;
	CMyDlgBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlgBar)
	enum { IDD = IDDLG_BAR };
	CButtonST	m_btnArLeft;
	CButtonST	m_btnArRight;
	CButtonST	m_btnArUp;
	CButtonST	m_btnArDown;
	CButtonST	m_btnWorkStart;
	CButtonST	m_btnWorkPause;
	CButtonST	m_btnWorkCancel;
	CButtonST	m_btnSpClean;
	CButtonST	m_btnZpSet;
	CButtonST	m_btnZpToDef;
	BOOL m_bCutDown;
	BOOL m_bPumpOn;
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
	virtual LRESULT OnInitDialog(UINT wParam,LONG lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnUpdateAr(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIdcbWorkCancel(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIdcbWorkPause(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIdcbWorkStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIdcbSpClean(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIdcbToDefZp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIdcbSetZp(CCmdUI *pCmdUI);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnBnClickedSpclean();
	afx_msg void OnBnClickedSetZp();
	afx_msg void OnBnClickedToDefzp();
	afx_msg void OnBnClickedCutDown();
	afx_msg void OnBnClickedPumpon();
	afx_msg void OnUpdateIdchkCutDown(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIdchkPumpon(CCmdUI *pCmdUI);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLGBAR_H__738B742C_2175_40F0_BDFD_CF7013F9C443__INCLUDED_)
