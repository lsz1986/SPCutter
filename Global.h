#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "GlobalDef.h"
#include "MacSet.h"
#include "DispSet.h"
#include "OnePage.h"
#include "MyUSB.h"
#include "MyReg.h"

long IntRound(double x);
BOOL IsAlpha(char ch);
BOOL IsDigit(char ch);
int ftoi(double f);

int ReadMacPara();
void WritePlotPara();
void delayus(int num); //延时num个us数
UINT ThreadWork(LPVOID pParam);
void gParaTogSet(void);
void gSetTogPara(void);
CPoint ptHpglToScr(CPoint ptHpgl);
void GetCncMaxPulse();
void setSpdLimit(int nLowSpdMode);

extern CString strZHKJ;

extern CSetMac gMacSet; //全局变量
extern ST_CNC_SPD_LIMIT gSpdLimit;

extern CSetDisp gDispSet;

extern ST_MAC_PARA gPara;
extern UNION_MAC_PARA gTempPara;

extern u8 gSysState;
extern u8 gWorkType; //工作类型

extern STRUCT_REG_INFO gRegInfo;

extern BOOL g_bParaRead; //已经成功读取了

extern const UINT YHZIntArray[16];
extern CPtrArray g_ptrCncList;
extern COnePage gWorkingPage;
extern CMyUSB gUSB;
extern CMyReg gMyReg;
extern int gnPackSum;
#endif

