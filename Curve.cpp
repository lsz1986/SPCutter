// Curve.cpp: implementation of the CCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpCutter.h"
#include "Curve.h"
#include "Global.h"

#define PT_OFFSET 4

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CCurve,CObject,1)
CCurve::CCurve()
{
    m_bIsSelected = FALSE;
	m_nPenNum = 1;
	m_pointList = new CArray<CPoint, CPoint>;
}

CCurve::~CCurve()
{
	m_pointList->RemoveAll();
	delete m_pointList;
}

void CCurve::operator=(CCurve &a)
{
	this->m_bIsSelected = a.m_bIsSelected;
	this->m_nPenNum = a.m_nPenNum;
	this->m_nXmax = a.m_nXmax;
	this->m_nXmin = a.m_nXmin;
	this->m_nYmax = a.m_nYmax;
	this->m_nYmin = a.m_nYmin;
	this->m_pointList->RemoveAll();
	for (int i=0; i<a.m_pointList->GetSize(); i++)
	{
		CPoint pt = a.m_pointList->GetAt(i);
		pt.x = pt.x;
		pt.y = pt.y;
		this->m_pointList->Add(pt);
	}
}

void CCurve::GetCurveMaxMin()
{
	int i;
	CPoint pt;
	pt = m_pointList->GetAt(0);
	m_nXmin = m_nXmax = pt.x;
	m_nYmin = m_nYmax = pt.y;
	for (i=1;i<m_pointList->GetSize();i++)
	{
		pt = m_pointList->GetAt(i);
		m_nXmin = (m_nXmin < pt.x) ? m_nXmin:pt.x;
		m_nXmax = (m_nXmax > pt.x) ? m_nXmax:pt.x;
		m_nYmin = (m_nYmin < pt.y) ? m_nYmin:pt.y;
		m_nYmax = (m_nYmax > pt.y) ? m_nYmax:pt.y;
	}
}

void CCurve::OnCombineLine()
{
	int i,nSize;
	CPoint ptA[3];
	CPoint pt,lastPt;
	int deltaX1,deltaY1,deltaX2,deltaY2;
	double dA,dB;

	nSize = m_pointList->GetSize();
	if (nSize <= 2)
	{
		return;
	}
	for (i=1;i<nSize-1;i++) //合并在一条直线上的点
	{
		ptA[0]=m_pointList->GetAt(i-1);
		ptA[1]=m_pointList->GetAt(i);
		ptA[2]=m_pointList->GetAt(i+1);
			
		deltaY1 = ptA[2].y - ptA[1].y;
		deltaX1 = ptA[2].x - ptA[1].x;
			
		deltaY2 = ptA[1].y - ptA[0].y;
		deltaX2 = ptA[1].x - ptA[0].x;
		
		dA = atan2((double)deltaY1 ,(double)deltaX1);
		dB = atan2((double)deltaY2 ,(double)deltaX2);
		if( dA == dB )
		{
			m_pointList->RemoveAt(i);
			i--;
			nSize--;
		}
	}
	return;
}

void CCurve::OnAngleAdjust(double dAngle,int iMaxX)
{
	int i;
	CPoint pt;
	for (i=0; i<m_pointList->GetSize(); i++)
	{
		pt = m_pointList->GetAt(i);
		if (dAngle >=0 )
		{
			pt.y = pt.y + ftoi(pt.x * tan(dAngle));
		}
		else
		{
			pt.y = pt.y + ftoi( (iMaxX-pt.x) * fabs(tan(dAngle)) );
		}
		m_pointList->RemoveAt(i);
		m_pointList->InsertAt(i,pt);
	}
}


void CCurve::OnMoveCurveTo(int nStartX, int nStartY)
{
	int i;
	CPoint pt;

	for (i=0; i<m_pointList->GetSize(); i++)
	{
 		pt = m_pointList->GetAt(i);
 		pt.x = pt.x - nStartX;
 		pt.y = pt.y - nStartY;
 		m_pointList->RemoveAt(i);
 		m_pointList->InsertAt(i,pt);
	}
	m_nXmin -= nStartX; 
	m_nXmax -= nStartX; 
	m_nYmin -= nStartY; 
	m_nYmax -= nStartY; 
}

void CCurve::OnReverse() //曲线反向
{
    CArray <CPoint, CPoint> m_PLHpglTemp;
	int nSize = m_pointList->GetSize();
	int i;
	for (i=nSize-1;i>=0;i--)
	{
		m_PLHpglTemp.Add(m_pointList->GetAt(i));
	}
	m_pointList->RemoveAll();
	
	for (i=0;i<nSize;i++)
	{
		m_pointList->Add(m_PLHpglTemp.GetAt(i));
	}
	m_PLHpglTemp.RemoveAll();
}


BOOL CCurve::CurveInRect(CRect rect) //鼠标在多边形的边上
{
	int i;
	CPoint ptScr;
	for (i=0;i<m_pointList->GetSize();i++)
	{
		ptScr = ptHpglToScr(m_pointList->GetAt(i));
		if (!rect.PtInRect(ptScr))
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CCurve::IsInRgn(CPoint point) //鼠标在多边形的边上
{
	CPoint point4[4];
	CPoint ptLastScr,ptCurScr;
	double dAngle;
	int i;
	CRgn rgn;
	ptLastScr = ptHpglToScr(m_pointList->GetAt(0));
	for(i = 1; i < m_pointList->GetSize(); i++)
	{
		ptCurScr = ptHpglToScr(m_pointList->GetAt(i));
		
		dAngle = atan2( (double)(ptCurScr.y-ptLastScr.y) , (double)(ptCurScr.x-ptLastScr.x) );
		point4[0].x = (int)(ptLastScr.x - PT_OFFSET*cos(dAngle) - PT_OFFSET*sin(dAngle));
		point4[0].y = (int)(ptLastScr.y - PT_OFFSET*sin(dAngle) + PT_OFFSET*cos(dAngle));
		
		point4[1].x = (int)(ptLastScr.x - PT_OFFSET*cos(dAngle) + PT_OFFSET*sin(dAngle));
		point4[1].y = (int)(ptLastScr.y- PT_OFFSET*sin(dAngle) - PT_OFFSET*cos(dAngle));
		
		point4[2].x = (int)(ptCurScr.x + PT_OFFSET*cos(dAngle) + PT_OFFSET*sin(dAngle));
		point4[2].y = (int)(ptCurScr.y + PT_OFFSET*sin(dAngle) - PT_OFFSET*cos(dAngle));
		
		point4[3].x = (int)(ptCurScr.x + PT_OFFSET*cos(dAngle) - PT_OFFSET*sin(dAngle));
		point4[3].y = (int)(ptCurScr.y + PT_OFFSET*sin(dAngle) + PT_OFFSET*cos(dAngle));
		
		rgn.CreatePolygonRgn(point4, 4, ALTERNATE);
        if(rgn.PtInRegion(point))
            return TRUE;
        rgn.DeleteObject();
		ptLastScr = ptCurScr;
    }
    return FALSE;
}

#define TRI_H 15 //三角形高
#define TRI_HALF_D 6  //三角形底边长的一半

void CCurve::DrawCurve(CDC *pDC)
{
	CPen penPen,penBlade,*pPenOld; //
	int i;
	CRect rect;
	
	penPen.CreatePen(LT_SOLID,0,gDispSet.getClrPen());
	penBlade.CreatePen(LT_SOLID,0,gDispSet.getClrCut());
	
	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	
	pPenOld=pDC->SelectObject(&penBlade);
	
	if (m_nPenNum<=1)
	{
		pDC->SelectObject(&penPen);
	}
	pDC->MoveTo( ptHpglToScr(m_pointList->GetAt(0)) );
	
	if(m_bIsSelected)
	{	
		for (i=0;i<m_pointList->GetSize();i++)
		{
			pDC->LineTo( ptHpglToScr(m_pointList->GetAt(i)) );
		}
		
		for (i=0;i<m_pointList->GetSize();i++)
		{
			rect = CRect(ptHpglToScr(m_pointList->GetAt(i)), ptHpglToScr(m_pointList->GetAt(i)) );
			rect.InflateRect(3, 3);
			pDC->Rectangle(rect);
		}
		
		for (i=0;i<m_pointList->GetSize()-1;i++)
		{
			CPoint pt;
			pt.x = (m_pointList->GetAt(i).x + m_pointList->GetAt(i+1).x )/2;
			pt.y = (m_pointList->GetAt(i).y + m_pointList->GetAt(i+1).y )/2;
			pt = ptHpglToScr(pt);
			rect = CRect(pt, pt);
			rect.InflateRect(3, 3);
			pDC->Rectangle(rect);
		}
	}
	else
	{
		for (i=0;i<m_pointList->GetSize();i++)
		{
			pDC->LineTo( ptHpglToScr(m_pointList->GetAt(i)) );
		}
	}
	
	pDC->SelectObject(pOldBrush);
	
	if (m_nPenNum > 1)
	{
		if(m_bIsSelected)
		{
			double thta1;
			CPoint pt0,pt1;
			pt0=m_pointList->GetAt(0);
			pt1=m_pointList->GetAt(1);
			thta1 = atan2( (double)(pt0.y - pt1.y),	(double)(pt1.x - pt0.x) );
			CPoint ptDraw;
			ptDraw = m_pointList->GetAt(0);
			ptDraw = ptHpglToScr(ptDraw);
			CPoint p[3] = 
			{
				CPoint((int)(ptDraw.x+TRI_H*cos(thta1)),(int)(ptDraw.y+TRI_H*sin(thta1))),
					CPoint((int)(ptDraw.x+TRI_HALF_D*cos(PI/2+thta1)),(int)(ptDraw.y+TRI_HALF_D*sin(PI/2+thta1))),
					CPoint((int)(ptDraw.x+TRI_HALF_D*cos(thta1-PI/2)),(int)(ptDraw.y+TRI_HALF_D*sin(thta1-PI/2))),
			};
			pDC->Polygon(p,3);
		}
	}
	
	pDC->SelectObject(pPenOld);
}

#define KP_XXX	333
#define KP_YYY	1560

void CCurve::OnToCutData()
{
	int i,nSizeCurve;
	ST_CNC_DATA_ALL *pCncData;
	int iKpDistX,iKpDistY;

	iKpDistX = (int)(gMacSet.getKPDistX()*0.1*gMacSet.getPPMMX()+KP_XXX);
	iKpDistY = (int)(gMacSet.getKPDistY()*0.1*gMacSet.getPPMMY())+KP_YYY+(gMacSet.getSpAccStep()-5000);

	nSizeCurve = m_pointList->GetSize();
	if (nSizeCurve == 0)
	{
		return;
	}
	for (i=0;i<nSizeCurve;i++)
	{
		pCncData = new ST_CNC_DATA_ALL;
		pCncData->m_iX = (int)(m_pointList->GetAt(i).x*gMacSet.getPPMMX()/40.0*gMacSet.getPltScale()*10.0/gMacSet.get10000X())+iKpDistX;
		pCncData->m_iY = (int)(m_pointList->GetAt(i).y*gMacSet.getPPMMY()/40.0*gMacSet.getPltScale()*10.0/gMacSet.get10000Y())+iKpDistY;
		if (0 == i)
		{
			pCncData->m_nCmdType = TYPE_MOVE;
		}
		else
		{
			pCncData->m_nCmdType = TYPE_CUT;
		}
		g_ptrCncList.Add(pCncData);
	}
}

void CCurve::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		ar<<strZHKJ<<m_nPenNum<<m_nXmax<<m_nYmax<<m_nXmin<<m_nYmin;
	}
	else
	{
		ar>>strZHKJ>>m_nPenNum>>m_nXmax>>m_nYmax>>m_nXmin>>m_nYmin;
	}
	m_pointList->Serialize(ar);
}

double GetDistance(CPoint pt1,CPoint pt2)
{
	double dx,dy,dr;
	dx = pt1.x-pt2.x;
	dy = pt1.y-pt2.y;
	dr=sqrt(dx*dx+dy*dy);
	return dr;
}
void CCurve::OnSpliteLine()
{
	int i,nCurveSize;
	nCurveSize = m_pointList->GetSize();
	CPoint pt0,pt1;
	CPoint ptAdd;
	double dR;
	for (i=1;i<nCurveSize;i++)
	{
		pt0 = m_pointList->GetAt(i-1);
		pt1 = m_pointList->GetAt(i);
		dR = GetDistance(pt0,pt1);
		if (dR > 300*40.0)
		{
			ptAdd.x = (pt0.x+pt1.x)/2;
			ptAdd.y = (pt0.y+pt1.y)/2;
			m_pointList->InsertAt(i,ptAdd);
//			i++;
			nCurveSize++;
		}
	}
}

inline double isLeft( CPoint *P0, CPoint *P1, CPoint *P2 )
{
	double d;
	d = ( (P1->x - P0->x) * 0.025 * (P2->y - P0->y) - (P2->x - P0->x) * 0.025 * (P1->y - P0->y) );
	return d;
}

BOOL CCurve::PtInPolygon(CPoint pt)
{
	int i,nRgnPointSize;
	int wn=0;
	CPoint ptS,ptE;
	nRgnPointSize = m_pointList->GetSize();
	for (i=0;i<nRgnPointSize-1;i++)
	{
		ptS = m_pointList->GetAt(i);
		ptE = m_pointList->GetAt(i+1);
		
		if (ptS.y <= pt.y)
		{
			if (ptE.y > pt.y)
				if (isLeft( &ptS, &ptE, &pt) > 0.0)
					++wn;
		}
		else
		{
			if (ptE.y <= pt.y)
				if (isLeft( &ptS, &ptE, &pt) < 0.0)
					--wn;
		}
	}
	if (wn==0)
		return FALSE;
	
	return TRUE;
}
