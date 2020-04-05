// BtnST.cpp : implementation file
//

#include "stdafx.h"
#include "ButtonClr.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CButtonClr
/*


*/
#define OUTBARBOTTOM 55
CButtonClr::CButtonClr()
{
  m_MouseOnButton = FALSE;
	m_bcheck=FALSE;
	m_hasbmp=FALSE;
  m_hIconIn = NULL;
  m_hIconOut = NULL;
  m_cxIcon = 0;
  m_cyIcon = 0;
  m_hCursor = NULL;
  bkmp=NULL;
  // Default type is "flat" button
  m_bIsFlat = TRUE;

  // By default draw border in "flat" button
  m_bDrawBorder = TRUE; 
  
  // By default icon is aligned horizontally
  m_nAlign = ST_ALIGN_HORIZ; 
  
  // By default show the text button
  m_bShowText = TRUE; 
  
  // By default, for "flat" button, don't draw the focus rect
  m_bDrawFlatFocus = FALSE;
	
  SetDefaultInactiveBgColor();
  SetDefaultInactiveFgColor();
  SetDefaultActiveBgColor();
  SetDefaultActiveFgColor();
} // End of CButtonClr


CButtonClr::~CButtonClr()
{
	// Destroy the icons (if any)
	if (m_hIconIn != NULL) ::DeleteObject(m_hIconIn);
	if (m_hIconOut != NULL) ::DeleteObject(m_hIconOut);
	// Destroy the cursor (if any)
	if (m_hCursor != NULL) ::DestroyCursor(m_hCursor);
} // End of ~CButtonClr


BEGIN_MESSAGE_MAP(CButtonClr, CButton)
    //{{AFX_MSG_MAP(CButtonClr)
	ON_WM_CAPTURECHANGED()
	ON_WM_SETCURSOR()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CButtonClr::SetIcon(int nIconInId, int nIconOutId, BYTE cx, BYTE cy)
{
	HINSTANCE hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nIconInId),
													RT_GROUP_ICON);
	// Set icon when the mouse is IN the button
	m_hIconIn = (HICON)::LoadImage(hInstResource/*AfxGetApp()->m_hInstance*/, MAKEINTRESOURCE(nIconInId), IMAGE_ICON, 0, 0, 0);
  
	// Set icon when the mouse is OUT the button
	m_hIconOut = (nIconOutId == NULL) ? m_hIconIn : (HICON)::LoadImage(hInstResource/*AfxGetApp()->m_hInstance*/, MAKEINTRESOURCE(nIconOutId), IMAGE_ICON, 0, 0, 0);
  
	m_cxIcon = cx;
	m_cyIcon = cy;

	RedrawWindow();
} // End of SetIcon


BOOL CButtonClr::SetBtnCursor(int nCursorId)
{
	HINSTANCE hInstResource;
	// Destroy any previous cursor
	if (m_hCursor != NULL) ::DestroyCursor(m_hCursor);
	m_hCursor = NULL;

	// If we want a cursor
	if (nCursorId != -1)
	{
		hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nCursorId),
											RT_GROUP_CURSOR);
		// Load icon resource
		m_hCursor = (HCURSOR)::LoadImage(hInstResource/*AfxGetApp()->m_hInstance*/, MAKEINTRESOURCE(nCursorId), IMAGE_CURSOR, 0, 0, 0);
		// If something wrong then return FALSE
		if (m_hCursor == NULL) return FALSE;
	}

	return TRUE;
} // End of SetBtnCursor


void CButtonClr::SetFlat(BOOL bState)
{
  m_bIsFlat = bState;
  Invalidate();
} // End of SetFlat


BOOL CButtonClr::GetFlat()
{
  return m_bIsFlat;
} // End of GetFlat


void CButtonClr::SetAlign(int nAlign)
{
  switch (nAlign)
  {    
    case ST_ALIGN_HORIZ:
         m_nAlign = ST_ALIGN_HORIZ;
         break;
    case ST_ALIGN_VERT:
         m_nAlign = ST_ALIGN_VERT;
         break;
  }
  Invalidate();
} // End of SetAlign


int CButtonClr::GetAlign()
{
  return m_nAlign;
} // End of GetAlign


void CButtonClr::DrawBorder(BOOL bEnable)
{
  m_bDrawBorder = bEnable;
} // End of DrawBorder


const char* CButtonClr::GetVersionC()
{
  return "2.3";
} // End of GetVersionC


const short CButtonClr::GetVersionI()
{
  return 23; // Divide by 10 to get actual version
} // End of GetVersionI


void CButtonClr::SetShowText(BOOL bShow)
{
  m_bShowText = bShow;
  Invalidate();
} // End of SetShowText


BOOL CButtonClr::GetShowText()
{
  return m_bShowText;
} // End of GetShowText


void CButtonClr::OnMouseMove(UINT nFlags, CPoint point)
{
  CWnd* pWnd;  // Finestra attiva
  CWnd* pParent; // Finestra che contiene il bottone

  CButton::OnMouseMove(nFlags, point);

  // If the mouse enter the button with the left button pressed
  // then do nothing
  if (nFlags & MK_LBUTTON && m_MouseOnButton == FALSE) return;

  // If our button is not flat then do nothing
  if (m_bIsFlat == FALSE) return;

  pWnd = GetActiveWindow();
  pParent = GetOwner();

	if ((GetCapture() != this) && 
		(
#ifndef ST_LIKEIE
		pWnd != NULL && 
#endif
		pParent != NULL)) 
	{
		m_MouseOnButton = TRUE;
		//SetFocus();	// Thanks Ralph!
		SetCapture();
		Invalidate();
	}
	else
  {
    CRect rc;
    GetClientRect(&rc);
    if (!rc.PtInRect(point))
    {
      // Redraw only if mouse goes out
      if (m_MouseOnButton == TRUE)
      {
        m_MouseOnButton = FALSE;
        Invalidate();
      }
      // If user is NOT pressing left button then release capture!
      if (!(nFlags & MK_LBUTTON)) ReleaseCapture();
    }
  }
} // End of OnMouseMove


void CButtonClr::OnKillFocus(CWnd * pNewWnd)
{
  CButton::OnKillFocus(pNewWnd);

  // If our button is not flat then do nothing
  if (m_bIsFlat == FALSE) return;

  if (m_MouseOnButton == TRUE)
  {
    m_MouseOnButton = FALSE;
    Invalidate();
  }
} // End of OnKillFocus


void CButtonClr::OnCaptureChanged(CWnd *pWnd) 
{
	if (m_MouseOnButton == TRUE)
	{
		ReleaseCapture();
		Invalidate();
	}

	// Call base message handler
	CButton::OnCaptureChanged(pWnd);
} // End of OnCaptureChanged


void CButtonClr::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
// return;
  CDC* DestDC = CDC::FromHandle(lpDIS->hDC);
  CBitmap bmp;
  
  CPen *pOldPen;
  BOOL bIsPressed  = (lpDIS->itemState & ODS_SELECTED);
  BOOL bIsFocused  = (lpDIS->itemState & ODS_FOCUS);
  BOOL bIsDisabled = (lpDIS->itemState & ODS_DISABLED);
  CRect itemRect = lpDIS->rcItem;
  bmp.CreateCompatibleBitmap(DestDC,itemRect.Width(),itemRect.Height());
  CDC Memdc;
  Memdc.CreateCompatibleDC(DestDC);
  CBitmap *oldbmp=Memdc.SelectObject(&bmp);
  CDC *pDC=&Memdc;
  if (m_bIsFlat == FALSE)
  {
    if (bIsFocused)
    {
      CBrush br(RGB(0,0,0));  
      pDC->FrameRect(&itemRect, &br);
      itemRect.DeflateRect(1, 1);
    }
  }

  // Prepare draw... paint button's area with background color
  COLORREF bgColor;
  if ((m_MouseOnButton == TRUE) || (bIsPressed))
    bgColor = GetActiveBgColor();
  else
    bgColor = GetInactiveBgColor();

  CBrush br(bgColor);
  if(!bkmp)
	pDC->FillRect(&itemRect, &br);
  else
  {
	  CDC memdc;
	  CRect rc;
	  GetWindowRect(&rc);
	  GetParent()->ScreenToClient(&rc);
	  memdc.CreateCompatibleDC(pDC);
	  CBitmap *oldbmp=memdc.SelectObject(bkmp);
	  pDC->BitBlt(0,0,rc.Width(),rc.Height(),&memdc,rc.left,rc.top,SRCCOPY);
//	  BITMAP bm;
//	  bkmp->GetObject(sizeof(BITMAP),&bm);
//	  GetParent()->GetClientRect(&rc);
//	  pDC->BitBlt(0,rc.Height()-OUTBARBOTTOM,bm.bmWidth,OUTBARBOTTOM,&memdc,0,bm.bmHeight-OUTBARBOTTOM,SRCCOPY);
	  memdc.SelectObject(oldbmp);
	  memdc.DeleteDC();
  }
	// Disegno lo sfondo del bottone
//CBrush br(GetSysColor(COLOR_BTNFACE));  
//pDC->FillRect(&itemRect, &br);

  // Draw pressed button
  if (bIsPressed||m_bcheck)
  {
    if (m_bIsFlat == TRUE)
    {
      if (m_bDrawBorder == TRUE)
      {
	    CPen penBtnHiLight(PS_SOLID, 0, GetSysColor(COLOR_BTNHILIGHT)); // Bianco
        CPen penBtnShadow(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));   // Grigio scuro

        // Disegno i bordi a sinistra e in alto
        // Dark gray line
        pOldPen = pDC->SelectObject(&penBtnShadow);
        pDC->MoveTo(itemRect.left, itemRect.bottom-1);
        pDC->LineTo(itemRect.left, itemRect.top);
        pDC->LineTo(itemRect.right, itemRect.top);
        // Disegno i bordi a destra e in basso
        // White line
        pDC->SelectObject(penBtnHiLight);
        pDC->MoveTo(itemRect.left, itemRect.bottom-1);
        pDC->LineTo(itemRect.right-1, itemRect.bottom-1);
        pDC->LineTo(itemRect.right-1, itemRect.top-1);
        //
        pDC->SelectObject(pOldPen);
      }
    }
    else    
    {
      CBrush brBtnShadow(GetSysColor(COLOR_BTNSHADOW));
      pDC->FrameRect(&itemRect, &brBtnShadow);
    }
  }
  else // ...else draw non pressed button
  {
    CPen penBtnHiLight(PS_SOLID, 0, GetSysColor(COLOR_BTNHILIGHT)); // White
    CPen pen3DLight(PS_SOLID, 0, GetSysColor(COLOR_3DLIGHT));       // Light gray
    CPen penBtnShadow(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));   // Dark gray
    CPen pen3DDKShadow(PS_SOLID, 0, GetSysColor(COLOR_3DDKSHADOW)); // Black

    if (m_bIsFlat == TRUE)
    {
      if (m_MouseOnButton == TRUE && m_bDrawBorder == TRUE)
      {
  	    // Disegno i bordi a sinistra e in alto
        // White line
        pOldPen = pDC->SelectObject(&penBtnHiLight);
        pDC->MoveTo(itemRect.left, itemRect.bottom-1);
        pDC->LineTo(itemRect.left, itemRect.top);
        pDC->LineTo(itemRect.right, itemRect.top);
        // Disegno i bordi a destra e in basso
        // Dark gray line
        pDC->SelectObject(penBtnShadow);
        pDC->MoveTo(itemRect.left, itemRect.bottom-1);
        pDC->LineTo(itemRect.right-1, itemRect.bottom-1);
        pDC->LineTo(itemRect.right-1, itemRect.top-1);
        //
        pDC->SelectObject(pOldPen);
      }
	  else
	  {
			//pDC->Draw3dRect(&itemRect,RGB(0,0,0),RGB(0,0,0));
	  }
    }
    else
    {
      // Disegno i bordi a sinistra e in alto
      // White line
      pOldPen = pDC->SelectObject(&penBtnHiLight);
      pDC->MoveTo(itemRect.left, itemRect.bottom-1);
      pDC->LineTo(itemRect.left, itemRect.top);
      pDC->LineTo(itemRect.right, itemRect.top);
      // Light gray line
      pDC->SelectObject(pen3DLight);
      pDC->MoveTo(itemRect.left+1, itemRect.bottom-1);
      pDC->LineTo(itemRect.left+1, itemRect.top+1);
      pDC->LineTo(itemRect.right, itemRect.top+1);
      // Disegno i bordi a destra e in basso
      // Black line
      pDC->SelectObject(pen3DDKShadow);
      pDC->MoveTo(itemRect.left, itemRect.bottom-1);
      pDC->LineTo(itemRect.right-1, itemRect.bottom-1);
      pDC->LineTo(itemRect.right-1, itemRect.top-1);
      // Dark gray line
      pDC->SelectObject(penBtnShadow);
      pDC->MoveTo(itemRect.left+1, itemRect.bottom-2);
      pDC->LineTo(itemRect.right-2, itemRect.bottom-2);
      pDC->LineTo(itemRect.right-2, itemRect.top);
      //
      pDC->SelectObject(pOldPen);
    }
  }

  // Read the button title
  CString sTitle;
  GetWindowText(sTitle);

  // If we don't want the title displayed
  if (m_bShowText == FALSE) sTitle.Empty();

  CRect captionRect = lpDIS->rcItem;

  // Draw the icon
  if (m_hIconIn != NULL||m_hasbmp)
  {
    DrawTheIcon(pDC, &sTitle, &lpDIS->rcItem, &captionRect, bIsPressed, bIsDisabled);
  }

  // Write the button title (if any)
  if (sTitle.IsEmpty() == FALSE)
  {
    // Disegno la caption del bottone
    // Se il bottone e' premuto muovo la captionRect di conseguenza
    if (bIsPressed)
      captionRect.OffsetRect(1, 1);
    
    // ONLY FOR DEBUG 
    // Evidenzia il rettangolo in cui verra' centrata la caption 
    //CBrush brBtnShadow(RGB(255, 0, 0));
    //pDC->FrameRect(&captionRect, &brBtnShadow);

#ifdef ST_USE_MEMDC
	// Get dialog's font
	CFont mcFont;
    CFont *pCurrentFont = GetFont(); 
//	if(pCurrentFont)
//		pCurrentFont->GetLogFont(&lgfont);
//	if(m_bcheck)
//		lgfont.lfWeight=5;
//	mcFont.CreateFontIndirect(&lgfont);
    CFont *pOldFont;// = pDC->SelectObject(pCurrentFont);
#endif
    if ((m_MouseOnButton == TRUE) || (bIsPressed)) 
	{
	  pOldFont=pDC->SelectObject(&m_HotFont);
      pDC->SetTextColor(GetActiveFgColor());
      pDC->SetBkColor(GetActiveBgColor());
    } 
	else 
	{
	  pOldFont=pDC->SelectObject(&m_NormalFont);
      pDC->SetTextColor(GetInactiveFgColor());
      pDC->SetBkColor(GetInactiveBgColor());
	  if(m_bcheck)
	  {
		  pDC->SetTextColor(RGB(255,0,0));
	  }
    }
	if(m_bcheck)
	{
		pDC->SelectObject(&m_PressedFont);
	}
    // Center text
    CRect centerRect = captionRect;
	pDC->SetBkMode(TRANSPARENT);
	if(m_bcheck)
	{
		sTitle="¡Ì"+sTitle;
	}
    pDC->DrawText(sTitle, -1, captionRect, DT_SINGLELINE|DT_CALCRECT);
    captionRect.OffsetRect((centerRect.Width() - captionRect.Width())/2, (centerRect.Height() - captionRect.Height())/2);
	/* RFU
    captionRect.OffsetRect(0, (centerRect.Height() - captionRect.Height())/2);
    captionRect.OffsetRect((centerRect.Width() - captionRect.Width())-4, (centerRect.Height() - captionRect.Height())/2);
	*/

    pDC->DrawState(captionRect.TopLeft(), captionRect.Size(), (LPCTSTR)sTitle, (bIsDisabled ? DSS_DISABLED : DSS_NORMAL), 
                   TRUE, 0, (CBrush*)NULL);
#ifdef ST_USE_MEMDC
    pDC->SelectObject(pOldFont);
	mcFont.DeleteObject();
#endif
  }

  if (m_bIsFlat == FALSE || (m_bIsFlat == TRUE && m_bDrawFlatFocus == TRUE))
  {
    // Draw the focus rect
    if (bIsFocused)
    {
      CRect focusRect = itemRect;
      focusRect.DeflateRect(3, 3);
      pDC->DrawFocusRect(&focusRect);
    }
  }
  DestDC->BitBlt(0,0,itemRect.Width(),itemRect.Height(),&Memdc,0,0,SRCCOPY);
  Memdc.SelectObject(oldbmp);
  Memdc.DeleteDC();
  bmp.DeleteObject();
} // End of DrawItem

void CButtonClr::TransparentBlt(CDC * pDestDc, int x, int y, int w, int h, CBitmap * pBmp, int sx, int sy, COLORREF crTransparent)
{
	CDC memDC, maskDC, tempDC;
	maskDC.CreateCompatibleDC(pDestDc);
	CBitmap maskBitmap;
	
	//add these to store return of SelectObject() calls
	CBitmap* pOldMemBmp = NULL;
	CBitmap* pOldMaskBmp = NULL;
	
	memDC.CreateCompatibleDC(pDestDc);
	tempDC.CreateCompatibleDC(pDestDc);
	CBitmap bmpImage;
	bmpImage.CreateCompatibleBitmap( pDestDc, w, h);
	pOldMemBmp = memDC.SelectObject( &bmpImage );

	CBitmap * oldBmp = tempDC.SelectObject(pBmp);
	
	memDC.BitBlt( 0,0,w, h, &tempDC, sx, sy, SRCCOPY );
	
	// Create monochrome bitmap for the mask
	maskBitmap.CreateBitmap(w, h, 1, 1, NULL);
	pOldMaskBmp = maskDC.SelectObject( &maskBitmap );
	memDC.SetBkColor(crTransparent);
	
	// Create the mask from the memory DC
	maskDC.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY);
	
	memDC.SetBkColor(RGB(0,0,0));
	memDC.SetTextColor(RGB(255,255,255));
	memDC.BitBlt(0, 0, w, h, &maskDC, 0, 0, SRCAND);
	
	// Set the foreground to black. See comment above.
	pDestDc->SetBkColor(RGB(255,255,255));
	pDestDc->SetTextColor(RGB(0,0,0));
	pDestDc->BitBlt(x, y, w, h, &maskDC, 0, 0, SRCAND);
	
	// Combine the foreground with the background
	pDestDc->BitBlt(x, y, w, h, &memDC, 0, 0, SRCPAINT);
	
	tempDC.SelectObject(oldBmp);
	if (pOldMaskBmp) maskDC.SelectObject( pOldMaskBmp );
	if (pOldMemBmp)  memDC.SelectObject( pOldMemBmp );
}
void CButtonClr::DrawTheIcon(CDC* pDC, CString* title, RECT* rcItem, CRect* captionRect, BOOL IsPressed, BOOL IsDisabled)
{
  CRect iconRect = rcItem;
	if(m_hasbmp)
	{
		m_cxIcon=bmwidth;
		m_cyIcon=bmheight;
	}
  switch (m_nAlign)
  {
    case ST_ALIGN_HORIZ:
         if (title->IsEmpty())
         {
           // Center the icon horizontally
			   iconRect.left += ((iconRect.Width() - m_cxIcon)/2);
		}
         else
         {
           // L'icona deve vedersi subito dentro il focus rect
           iconRect.left += 3;  
           captionRect->left += m_cxIcon + 3;
         }
         // Center the icon vertically
         iconRect.top += ((iconRect.Height() - m_cyIcon)/2);
         break;
    case ST_ALIGN_VERT:
         // Center the icon horizontally
         iconRect.left += ((iconRect.Width() - m_cxIcon)/2);
         if (title->IsEmpty())
         {
           // Center the icon vertically
           iconRect.top += ((iconRect.Height() - m_cyIcon)/2);           
         }
         else
         {
           captionRect->top += m_cyIcon;
         }
         break;
  }
    
  // If button is pressed then press the icon also
  if (IsPressed) iconRect.OffsetRect(1, 1);
  // Ole'!
  if(m_hasbmp)
  {
	  CDC memdc;
	  COLORREF cr;
//	  BITMAP bm;
//	  bmp.GetObject(sizeof(bm),&bm);
	  memdc.CreateCompatibleDC(pDC);
	  CBitmap *old=memdc.SelectObject(&bmp);
	  cr=memdc.GetPixel(0,0);
	  memdc.SelectObject(old);
	  memdc.DeleteDC(); 
	  
//	  pDC->BitBlt(iconRect.left,iconRect.top,bm.bmWidth,bm.bmHeight,&memdc,0,0,SRCCOPY);
	  TransparentBlt(pDC,iconRect.left,iconRect.top,bmwidth,bmheight,&bmp,0,0,cr);
	  
  }
  else
  {
  pDC->DrawState(iconRect.TopLeft(), 
	               iconRect.Size(), 
				         (m_MouseOnButton == TRUE || IsPressed) ? m_hIconIn : m_hIconOut, 
				         (IsDisabled ? DSS_DISABLED : DSS_NORMAL), 
                 (CBrush*)NULL);
  }
} // End of DrawTheIcon


void CButtonClr::PreSubclassWindow() 
{
  // Add BS_OWNERDRAW style
  SetButtonStyle(GetButtonStyle() | BS_OWNERDRAW);
  CButton::PreSubclassWindow();
} // End of PreSubclassWindow


void CButtonClr::SetDefaultInactiveBgColor(BOOL bRepaint)
{
	m_crInactiveBg = ::GetSysColor(COLOR_BTNFACE); 
	if (bRepaint == TRUE) Invalidate();
} // End of SetDefaultInactiveBgColor


void CButtonClr::SetInactiveBgColor(COLORREF crNew, BOOL bRepaint)
{
	m_crInactiveBg = crNew; 
	if (bRepaint == TRUE) Invalidate();
} // End of SetInactiveBgColor


const COLORREF CButtonClr::GetInactiveBgColor()
{
	return m_crInactiveBg;
} // End of GetInactiveBgColor


void CButtonClr::SetDefaultInactiveFgColor(BOOL bRepaint)
{
	m_crInactiveFg = ::GetSysColor(COLOR_BTNTEXT); 
	if (bRepaint == TRUE) Invalidate();
} // End of SetDefaultInactiveFgColor


void CButtonClr::SetInactiveFgColor(COLORREF crNew, BOOL bRepaint)
{
	m_crInactiveFg = crNew; 
	if (bRepaint == TRUE) Invalidate();
} // End of SetInactiveFgColor


const COLORREF CButtonClr::GetInactiveFgColor()
{
	return m_crInactiveFg;
} // End of GetInactiveFgColor


void CButtonClr::SetDefaultActiveBgColor(BOOL bRepaint)
{
	m_crActiveBg = ::GetSysColor(COLOR_BTNFACE); 
	if (bRepaint == TRUE) Invalidate();
} // End of SetDefaultActiveBgColor


void CButtonClr::SetActiveBgColor(COLORREF crNew, BOOL bRepaint)
{
	m_crActiveBg = crNew; 
	if (bRepaint == TRUE) Invalidate();
} // End of SetActiveBgColor


const COLORREF CButtonClr::GetActiveBgColor()
{
	return m_crActiveBg;
} // End of GetActiveBgColor


void CButtonClr::SetDefaultActiveFgColor(BOOL bRepaint)
{
	m_crActiveFg = ::GetSysColor(COLOR_BTNTEXT); 
	if (bRepaint == TRUE) Invalidate();
} // End of SetDefaultActiveFgColor


void CButtonClr::SetActiveFgColor(COLORREF crNew, BOOL bRepaint)
{
	m_crActiveFg = crNew; 
	if (bRepaint == TRUE) Invalidate();
} // End of SetActiveFgColor


const COLORREF CButtonClr::GetActiveFgColor()
{
	return m_crActiveFg;
} // End of GetActiveFgColor


void CButtonClr::SetFlatFocus(BOOL bDrawFlatFocus, BOOL bRepaint)
{
	m_bDrawFlatFocus = bDrawFlatFocus;
	
	// Repaint the button
	if (bRepaint == TRUE) Invalidate();
} // End of SetFlatFocus


BOOL CButtonClr::GetFlatFocus()
{
	return m_bDrawFlatFocus;
} // End of GetFlatFocus

BOOL CButtonClr::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}
BOOL CButtonClr::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// If a cursor was specified then use it!
	if (m_hCursor != NULL)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}

	return CButton::OnSetCursor(pWnd, nHitTest, message);
} // End of OnSetCursor

#undef ST_USE_MEMDC
#undef ST_LIKE
