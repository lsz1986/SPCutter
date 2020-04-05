// MyUSB.cpp: implementation of the CMyUSB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyUSB.h"
#include "Global.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

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
	InitializeCriticalSection(&m_cs);
}

CMyUSB::~CMyUSB()
{
	USBClose();
}

void CMyUSB::USBClose()
{
	if (m_pUSBdev != 0)
	{
		usb_release_interface(m_pUSBdev,0);
		usb_close(m_pUSBdev);
		m_pUSBdev = 0;
	}
}

int CMyUSB::USBOpen()
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

int CMyUSB::UsbRead(char *pbBuf, ULONG len)
{
	int ret;
	if (USBOpen() != 0)
	{
		return -1;
	}

	ret = usb_bulk_read(m_pUSBdev, EP1_IN, pbBuf, len, 1000);

	USBClose(); //每读取一次就关闭??
	return ret;
}

int CMyUSB::USBWrite(char *pbBuf, ULONG len)
{
	int ret;
	if (USBOpen() != 0)
	{
		return -1;
	}

	ret = usb_bulk_write(m_pUSBdev, EP2_OUT, pbBuf, len, 50);

	USBClose(); //每发送一个命令就关闭??
	return ret;
}

int CMyUSB::WriteBulk(char *pbBuf, ULONG len)
{
	int ret=0;

	EnterCriticalSection(&m_cs);
	if (USBOpen() != 0)
	{
		ret = -1;
	}

	ret = usb_bulk_write(m_pUSBdev, EP3_OUT, pbBuf, len, 1000);
	USBClose(); //每发送一包数据就关闭
	LeaveCriticalSection(&m_cs);
	return ret;
}

int CMyUSB::OnCmd0(u8 cmd)
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnCmd0_USB(cmd);
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnCmd0_USB(u8 cmd)
{
	char buff[64];
	int rlen;
	buff[0] = 2;
	buff[1] = cmd;

	if (((int)buff[0]) != (USBWrite(&buff[0], buff[0])))
	{
		return -1; //命令发送失败
	}
	rlen = UsbRead(buff, 64);
	if (rlen != 1)
	{
		return -2;
	}
	gSysState = buff[0]; //CMD0_GET_STAT
	return 0;
}


int CMyUSB::OnCmd1(u8 cmd, u8 slen, u8* sbuf, u8 rlen, u8* rbuf)
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnCmd1_USB(cmd, slen, sbuf, rlen, rbuf);
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyUSB::OnCmd1_USB(u8 cmd, u8 slen, u8* sbuf, u8 rlen, u8* rbuf)
{
	char buff[64];
	int i;
	buff[0] = slen+2;
	buff[1] = cmd;
	for (i=0;i<slen;i++)
	{
		buff[i+2] = sbuf[i];
	}

	if (((int)buff[0]) != (USBWrite(&buff[0], buff[0])))
	{
		return -1;
	}
	if (UsbRead((char*)rbuf, rlen) != rlen)
	{
		return -1;
	}
	if (rlen == 1)
	{
		gSysState = rbuf[0];
	}
	return 0;
}
