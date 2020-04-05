#ifndef _USER_USB_CMD_H_
#define _USER_USB_CMD_H_
//-------ϵͳ״̬������-----------------------------------
#define SYS_INIT     0 //ϵͳ��ʼ��
#define SEEK_ZP      1
#define INIT_USB     2  //��ʼ������ USB
//#define MOVE_TO_DEFZP   3 //
#define READY        4 //׼������ 
//#define READY_PAUSE     5
//#define PLOTTING     6 //���ڴ�ӡ
//#define PLOT_PAUSE   7 //��ӡ��ͣ
//#define CUTTING      8 //�����и�
//#define CUT_PAUSE    9 //�и���ͣ
#define PRT_TEST     10 //���ڴ�ӡ����ͼ
#define PROCESSING   11
#define WORKING      12
#define WORK_PAUSE   13
#define CHECK_SRAM   14 //����ڴ�
#define ERROR_SRAM   15 //�ڴ����
#define ERROR_REG    16
#define STEPM_LOST   17
//-------------------------------------------------------
#define CMD_GET_STATE   0x0a //��ѯ����״̬

#define CMD_PARA_READ   0x10 //������
#define CMD_PARA_WRITE  0x11 //д����
#define CMD_CUT_DOWN	0x12 //�䵶oŗ��
#define CMD_PUMP_ON		0x14 //��������
#define CMD_PUMP_OFF	0x15 //�ر�����

#define CMD_SET_ZP		0x16 //��Ĭ��ԭ��
#define CMD_TO_DEFZP	0x17 //��Ĭ��ԭ��
#define CMD_SYS_RST		0x18 //ϵͳ��λ

#define CMD_SPCLEAN		0x1a //��ϴ��ͷ

#define CMD_GET_CHIPID    0x20 //��ȡSTM32ID��
#define CMD_GET_LAST_TIME 0x21 //��ȡ���һ��ʹ��ʱ��
#define CMD_SET_LAST_TIME 0x22 //�������һ��ʹ��ʱ��
#define CMD_ERASE         0x24

#define CMD_GET_DEB_CODE  0x2a //�ж��Ƿ���ȫ����
#define CMD_SET_DEB_CODE  0x2b //������ȫ������

#define WORKCMD_START     0x40 //��λ�����빤��״̬
#define WORKCMD_END       0x41 //һ���ļ�����ʱ�Ĵ���(��ԭ�㣬��ֽ��)
#define WORKCMD_CANCEL    0x42 //��λ���˳�����״̬
#define WORKCMD_PLOT      0x43 //�������� ��ī
#define WORKCMD_CUT       0x44 //�������� �и�
#define WORKCMD_RESUME    0x45 //
#define WORKCMD_PAUSE     0x46 //

#define RESET_RCV_ADDR    0x50 //���ý��յ�ַ
#define USB_DEMO_KEY      0x5a //USB��ģ�ⰴ��

#define ERROR_NONE        0
#define ERROR_NOTREADY    1
#define ERROR_XYSIZE      2
#define ERROR_CANCEL_FILE 3

#define WT_NONE       0
#define WT_START      1
#define WT_END        2
#define WT_PLOTTING   3
#define WT_CUTTING    4
#define WT_CANCEL     5

#endif
