// CutPlotterDoc.h : interface of the CSpCutterDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUTPLOTTERDOC_H__393138C6_618A_42B3_82D3_2D016B701F39__INCLUDED_)
#define AFX_CUTPLOTTERDOC_H__393138C6_618A_42B3_82D3_2D016B701F39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Curve.h"
#include "OnePage.h"

class CSpCutterDoc : public CDocument
{
protected: // create from serialization only
	CSpCutterDoc();
	DECLARE_DYNCREATE(CSpCutterDoc)

// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpCutterDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CTypedPtrArray <CObArray, COnePage*>  m_ArrayPage;
	void OnSaveAsPlt(CString strFileName);
	void OnRemoveOnePageData(int nPage);
	void OnRemoveDocAllData();
	void CheckDocData();
	void SpliteLastPage(int nPageLenHpgl);
public:
	virtual ~CSpCutterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSpCutterDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUTPLOTTERDOC_H__393138C6_618A_42B3_82D3_2D016B701F39__INCLUDED_)
