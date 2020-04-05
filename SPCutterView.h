// CutPlotterView.h : interface of the CSpCutterView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUTPLOTTERVIEW_H__40C06C31_F4F3_4E86_992C_92EF62ED44D5__INCLUDED_)
#define AFX_CUTPLOTTERVIEW_H__40C06C31_F4F3_4E86_992C_92EF62ED44D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "SpCutterDoc.h"
#endif // _MSC_VER > 1000
#include "Thread.h"

class CSpCutterView : public CView
{
protected: // create from serialization only
	CSpCutterView();
	DECLARE_DYNCREATE(CSpCutterView)

// Attributes
public:
	CSpCutterDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpCutterView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation

public:
	void SetCurrentDrawPage(int nPage);
	void OnDrawAll(CDC* pDrawDC);
	CPoint HpglToPt(int hpglX,int hpglY);
	void OnCalcDispProportion();
	void ZoomIn();
	void ZoomOut();
	void OnZoomAll();
	void OnReDraw();

public:
	int m_nCurrentPage;

private:
	BOOL m_bLBDown;
	CPoint m_ptLBDown;
	CPoint m_ptMouseMove;

public:
	void OnSetViewCursor();
	void ResetSelectStatus();
	virtual ~CSpCutterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSpCutterView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDelCurve();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnToCut();
	afx_msg void OnToPen();
	afx_msg void OnChangeDir();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDelCutData();
	afx_msg void OnDelPlotData();
	afx_msg void OnAllToPlot();
	afx_msg void OnAllToCut();
	afx_msg void OnBreakCurve();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CutPlotterView.cpp
inline CSpCutterDoc* CSpCutterView::GetDocument()
   { return (CSpCutterDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUTPLOTTERVIEW_H__40C06C31_F4F3_4E86_992C_92EF62ED44D5__INCLUDED_)
