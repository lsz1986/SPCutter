#include "StdAfx.h"
#include "Global.h"

CSettings gSet; //全局变量
CSetDisp gDispSet;

CMyReg gMyReg;

ST_MAC_PARA gPara;

u8 gSysState;
u8 gWorkType; //工作类型

STRUCT_REG_INFO gRegInfo;
u32 gMcuCode;
CString strZHKJ="ZHKJ";

BOOL g_bParaRead = FALSE;
COnePage gWorkingPage;
CMyCommu gCommu;
CMyUSB gMyUSB;
CMyEth gMyEth;

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
	int rev;
	u8 sbuf[64];
	u8 rbuf[64];
	sbuf[0] = MAC_PARA_SIZE; //YHZ注，这个参数实际没有用到，仅仅为了区分CMD0
	rev = gCommu.OnCmd1(CMD1_PARA_READ, 1, sbuf, MAC_PARA_SIZE, rbuf);
	if (0 == rev) //参数读取成功
	{
		g_bParaRead = TRUE;

		gPara = *((ST_MAC_PARA*)(&rbuf[0]));
		gParaTogSet();
		return 0;
	}
	return -1;
}

void gParaTogSet()
{
//------------------------------高级参数-----------------------------		
	gSet.setPPMMX(gPara.m_dPPMM_X);
	gSet.setPPMMY(gPara.m_dPPMM_Y);
	gSet.setMachineIpAddr(gPara.m_nW5500Ip);

	gSet.setMacSizeX(gPara.m_sMacSizeXmm);
	gSet.setMacSizeY(gPara.m_sMacSizeYmm);
	gSet.setSpAccDistmm(gPara.m_cSpAccDistMm);
	gSet.setSpdCut(gPara.m_cSpdCut);
	gSet.setSpdMove(gPara.m_cSpdMove);
	gSet.setSecLen(gPara.m_cSecLen);
//------------------------------高级参数-----------------------------		

//------------------------------普通参数-----------------------------		
	gSet.setPwmKStart(gPara.m_cPwmKStart);
	gSet.setPwmKWork(gPara.m_cPwmKWork);
	
	gSet.setCutPaperStartYmm(gPara.m_sCutPaperStartYmm);
	gSet.setCutPaperEndYmm(gPara.m_sCutPaperEndYmm);
	gSet.setAngleAdjust(gPara.m_cAngleAdjust);
	gSet.setKPDistX(gPara.m_cKPDistX);
	gSet.setKPDistY(gPara.m_cKPDistY);
	
	gSet.set10000X(gPara.m_s10000X);
	gSet.set10000Y(gPara.m_s10000Y);
	
	gSet.setSP1DOTLR(gPara.m_cSp1DotLR);
	gSet.setSP2DOTLR(gPara.m_cSp2DotLR);
	
	gSet.setJobEndHeadPos(gPara.m_cJobEndHeadPos);
	gSet.setJobEndPosXmm(gPara.m_sJobEndPosXmm);
	gSet.setJobEndPosYmm(gPara.m_sJobEndPosYmm);

	gSet.setSpStat(gPara.m_cSpStat);
	gSet.setSpType(gPara.m_cSpType); //设置墨盒类型

	gSet.setSpEX(gPara.m_cSpEX); //喷头重叠
	gSet.setSp12EY(gPara.m_cSp12Y); //喷头间距
	gSet.setJamDetect(gPara.m_cJamDetect); //双向打印

	gSet.setSpDDY(gPara.m_cYLRError); //双向误差
	gSet.setPPDOTY(gPara.m_cPPDOT_Y); //喷墨间隔脉冲
	gSet.setLedLan(gPara.m_cLedLan);
	return;
}

void gSetTogPara()
{
//double-------------------------------------------------------
	gPara.m_dPPMM_X = gSet.getPPMMX();
	gPara.m_dPPMM_Y = gSet.getPPMMY();

//short-4bytes---------------------------
	gPara.m_nW5500Ip = gSet.getMachineIpAddr();

//unsigned short------------------------------------------------
	gPara.m_s10000X = gSet.get10000X();
	gPara.m_s10000Y = gSet.get10000Y();
	gPara.m_cSpAccDistMm = gSet.getSpAccDistmm();
	gPara.m_sMacSizeXmm = gSet.getMacSizeX();
	gPara.m_sMacSizeYmm = gSet.getMacSizeY();

	gPara.m_sCutPaperStartYmm = gSet.getCutPaperStartYmm();
	gPara.m_sCutPaperEndYmm = gSet.getCutPaperEndYmm();

	gPara.m_sJobEndPosXmm = gSet.getJobEndPosXmm();
	gPara.m_sJobEndPosYmm = gSet.getJobEndPosYmm();

//unsigned char 10byte------------------------------------------
	gPara.m_cKPDistX = gSet.getKPDistX();
	gPara.m_cKPDistY = gSet.getKPDistY();

	gPara.m_cPwmKStart = gSet.getPwmKStart();
	gPara.m_cPwmKWork =  gSet.getPwmKWork();

	gPara.m_cSp12Y = gSet.getSp12EY(); //喷头间距
	gPara.m_cJamDetect = gSet.getJamDetect(); //喷墨时卡纸检测

	gPara.m_cSp1DotLR = gSet.getSP1DOTLR();
	gPara.m_cSp2DotLR = gSet.getSP2DOTLR();
//unsigned char 10byte------------------------------------------
	gPara.m_cSpdMove = gSet.getSpdMove();
	gPara.m_cSpdCut = gSet.getSpdCut();
	gPara.m_cYLRError = gSet.getSpDDY(); //双向误差
	gPara.m_cSpStat = gSet.getSpStat();
	gPara.m_cSpType =  gSet.getSpType(); //墨盒类型 

	gPara.m_cSpEX = gSet.getSpEX(); //喷头重叠
	gPara.m_cAngleAdjust = gSet.getAngleAdjust();
	gPara.m_cJobEndHeadPos = gSet.getJobEndHeadPos();
	gPara.m_cPPDOT_Y = 18;
	gPara.m_cSecLen = gSet.getSecLen();
	gPara.m_cLedLan = gSet.getLedLan();
	return;
}

void WritePlotPara()
{
	int rev;
	u8 sbuf[64];
	u8 rbuf[64];
	gSetTogPara();

	*((ST_MAC_PARA*)(&sbuf[0])) = gPara;
	rev = gCommu.OnCmd1(CMD1_PARA_WRITE, MAC_PARA_SIZE, sbuf, 1, rbuf);
	if (0 != rev)
	{
		if (gDispSet.getLanguage() == 0)
		{
			AfxMessageBox("保存参数失败!");
		}
		else
		{
			AfxMessageBox("Failed To Save Parameter!");
		}
	}
	Sleep(300);
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
	ptScr.x = (int)( ptHpgl.x*gDispSet.getDispScale()+DISP_START_X - gDispSet.getDispStartX() );
	ptScr.y = (int)( gDispSet.getScrYPixel()-ptHpgl.y*gDispSet.getDispScale()-DISP_START_Y - gDispSet.getDispStartY() );
	return ptScr;
}

CPoint ptScrToHpgl(CPoint ptScr)
{
	CPoint ptHpgl;
	ptHpgl.x = (int)( (ptScr.x + gDispSet.getDispStartX() - DISP_START_X) / gDispSet.getDispScale());
	ptHpgl.y = (int)( (gDispSet.getScrYPixel() - ptScr.y - gDispSet.getDispStartY() - DISP_START_Y) / gDispSet.getDispScale());
	return ptHpgl;
}
