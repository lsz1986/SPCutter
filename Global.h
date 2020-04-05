#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "GlobalDef.h"
#include "Settings.h"
#include "DispSet.h"
#include "OnePage.h"
#include "MyUSB.h"
#include "MyEth.h"
#include "MyCommu.h"

#include "MyReg.h"

long IntRound(double x);
BOOL IsAlpha(char ch);
BOOL IsDigit(char ch);
int ftoi(double f);

int ReadMacPara();
void WritePlotPara();
void delayus(int num); //��ʱnum��us��
UINT ThreadWork(LPVOID pParam);
void gParaTogSet(void);
void gSetTogPara(void);
CPoint ptHpglToScr(CPoint ptHpgl);
CPoint ptScrToHpgl(CPoint ptScr);

//extern u8 gWorkType; //��������

extern int gPlotPackNo;
extern CSettings gSet; //ȫ�ֱ���

extern CSetDisp gDispSet;
extern ST_MAC_PARA gPara;
extern STRUCT_REG_INFO gRegInfo;

extern u8 gSysState;
extern int gCarCurPosX;
extern int gCarCurPosY;

extern CString strZHKJ;

extern BOOL g_bParaRead; //�Ѿ��ɹ���ȡ��
extern const UINT YHZIntArray[16];
extern CPtrArray g_ptrCncList;
extern COnePage gWorkingPage;


extern CMyCommu gCommu;

extern CMyReg gMyReg;
extern u32 gMcuCode;

extern int gPackSumPlotOnly;
#endif

