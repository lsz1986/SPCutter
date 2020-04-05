#ifndef _USER_USB_CMD_H_
#define _USER_USB_CMD_H_
//-------系统状态定义区-----------------------------------
#define SYS_INIT     0 //系统初始化
#define SEEK_ZP      1
//#define INIT_USB     2  //初始化串口 USB
//#define MOVE_TO_DEFZP   3 //
#define READY        4 //准备就绪 
//#define READY_PAUSE     5
//#define PLOTTING     6 //正在打印
//#define PLOT_PAUSE   7 //打印暂停
//#define CUTTING      8 //正在切割
//#define CUT_PAUSE    9 //切割暂停
#define PRT_TEST     10 //正在打印测试图
#define PROCESSING   11
#define WORKING      12
#define WORK_PAUSE   13
//#define CHECK_SRAM   14 //检查内存
#define ERROR_SRAM   15 //内存错误
//#define ERROR_REG    16
#define STEPM_LOST   17
//-------------------------------------------------------

#define WT_NONE			(0x0)
#define WT_START		(0x10) //准备开始新任务
#define WT_END			(0x20) //正在执行工作完成动作
#define WT_PLOTTING		(0x30)
#define WT_CUTTING  	(0x40)
#define WT_CANCEL   	(0x50)
//-------------------------------------------------------
#define CMD0_GET_STAT	(0x3a) // 上位机查询状态指令
#define CMD0_DIR_NONE	(0x0) // 上位机发机头移动指令
#define CMD0_DIR_UP		(0x01) // 上位机发机头移动指令
#define CMD0_DIR_DOWN	(0x02) // 上位机发机头移动指令
#define CMD0_DIR_LEFT	(0x03) // 上位机发机头移动指令
#define CMD0_DIR_RIGHT	(0x04) // 上位机发机头移动指令
#define CMD0_PUMP_ON	(0x05) //开气泵
#define CMD0_PUMP_OFF	(0x06) //关气泵
#define CMD0_SPCLEAN	(0x07) //开启进程 清洗过程
#define CMD0_CUT_DOWN   (0x08) //落刀
#define CMD0_CUT_UP     (0x09) //抬刀
#define CMD0_WEND       (0x0a) //一个文件结束时的处理(回原点，裁纸等)
#define CMD0_WCANCEL    (0x0b) //下位机退出工作状态
#define CMD0_WRESUME    (0x0c) //
#define CMD0_WPAUSE     (0x0d) //

#define CMD0_ZP_SET		(0x10) //设置当前点为原点
#define CMD0_ZP_TODEF	(0x11) //回默认原点




//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define CMD1_PARA_READ			(0x20) //读参数
#define CMD1_GET_CAR_POS		(0x21) //获取当前位置 ok
#define CMD1_GET_ZP_POS			(0x22) //获取原点位置 ok
#define CMD1_GET_MCU_ID			(0x23) //获取MCU_ID  待测
#define CMD1_GET_UL_CODE		(0x24) //获取完全解锁码
#define CMD1_GET_LASTTIME		(0x25) //获取最后一次工作时间
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define CMD1_SET_UL_CODE		(0x30) //设置完全解锁码
#define CMD1_SET_LASTTIME		(0x31) //设置最后一次工作时间
#define CMD1_PARA_WRITE			(0x32) //写参数

#define CMD1_NEWF_PAUSE			(0x33) //下位机进入工作状态(暂停)
#define CMD1_NEWF_RUN			(0x34) //下位机进入工作状态(工作中)
#define CMD1_PLOT				(0x35) //开启进程 喷墨
#define CMD1_CUT				(0x36) //开启进程 切割

#define ERROR_NONE        0
#define ERROR_NOTREADY    1
#define ERROR_XYSIZE      2
#define ERROR_CANCEL_FILE 3

#endif
