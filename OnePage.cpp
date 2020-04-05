// COnePage.cpp: implementation of the COnePage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpCutter.h"
#include "OnePage.h"
#include "Global.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(COnePage,CObject,1)
COnePage::COnePage()
{
	m_bIsPlotOnlyFile = TRUE;
}

COnePage::~COnePage()
{
	OnRemoveAllData();
}

void COnePage::operator=(COnePage &a)
{
	CCurve* pCurve;
	this->m_strFileName = a.m_strFileName;
	this->m_nXmax = a.m_nXmax;
	this->m_nXmin = a.m_nXmin;
	this->m_nYmax = a.m_nYmax;
	this->m_nYmin = a.m_nYmin;
	
	for (int i=0;i<a.m_CurveList.GetSize();i++)
	{
		pCurve = a.m_CurveList.GetAt(i);
		CCurve* pNewCurve = new CCurve;
		*pNewCurve = *pCurve;
		this->m_CurveList.Add(pNewCurve);
	}
}

void COnePage::OnRemoveInvalidPoints()
{
	int i,j;
	CPoint pt,lastPt;
	int CurveArraySize,PLSize;
	CurveArraySize = m_CurveList.GetSize();
	for(i = 0; i < CurveArraySize; i++)
	{
		CCurve* pCurve = (CCurve*)m_CurveList.GetAt(i);
		PLSize = pCurve->m_pointList->GetSize();
		if (PLSize <= 1) //删除无效的数据
		{
			pCurve->m_pointList->RemoveAll();
			m_CurveList.RemoveAt(i);
			CurveArraySize--;
			i--;
		}
		else
		{
			for (j=1; j<PLSize; j++)
			{
				pt = pCurve->m_pointList->GetAt(j);
				lastPt = pCurve->m_pointList->GetAt(j-1); //前一个点
				if (lastPt == pt)
				{
					pCurve->m_pointList->RemoveAt(j);
					PLSize --;
					j--;
				}
			}
		}
		if (PLSize <= 1) //删除无效的数据
		{
			pCurve->m_pointList->RemoveAll();
			m_CurveList.RemoveAt(i);
			CurveArraySize--;
			i--;
		}
	}
}

void COnePage::OnCheckPageData()
{
	CCurve *pCurve;
	int nCurveSum,nCurveIndex;
	nCurveSum = m_CurveList.GetSize();
	if (nCurveSum == 0)
		return;
	
	for (nCurveIndex=0; nCurveIndex<nCurveSum; nCurveIndex++)
	{
		pCurve = (CCurve *)m_CurveList.GetAt(nCurveIndex);
		pCurve->OnCombineLine();
		if (pCurve->m_pointList->GetSize() == 0)
		{
			delete pCurve;
			m_CurveList.RemoveAt(nCurveIndex);
			nCurveSum --;
			nCurveIndex--;
		}
	}

	return;
}

void COnePage::OnGetPageMaxMin()
{
	int i;
	CCurve* pCurve;
	int nPageSize = m_CurveList.GetSize();
	if (nPageSize == 0)
	{
		return;
	}
	pCurve = (CCurve*)m_CurveList.GetAt(0);
	pCurve->GetCurveMaxMin();
	m_nXmin = pCurve->m_nXmin;
	m_nXmax = pCurve->m_nXmax;
	m_nYmin = pCurve->m_nYmin;
	m_nYmax = pCurve->m_nYmax;

	if (nPageSize > 1)
	{
		for (i=1;i<nPageSize;i++)
		{
			pCurve = (CCurve*)m_CurveList.GetAt(i);
			pCurve->GetCurveMaxMin();
			m_nXmin = (m_nXmin < pCurve->m_nXmin) ? m_nXmin:pCurve->m_nXmin;
			m_nXmax = (m_nXmax > pCurve->m_nXmax) ? m_nXmax:pCurve->m_nXmax;
			m_nYmin = (m_nYmin < pCurve->m_nYmin) ? m_nYmin:pCurve->m_nYmin;
			m_nYmax = (m_nYmax > pCurve->m_nYmax) ? m_nYmax:pCurve->m_nYmax;
		}
	}
}

void COnePage::OnMoveToLeft()
{
	int i;
	CCurve* pCurve;
	int nPageSize = m_CurveList.GetSize();
	if (nPageSize == 0)
	{
		return;
	}

	for (i=0;i<nPageSize;i++)
	{
		pCurve = (CCurve*)m_CurveList.GetAt(i);
		pCurve->OnMoveCurveTo(m_nXmin,0);
	}

	m_nXmax = m_nXmax - m_nXmin;
	m_nXmin = 0;
}

void COnePage::OnAddYMargin(int YDistHpgl)
{
	int i;
	CCurve* pCurve;
	int nPageSize = m_CurveList.GetSize();
	if (nPageSize == 0)
	{
		return;
	}
	
	for (i=0;i<nPageSize;i++)
	{
		pCurve = (CCurve*)m_CurveList.GetAt(i);
		pCurve->OnMoveCurveTo(0,-YDistHpgl);
	}
	
	m_nYmax = m_nYmax + YDistHpgl;
	m_nYmin = 0;
}

void COnePage::OnMoveToBottom()
{
	int i;
	CCurve* pCurve;
	int nPageSize = m_CurveList.GetSize();
	if (nPageSize == 0)
	{
		return;
	}
	
	for (i=0;i<nPageSize;i++)
	{
		pCurve = (CCurve*)m_CurveList.GetAt(i);
		pCurve->OnMoveCurveTo(0,m_nYmin);
	}

	m_nYmax = m_nYmax - m_nYmin;
	m_nYmin = 0;
}

void COnePage::OnPageAngleAdjust()
{
	int i;
	CCurve* pCurve;
	double dAngle = (100.0-gSet.getAngleAdjust())*0.01*PI/180.0;
	int nPageSize = m_CurveList.GetSize();
	if (nPageSize == 0)
	{
		return;
	}
	if (gSet.getAngleAdjust() == 100)
	{
		return;
	}
	for (i=0;i<nPageSize;i++)
	{
		pCurve = (CCurve*)m_CurveList.GetAt(i);
		pCurve->OnAngleAdjust(dAngle,m_nXmax);
	}

}

void COnePage::OnGetSizePlotCut()
{
	CCurve* pCurve;
	int i;
	int nPageSize = m_CurveList.GetSize();
	if (nPageSize == 0)
	{
		return;
	}

	m_nPlotXMax = 0;
	m_nPlotYMax = 0;
	m_nCutXMax = 0;
	m_nCutYMax = 0;

	for (i=0;i<nPageSize;i++)
	{
		pCurve = (CCurve*)m_CurveList.GetAt(i);
		if (pCurve->m_nPenNum <= 1)
		{
			m_nPlotXMax = (m_nPlotXMax > pCurve->m_nXmax) ? m_nPlotXMax : pCurve->m_nXmax;
			m_nPlotYMax = (m_nPlotYMax > pCurve->m_nYmax) ? m_nPlotYMax : pCurve->m_nYmax;
		}
		else
		{
			m_nCutXMax = (m_nCutXMax > pCurve->m_nXmax) ? m_nCutXMax : pCurve->m_nXmax;
			m_nCutYMax = (m_nCutYMax > pCurve->m_nYmax) ? m_nCutYMax : pCurve->m_nYmax;
		}
	}
}

void COnePage::OnDeleteSelect()
{
	int i;
	for(i = 0; i < m_CurveList.GetSize(); i++)
	{
		CCurve *pCurve = (CCurve *)m_CurveList.GetAt(i);
		if(pCurve->m_bIsSelected)
		{
			m_CurveList.RemoveAt(i);
			delete 	pCurve;
			i--;
		}
	}
}

void COnePage::OnResetSelectStatus()
{
	int i;
	for(i = 0; i < m_CurveList.GetSize(); i++)
	{
		CCurve *pCurve = (CCurve *)m_CurveList.GetAt(i);
		pCurve->m_bIsSelected = false;
	}
}

void COnePage::OnAdjSeq(int nType)
{
	CTypedPtrArray <CObArray,CCurve*> TAPen;
	CTypedPtrArray <CObArray,CCurve*> TABlade;
	CCurve *pCurve;
	int i;
	int nSize = m_CurveList.GetSize();
	
	for(i=0;i<nSize;i++)
	{
		pCurve = (CCurve*)m_CurveList.GetAt(i);
		if (pCurve->m_nPenNum<=1) //
		{
			TAPen.Add(pCurve);
		}
		else
		{
			TABlade.Add(pCurve);
		}
	}
	m_CurveList.RemoveAll();
	
	if (0==nType)
	{
		for (i=0;i<TABlade.GetSize();i++)
		{
			m_CurveList.Add(TABlade.GetAt(i));
		}
		
		for (i=0;i<TAPen.GetSize();i++)
		{
			m_CurveList.Add(TAPen.GetAt(i));
		}
	}
	else
	{
		for (i=0;i<TAPen.GetSize();i++)
		{
			m_CurveList.Add(TAPen.GetAt(i));
		}
		for (i=0;i<TABlade.GetSize();i++)
		{
			m_CurveList.Add(TABlade.GetAt(i));
		}
	}	
	TAPen.RemoveAll();
	TABlade.RemoveAll();
}

void COnePage::OnChangeDir()
{
	int i;
	CCurve* pCurve;
	for (i=0;i<m_CurveList.GetSize();i++)
	{
		pCurve = (CCurve*)m_CurveList.GetAt(i);
		if (pCurve->m_bIsSelected) //被选中了
		{
			pCurve->OnReverse();
		}
	}
}

void COnePage::OnAddSpCleanData()
{
	int i,j,nSizeCurve;
	CCurve *pCurve;
	nSizeCurve = m_CurveList.GetSize();
	if (gSet.getSpType() == 0) //HP45
	{
		for (i = 0; i<nSizeCurve; i++)
		{
			pCurve = (CCurve *)m_CurveList.GetAt(i);
			pCurve->OnMoveCurveTo(-25 * 40, 0); //图形右移2.5cm
		}
		for (i = 0; i<100; i++)
		{
			if (i % 25 == 0)
			{
				for (j = 0; j < 10; j++)
				{
					pCurve = new CCurve;
					pCurve->m_nPenNum = 1; //笔
					CPoint pt1(0, i * 40+j);
					CPoint pt2(25 * 40, i * 40+j);
					pCurve->m_pointList->Add(pt1);
					pCurve->m_pointList->Add(pt2);
					m_CurveList.Add(pCurve);
				}
			}
		}
	}
	else //IUT308
	{
		for (i = 0; i<nSizeCurve; i++)
		{
			pCurve = (CCurve *)m_CurveList.GetAt(i);
			pCurve->OnMoveCurveTo( (int)(-50.8 * 40), 0); //图形右移5.08cm
		}
		for (i = 0; i<100; i++)
		{
			if (i % 25 == 0)
			{
				for (j = 0; j < 10; j++)
				{
					pCurve = new CCurve;
					pCurve->m_nPenNum = 1; //笔
					CPoint pt1(0, i * 40+j);
					CPoint pt2((int)(50.8 * 40), i * 40 + j);
					pCurve->m_pointList->Add(pt1);
					pCurve->m_pointList->Add(pt2);
					m_CurveList.Add(pCurve);
				}
			}
		}
	}
}

void COnePage::OnRemoveAllData()
{
	CCurve* pCurve;
	while( m_CurveList.GetSize() > 0)
	{
		pCurve = (CCurve*)m_CurveList.GetAt(0);
		delete pCurve; 
		m_CurveList.RemoveAt(0);
	}
}

void COnePage::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		ar<<m_nCutXMax<<m_nCutYMax<<m_nPlotXMax<<m_nPlotYMax<<m_nXmax<<m_nXmin<<m_nYmax<<m_nYmin<<m_strFileName<<m_nOrgPageNum;
	}
	else
	{
		ar>>m_nCutXMax>>m_nCutYMax>>m_nPlotXMax>>m_nPlotYMax>>m_nXmax>>m_nXmin>>m_nYmax>>m_nYmin>>m_strFileName>>m_nOrgPageNum;
	}
	m_CurveList.Serialize(ar);
}

void COnePage::OnDelCutData()
{
	int i;
	int nSize;
	CCurve* pCurve;
	nSize = m_CurveList.GetSize();
	for (i=0;i<nSize;i++)
	{
		pCurve = m_CurveList.GetAt(i);
		if (pCurve->m_nPenNum >1)
		{
			delete pCurve;
			m_CurveList.RemoveAt(i);
			i--;
			nSize--;
		}
	}
}

void COnePage::OnDelPlotData()
{
	int i;
	int nSize;
	CCurve* pCurve;
	nSize = m_CurveList.GetSize();
	for (i=0;i<nSize;i++)
	{
		pCurve = m_CurveList.GetAt(i);
		if (pCurve->m_nPenNum <= 1)
		{
			delete pCurve;
			m_CurveList.RemoveAt(i);
			i--;
			nSize--;
		}
	}
}

void COnePage::DrawOnePage(CDC *pDC)
{
	int i;
	int j=1;
	CFont font;

	font.CreatePointFont(160,_T("Arial")); //参数含义1，字体大小，2字体类型，3字体颜色
	CFont* pOldFont = pDC->SelectObject(&font);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,50));

	for(i=0; i < m_CurveList.GetSize(); i++)
	{
		CCurve *pCurve = (CCurve *)m_CurveList.GetAt(i);
		pCurve->DrawCurve(pDC);
		if( (gSet.getDisplaySequence()) && (pCurve->m_nPenNum > 1) )
		{
			CPoint ptCenter;
			ptCenter.x = (pCurve->m_nXmax+pCurve->m_nXmin)/2;
			ptCenter.y = (pCurve->m_nYmax+pCurve->m_nYmin)/2;
			ptCenter = ptHpglToScr(ptCenter);
			
			CString str;
			str.Format("%02d",j++);
			pDC->TextOut(ptCenter.x,ptCenter.y,str);
		}
	}
	pDC->SelectObject(pOldFont);
}

void COnePage::OnSplitLongLine()
{
	CCurve *pCurve;
	int nCurveSum,nCurveIndex;
	nCurveSum = m_CurveList.GetSize();
	if (nCurveSum == 0)
		return;
	
	for (nCurveIndex=0; nCurveIndex<nCurveSum; nCurveIndex++)
	{
		pCurve = (CCurve *)m_CurveList.GetAt(nCurveIndex);
		pCurve->OnSpliteLine();
		if (pCurve->m_pointList->GetSize() == 0)
		{
			delete pCurve;
			m_CurveList.RemoveAt(nCurveIndex);
			nCurveSum --;
			nCurveIndex--;
		}
	}
	
	return;
}

void COnePage::OnSpliteCurveByAngle(double dAngle) //分割曲线
{
	CCurve* pCurve;
	CCurve* pNewCurve;
	double dAngle1,dAngle2,dDeltaAngle;
	CPoint pt0,pt1,pt2;
	int i,j;
	int nCurveSum,nCurveSize;
	nCurveSum = m_CurveList.GetSize();
	for (i=0;i<nCurveSum;i++)
	{
		pCurve = m_CurveList.GetAt(i);
		if (pCurve->m_nPenNum <= 1)
		{
			continue;
		}
		if (pCurve->m_bIsSelected == FALSE)
		{
			continue;
		}
		nCurveSize = pCurve->m_pointList->GetSize();
		for (j=1;j<nCurveSize-1;j++)
		{
			pt0 = pCurve->m_pointList->GetAt(j-1);
			pt1 = pCurve->m_pointList->GetAt(j);
			pt2 = pCurve->m_pointList->GetAt(j+1);
			dAngle1 = atan2( (double)(pt1.y-pt0.y) , (double)(pt1.x-pt0.x) );
			dAngle2 = atan2( (double)(pt2.y-pt1.y) , (double)(pt2.x-pt1.x) );
			
			dDeltaAngle = dAngle2-dAngle1;
			if (dDeltaAngle>PI)
			{
				dDeltaAngle = dDeltaAngle - 2.0*PI;
			}
			else if (dDeltaAngle <= -PI)
			{
				dDeltaAngle = dDeltaAngle + 2.0*PI;
			}
			
			if (fabs(dDeltaAngle) > dAngle)
			{
				pNewCurve = new CCurve;
				*pNewCurve = *pCurve;
				
				while( ( pNewCurve->m_pointList->GetSize() ) > (nCurveSize-j) )
				{
					pNewCurve->m_pointList->RemoveAt(0);
				}
				m_CurveList.InsertAt((i+1),pNewCurve);
				
				while( ( pCurve->m_pointList->GetSize() ) > (j+1) )
				{
					pCurve->m_pointList->RemoveAt(j+1);
				}
				nCurveSum++;
				break;
			}
		}
	}
}

void COnePage::OnSetOnlyPlot()
{
	int i;
	CCurve *pCurve;
	for (i=0;i<m_CurveList.GetSize();i++)
	{
		pCurve = (CCurve *)m_CurveList.GetAt(i);
		pCurve->m_nPenNum = 1;
	}
}

void COnePage::OnCheckPlotOnly()
{
	int i;
	CCurve* pCurve;
	int nPageSize = m_CurveList.GetSize();
	if (nPageSize == 0)
	{
		return;
	}
	
	for (i=0;i<nPageSize;i++)
	{
		pCurve = m_CurveList.GetAt(i);
		if (pCurve->m_nPenNum > 1 )
		{
			m_bIsPlotOnlyFile = FALSE;
			return;
		}
	}
	m_bIsPlotOnlyFile = TRUE;	
	return;	
}

void COnePage::OnSearchOutLine()
{
	OnCheckPlotOnly();
	if (!m_bIsPlotOnlyFile)
	{
		return;
	}
	int i;
	CCurve* pCurve;
	int nPageSize = m_CurveList.GetSize();
	if (nPageSize == 0)
	{
		return;
	}
	
	for (i=0;i<nPageSize;i++)
	{
		pCurve = m_CurveList.GetAt(i);
		if (pCurve->m_pointList->GetSize() < 4)
		{
			continue;
		}
		if( (pCurve->m_nXmax-pCurve->m_nXmin)<400 )
		{
			continue;
		}
		if( (pCurve->m_nYmax-pCurve->m_nYmin)<400 )
		{
			continue;
		}
		int nCurveSize = pCurve->m_pointList->GetSize();
		CPoint ptS,ptE;
		ptS = pCurve->m_pointList->GetAt(0);
		ptE = pCurve->m_pointList->GetAt(nCurveSize-1);
		if ( fabs((double)(ptS.x-ptE.x)) > 12 )
		{
			continue;
		}
		if ( fabs((double)(ptS.y-ptE.y)) > 12 )
		{
			continue;
		}
		pCurve->m_nPenNum = 4;
	}
	
	OnRemoveCurveNotOutline();
	return;
}


void COnePage::OnRemoveCurveNotOutline()
{
	CPoint pt10,pt11,pt12;
	CPoint pt20,pt21,pt22;
	CCurve* pCurve1;
	CCurve* pCurve2;
	int CurveSize1,CurveSize2;

	int i,j;
	int nPageSize = m_CurveList.GetSize();
	if (nPageSize<=2)
	{
		return;
	}
	
	for (i=0;i<nPageSize;i++)
	{
		pCurve1 = m_CurveList.GetAt(i);
		CurveSize1 = pCurve1->m_pointList->GetSize();
		if (CurveSize1 < 4)
		{
			continue;
		}

		pt10 = pCurve1->m_pointList->GetAt(0);
		pt11 = pCurve1->m_pointList->GetAt(1);
		pt12 = pCurve1->m_pointList->GetAt(2);
		if (pCurve1->m_nPenNum == 4)
		{
			for (j=0;j<nPageSize;j++)
			{
				pCurve2 = m_CurveList.GetAt(j);
				CurveSize2 = pCurve2->m_pointList->GetSize();
				
				if( (j==i) || (pCurve2->m_nPenNum != 4) || (CurveSize2<4) )
				{
					continue;
				}
				pt20 = pCurve2->m_pointList->GetAt(0);
				pt21 = pCurve2->m_pointList->GetAt(1);
				pt22 = pCurve2->m_pointList->GetAt(2);
				if( pCurve1->PtInPolygon(pt20) && pCurve1->PtInPolygon(pt21) && pCurve1->PtInPolygon(pt22) )
				{
					pCurve2->m_nPenNum = 1;
				}
				
				if( pCurve2->PtInPolygon(pt10) && pCurve2->PtInPolygon(pt11) && pCurve2->PtInPolygon(pt12) )
				{
					pCurve1->m_nPenNum = 1;
				}
				
			}
		}
	}
}
