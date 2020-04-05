#ifndef _THREAD_H_
#define _THREAD_H_
#include "SpCutterDoc.h"
#include "Global.h"

extern int g_iPlotPixelX; //图形X向的像素值
extern int g_iBmpPixelY; //图形Y向的像素值
extern int g_iMacPixelY; //包含对喷头间距填充后的喷墨数据，Y向的像素值
extern int g_iSpdataSizeZipped;

extern int gnCncXMax;
extern int gnCncYMax;

//#define MAX_PIXEL 25000 //此时发送数据为25000*44 = 1100000，保证发送数据不超过880K
// extern char g_SpDataOrg[MAX_PIXEL][40]; 
// extern char g_SpDataSend[MAX_PIXEL][44]; 
// extern unsigned short g_ZippedSpDataSend[MAX_PIXEL*44];
// extern unsigned short g_TempSpDataSend[MAX_PIXEL*44];

//1024*1024/88 = 11915
#define MAX_PIXEL 11800 //此时11800*18/104.16=2040mm

extern char g_SpDataOrg[MAX_PIXEL][80]; 
extern char g_SpDataSend[MAX_PIXEL][88];
extern unsigned short g_ZippedSpDataSend[MAX_PIXEL*88];
extern unsigned short g_TempSpDataSend[MAX_PIXEL*88];


extern u8 g_Hp45_000To150Pixel[150];
extern u8 g_Hp45_150To300Pixel[150];

extern u8 g_IUT308_001To308Pixel[308];
extern u8 g_IUT308_309To616Pixel[308];

extern u8 g_HP45_SpAOneLinePixel[22][8];
extern u8 g_HP45_SpBOneLinePixel[22][8];

extern u8 g_IUT308_SpAOneLinePixel[44][8];
extern u8 g_IUT308_SpBOneLinePixel[44][8];

extern u8 g_SpAOneLinePixelZipped[44];
extern u8 g_SpBOneLinePixelZipped[44];

extern CWinThread* gThreadTimeDetect;
extern ST_THREAD_PARA gParaTimeDetect;

extern CWinThread* gThreadAutoConnect;
extern ST_THREAD_PARA gParaAutoConnect;

extern CWinThread* gThrdWork;
extern ST_THREAD_PARA gParaWork;


void CalcPlotPackSum(void); //计算喷墨数据的包数
void GetOnePackOrgData(int nPackNo); //获取一包喷墨数据，存入 g_SpDataOrg 中

void HP45_SetSpDataZero(void);
void HP45_Get001To150Pixel(int nYPixel);
void HP45_Get150To300Pixel(int nYPixel);
void HP45_ConvertOrgDataToSendData(int packNo);
void HP45_ZipSpSendData(); //将要发送的数据压缩存入 g_ZippedSpDataSend 中
void HP45_getSpAOneLineData(char Type);
void HP45_getSpBOneLineData(char Type);
void HP45_ZipSpData(); //压缩SpA,SpB数据


void IUT308_SetSpDataZero(void);
void IUT308_Get001To308Pixel(int nYPixel);
void IUT308_Get309To616Pixel(int nYPixel);
void IUT308_ConvertOrgDataToSendData(int packNo);
void IUT308_ZipSpSendData(); //将要发送的数据压缩存入 g_ZippedSpDataSend 中
void IUT308_getSpAOneLineData(char Type);
void IUT308_getSpBOneLineData(char Type);
void IUT308_ZipSpData(); //压缩SpA,SpB数据


void DrawBmp(CDC *pDC,int StartPixelX);
BOOL SaveBmp(HBITMAP hBitmap, CString FileName);

void dumpCutDataToFile();
void ReleaseCncDataBuffer();

void CalculateAngles();
void CalcCurvature();
int SendCncData();
void AddOverCutData();
void GetLongAxialSteps();
void CalcCncSpeed();
void CalcSdPercent();
#endif


