// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__F7AF4AE4_EAA0_4984_95BE_86C36989C685__INCLUDED_)
#define AFX_MAINFRM_H__F7AF4AE4_EAA0_4984_95BE_86C36989C685__INCLUDED_

#if _MSC_VER > 1000
#pragma once

#include "MyListView.h"
#include "SpCutterView.h"
#endif // _MSC_VER > 1000

#include "SpCutterDoc.h"
#include "MyDlgBar.h"
#include "Global.h"
#include "Thread.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	CSpCutterView* m_pMainView;
	CMyListView* m_pListView;
public:
	CSpCutterDoc* GetDocument();

public:
	int CreateCncList();
	int OnStartProcess();
	void OnPltAddAuto(CString strFileName,BOOL bDeleteFile);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CProgressCtrl m_wndProgress;
	CMyDlgBar m_wndDlgBar;
	CToolBar m_wndToolBar;
	CSplitterWnd m_wndSplitter;

	afx_msg LRESULT OnEndWorkThread(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnDispSysStatus(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSearchNewPltFile(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnAutoStartWork(WPARAM wParam,LPARAM lParam);

	afx_msg void OnUpdateCmdUISysState(CCmdUI* pCmdUI);
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetClr();
	afx_msg void OnSetDir();
	afx_msg void OnPaint();
	afx_msg LRESULT onShowTask(WPARAM wParam,LPARAM lParam); 
	afx_msg void OnAppToTray();
	afx_msg void OnPltOpen();
	afx_msg void OnPltAdd();
	afx_msg void OnPltSave();
	afx_msg void OnParaSet();
	afx_msg void OnManualCtrl();
	afx_msg void OnClose();
	afx_msg void OnSpClean();
	afx_msg void OnAuthInfo();
	afx_msg void OnSuperUser();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnZoomAll();
	afx_msg void OnVSel();
	afx_msg void OnVMove();
	afx_msg void OnUpdateVMove(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVSel(CCmdUI* pCmdUI);
	afx_msg void OnFILEATF10x10();
	afx_msg void OnFILEATF20x20();
	afx_msg void OnFILEATF30x30();
	afx_msg void OnFILEATF40x40();
	afx_msg void OnFILEATF50x50();
	afx_msg void OnWorkStart();
	afx_msg void OnWorkPause();
	afx_msg void OnWorkCancel();
	afx_msg void OnUpdateWorkPause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWorkStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWorkCancel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateManualCtrl(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSpClean(CCmdUI* pCmdUI);
	afx_msg void OnLanChs();
	afx_msg void OnLanEn();
	afx_msg void OnUpdateLanChs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLanEn(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__F7AF4AE4_EAA0_4984_95BE_86C36989C685__INCLUDED_)
