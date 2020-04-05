// MyUSB.h: interface for the CMyUSB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYUSB_H__A22D3F96_2E73_4786_AB10_0918E5CE35C0__INCLUDED_)
#define AFX_MYUSB_H__A22D3F96_2E73_4786_AB10_0918E5CE35C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "libusb\\lusb0_usb.h"
#include "GlobalDef.h"
#include "afxmt.h"

#define CMD_HEAD "ZHV6"
class CMyUSB  
{
public:
	int m_nDeviceFound;
	CRITICAL_SECTION m_cs;

public:
	int OnSendUsbKeyValue_0(u8 KeyVal);
	int OnSendUsbKeyValue(u8 KeyVal);

	int OnWorkCmdStart_0(int XSizeCut,int YSizeCut,int nPackSum,int YPixPlot,u8 Pause);
	int OnWorkCmdStart(int XSizeCut,int YSizeCut,int nPackSum,int YPixPlot,u8 Pause);

	int OnWorkCtrl_0(u8 CtrlType); 
	int OnWorkCtrl(u8 CtrlType); 

	int OnWorkCmdPlot_0(int nPackNum,u8 dir);
	int OnWorkCmdPlot(int nPackNum,u8 dir);

	int OnWorkCmdCut_0(int nCutSum);
	int OnWorkCmdCut(int nCutSum);

	int OnResetRcvAddr_0();
	int OnResetRcvAddr();

	int OnGetLastTime_0();
	int OnGetLastTime();

	int OnSetLastTime_0(u32 Time);
	int OnSetLastTime(u32 Time);

	int OnGetDeblockCode_0();
	int OnGetDeblockCode();

	int OnSetDeblockCode_0(u32 debCode);
	int OnSetDeblockCode(u32 debCode);

	int OnEraseMcuFlash_0();
	int OnEraseMcuFlash();

	int OnGetChipID_0();
	int OnGetChipID();

	int OnPumpCtrl_0(BOOL b);
	int OnPumpCtrl(BOOL b);

	int OnCutDown_0(u8 CutPwm);
	int OnCutDown(u8 CutPwm);

	int OnSetZp_0();
	int OnSetZp();

	int OnSysReset_0();
	int OnSysReset();

	int OnToDefZp_0();
	int OnToDefZp();

	int OnSpClean_0();
	int OnSpClean();

	int OnParaWrite_0();
	int OnParaWrite();

	int OnParaRead_0();
	int OnParaRead();

	int OnGetMacState_0();
	int OnGetMacState();

	int WriteBulk(char *pbBuf, ULONG len);

	int WriteCmd(char *pbBuf, ULONG len);
	void Close();
	int Open();
	int Read(char *pbBuf, ULONG len);
	usb_dev_handle *m_pUSBdev;
	CMyUSB();
	virtual ~CMyUSB();
};

#endif // !defined(AFX_MYUSB_H__A22D3F96_2E73_4786_AB10_0918E5CE35C0__INCLUDED_)
