// MyUSB.h: interface for the CMyUSB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYUSB_H__A22D3F96_2E73_4786_AB10_0918E5CE35C0__INCLUDED_)
#define AFX_MYUSB_H__A22D3F96_2E73_4786_AB10_0918E5CE35C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GlobalDef.h"
#include "afxmt.h"

#include "LibUsb\\lusb0_usb.h"
#define MY_VID 0xA728 //厂商ID
#define MY_PID 0x0701 //产品ID 切绘带网络

#define EP1_IN 0x81
#define EP2_OUT 0x02
#define EP3_OUT 0x03
class CMyUSB  
{
public:
	CMyUSB();
	virtual ~CMyUSB();
	int WriteBulk(char *pbBuf, ULONG len);
	int OnCmd0(u8 cmd);

	int OnCmd1(u8 cmd, u8 slen, u8* sbuf, u8 rlen, u8* rbuf);
private:
	CRITICAL_SECTION m_cs;
	usb_dev_handle *m_pUSBdev;
	int m_nDeviceFound;

	void USBClose();
	int USBOpen();
	int UsbRead(char *pbBuf, ULONG len);
	int USBWrite(char *pbBuf, ULONG len);
	int OnCmd0_USB(u8 cmd);
	int OnCmd1_USB(u8 cmd, u8 slen, u8* sbuf, u8 rlen, u8* rbuf);
};
#endif
