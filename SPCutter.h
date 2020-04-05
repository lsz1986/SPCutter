// CutPlotter.h : main header file for the CUTPLOTTER application
//

#if !defined(AFX_CUTPLOTTER_H__13CEA9DA_2E6C_4ABF_AF97_B6964785A269__INCLUDED_)
#define AFX_CUTPLOTTER_H__13CEA9DA_2E6C_4ABF_AF97_B6964785A269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpCutterApp:
// See CutPlotter.cpp for the implementation of this class
//

class CSpCutterApp : public CWinApp
{
public:
	void SetLanguage();
	void WriteSettings();
	void ReadSettings();

	CSpCutterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpCutterApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSpCutterApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUTPLOTTER_H__13CEA9DA_2E6C_4ABF_AF97_B6964785A269__INCLUDED_)
