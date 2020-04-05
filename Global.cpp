#include "StdAfx.h"
#include "Global.h"

CSetMac gMacSet; //全局变量
CSetDisp gDispSet;
ST_CNC_SPD_LIMIT gSpdLimit;

CMyReg gMyReg;

ST_MAC_PARA gPara;
UNION_MAC_PARA gTempPara;

u8 gSysState;
u8 gWorkType; //工作类型

STRUCT_REG_INFO gRegInfo;

CString strZHKJ="ZHKJ";

BOOL g_bParaRead = FALSE;
COnePage gWorkingPage;
CMyUSB gUSB;

long IntRound(double x)
{
    double d;
    long lResult;
	
    if (x < 0)
        d = x - 0.5;
    else
        d = x + 0.5;
    lResult = (long)d;
    return lResult;
}

BOOL IsAlpha(char ch)
{
    if(ch >= 'a' && ch <= 'z') return TRUE;
    if(ch >= 'A' && ch <= 'Z') return TRUE;
    return FALSE;
}

BOOL IsDigit(char ch)
{
    if(ch >= '0' && ch <= '9') return TRUE;
    if(ch == '.') return TRUE;
    if(ch == '-' || ch == '+') return TRUE;
    return FALSE;
}

int ftoi(double f)
{
    int k;
    if(f > 5e+75 || f < -5e+75) return 1;
    if(f >= 0)
    {
        f += 0.5;
        k = (int)f;
    }
    else
    {
        f -= 0.5;
        k = (int)f;
        if(k == f) k++; // ftoi(0.5)=1,ftoi(-0.5)=0
    }
    return k;
}

int ReadMacPara()
{
	g_bParaRead = FALSE;
	if(0 == gUSB.OnParaRead()) //参数读取成功
	{
		g_bParaRead = TRUE;
		gPara = gTempPara.stBuff;
		gParaTogSet();
		return 0;
	}
	return -1;
}

void gParaTogSet()
{
//------------------------------高级参数-----------------------------		
	gMacSet.setPPMMX(gPara.m_dPPMM_X);
	gMacSet.setPPMMY(gPara.m_dPPMM_Y);
	gMacSet.setMacSizeX(gPara.m_sMacSizeXmm);
	gMacSet.setMacSizeY(gPara.m_sMacSizeYmm);
	gMacSet.setSpAccStep(gPara.m_sSpAccStep);
	gMacSet.setSpdCut(gPara.m_cSpdCut);
	gMacSet.setSpdMove(gPara.m_cSpdMove);
//------------------------------高级参数-----------------------------		

//------------------------------普通参数-----------------------------		
	gMacSet.setPwmKStart(gPara.m_cPwmKStart);
	gMacSet.setPwmKWork(gPara.m_cPwmKWork);
	
	gMacSet.setCutEndPosYmm(gPara.m_sCutEndPosYmm);
	gMacSet.setAngleAdjust(gPara.m_cAngleAdjust);
	gMacSet.setKPDistX(gPara.m_cKPDistX);
	gMacSet.setKPDistY(gPara.m_cKPDistY);
	
	gMacSet.set10000X(gPara.m_s10000X);
	gMacSet.set10000Y(gPara.m_s10000Y);
	
	gMacSet.setSP1DOTLR(gPara.m_cSp1DotLR);
	gMacSet.setSP2DOTLR(gPara.m_cSp2DotLR);
	
	gMacSet.setJobEndHeadPos(gPara.m_cJobEndHeadPos);
	gMacSet.setJobEndPosXmm(gPara.m_sJobEndPosXmm);
	gMacSet.setJobEndPosYmm(gPara.m_sJobEndPosYmm);

	gMacSet.setSpStat(gPara.m_cSpStat);
	gMacSet.setSpType(gPara.m_cSpType); //设置墨盒类型

	gMacSet.setSpEX(gPara.m_cSpEX); //喷头重叠
	gMacSet.setSp12EY(gPara.m_cSp12Y); //喷头间距
	gMacSet.setJamDetect(gPara.m_cJamDetect); //双向打印
	gMacSet.setSpdDownType(gPara.m_cLowSpdMode);
	
	gMacSet.setSpDDY(gPara.m_cYLRError); //双向误差
	gMacSet.setPPDOTY(gPara.m_cPPDOT_Y); //喷墨间隔脉冲
	gMacSet.setLedLan(gPara.m_cLedLan);
	return;
}

void gSetTogPara()
{
//double-------------------------------------------------------
	gPara.m_dPPMM_X = gMacSet.getPPMMX();
	gPara.m_dPPMM_Y = gMacSet.getPPMMY();
//unsigned short------------------------------------------------
	gPara.m_s10000X = gMacSet.get10000X();
	gPara.m_s10000Y = gMacSet.get10000Y();
	gPara.m_sSpAccStep = gMacSet.getSpAccStep();
	gPara.m_sMacSizeXmm = gMacSet.getMacSizeX();
	gPara.m_sMacSizeYmm = gMacSet.getMacSizeY();

	gPara.m_sCutEndPosYmm = gMacSet.getCutEndPosYmm();
	gPara.m_sJobEndPosXmm = gMacSet.getJobEndPosXmm();
	gPara.m_sJobEndPosYmm = gMacSet.getJobEndPosYmm();

//unsigned char 10byte------------------------------------------
	gPara.m_cKPDistX = gMacSet.getKPDistX();
	gPara.m_cKPDistY = gMacSet.getKPDistY();

	gPara.m_cPwmKStart = gMacSet.getPwmKStart();
	gPara.m_cPwmKWork =  gMacSet.getPwmKWork();

	gPara.m_cSp12Y = gMacSet.getSp12EY(); //喷头间距
	gPara.m_cJamDetect = gMacSet.getJamDetect(); //喷墨时卡纸检测
	gPara.m_cLowSpdMode = gMacSet.getSpdDownType(); //慢速模式

	gPara.m_cSp1DotLR = gMacSet.getSP1DOTLR();
	gPara.m_cSp2DotLR = gMacSet.getSP2DOTLR();
//unsigned char 10byte------------------------------------------
	gPara.m_cSpdMove = gMacSet.getSpdMove();
	gPara.m_cSpdCut = gMacSet.getSpdCut();
	gPara.m_cYLRError = gMacSet.getSpDDY(); //双向误差
	gPara.m_cSpStat = gMacSet.getSpStat();
	gPara.m_cSpType =  gMacSet.getSpType(); //墨盒类型 

	gPara.m_cSpEX = gMacSet.getSpEX(); //喷头重叠
	gPara.m_cAngleAdjust = gMacSet.getAngleAdjust();
	gPara.m_cJobEndHeadPos = gMacSet.getJobEndHeadPos();
	gPara.m_cPPDOT_Y = 18;
	gPara.m_cLedLan = gMacSet.getLedLan();
	return;
}

void WritePlotPara()
{
	if (FALSE == g_bParaRead)
	{
		return;
	}
	gSetTogPara();
	gTempPara.stBuff = gPara;
	if(0 != gUSB.OnParaWrite() )
	{
		if (gDispSet.getLanguage() == 0) {
			AfxMessageBox("保存参数失败!");
		}else {
			AfxMessageBox("Failed To Save Parameter!");
		}
	}
}

void delayus(int num)
{
	LARGE_INTEGER litmp;
	LONGLONG QPart1,QPart2;
	double dfMinus, dfFreq, dfTim;
	QueryPerformanceFrequency(&litmp);
	dfFreq = (double)litmp.QuadPart;// 获得计数器的时钟频率
	QueryPerformanceCounter(&litmp);
	QPart1 = litmp.QuadPart;// 获得初始值
	do
	{
		QueryPerformanceCounter(&litmp);
		QPart2 = litmp.QuadPart;//获得中止值
		dfMinus = (double)(QPart2-QPart1);
		dfTim = dfMinus / dfFreq;// 获得对应的时间值，单位为秒
	}while(dfTim < 0.000001*num);
}

//9位整数 最大 23 27 5E 62
const UINT YHZIntArray[16] = {
	214072011,/*0*/
	180416531,/*1*/
	188092317,/*2*/
	122988619,/*3*/
	142797956,/*4*/
	366543210,/*5*/
	305219805,/*6*/
	111022060,/*7*/
	151032792,/*8*/
	187654328,/*9*/
	169227610,/*10*/
	168688886,/*11*/
	121314872,/*12*/
	151327678,/*13*/
	141526598,/*14*/
	589782626/*15*/
};

CPoint ptHpglToScr(CPoint ptHpgl)
{
	CPoint ptScr;
	ptScr.x = (int)(ptHpgl.x*gDispSet.getDispScale())+DISP_START_X - gDispSet.getDispStartX();
	ptScr.y = (int)(gDispSet.getScrYPixel()-ptHpgl.y*gDispSet.getDispScale())-DISP_START_Y - gDispSet.getDispStartY();
	return ptScr;
}

void setSpdLimit(int nLowSpdMode)
{
	switch(nLowSpdMode)
	{
		case 1:
		gSpdLimit.m_spdMax = 2800;
		gSpdLimit.m_spdLV1 = 200;
		gSpdLimit.m_spdLV2_R002 = 250;
		gSpdLimit.m_spdLV3_R004 = 300;
		gSpdLimit.m_spdLV4_R005 = 350;
		gSpdLimit.m_spdLV5_R010 = 400;
		gSpdLimit.m_spdLV6_R020 = 450;
		gSpdLimit.m_spdLV7_R050 = 500;
		gSpdLimit.m_spdLV8_R100 = 600;
		gSpdLimit.m_spdLV9_R150 = 800;
		gSpdLimit.m_spdLV10_R200 = 1000;
		gSpdLimit.m_spdLV11_R300 = 1200;
		break;

		case 2:
 		gSpdLimit.m_spdMax = 1000;
 		gSpdLimit.m_spdLV1 = 150;
 		gSpdLimit.m_spdLV2_R002 = 160;
 		gSpdLimit.m_spdLV3_R004 = 200;
 		gSpdLimit.m_spdLV4_R005 = 240;
 		gSpdLimit.m_spdLV5_R010 = 280;
 		gSpdLimit.m_spdLV6_R020 = 320;
 		gSpdLimit.m_spdLV7_R050 = 360;
 		gSpdLimit.m_spdLV8_R100 = 400;
 		gSpdLimit.m_spdLV9_R150 = 450;
 		gSpdLimit.m_spdLV10_R200 = 500;
 		gSpdLimit.m_spdLV11_R300 = 600;
		break;

		case 3:
		gSpdLimit.m_spdMax = 360;
		gSpdLimit.m_spdLV1 = 120;
		gSpdLimit.m_spdLV2_R002 = 140;
		gSpdLimit.m_spdLV3_R004 = 160;
		gSpdLimit.m_spdLV4_R005 = 180;
		gSpdLimit.m_spdLV5_R010 = 200;
		gSpdLimit.m_spdLV6_R020 = 220;
		gSpdLimit.m_spdLV7_R050 = 240;
		gSpdLimit.m_spdLV8_R100 = 260;
		gSpdLimit.m_spdLV9_R150 = 280;
		gSpdLimit.m_spdLV10_R200 = 300;
 		gSpdLimit.m_spdLV11_R300 = 320;
		break;
	
		default:
		gSpdLimit.m_spdMax = 4000;
		gSpdLimit.m_spdLV1 = 300;
		gSpdLimit.m_spdLV2_R002 = 400;
		gSpdLimit.m_spdLV3_R004 = 480;
		gSpdLimit.m_spdLV4_R005 = 560;
		gSpdLimit.m_spdLV5_R010 = 640;
		gSpdLimit.m_spdLV6_R020 = 720;
		gSpdLimit.m_spdLV7_R050 = 800;
		gSpdLimit.m_spdLV8_R100 = 1000;
		gSpdLimit.m_spdLV9_R150 = 1200;
		gSpdLimit.m_spdLV10_R200 = 1400;
		gSpdLimit.m_spdLV11_R300 = 1600;
		break;
	}
	return;
}