// CutPlotterDoc.cpp : implementation of the CSpCutterDoc class
//

#include "stdafx.h"
#include "SpCutter.h"
#include "Global.h"
#include "SpCutterDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpCutterDoc

IMPLEMENT_DYNCREATE(CSpCutterDoc, CDocument)

BEGIN_MESSAGE_MAP(CSpCutterDoc, CDocument)
	//{{AFX_MSG_MAP(CSpCutterDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpCutterDoc construction/destruction

CSpCutterDoc::CSpCutterDoc()
{
	// TODO: add one-time construction code here

}

CSpCutterDoc::~CSpCutterDoc()
{
	OnRemoveDocAllData();
}

void CSpCutterDoc::OnRemoveDocAllData()
{
	COnePage* pPage;
	while(m_ArrayPage.GetSize() > 0)
	{
		pPage = (COnePage*)m_ArrayPage.GetAt(0);
		delete pPage;
		m_ArrayPage.RemoveAt(0);
	}
}

void CSpCutterDoc::OnRemoveOnePageData(int nPage)
{
	COnePage* pPage;
	if( nPage <= (m_ArrayPage.GetSize()-1) )
	{
		pPage = (COnePage*)m_ArrayPage.GetAt(nPage);
		delete pPage;
		m_ArrayPage.RemoveAt(nPage);
	}
}

void CSpCutterDoc::OnSaveAsPlt(CString strFileName)
{
	COnePage* pPage;
	int nPage;
	int i,j;
	CFile pltFile;
	CCurve *pCurve;
	int nPenNum;
	CString str,str1;
	pltFile.Open(strFileName,CFile::modeCreate|CFile::modeReadWrite|CFile::typeBinary);
	
	for( nPage=0; nPage < m_ArrayPage.GetSize(); nPage++ )
	{
		pPage = (COnePage*)m_ArrayPage.GetAt(nPage);
		nPenNum = 1;
		for (i=0;i<pPage->m_CurveList.GetSize();i++)
		{
			pCurve = (CCurve *)pPage->m_CurveList.GetAt(i);
			if ((pCurve->m_nPenNum != nPenNum)||(i==0))
			{
				nPenNum = pCurve->m_nPenNum; 
				str.Format("SP%d;",nPenNum);
				pltFile.Write(str.GetBuffer(0),str.GetLength());
			}
			int nPLSize = pCurve->m_pointList->GetSize();
			if (nPLSize>0)
			{
				str.Format("PU%d,%d;PD",
					(int)((double)pCurve->m_pointList->GetAt(0).x * gSet.getPltSaveScaleX()/1000.0),
					(int)((double)pCurve->m_pointList->GetAt(0).y * gSet.getPltSaveScaleY()/1000.0) );
				for (j=0;j<nPLSize;j++)
				{
					str1.Format("%d,%d,",
						(int)((double)pCurve->m_pointList->GetAt(j).x * gSet.getPltSaveScaleX()/1000.0),
						(int)((double)pCurve->m_pointList->GetAt(j).y * gSet.getPltSaveScaleY()/1000.0) );
					str+=str1;
				}
				pltFile.Write(str.GetBuffer(0),str.GetLength()-1);
				str = ";";
				pltFile.Write(str.GetBuffer(0),1);
			}
		}
		str = "PG;";
		pltFile.Write(str.GetBuffer(0),3);
	}
	pltFile.Close();
}


BOOL CSpCutterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

void CSpCutterDoc::SpliteLastPage(int nPageLenHpgl)
{
	COnePage* pOldPage;
	CCurve* pCurve;
	int i,j;
	CPoint pt;
	int nCurveSum;
	int nPlSize;
	int nPageSum = m_ArrayPage.GetSize();
	if ( nPageSum == 0)
		return;
	BOOL bCurveIsInZone;

	int nNewPageNum=1;
	while(1)
	{
		pOldPage = (m_ArrayPage.GetAt(nPageSum-1)); //获取最后一页
		pOldPage->OnGetPageMaxMin();
		if (pOldPage->m_nXmax <= nPageLenHpgl)
		{
			break;
		}

		COnePage *pNewPage = new COnePage;
		pNewPage->m_strFileName = pOldPage->m_strFileName;
		pNewPage->m_nOrgPageNum = nNewPageNum++;
		m_ArrayPage.InsertAt(nPageSum-1,pNewPage);
		nPageSum++;

		nCurveSum = pOldPage->m_CurveList.GetSize(); 
		for (i=0;i<nCurveSum;i++)
		{
			pCurve = pOldPage->m_CurveList.GetAt(i);
			nPlSize = pCurve->m_pointList->GetSize();
			bCurveIsInZone = TRUE;
			for (j=0;j<nPlSize;j++)
			{
				pt = pCurve->m_pointList->GetAt(j);
				if (pt.x > nPageLenHpgl)
				{
					bCurveIsInZone = FALSE;
					break;
				}
			}
			if (bCurveIsInZone)
			{
				CCurve* pNewCurve =new CCurve;
				*pNewCurve = *pCurve;
				pNewPage->m_CurveList.Add(pNewCurve);

				delete pCurve;
				pOldPage->m_CurveList.RemoveAt(i);
				i--;
				nCurveSum--;
			}
		}
		pNewPage->OnGetPageMaxMin();

		nCurveSum = pOldPage->m_CurveList.GetSize(); 
		for (i=0;i<nCurveSum;i++)
		{
			pCurve = pOldPage->m_CurveList.GetAt(i);
			pCurve->OnMoveCurveTo(nPageLenHpgl,0);
		}
	}
	pOldPage->m_nOrgPageNum = nNewPageNum;
}

void CSpCutterDoc::CheckDocData()
{
	COnePage* pPage;
	int nPageSum,nPageIndex;
	
	nPageSum = m_ArrayPage.GetSize();
	if ( nPageSum == 0)
		return;
	for (nPageIndex=0;nPageIndex<nPageSum;nPageIndex++)
	{
		pPage = m_ArrayPage.GetAt(nPageIndex);
		pPage->OnRemoveInvalidPoints();
		pPage->OnCheckPageData();
		pPage->OnGetPageMaxMin();
		if (gSet.getAutoMoveToLeft())
		{
			pPage->OnMoveToLeft();
		}
		if (gSet.getAutoMoveToBottom())
		{
			pPage->OnMoveToBottom();
		}

		pPage->OnGetSizePlotCut();
		
		if (pPage->m_CurveList.GetSize() == 0)
		{
			delete pPage;
			m_ArrayPage.RemoveAt(nPageIndex);
			nPageIndex--;
			nPageSum--;
		}
		else if (gSet.getFindOutLine())
		{
			pPage->OnSearchOutLine();
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// CSpCutterDoc serialization

void CSpCutterDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
	m_ArrayPage.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CSpCutterDoc diagnostics

#ifdef _DEBUG
void CSpCutterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSpCutterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpCutterDoc commands

