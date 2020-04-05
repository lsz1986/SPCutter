// Curve.h: interface for the CCurve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVE_H__CB6506A9_3D34_429C_B30F_83B9CC32A154__INCLUDED_)
#define AFX_CURVE_H__CB6506A9_3D34_429C_B30F_83B9CC32A154__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCurve : public CObject  
{
public:
	CCurve();
	DECLARE_SERIAL(CCurve)
	virtual ~CCurve();

public:
	CArray <CPoint,CPoint> *m_pointList;

public:
    BOOL m_bIsSelected;
	int m_nPenNum;
	int m_nXmin;
	int m_nXmax;
	int m_nYmin;
	int m_nYmax;

public:
	BOOL PtInPolygon(CPoint pt);
	void operator=(CCurve &a);
	void OnMoveCurveTo(int nStartX,int nStartY);
	void OnAngleAdjust(double dAngle,int iMaxX);
	void OnToCutData();
	void GetCurveMaxMin();

	void OnReverse(); //改变方向
	void OnCombineLine();
	void OnSpliteLine();
	void DrawCurve(CDC *pDC);
	BOOL IsInRgn(CPoint point);
	BOOL CurveInRect(CRect rect);

	virtual void Serialize(CArchive& ar);
};

#endif // !defined(AFX_CURVE_H__CB6506A9_3D34_429C_B30F_83B9CC32A154__INCLUDED_)
