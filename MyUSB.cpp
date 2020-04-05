// MyUSB.cpp: implementation of the CMyUSB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyUSB.h"
#include "Global.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define MY_VID 0xA728 //³§ÉÌID
#define MY_PID 0x0500 //²úÆ·ID

#define MY_CONFIG 1
#define MY_INTF 0


#define EP1_IN 0x81
#define EP2_OUT 0x02
#define EP3_OUT 0x03

usb_dev_handle *open_dev(void);


usb_dev_handle *open_dev(void)
{
	struct usb_bus *bus;
	struct usb_device *dev;
	
	for (bus = usb_get_busses(); bus; bus = bus->next)
	{
		for (dev = bus->devices; dev; dev = dev->next)
		{
			if (dev->descriptor.idVendor == MY_VID
				&& dev->descriptor.idProduct == MY_PID)
			{
				return usb_open(dev);
			}
		}
	}
	return NULL;
}

CMyUSB::CMyUSB()
{
	usb_init(); /* initialize the library */
	usb_find_busses(); /* find all busses */
	m_nDeviceFound = usb_find_devices(); /* find all connected devices */
	InitializeCriticalSection(&m_cs);//
}

CMyUSB::~CMyUSB()
{
	Close();
}

void CMyUSB::Close()
{
	if (m_pUSBdev != 0)
	{
		usb_release_interface(m_pUSBdev,0);
		usb_close(m_pUSBdev);
		m_pUSBdev = 0;
	}
}

int CMyUSB::Open()
{
	if (m_pUSBdev == 0)
	{
		if (m_nDeviceFound != 1)
		{
			m_nDeviceFound = usb_find_devices();
//			return -1;
		}
		if (!(m_pUSBdev = open_dev()))
		{
			return -1;
		}
		if (usb_claim_interface(m_pUSBdev, 0) < 0)
		{
			usb_close(m_pUSBdev);
			return -1;
		}
	}
	return 0;
}

int CMyUSB::Read(char *pbBuf, ULONG len)
{
	int ret;
	if (Open() != 0)
	{
		return -1;
	}

	ret = usb_bulk_read(m_pUSBdev, EP1_IN, pbBuf, len, 1000);
	Close(); //Ã¿¶ÁÈ¡Ò»´Î¾Í¹Ø±Õ??
	return ret;
}

int CMyUSB::WriteCmd(char *pbBuf, ULONG len)
{
	int ret;

	if (Open() != 0)
	{
		return -1;
	}

	ret = usb_bulk_write(m_pUSBdev, EP2_OUT, pbBuf, len, 50);

	Close(); //Ã¿·¢ËÍÒ»¸öÃüÁî¾Í¹Ø±Õ??
	return ret;
}

int CMyUSB::WriteBulk(char *pbBuf, ULONG len)
{
	int ret=0;
	EnterCriticalSection(&m_cs);

	if (Open() != 0)
	{
		ret = -1;
	}

	ret = usb_bulk_write(m_pUSBdev, EP3_OUT, pbBuf, len, 1000);
	Close(); //Ã¿·¢ËÍÒ»°üÊý¾Ý¾Í¹Ø±Õ
	LeaveCriticalSection(&m_cs);
	return ret;
}

int CMyUSB::OnParaRead()
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnParaRead_0();
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnParaRead_0()
{
//ÃüÁî¸ñÊ½: ³¤¶È(1B) + ÃüÁîÍ·ZHKJ(4B) + CMD_READ_PARA 
//·µ»ØÖµ: -1 ÃüÁîÊ§°Ü,0 ÃüÁî³É¹¦

	char buff[64];
	int ret=0;
	int i;
	buff[0] = 6;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CMD_PARA_READ;
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != MAC_PARA_SIZE)
	{
		return -1;
	}
	for(i=0;i<MAC_PARA_SIZE;i++)
	{
		gTempPara.charBuff[i] = buff[i];
	}
	return 0;
}

int CMyUSB::OnParaWrite()
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnParaWrite_0();
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnParaWrite_0()
{
//ÃüÁî¸ñÊ½: ³¤¶È(1B) + ÃüÁîÍ·ZHKJ(4B) + CMD_READ_WITE 
//·µ»ØÖµ: -1 ÃüÁîÊ§°Ü,0 ÃüÁî³É¹¦
	char buff[64];
	int ret=0;
	int i;
	buff[0] = MAC_PARA_SIZE+6;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CMD_PARA_WRITE;

	for (i=0;i<MAC_PARA_SIZE;i++)
	{
		buff[i+6] = gTempPara.charBuff[i];
	}
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; 
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnGetMacState()
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnGetMacState_0();
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnGetMacState_0()
{
	//ÃüÁî¸ñÊ½: ³¤¶È(1B) + ÃüÁîÍ·ZHKJ(4B) + CMD_READ_WITE 
	//·µ»ØÖµ: -1 ÃüÁîÊ§°Ü,0 ÃüÁî³É¹¦
	char buff[64];
	buff[0] = 6;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CMD_GET_STATE;
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 2)
	{
		return -2;
	}
	gSysState = buff[0];
	gWorkType = buff[1]; //¹¤×÷ÀàÐÍ
	return 0;
}

int CMyUSB::OnPumpCtrl(BOOL b)
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnPumpCtrl_0(b);
	LeaveCriticalSection(&m_cs);
	return rev;
}

//XÏñËØ,°ü×ÜÊý
int CMyUSB::OnPumpCtrl_0(BOOL b)
{
	char buff[64];
	buff[0] = 6;
	strncpy(&buff[1],CMD_HEAD,4);
	if (b)	{
		buff[5] = CMD_PUMP_ON;
	}else{
		buff[5] = CMD_PUMP_OFF;
	}
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnCutDown(u8 CutPwm)
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnCutDown_0(CutPwm);
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnCutDown_0(u8 CutPwm)
{
	char buff[64];
	buff[0] = 7;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CMD_CUT_DOWN;
	buff[6] = CutPwm;
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnSysReset()
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnSysReset_0();
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnSysReset_0()
{
	char buff[64];
	buff[0] = 6;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CMD_SYS_RST;
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnSetZp()
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnSetZp_0();
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnSetZp_0()
{
	char buff[64];
	buff[0] = 6;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CMD_SET_ZP;
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnToDefZp()
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnToDefZp_0();
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnToDefZp_0()
{
	char buff[64];
	buff[0] = 6;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CMD_TO_DEFZP;
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnSpClean()
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnSpClean_0();
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnSpClean_0()
{
	char buff[64];
	buff[0] = 6;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CMD_SPCLEAN;
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnWorkCmdStart(int XSizeCut,int YSizeCut,int nPackSum,int YPixPlot,u8 Pause)
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnWorkCmdStart_0(XSizeCut, YSizeCut, nPackSum, YPixPlot, Pause);
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnWorkCmdStart_0(int XSizeCut,int YSizeCut,int nPackSum,int YPixPlot,u8 Pause)
{
	char buff[64];
	int i;
	UNION_U8U32 u832Temp;
	buff[0] = 23;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = WORKCMD_START;

	u832Temp.u32buff = XSizeCut;
	for (i=0;i<4;i++)
	{
		buff[6+i] = u832Temp.u8buff[i];
	}
	u832Temp.u32buff = YSizeCut;
	for (i=0;i<4;i++)
	{
		buff[10+i] = u832Temp.u8buff[i];
	}
	u832Temp.u32buff = nPackSum;
	for (i=0;i<4;i++)
	{
		buff[14+i] = u832Temp.u8buff[i];
	}

	u832Temp.u32buff = YPixPlot;
	for (i=0;i<4;i++)
	{
		buff[18+i] = u832Temp.u8buff[i];
	}
	buff[22] = Pause;
	
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnWorkCtrl(u8 CtrlType)
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnWorkCtrl_0(CtrlType);
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnWorkCtrl_0(u8 CtrlType)
{
	char buff[64];
	buff[0] = 6;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CtrlType;
	
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -1;
	}
	return buff[0];
}

int CMyUSB::OnWorkCmdPlot(int nPackNum,u8 dir)
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnWorkCmdPlot_0(nPackNum,dir);
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnWorkCmdPlot_0(int nPackNum,u8 dir)
{
	char buff[64];
	int i;
	UNION_U8U32 u832Temp;
	buff[0] = 11;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = WORKCMD_PLOT;
	
	u832Temp.u32buff = nPackNum;
	for (i=0;i<4;i++)
	{
		buff[6+i] = u832Temp.u8buff[i];
	}
	buff[10] = dir;
	
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnWorkCmdCut(int nCutSum)
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnWorkCmdCut_0(nCutSum);
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnWorkCmdCut_0(int nCutSum)
{
	char buff[64];
	UNION_U8U32 u832Temp;
	int i;
	buff[0] = 10;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = WORKCMD_CUT;
	u832Temp.u32buff = nCutSum;
	for(i=0;i<4;i++)
	{
		buff[6+i] = u832Temp.u8buff[i];
	}

	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnResetRcvAddr()
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnResetRcvAddr_0();
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnResetRcvAddr_0()
{
	char buff[64];
	buff[0] = 6;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = RESET_RCV_ADDR;
	
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnSendUsbKeyValue(u8 KeyVal)
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnSendUsbKeyValue_0(KeyVal);
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnSendUsbKeyValue_0(u8 KeyVal)
{
	char buff[64];
	buff[0] = 7;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = USB_DEMO_KEY;
	buff[6] = KeyVal;

	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnGetChipID()
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnGetChipID_0();
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnGetChipID_0()
{
	UNION_U8U32 temp;
	char buff[64];
	
	buff[0] = 7;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CMD_GET_CHIPID;
	buff[6] = 0x60; //¿É±äµØÖ· ·ÀÖ¹ÆÆ½â 
	
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 4)
	{
		return -1;
	}
	for (int i=0;i<4;i++)
	{
		temp.u8buff[i] = buff[i];
	}

	return temp.u32buff;
}

int CMyUSB::OnEraseMcuFlash()
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnEraseMcuFlash_0();
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnEraseMcuFlash_0()
{
	char buff[64];
	buff[0] = 6;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CMD_ERASE;
	
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnSetLastTime(u32 Time)
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnSetLastTime_0(Time);
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnSetLastTime_0(u32 Time)
{
	char buff[64];
	UNION_U8U32 u832temp;
	u832temp.u32buff = Time;
	buff[0] = 10;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CMD_SET_LAST_TIME;

	buff[6] = u832temp.u8buff[0];
	buff[7] = u832temp.u8buff[1];
	buff[8] = u832temp.u8buff[2];
	buff[9] = u832temp.u8buff[3];
	
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnGetLastTime()
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnGetLastTime_0();
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnGetLastTime_0()
{
	UNION_U8U32 temp;
	char buff[64];
	
	buff[0] = 6;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CMD_GET_LAST_TIME;
	
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 4)
	{
		return -1;
	}
	for (int i=0;i<4;i++)
	{
		temp.u8buff[i] = buff[i];
	}
	return temp.u32buff;
}

int CMyUSB::OnSetDeblockCode(u32 debCode)
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnSetDeblockCode_0(debCode);
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnSetDeblockCode_0(u32 debCode)
{
	char buff[64];
	UNION_U8U32 u832temp;
	u832temp.u32buff = debCode;
	buff[0] = 10;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CMD_SET_DEB_CODE;
	
	buff[6] = u832temp.u8buff[0];
	buff[7] = u832temp.u8buff[1];
	buff[8] = u832temp.u8buff[2];
	buff[9] = u832temp.u8buff[3];
	
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 1)
	{
		return -2;
	}
	return buff[0];
}

int CMyUSB::OnGetDeblockCode()
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnGetDeblockCode_0();
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnGetDeblockCode_0()
{
	UNION_U8U32 temp;
	char buff[64];
	
	buff[0] = 6;
	strncpy(&buff[1],CMD_HEAD,4);
	buff[5] = CMD_GET_DEB_CODE;
	
	if ( ((int)buff[0] ) != (WriteCmd(&buff[0],buff[0]) ) )
	{
		return -1; //ÃüÁî·¢ËÍÊ§°Ü
	}
	if( Read(buff,64) != 4)
	{
		return -1;
	}
	for (int i=0;i<4;i++)
	{
		temp.u8buff[i] = buff[i];
	}
	return temp.u32buff;
}

