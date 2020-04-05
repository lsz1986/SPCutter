// CSetDisp.h: interface for the CDispSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISPSET_H__C7173F69_FE30_44D3_98D6_C60FF094036B__INCLUDED_)
#define AFX_DISPSET_H__C7173F69_FE30_44D3_98D6_C60FF094036B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSetDisp  
{
public:
	CSetDisp();
	virtual ~CSetDisp();

public:
	COLORREF m_clrBG; //±³¾°ÑÕÉ«
	COLORREF m_clrFR; //±ß¿òµÄÑÕÉ«
	COLORREF m_clrPen; //±ÊµÄÑÕÉ«
	COLORREF m_clrK1; //°ëµ¶ÑÕÉ«	
	
public:
	inline void setClrBG(COLORREF clr){ m_clrBG = clr;};
	inline void setClrFR(COLORREF clr){ m_clrFR = clr;};
	inline void setClrCut(COLORREF clr){ m_clrK1 = clr;};	
	inline void setClrPen(COLORREF clr){ m_clrPen = clr;};
	
public:
	inline COLORREF getClrBG(){ return m_clrBG;};
	inline COLORREF getClrFR(){ return m_clrFR;};
	inline COLORREF getClrCut(){ return m_clrK1;};	
	inline COLORREF getClrPen(){ return m_clrPen;};
	
	inline void setDispStartX(int n){m_nDispStartX = n;};
	inline int getDispStartX(){return m_nDispStartX;};
	inline void setDispStartY(int n){m_nDispStartY = n;};
	inline int getDispStartY(){return m_nDispStartY;};

	inline void setScrXPixel(int n){m_nScrXPixel = n;};
	inline int getScrXPixel(){return m_nScrXPixel;};

	inline void setScrYPixel(int n){m_nScrYPixel = n;};
	inline int getScrYPixel(){return m_nScrYPixel;};	

	inline void setDispScale(double d){m_dDispScale = d;};
	inline double getDispScale(){return m_dDispScale;};

	inline void setDispSizeX(int n){m_nDispSizeXmm = n;};
	inline int getDispSizeX() { return m_nDispSizeXmm; };

	inline void setDispSizeY(int n){m_nDispSizeYmm = n;};
	inline int getDispSizeY() { return m_nDispSizeYmm; };

	inline void setLanguage(int n){m_nLanguage = n;};
	inline int getLanguage() { return m_nLanguage; };
	
private:
	int m_nScrXPixel;
	int m_nScrYPixel;
	int m_nDispStartX;
	int m_nDispStartY;
	double m_dDispScale;

	int m_nDispSizeXmm;
	int m_nDispSizeYmm;
	int m_nLanguage;
};

#endif // !defined(AFX_DISPSET_H__C7173F69_FE30_44D3_98D6_C60FF094036B__INCLUDED_)
