#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_
#include "zh_cmd_def.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define USER_SHOWTASK		WM_USER+101
#define USER_END_WTHREAD	WM_USER+102
#define USER_SEARCH_PLT		WM_USER+103
#define USER_AUTO_START		WM_USER+104

#define LT_SOLID		0 //实线
#define LT_DASH			1 //短线 大于1 都为短线

typedef struct _struct_reginfo_
{
	u16 m_nCpuCode;
	u16 m_nAuthDays;
	u32 m_nRtcStart;
	u32 m_nRtcNow;
}STRUCT_REG_INFO;

#define MAC_PARA_SIZE 60
typedef struct _mac_para_
{
//16Byte--------------------------------------
	double m_dPPMM_X;
	double m_dPPMM_Y;
//4byte---------------------------------------
	u32 m_nW5500Ip;
//16byte--------------------------------------
	unsigned short m_s10000X;
	unsigned short m_s10000Y;

	unsigned short m_sMacSizeXmm; //X软件保护值mm
	unsigned short m_sMacSizeYmm; //Y软件保护值mm

	unsigned short m_sCutPaperStartYmm; //裁断Y向起始位置
	unsigned short m_sCutPaperEndYmm; //裁断Y向停止位置

	unsigned short m_sJobEndPosXmm;  //停机时指定位置X
	unsigned short m_sJobEndPosYmm;  //停机时指定位置Y
//10byte--------------------------------------------------------------------------------
	unsigned char m_cSpStat;     //喷头状态 0-喷头全选，1-仅选择喷头1 2-仅选择喷头2
	unsigned char m_cSp12Y; //喷头12之间Y方向错开的点数
	unsigned char m_cSp1DotLR; //喷头1左右两列的距离
	unsigned char m_cSp2DotLR; //喷头2左右两列的距离
	unsigned char m_cYLRError; //Y双向打印误差(单位，线素)

	unsigned char m_cSpEX; //喷头12之间重叠的点行数
	unsigned char m_cKPDistX; //刀笔补偿X
	unsigned char m_cKPDistY; //刀笔补偿Y
	unsigned char m_cPwmKStart;  //启动刀压
	unsigned char m_cPwmKWork;   //工作刀压

//11byte--------------------------------------------------------------------------------
	unsigned char m_cSpAccDistMm; //喷墨加速距离
	unsigned char m_cSpdMove;    //空程速度
	unsigned char m_cSpdCut;     //切割速度
	unsigned char m_cAngleAdjust; //垂直度校正 50~150
	unsigned char m_cJobEndHeadPos; //切割完成时机头位置

	unsigned char m_cPPDOT_Y;
	unsigned char m_cNull; //不再使用
	unsigned char m_cSpType; //墨盒类型
	unsigned char m_cSecLen;//默认 80
	unsigned char m_cLedLan;

	unsigned char m_cJamDetect; //喷墨时卡纸检测开启
	unsigned char m_cVer;

}ST_MAC_PARA;

typedef struct
{
	int m_iX; //目标X
	int m_iY; //目标Y

	int m_iDeltaX; //X变化量
	int m_iDeltaY; //Y变化量

	UINT m_nLongAxialStep; 
	UINT m_nSecNum;	//分段数
	double m_dAngle;
	double m_dDeltaAngle;

	int m_nMaxEndSpeed; //计算时int,发送是变为8位
	int m_nMaxSpeed;
	int m_cIsCurve; //0 直线 1弧线 2线密的弧线 
	u8 m_cCmdType;
}ST_CNC_DATA_ALL;

typedef struct
{
	int m_iX;
	int m_iY;
	u8 m_nMaxSpeed;
	u8 m_nEndSpeed;
	u8 m_cCmdType;
	u8 m_cNull;
}STRUCT_CNC_DATA;

typedef union
{
	u8 u8Buff[CNC_DATA_SIZE];
	STRUCT_CNC_DATA stBuff;
}UNION_CNC_DATA_SEND;

#endif
