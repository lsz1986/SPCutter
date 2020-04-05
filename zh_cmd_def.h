#ifndef _USER_USB_CMD_H_
#define _USER_USB_CMD_H_
//-------ϵͳ״̬������-----------------------------------
#define SYS_INIT     0 //ϵͳ��ʼ��
#define SEEK_ZP      1
//#define INIT_USB     2  //��ʼ������ USB
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
//#define CHECK_SRAM   14 //����ڴ�
#define ERROR_SRAM   15 //�ڴ����
//#define ERROR_REG    16
#define STEPM_LOST   17
//-------------------------------------------------------

#define WT_NONE			(0x0)
#define WT_START		(0x10) //׼����ʼ������
#define WT_END			(0x20) //����ִ�й�����ɶ���
#define WT_PLOTTING		(0x30)
#define WT_CUTTING  	(0x40)
#define WT_CANCEL   	(0x50)
//-------------------------------------------------------
#define CMD0_GET_STAT	(0x3a) // ��λ����ѯ״ָ̬��
#define CMD0_DIR_NONE	(0x0) // ��λ������ͷ�ƶ�ָ��
#define CMD0_DIR_UP		(0x01) // ��λ������ͷ�ƶ�ָ��
#define CMD0_DIR_DOWN	(0x02) // ��λ������ͷ�ƶ�ָ��
#define CMD0_DIR_LEFT	(0x03) // ��λ������ͷ�ƶ�ָ��
#define CMD0_DIR_RIGHT	(0x04) // ��λ������ͷ�ƶ�ָ��
#define CMD0_PUMP_ON	(0x05) //������
#define CMD0_PUMP_OFF	(0x06) //������
#define CMD0_SPCLEAN	(0x07) //�������� ��ϴ����
#define CMD0_CUT_DOWN   (0x08) //�䵶
#define CMD0_CUT_UP     (0x09) //̧��
#define CMD0_WEND       (0x0a) //һ���ļ�����ʱ�Ĵ���(��ԭ�㣬��ֽ��)
#define CMD0_WCANCEL    (0x0b) //��λ���˳�����״̬
#define CMD0_WRESUME    (0x0c) //
#define CMD0_WPAUSE     (0x0d) //

#define CMD0_ZP_SET		(0x10) //���õ�ǰ��Ϊԭ��
#define CMD0_ZP_TODEF	(0x11) //��Ĭ��ԭ��




//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define CMD1_PARA_READ			(0x20) //������
#define CMD1_GET_CAR_POS		(0x21) //��ȡ��ǰλ�� ok
#define CMD1_GET_ZP_POS			(0x22) //��ȡԭ��λ�� ok
#define CMD1_GET_MCU_ID			(0x23) //��ȡMCU_ID  ����
#define CMD1_GET_UL_CODE		(0x24) //��ȡ��ȫ������
#define CMD1_GET_LASTTIME		(0x25) //��ȡ���һ�ι���ʱ��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define CMD1_SET_UL_CODE		(0x30) //������ȫ������
#define CMD1_SET_LASTTIME		(0x31) //�������һ�ι���ʱ��
#define CMD1_PARA_WRITE			(0x32) //д����

#define CMD1_NEWF_PAUSE			(0x33) //��λ�����빤��״̬(��ͣ)
#define CMD1_NEWF_RUN			(0x34) //��λ�����빤��״̬(������)
#define CMD1_PLOT				(0x35) //�������� ��ī
#define CMD1_CUT				(0x36) //�������� �и�

#define ERROR_NONE        0
#define ERROR_NOTREADY    1
#define ERROR_XYSIZE      2
#define ERROR_CANCEL_FILE 3

#endif
