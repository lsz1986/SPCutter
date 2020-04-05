#ifndef _BTNCLR_H
#define _BTNCLR_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// CBtnST.h : header file
//

// Comment this if you don't want that CButtonClr hilights itself
// also when the window is inactive (like happens in Internet Explorer)
#define ST_LIKEIE

// Comment this if you don't want to use CMemDC class
#define ST_USE_MEMDC

/////////////////////////////////////////////////////////////////////////////
// CButtonClr window

class CButtonClr : public CButton
{
// Construction
public:
	BOOL m_bcheck;
	CBitmap bmp;
    CButtonClr();
	~CButtonClr();
    enum {ST_ALIGN_HORIZ, ST_ALIGN_VERT};
	CFont m_NormalFont;
	CFont m_HotFont;
	CFont m_PressedFont;
	void SetNormalFont(LOGFONT lgfont)
	{
		m_NormalFont.CreateFontIndirect(&lgfont);
	}
	void SetHotFont(LOGFONT lgfont)
	{
		m_HotFont.CreateFontIndirect(&lgfont);
	}
	void SetPressedFont(LOGFONT lgfont)
	{
		m_PressedFont.CreateFontIndirect(&lgfont);
	}
	void TransparentBlt(CDC * pDestDc, int x, int y, int w, int h, CBitmap * pBmp, int sx, int sy, COLORREF crTransparent);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CButtonClr)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	CBitmap *bkmp;
// Implementation
public:
	BOOL m_hasbmp;
	int bmwidth,bmheight;
	void SetFgbmp(int nID){bmp.LoadBitmap(nID);m_hasbmp=TRUE; BITMAP bm;
	bmp.GetObject(sizeof(bm),&bm);bmwidth=bm.bmWidth,bmheight=bm.bmHeight;}
	BOOL SetBtnCursor(int nCursorId = -1);
	void SetBkBmp(CBitmap *bmp){bkmp=bmp;}
	void SetFlatFocus(BOOL bDrawFlatFocus, BOOL bRepaint = FALSE);
	BOOL GetFlatFocus();

	void SetDefaultActiveFgColor(BOOL bRepaint = FALSE);
	void SetActiveFgColor(COLORREF crNew, BOOL bRepaint = FALSE);
	const COLORREF GetActiveFgColor();
	
	void SetDefaultActiveBgColor(BOOL bRepaint = FALSE);
	void SetActiveBgColor(COLORREF crNew, BOOL bRepaint = FALSE);
	const COLORREF GetActiveBgColor();
	
	void SetDefaultInactiveFgColor(BOOL bRepaint = FALSE);
	void SetInactiveFgColor(COLORREF crNew, BOOL bRepaint = FALSE);
	const COLORREF GetInactiveFgColor();

	void SetDefaultInactiveBgColor(BOOL bRepaint = FALSE);
	void SetInactiveBgColor(COLORREF crNew, BOOL bRepaint = FALSE);
	const COLORREF GetInactiveBgColor();

	void SetShowText(BOOL bShow = TRUE);
	BOOL GetShowText();

	void SetAlign(int nAlign);
	int GetAlign();

	void SetFlat(BOOL bState = TRUE);
	BOOL GetFlat();

	void DrawBorder(BOOL bEnable = TRUE);
	void SetIcon(int nIconInId, int nIconOutId = NULL, BYTE cx = 32, BYTE cy = 32);

	static const short GetVersionI();
	static const char* GetVersionC();

protected:
    //{{AFX_MSG(CButtonClr)
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void DrawTheIcon(CDC* pDC, CString* title, RECT* rcItem, CRect* captionRect, BOOL IsPressed, BOOL IsDisabled);

	int m_nAlign;
	BOOL m_bShowText;
	BOOL m_bDrawBorder;
	BOOL m_bIsFlat;
	BOOL m_MouseOnButton;
	BOOL m_bDrawFlatFocus;

	HCURSOR m_hCursor;

	HICON m_hIconIn;
	HICON m_hIconOut;
	BYTE m_cyIcon;
	BYTE m_cxIcon;

	COLORREF  m_crInactiveBg;
    COLORREF  m_crInactiveFg;
    COLORREF  m_crActiveBg;
    COLORREF  m_crActiveFg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
