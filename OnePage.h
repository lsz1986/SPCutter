// OnePage.h: interface for the COnePage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONEPAGEDOC_H__C8788939_7A10_4A56_A62A_3652E43B688D__INCLUDED_)
#define AFX_ONEPAGEDOC_H__C8788939_7A10_4A56_A62A_3652E43B688D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Curve.h"

class COnePage : public CObject  
{
public:
	COnePage();
	DECLARE_SERIAL(COnePage)
	virtual ~COnePage();

public:
	CTypedPtrArray <CObArray,CCurve*> m_CurveList;
	CString m_strFileName;
	UINT m_nOrgPageNum;

	int m_nXmax;
	int m_nXmin;
	int m_nYmax;
	int m_nYmin;

	int m_nPlotXMax;
	int m_nPlotYMax;
	int m_nCutXMax;
	int m_nCutYMax;

	BOOL m_bIsPlotOnlyFile;

public:
	void OnRemoveCurveNotOutline();
	void OnCheckPlotOnly();
	void OnSearchOutLine();
	void OnSetOnlyPlot();
	void OnSpliteCurveByAngle(double dAngle);
	void OnSplitLongLine();
	void OnDelPlotData();
	void OnDelCutData();
	void operator=(COnePage &a);
	void OnAddSpCleanData();
	void OnRemoveInvalidPoints();
	void OnRemoveAllData();
	void OnChangeDir();
	void OnAdjSeq(int nType);
	void OnResetSelectStatus();
	void OnDeleteSelect();
	void OnPageAngleAdjust();
	void OnGetSizePlotCut();
	void OnMoveToLeft();
	void OnMoveToBottom();
	void OnAddYMargin(int YDistHpgl);
	void DrawOnePage(CDC* pDC);
	void OnGetPageMaxMin();
	void OnCheckPageData();
	virtual void Serialize(CArchive& ar);
};

#endif // !defined(AFX_ONEPAGEDOC_H__C8788939_7A10_4A56_A62A_3652E43B688D__INCLUDED_)
