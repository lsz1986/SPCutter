// MyCommu.h: interface for the CMyUSB class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _MYCOMMU_H_
#define _MYCOMMU_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GlobalDef.h"

class CMyCommu
{
public:
	CMyCommu();
	virtual ~CMyCommu();

	int OnCmd0(u8 cmd);
	int WriteBulk(char *pbBuf, ULONG len);
	int OnCmd1(u8 cmd, u8 slen, u8* sbuf, u8 rlen, u8* rbuf);

};
#endif // !defined(AFX_MYUSB_H__A22D3F96_2E73_4786_AB10_0918E5CE35C0__INCLUDED_)

