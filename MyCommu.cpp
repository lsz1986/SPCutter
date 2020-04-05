// MyCommu.cpp: implementation of the CMyUSB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyCommu.h"
#include "Global.h"

extern CMyUSB gMyUSB;
extern CMyEth gMyEth;

CMyCommu::CMyCommu()
{
}

CMyCommu::~CMyCommu()
{
}

int CMyCommu::WriteBulk(char *pbBuf, ULONG len)
{
	int rev;
	if (gSet.getConnetViaEth())
	{
		rev = gMyEth.WriteBulk(pbBuf, len);
	}
	else
	{
		rev = gMyUSB.WriteBulk(pbBuf, len);
	}
	return rev;
}

int CMyCommu::OnCmd0(u8 cmd)
{
	int rev;
	if (gSet.getConnetViaEth())
	{
		rev = gMyEth.OnCmd0(cmd);
	}
	else
	{
		rev = gMyUSB.OnCmd0(cmd);
	}
	return rev;
}

int CMyCommu::OnCmd1(u8 cmd, u8 slen, u8* sbuf, u8 rlen, u8* rbuf)
{
	int rev;
	if (gSet.getConnetViaEth())
	{
		rev = gMyEth.OnCmd1(cmd,slen,sbuf,rlen,rbuf);
	}
	else
	{
		rev = gMyUSB.OnCmd1(cmd, slen, sbuf, rlen, rbuf);
	}
	return rev;
}
