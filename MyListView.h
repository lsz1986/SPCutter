#if !defined(AFX_MYLISTVIEW_H__248B5D7F_CFBB_4C9C_93F3_472F75A52FDA__INCLUDED_)
#define AFX_MYLISTVIEW_H__248B5D7F_CFBB_4C9C_93F3_472F75A52FDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListView.h : header file
//
#include "SpCutterView.h"
#include "SpCutterDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CMyListView view

class CMyListView : public CListView
{
protected:
	CMyListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyListView)

// Attributes
public:
	CSpCutterView* m_pMainView;

// Operations
public:
	void OnSelChg();
	void UpdateList();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListView)
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnListClean();
	afx_msg void OnListDel();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnListTop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTVIEW_H__248B5D7F_CFBB_4C9C_93F3_472F75A52FDA__INCLUDED_)
