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

#define LT_SOLID		0 //ʵ��
#define LT_DASH			1 //���� ����1 ��Ϊ����

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
	unsigned short m_sSpAccStep; //��ī���پ���
	unsigned short m_sMacSizeXmm; //X�������ֵmm
	unsigned short m_sMacSizeYmm; //Y�������ֵmm

//6byte---------------------------------------
	unsigned short m_sCutEndPosYmm; //�Զ��ö�ֹͣλ��
	unsigned short m_sJobEndPosXmm;  //ͣ��ʱָ��λ��X
	unsigned short m_sJobEndPosYmm;  //ͣ��ʱָ��λ��Y
//10byte--------------------------------------------------------------------------------
	unsigned char m_cKPDistX; //���ʲ���X
	unsigned char m_cKPDistY; //���ʲ���Y
	unsigned char m_cPwmKStart;  //������ѹ
	unsigned char m_cPwmKWork;   //������ѹ
	unsigned char m_cSp12Y; //��ͷ12֮��Y������ĵ���

	unsigned char m_cJamDetect; //��īʱ��ֽ��⿪��
	unsigned char m_cSp1DotLR; //��ͷ1�������еľ���
	unsigned char m_cSp2DotLR; //��ͷ2�������еľ���
	unsigned char m_cSpdMove;    //�ճ��ٶ�
	unsigned char m_cSpdCut;     //�и��ٶ�
//9byte--------------------------------------------------------------------------------
	unsigned char m_cYLRError; //Y˫���ӡ���(��λ������)
	unsigned char m_cSpStat;     //��ͷ״̬ 0-��ͷȫѡ��1-��ѡ����ͷ1 2-��ѡ����ͷ2
	unsigned char m_cSpEX; //��ͷ12֮���ص��ĵ�����
	unsigned char m_cAngleAdjust; //��ֱ��У�� 50~150
	unsigned char m_cJobEndHeadPos; //�и����ʱ��ͷλ��
	unsigned char m_cPPDOT_Y;
	unsigned char m_cLedLan;
	unsigned char m_cLowSpdMode;
	unsigned char m_cSpType; //ī������

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
	u8 macState; //����״̬
	u8 lastCmdState; //����ִ�з���ֵ
}ST_SYS_STATE; //16�ֽ�

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
	int m_iX; //Ŀ��X
	int m_iY; //Ŀ��Y
	int m_iDeltaX; //X�仯��
	int m_iDeltaY; //Y�仯��
	int m_nLongAxialStep; //�ֶ���
	double m_dAngle;
	double m_dDeltaAngle;
	double m_dCurvature;
	double m_dDccPerCent;

	int m_nEndSpeed; //����ʱ����int����Խ��
	int m_nMaxSpeed;
	u16 m_nCmdType;
}ST_CNC_DATA_ALL;

typedef struct
{
	int m_iX; //Ŀ��X
	int m_iY; //Ŀ��Y
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
