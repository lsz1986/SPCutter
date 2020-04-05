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
void delayus(int num); //��ʱnum��us��
UINT ThreadWork(LPVOID pParam);
void gParaTogSet(void);
void gSetTogPara(void);
CPoint ptHpglToScr(CPoint ptHpgl);
void GetCncMaxPulse();
void setSpdLimit(int nLowSpdMode);

extern CString strZHKJ;

extern CSetMac gMacSet; //ȫ�ֱ���
extern ST_CNC_SPD_LIMIT gSpdLimit;

extern CSetDisp gDispSet;

extern ST_MAC_PARA gPara;
extern UNION_MAC_PARA gTempPara;

extern u8 gSysState;
extern u8 gWorkType; //��������

extern STRUCT_REG_INFO gRegInfo;

extern BOOL g_bParaRead; //�Ѿ��ɹ���ȡ��

extern const UINT YHZIntArray[16];
extern CPtrArray g_ptrCncList;
extern COnePage gWorkingPage;
extern CMyUSB gUSB;
extern CMyReg gMyReg;
extern int gnPackSum;
#endif

