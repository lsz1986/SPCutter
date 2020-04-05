// MyUSB.h: interface for the CMyUSB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYETH_H__A22D3F96_2E73_4786_AB10_0918E5CE35C0__INCLUDED_)
#define AFX_MYETH_H__A22D3F96_2E73_4786_AB10_0918E5CE35C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GlobalDef.h"
#include "afxmt.h"

#define ETH_PORT (5166)
class CMyEth
{
public:
	CMyEth();
	virtual ~CMyEth();

	int OnCmd0(u8 cmd);
	int OnCmd1(u8 cmd, u8 slen, u8* sbuf, u8 rlen, u8* rbuf);
	int WriteBulk(char *pbBuf, ULONG len);
private:
	CRITICAL_SECTION m_cs;
	BOOL m_bEthConnected;
	SOCKET m_socket;
	BOOL m_bWsaStarted;

	int EthInit();
	int EthConnect();
	int EthClose();
	int OnCmd0_Eth(u8 cmd);
	int OnCmd1_Eth(u8 cmd, u8 slen, u8* sbuf, u8 rlen, u8* rbuf);
};
#endif
