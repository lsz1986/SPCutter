#if !defined(AFX_DLGSETCLR_H__2ED3F142_3572_42B7_B200_E476F5954C72__INCLUDED_)
#define AFX_DLGSETCLR_H__2ED3F142_3572_42B7_B200_E476F5954C72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetClr.h : header file
//
#include "ButtonClr.h"
#include "SpCutter.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSetClr dialog

class CDlgSetClr : public CDialog
{
// Construction
public:
	CDlgSetClr(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetClr)
	enum { IDD = IDDLG_DISP };
	CButtonClr	m_btnBG;
	CButtonClr	m_btnFR;
	CButtonClr	m_btnPen;
	CButtonClr	m_btnBlade;
	BOOL	m_bDisplayDirection;
	BOOL	m_bDisplaySequence;
	BOOL	m_bListDispLeft;
	UINT	m_nDispSizeX;
	UINT	m_nDispSizeY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetClr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetClr)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClrBg();
	afx_msg void OnClrFr();
	afx_msg void OnClrPen();
	afx_msg void OnClrBlade();
	afx_msg void OnClrDefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETCLR_H__2ED3F142_3572_42B7_B200_E476F5954C72__INCLUDED_)
