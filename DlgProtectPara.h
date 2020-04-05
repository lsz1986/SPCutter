#if !defined(AFX_DLGPROTECTPRAR_H__81A3A5AF_5948_41DA_ABFF_09B0867987A1__INCLUDED_)
#define AFX_DLGPROTECTPRAR_H__81A3A5AF_5948_41DA_ABFF_09B0867987A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProtectPrar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProtectPara dialog

class CDlgProtectPara : public CDialog
{
// Construction
public:
	CDlgProtectPara(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProtectPara)
	enum { IDD = IDDLG_PROTECTPARA };
	CString	m_sPPW;
	double	m_dPPMMX;
	double	m_dPPMMY;
	UINT	m_nSpAccStep;
	UINT	m_nMacSizeX;
	UINT	m_nMacSizeY;
	UINT	m_nSpdCut;
	UINT	m_nSpdMove;
	BOOL	m_bJamDetectOn;
	UINT	m_nSdPercent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProtectPara)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProtectPara)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROTECTPRAR_H__81A3A5AF_5948_41DA_ABFF_09B0867987A1__INCLUDED_)
