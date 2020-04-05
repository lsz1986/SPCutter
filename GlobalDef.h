#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_
#include "user_usb_cmd.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define USER_SHOWTASK		WM_USER+101
#define USER_END_WTHREAD	WM_USER+110
#define USER_DISP_STAT		WM_USER+111
#define USER_SEARCH_PLT		WM_USER+112
#define USER_AUTO_START		WM_USER+113

#define LT_SOLID		0 //实线
#define LT_DASH			1 //短线 大于1 都为短线

#define MAC_STATE_SIZE 16

#define REG_INFO_SIZE 12
typedef struct  
{
	u16 m_nCpuCode;
	u16 m_nAuthDays;
	u32 m_nRtcStart;
	u32 m_nRtcNow;
}STRUCT_REG_INFO;

#define MAC_PARA_SIZE 56
typedef struct
{
//16Byte---------------------------------------
	double m_dPPMM_X;
	double m_dPPMM_Y;
//10byte---------------------------------------
	unsigned short m_s10000X;
	unsigned short m_s10000Y;
	unsigned short m_sSpAccStep; //喷墨加速距离
	unsigned short m_sMacSizeXmm; //X软件保护值mm
	unsigned short m_sMacSizeYmm; //Y软件保护值mm

//6byte---------------------------------------
	unsigned short m_sCutEndPosYmm; //自动裁断停止位置
	unsigned short m_sJobEndPosXmm;  //停机时指定位置X
	unsigned short m_sJobEndPosYmm;  //停机时指定位置Y
//10byte--------------------------------------------------------------------------------
	unsigned char m_cKPDistX; //刀笔补偿X
	unsigned char m_cKPDistY; //刀笔补偿Y
	unsigned char m_cPwmKStart;  //启动刀压
	unsigned char m_cPwmKWork;   //工作刀压
	unsigned char m_cSp12Y; //喷头12之间Y方向错开的点数

	unsigned char m_cJamDetect; //喷墨时卡纸检测开启
	unsigned char m_cSp1DotLR; //喷头1左右两列的距离
	unsigned char m_cSp2DotLR; //喷头2左右两列的距离
	unsigned char m_cSpdMove;    //空程速度
	unsigned char m_cSpdCut;     //切割速度
//9byte--------------------------------------------------------------------------------
	unsigned char m_cYLRError; //Y双向打印误差(单位，线素)
	unsigned char m_cSpStat;     //喷头状态 0-喷头全选，1-仅选择喷头1 2-仅选择喷头2
	unsigned char m_cSpEX; //喷头12之间重叠的点行数
	unsigned char m_cAngleAdjust; //垂直度校正 50~150
	unsigned char m_cJobEndHeadPos; //切割完成时机头位置
	unsigned char m_cPPDOT_Y;
	unsigned char m_cLedLan;
	unsigned char m_cLowSpdMode;
	unsigned char m_cSpType; //墨盒类型

}ST_MAC_PARA;

typedef union
{
	ST_MAC_PARA stBuff; 
	unsigned short shortBuff[MAC_PARA_SIZE/2];
	unsigned char charBuff[MAC_PARA_SIZE]; 
} UNION_MAC_PARA;

typedef struct
{
	u32 cutNo;
	u32 cutSum;
	u16 plotNo;
	u16 plotRcvNo;
	u16 plotSum;
	u8 macState; //主机状态
	u8 lastCmdState; //命令执行返回值
}ST_SYS_STATE; //16字节

typedef union
{
	ST_SYS_STATE stBuff;
	unsigned char charBuff[MAC_STATE_SIZE];
}UNION_SYS_STATE;

typedef union 
{
	u8 u8buff[2];
	u16 u16buff;
}UNION_U8U16;

typedef union 
{
	u8 u8buff[4];
	u32 u32buff;
}UNION_U8U32;

typedef struct  
{
	CWnd *m_pWnd;
}ST_THREAD_PARA;

typedef struct
{
	int m_iX; //目标X
	int m_iY; //目标Y
	int m_iDeltaX; //X变化量
	int m_iDeltaY; //Y变化量
	int m_nLongAxialStep; //分段数
	double m_dAngle;
	double m_dDeltaAngle;
	double m_dCurvature;
	double m_dDccPerCent;

	int m_nEndSpeed; //计算时必须int否则越界
	int m_nMaxSpeed;
	u16 m_nCmdType;
}ST_CNC_DATA_ALL;

typedef struct
{
	int m_iX; //目标X
	int m_iY; //目标Y
	u16 m_nMaxSpeed;
	u16 m_nEndSpeed;
	u16 m_nCmdType;
	u16 m_nDccPerCent;
}ST_CNC_DATA_SEND;

typedef struct  
{
	int m_spdMax;	//	5000
	int m_spdLV1;	//	300
	int m_spdLV2_R002;  //400 
	int m_spdLV3_R004;  //480 
	int m_spdLV4_R005;  //560
	int m_spdLV5_R010;  //640
	int m_spdLV6_R020;  //720
	int m_spdLV7_R050;  //800
	int m_spdLV8_R100;  //1000
	int m_spdLV9_R150;  //1200
	int m_spdLV10_R200;  //1400
	int m_spdLV11_R300;  //1600
}ST_CNC_SPD_LIMIT;

typedef union
{
	u8 u8Buff[CNC_DATA_SIZE];
	ST_CNC_DATA_SEND stBuff;
}UNION_CNC_DATA_SEND;

#endif
