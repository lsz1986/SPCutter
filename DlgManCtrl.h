#if !defined(AFX_DLGMANCTRL_H__91C7792C_FAC8_41E9_A991_DE6DBB1229BC__INCLUDED_)
#define AFX_DLGMANCTRL_H__91C7792C_FAC8_41E9_A991_DE6DBB1229BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLgManCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgManCtrl dialog

class CDlgManCtrl : public CDialog
{
// Construction
public:
	CDlgManCtrl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgManCtrl)
	enum { IDD = IDDLG_MAN_CTRL };
	UINT	m_nKPwm;
	BOOL	m_bCutDown;
	BOOL	m_bPumpOn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgManCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgManCtrl)
	afx_msg void OnBtnManOrg();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnCutDown();
	afx_msg void OnPumpon();
	afx_msg void OnSetZp();
	afx_msg void OnXn();
	afx_msg void OnXp();
	afx_msg void OnYn();
	afx_msg void OnYp();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMANCTRL_H__91C7792C_FAC8_41E9_A991_DE6DBB1229BC__INCLUDED_)
