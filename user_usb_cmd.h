#ifndef _USER_USB_CMD_H_
#define _USER_USB_CMD_H_
//-------系统状态定义区-----------------------------------
#define SYS_INIT     0 //系统初始化
#define SEEK_ZP      1
#define INIT_USB     2  //初始化串口 USB
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
#define CHECK_SRAM   14 //检查内存
#define ERROR_SRAM   15 //内存错误
#define ERROR_REG    16
#define STEPM_LOST   17
//-------------------------------------------------------
#define CMD_GET_STATE   0x0a //查询主机状态

#define CMD_PARA_READ   0x10 //读参数
#define CMD_PARA_WRITE  0x11 //写参数
#define CMD_CUT_DOWN	0x12 //落刀or抬刀
#define CMD_PUMP_ON		0x14 //开启气泵
#define CMD_PUMP_OFF	0x15 //关闭气泵

#define CMD_SET_ZP		0x16 //回默认原点
#define CMD_TO_DEFZP	0x17 //回默认原点
#define CMD_SYS_RST		0x18 //系统软复位

#define CMD_SPCLEAN		0x1a //清洗喷头

#define CMD_GET_CHIPID    0x20 //获取STM32ID号
#define CMD_GET_LAST_TIME 0x21 //获取最后一次使用时间
#define CMD_SET_LAST_TIME 0x22 //更新最后一次使用时间
#define CMD_ERASE         0x24

#define CMD_GET_DEB_CODE  0x2a //判断是否完全解锁
#define CMD_SET_DEB_CODE  0x2b //更新完全解锁码

#define WORKCMD_START     0x40 //下位机进入工作状态
#define WORKCMD_END       0x41 //一个文件结束时的处理(回原点，裁纸等)
#define WORKCMD_CANCEL    0x42 //下位机退出工作状态
#define WORKCMD_PLOT      0x43 //开启进程 喷墨
#define WORKCMD_CUT       0x44 //开启进程 切割
#define WORKCMD_RESUME    0x45 //
#define WORKCMD_PAUSE     0x46 //

#define RESET_RCV_ADDR    0x50 //重置接收地址
#define USB_DEMO_KEY      0x5a //USB口模拟按键

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
