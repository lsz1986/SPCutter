// CutPlotterView.cpp : implementation of the CSpCutterView class
//

#include "stdafx.h"
#include "SpCutter.h"
#include "Global.h"
#include "HpglFile.h"
#include "MainFrm.h"
#include "SpCutterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FR_DIST_PIXEL_X 20
#define FR_DIST_PIXEL_Y 40

/////////////////////////////////////////////////////////////////////////////
// CSpCutterView

IMPLEMENT_DYNCREATE(CSpCutterView, CView)

BEGIN_MESSAGE_MAP(CSpCutterView, CView)
	//{{AFX_MSG_MAP(CSpCutterView)
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDM_DEL_CURVE, OnDelCurve)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_TO_CUT, OnToCut)
	ON_COMMAND(IDM_TO_PEN, OnToPen)
	ON_COMMAND(IDM_CHANGE_DIR, OnChangeDir)
	ON_WM_KEYUP()
	ON_COMMAND(IDM_DEL_CUT_DATA, OnDelCutData)
	ON_COMMAND(IDM_DEL_PLOT_DATA, OnDelPlotData)
	ON_COMMAND(IDM_ALL_TO_PLOT, OnAllToPlot)
	ON_COMMAND(IDM_ALL_TO_CUT, OnAllToCut)
	ON_COMMAND(IDM_BREAK_CURVE, OnBreakCurve)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpCutterView construction/destruction

CSpCutterView::CSpCutterView()
{
	m_bLBDown = FALSE;
	m_nCurrentPage = 0;
}

CSpCutterView::~CSpCutterView()
{
}

BOOL CSpCutterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSpCutterView drawing

void CSpCutterView::OnDraw(CDC* pDC)
{
	OnDrawAll(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CSpCutterView diagnostics

#ifdef _DEBUG
void CSpCutterView::AssertValid() const
{
	CView::AssertValid();
}

void CSpCutterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSpCutterDoc* CSpCutterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpCutterDoc)));
	return (CSpCutterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpCutterView message handlers


void CSpCutterView::OnCalcDispProportion()
{
	CRect rect;
	double d,dX,dY;
	GetWindowRect(rect);
	gDispSet.setScrXPixel(rect.Width());
	gDispSet.setScrYPixel(rect.Height());
	gDispSet.setDispStartX(0);
	gDispSet.setDispStartY(0);

	dX = (double)(rect.Width()-2*FR_DIST_PIXEL_X)/(double)(gDispSet.getDispSizeX()*40);
	dY = (double)(rect.Height()-2*FR_DIST_PIXEL_Y)/(double)(gDispSet.getDispSizeY()*40);

	d = (dX < dY)?dX:dY;
	gDispSet.setDispScale(d);
}

void CSpCutterView::OnDrawAll(CDC *pDrawDC)
{
	CRect rect;
	CBrush brushNew,*pBrushOld;
	brushNew.CreateSolidBrush(RGB(0,0,0));
	pBrushOld = pDrawDC->SelectObject(&brushNew);

	GetWindowRect(rect);
	pDrawDC->Rectangle(0,0,rect.Width(),rect.Height());
	brushNew.DeleteObject();
	
	if(GetDocument()->m_ArrayPage.GetSize() <= 0)
	{
		m_nCurrentPage = 0;
		return;
	}
	
	if(m_nCurrentPage >= GetDocument()->m_ArrayPage.GetSize())
	{
		m_nCurrentPage = 0;
	}
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	pDrawDC->SelectObject(pBrush);
	
	CPen penFrame,*pPenOld; //
	penFrame.CreatePen(LT_SOLID,0,gDispSet.getClrFR());
	pPenOld = pDrawDC->SelectObject(&penFrame);

	COnePage *pPage;
	pPage = GetDocument()->m_ArrayPage.GetAt(m_nCurrentPage);

	CPoint pt1,pt2;
	pt1 = ptHpglToScr(CPoint(0,0));
	pt2 = ptHpglToScr(CPoint((int)(gDispSet.getDispSizeX()*40.0 ),(int)(gDispSet.getDispSizeY()*40.0 )));
	
	pDrawDC->Rectangle((pt1.x-4),(pt1.y+4),(pt2.x+4),(pt2.y-4));
	
	penFrame.DeleteObject();
	pDrawDC->SelectObject(pBrushOld);
	pDrawDC->SelectObject(pPenOld);
	
	pPage->DrawOnePage(pDrawDC);
}

void CSpCutterView::OnZoomAll() 
{
	OnCalcDispProportion();
	OnReDraw();
}

void CSpCutterView::SetCurrentDrawPage(int nPage)
{
	m_nCurrentPage = nPage;

	if (m_nCurrentPage < 0)
	{
		m_nCurrentPage = 0;
	}
	if (GetDocument()->m_ArrayPage.GetSize() <= 0)
	{
		m_nCurrentPage = 0;
		return;
	}
	else if( m_nCurrentPage >= GetDocument()->m_ArrayPage.GetSize() )
	{
		m_nCurrentPage = 0;
	}
	
	OnCalcDispProportion();
	OnReDraw();
	return;
}

void CSpCutterView::OnReDraw()
{
    CClientDC dc(this);
    CBitmap *Oldmap;
    CBitmap Bitmap;
	CRect rect;
    CDC memDC;
	GetWindowRect(rect);
    Bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
    memDC.CreateCompatibleDC(&dc);
    Oldmap = memDC.SelectObject(&Bitmap);
	
    CRect rectClient;
    GetClientRect(rectClient);
    dc.DPtoLP(&rectClient);
    memDC.SetMapMode(dc.GetMapMode());
    memDC.PatBlt(rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), WHITENESS);
	
    OnDrawAll(&memDC);
	
    dc.BitBlt(rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), &memDC,
		rectClient.left, rectClient.top, SRCCOPY);
    memDC.DeleteDC();
}

void CSpCutterView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	OnCalcDispProportion();
	OnReDraw();
}


void CSpCutterView::OnDelCurve() 
{
	if (GetDocument()->m_ArrayPage.GetSize()<=0)
	{
		m_nCurrentPage = 0;
		return;
	}
	if (m_nCurrentPage > GetDocument()->m_ArrayPage.GetSize())
	{
		m_nCurrentPage = 0;
	}
	
	COnePage* pPage = (COnePage*)GetDocument()->m_ArrayPage.GetAt(m_nCurrentPage);
	pPage->OnDeleteSelect();
	OnReDraw();
}

void CSpCutterView::ResetSelectStatus()
{
	if (GetDocument()->m_ArrayPage.GetSize()<=0)
	{
		m_nCurrentPage = 0;
		return;
	}
	if (m_nCurrentPage >= GetDocument()->m_ArrayPage.GetSize())
	{
		m_nCurrentPage = 0;
	}
	
	COnePage* pPage = (COnePage* )GetDocument()->m_ArrayPage.GetAt(m_nCurrentPage);
	pPage->OnResetSelectStatus();
	OnReDraw();
}

void CSpCutterView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(!( GetKeyState(VK_CONTROL) < 0 ) ) //按住Ctrl键可多选
	{
		ResetSelectStatus();
	}

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);
	m_bLBDown = TRUE;
	m_ptLBDown = point;
	m_ptMouseMove = point;
	CView::OnLButtonDown(nFlags, point);
}

void CSpCutterView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bLBDown)
	{
		if (TBS_SEL == gMacSet.getToolBarState())
		{
			CClientDC dc(this);
			OnPrepareDC(&dc);
			dc.DPtoLP(&point);
			int i;
			
			CPoint pt1,pt2;
			if(m_ptLBDown.x<point.x)
			{
				pt1.x=m_ptLBDown.x;
				pt2.x=point.x;
			}
			else
			{
				pt1.x=point.x;
				pt2.x=m_ptLBDown.x;
			}
			
			if(m_ptLBDown.y<point.y)
			{
				pt1.y=m_ptLBDown.y;
				pt2.y=point.y;
			}
			else
			{
				pt1.y=point.y;
				pt2.y=m_ptLBDown.y;
			}
			
			CRect rect(pt1,pt2);
			if ( (GetDocument()->m_ArrayPage.GetSize() > 0) && (m_nCurrentPage < GetDocument()->m_ArrayPage.GetSize() ) )
			{
				COnePage* pPage;
				pPage = (COnePage*)GetDocument()->m_ArrayPage.GetAt(m_nCurrentPage);
				if( (rect.Width()>10)&&(rect.Height()>10) )
				{
					for(i = 0; i < pPage->m_CurveList.GetSize(); i++)
					{
						CCurve *pCurve = (CCurve *)pPage->m_CurveList.GetAt(i);
						if (pCurve->CurveInRect(rect))
						{
							pCurve->m_bIsSelected = true;
						}
					}
				}
				else
				{
					for(i = 0; i < pPage->m_CurveList.GetSize(); i++)
					{
						CCurve *pCurve = (CCurve *)pPage->m_CurveList.GetAt(i);
						if(pCurve->IsInRgn(point))
						{
							pCurve->m_bIsSelected = !(pCurve->m_bIsSelected);
							break;
						}
					}
				}
			}
		}
		m_bLBDown = FALSE;
		OnReDraw();
	}
	CView::OnLButtonUp(nFlags, point);
}

void CSpCutterView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	CPen pen;
	CPen *pOldPen;
	
	OnPrepareDC(&dc);
	dc.DPtoLP(&point); //此时的Point是考虑到Scroll之后的坐标
	
	pen.CreatePen(2, 1, RGB(0, 0, 0));
	pOldPen = dc.SelectObject(&pen);
	
	if (m_bLBDown)
	{
		if (gMacSet.getToolBarState() == TBS_SEL)
		{
			dc.SetROP2(R2_XORPEN);
			
			dc.MoveTo(m_ptLBDown);
			dc.LineTo(m_ptLBDown.x, m_ptMouseMove.y);
			dc.LineTo(m_ptMouseMove);
			dc.LineTo(m_ptMouseMove.x, m_ptLBDown.y);
			dc.LineTo(m_ptLBDown);
			
			dc.MoveTo(m_ptLBDown);
			dc.LineTo(m_ptLBDown.x, point.y);
			dc.LineTo(point);
			dc.LineTo(point.x, m_ptLBDown.y);
			dc.LineTo(m_ptLBDown);
		}
		if (gMacSet.getToolBarState() == TBS_MOVE)
		{
			int deltaX,deltaY;
			deltaX = point.x-m_ptMouseMove.x;
			deltaY = point.y-m_ptMouseMove.y;
			gDispSet.setDispStartX(gDispSet.getDispStartX()-deltaX);
			gDispSet.setDispStartY(gDispSet.getDispStartY()-deltaY);
			OnReDraw();
		}
		m_ptMouseMove = point;
	}
	dc.SelectObject(pOldPen);
	pen.DeleteObject();
	CView::OnMouseMove(nFlags, point);
}

void CSpCutterView::OnToCut() 
{
	if (GetDocument()->m_ArrayPage.GetSize() <= 0)
	{
		m_nCurrentPage = 0;
		return;
	}
	else if(m_nCurrentPage >= GetDocument()->m_ArrayPage.GetSize())
	{
		m_nCurrentPage = 0;
	}
	
	int i;
	COnePage* pPage = (COnePage*)GetDocument()->m_ArrayPage.GetAt(m_nCurrentPage);
	
	for(i=0; i<pPage->m_CurveList.GetSize();i++)
	{
		CCurve *pCurve = (CCurve *)pPage->m_CurveList.GetAt(i);
		if(pCurve->m_bIsSelected)
		{
			pCurve->m_nPenNum=4;
		}
	}
	pPage->OnAdjSeq(0);
	OnReDraw();
}

void CSpCutterView::OnToPen() 
{
	if (GetDocument()->m_ArrayPage.GetSize() <= 0)
	{
		m_nCurrentPage = 0;
		return;
	}
	else if(m_nCurrentPage >= GetDocument()->m_ArrayPage.GetSize())
	{
		m_nCurrentPage = 0;
	}

	int i;
	COnePage* pPage = (COnePage*)GetDocument()->m_ArrayPage.GetAt(m_nCurrentPage);
	
	for(i=0; i<pPage->m_CurveList.GetSize();i++)
	{
		CCurve *pCurve = (CCurve *)pPage->m_CurveList.GetAt(i);
		if(pCurve->m_bIsSelected)
		{
			pCurve->m_nPenNum = 1;
		}
	}
	pPage->OnAdjSeq(1);
 	OnReDraw();
}


void CSpCutterView::OnAllToPlot() 
{
	if (GetDocument()->m_ArrayPage.GetSize() <= 0)
	{
		m_nCurrentPage = 0;
		return;
	}
	else if(m_nCurrentPage >= GetDocument()->m_ArrayPage.GetSize())
	{
		m_nCurrentPage = 0;
	}
	
	int i;
	COnePage* pPage = (COnePage*)GetDocument()->m_ArrayPage.GetAt(m_nCurrentPage);
	
	for(i=0; i<pPage->m_CurveList.GetSize();i++)
	{
		CCurve *pCurve = (CCurve *)pPage->m_CurveList.GetAt(i);
		pCurve->m_nPenNum = 1;
	}
	OnReDraw();
}

void CSpCutterView::OnAllToCut() 
{
	if (GetDocument()->m_ArrayPage.GetSize() <= 0)
	{
		m_nCurrentPage = 0;
		return;
	}
	else if(m_nCurrentPage >= GetDocument()->m_ArrayPage.GetSize())
	{
		m_nCurrentPage = 0;
	}
	
	int i;
	COnePage* pPage = (COnePage*)GetDocument()->m_ArrayPage.GetAt(m_nCurrentPage);
	
	for(i=0; i<pPage->m_CurveList.GetSize();i++)
	{
		CCurve *pCurve = (CCurve *)pPage->m_CurveList.GetAt(i);
		pCurve->m_nPenNum = 4;
	}
 	OnReDraw();
}

void CSpCutterView::OnChangeDir() 
{
	COnePage* pPage;
	if (GetDocument()->m_ArrayPage.GetSize() <= 0)
	{
		m_nCurrentPage = 0;
		return;
	}
	else if(m_nCurrentPage >= GetDocument()->m_ArrayPage.GetSize())
	{
		m_nCurrentPage = 0;
	}
	
	pPage = (COnePage*)GetDocument()->m_ArrayPage.GetAt(m_nCurrentPage);
	pPage->OnChangeDir();
 	OnReDraw();	
}

void CSpCutterView::OnDelCutData() 
{
	COnePage* pPage;
	if (GetDocument()->m_ArrayPage.GetSize() <= 0)
	{
		m_nCurrentPage = 0;
		return;
	}
	else if(m_nCurrentPage >= GetDocument()->m_ArrayPage.GetSize())
	{
		m_nCurrentPage = 0;
	}
	
	pPage = (COnePage*)GetDocument()->m_ArrayPage.GetAt(m_nCurrentPage);
	pPage->OnDelCutData();
	OnReDraw();	
}

void CSpCutterView::OnDelPlotData() 
{
	COnePage* pPage;
	if (GetDocument()->m_ArrayPage.GetSize() <= 0)
	{
		m_nCurrentPage = 0;
		return;
	}
	else if(m_nCurrentPage >= GetDocument()->m_ArrayPage.GetSize())
	{
		m_nCurrentPage = 0;
	}
	
	pPage = (COnePage*)GetDocument()->m_ArrayPage.GetAt(m_nCurrentPage);
	pPage->OnDelPlotData();
	OnReDraw();	
}

void CSpCutterView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMenu menu;
	CPoint pt;
	menu.LoadMenu(IDR_POPMENU_VIEW);
	GetCursorPos(&pt);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, pt.x, pt.y, this);
	CView::OnRButtonDown(nFlags, point);
}

void CSpCutterView::ZoomIn() 
{
	double d = gDispSet.getDispScale();
	gDispSet.setDispScale(d*1.25);
	OnReDraw();
}

void CSpCutterView::ZoomOut() 
{
	double d = gDispSet.getDispScale();
	gDispSet.setDispScale(d*0.8);
	OnReDraw();	
}

void CSpCutterView::OnSetViewCursor()
{
	if(TBS_MOVE == gMacSet.getToolBarState())
	{
		SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR ,(LONG)LoadCursor(NULL,IDC_SIZEALL));
	}
	else
	{
		SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR ,(LONG)LoadCursor(NULL,IDC_ARROW));
	}
}

void CSpCutterView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_DELETE)
	{
		OnDelCurve();
	}
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CSpCutterView::OnBreakCurve() 
{
	if (GetDocument()->m_ArrayPage.GetSize() <= 0)
	{
		return;
	}
	COnePage* pPage = GetDocument()->m_ArrayPage.GetAt(0);
	pPage->OnSpliteCurveByAngle(OVERCUT_ANGLE*PI/180.0);
	Invalidate();
}
