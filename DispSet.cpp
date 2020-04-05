// CSetDisp.cpp: implementation of the CDispSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "spcutter.h"
#include "DispSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSetDisp::CSetDisp()
{
	m_nDispSizeYmm = 900;
	m_nScrYPixel= 400;
	m_dDispScale = 0.01;
	m_nDispStartX = 0;
	m_nDispStartY = 0;
}

CSetDisp::~CSetDisp()
{

}
