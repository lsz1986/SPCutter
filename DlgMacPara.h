#if !defined(AFX_DLGSETMAC_H__7A4E0D5B_57F9_4DC9_8607_9D33705B4942__INCLUDED_)
#define AFX_DLGSETMAC_H__7A4E0D5B_57F9_4DC9_8607_9D33705B4942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMacPara.h : header file
//
#include "Global.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgMacPara dialog

class CDlgMacPara : public CDialog
{
// Construction
public:
	void OnRestorePara(CString ParaFileName);
	void OnUpdateParaToCtrl();
	CDlgMacPara(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMacPara)
	enum { IDD = IDDLG_SET_MAC };
	CComboBox	m_ComboSpType;
	CComboBox	m_ctrlComboEndPos;
	BOOL	m_bSp1;
	BOOL	m_bSp2;
	int		m_nLineWidth;
	int 	m_nJobEndHeadPos;
	int		m_nSpType;
	int		m_nKPDistX;
	int		m_nKPDistY;
	int		m_n10000X;
	int		m_n10000Y;
	int		m_nSpEx;
	int		m_nSp12EY;
	int		m_nSpDDy;
	int		m_nKVolt_Start;
	int		m_nKVolt_Work;
	int		m_iAngleAdjust;
	int		m_nAutoCutLen;
	UINT	m_nOverCutLen;
	int		m_nJobEndPosXmm;
	int		m_nJobEndPosYmm;
	UINT	m_nSp1LrDot;
	UINT	m_nSp2LrDot;
	BOOL	m_bBiDir;
	UINT	m_nLedLan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMacPara)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMacPara)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnProtectPara();
	afx_msg void OnParaSave();
	afx_msg void OnParaRestore();
	afx_msg void OnParaDefault();
	afx_msg void On1209();
	afx_msg void On1509();
	afx_msg void On1510();
	afx_msg void On1512();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETMAC_H__7A4E0D5B_57F9_4DC9_8607_9D33705B4942__INCLUDED_)
