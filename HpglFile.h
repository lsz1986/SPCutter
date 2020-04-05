// HpglFile.h: interface for the CHpglFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HPGLFILE_H__8CB4A146_F567_4924_BDC1_F3FA4BBDDE77__INCLUDED_)
#define AFX_HPGLFILE_H__8CB4A146_F567_4924_BDC1_F3FA4BBDDE77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Global.h"
#include "Charactor.h"
#include "SpCutterDoc.h"
#include "OnePage.h"
#include "Curve.h"

#define NONE_TYPE			10
#define DIGIT_TYPE			11
#define STRING_TYPE			12
#define ESC_TYPE			13
#define DT_TYPE				14

//ͼԪ����
#define PLOT_CMD_PD		20  //�߶Σ���1 X1��Y1����2 X2��Y2,...
#define PLOT_CMD_PU		21  //�߶Σ���1 X1��Y1����2 X2��Y2,...

#define PLOT_CMD_PG			22
#define PLOT_CMD_LT			23 //����
#define PLOT_CMD_SP			24

#define	PROCESS_MNEMONIC	30//����
#define PROCESS_PARAMETER	31//����
#define PROCESS_FIND		32//������

class CDPoint  
{
public:
	double x;
	double y;
};

class CPlotCmd //һ�λ�ͼָ��
{
public:
	int m_nType;
	CArray <int,int> m_anData;
};

class CInstruct
{
public:
	char m_cName[3];
	CArray<double,double> m_adPara;
};

class CHpglFile  
{
public:
	CHpglFile();
	virtual ~CHpglFile();

public:
	CPoint CPToLP(CPoint ptCP, int nHeight, CPoint ptPointLU, double dSin, double dCos, double dScale);
	CPoint GetNextCoodinate(WORD wDirection, WORD wLength, CPoint ptPoint);
	void WriteTextData(BOOL bFirst, long x, long y);
	void LineTo(long x, long y);
	void MoveTo(long x, long y);
	void Text2LineInit(void);
	void PlotChar(CPoint ptPointLT,BYTE *pbyData,WORD wBytes,int nLeft,int nDown,int nFontScale,double dTextAngle);
	void Text2Line(CPoint dp,LPCTSTR lpszString, int nCount);
	void CalcTextStartPoint(CDPoint *dp, int strLen);
	void InitHPGL();

	void RemoveBuffer();
	int GetParameterType(char cName[]);
	void Instruct2PlotCmd(CInstruct *pInstruct);
	int OpenPltFile();
	void HpglCmdToDoc(CSpCutterDoc *pDoc);

public:
	CString m_strPathAndName; //������·�����ļ���
	CString m_strName; //������ʾ
	CPtrArray m_pCmdList_ORG; //ԭʼ����

public:
	int m_nLineType;
	CPoint m_dpCurrent;//��ǰ����
	unsigned char m_cTerminator;//��־�ս��
	unsigned char m_cTerminatorMode;//ģʽ
	CString m_strText;//�ַ�
	
	double m_dTextAngle;//�ַ�����
	double m_dTextHeight;//�ַ��߶�
	double m_dTextWidth;//�ַ����
	int m_nTextPosition;//�ַ����ԭ���λ��
	BOOL m_bPenDown;//���Ƿ�����
	
private:
	CArray <CCharactor,CCharactor> m_aChinese_char;
	CArray <CCharactor,CCharactor> m_aEnglish_char;
	int m_nInternalLeading_E,m_nHeight_E,m_nDescent_E; //m_nHeight_E��windows�������Ascent-InternalLeading
	int m_nHeight_C,m_nWidth_C;
	CPoint m_ptCurrentPosition;   //��ǰλ��(����)
	CPoint m_ptPrevPosition;      //ǰһλ��(����)

};
#endif // !defined(AFX_HPGLFILE_H__8CB4A146_F567_4924_BDC1_F3FA4BBDDE77__INCLUDED_)
