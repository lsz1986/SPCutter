// MyUSB.cpp: implementation of the CMyUSB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyEth.h"

#include "Global.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyEth::CMyEth()
{
	InitializeCriticalSection(&m_cs);
	m_bWsaStarted = FALSE;
}

CMyEth::~CMyEth()
{
	//�ر��׽���
	EthClose();
	if (m_bWsaStarted == TRUE)
	{
		WSACleanup();
		m_bWsaStarted = FALSE;
	}
}

int CMyEth::EthInit()
{
	int err;
	WSADATA wsaData;
	err = WSAStartup(MAKEWORD(2, 1), &wsaData);
	if (err != 0)
	{
		AfxMessageBox(_T("Winsock����ʧ��!\n"));
		return -1;
	}
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return -1;
	}

	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		AfxMessageBox(_T("Winsock����ʧ��!\n"));
		return -1;
	}
	return 0;
}

int CMyEth::EthClose()
{
	if (TRUE == m_bEthConnected)
	{
		closesocket(m_socket);
		m_bEthConnected = FALSE;
	}
	return 0;
}

int CMyEth::EthConnect()
{
	int err;
	//��Ҫ���ӵķ�����׽��ֽṹ��Ϣ
	if (m_bEthConnected == TRUE )
	{
		return 0;
	}
	if (m_bWsaStarted == FALSE)
	{
		EthInit();
		m_bWsaStarted = TRUE;
	}
	SOCKADDR_IN addrServer;
	unsigned int aa = gSet.getMachineIpAddr();
	addrServer.sin_addr.S_un.S_addr = aa;//�趨��������IP��ַ
//	addrServer.sin_addr.S_un.S_addr = inet_addr("192.168.1.215");//�趨��������IP��ַ

	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(ETH_PORT);//�趨�������Ķ˿ں�(ʹ�������ֽ���)

	err = connect(m_socket, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));//�������������������
	if (err == SOCKET_ERROR)
	{
		CString str;
		str.Format(_T("��������ʧ�ܣ������� %d\n"), WSAGetLastError());
//		AfxMessageBox(str);
		return -1;
	}
	m_bEthConnected = TRUE;
	return 0;
}

int CMyEth::OnCmd0(u8 cmd)
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnCmd0_Eth(cmd);
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyEth::OnCmd0_Eth(u8 cmd)
{
	char buff[64];
	int rlen;
	buff[0] = 2;
	buff[1] = cmd;
	if (EthConnect() != 0)
	{
		return -1;
	}
	int real_slen = send(m_socket, buff, buff[0], 0);
	if (real_slen != 2 )
	{
		return -1;
	}
	rlen = recv(m_socket, buff, 64, 0);
	if (rlen != 1)
	{
		return -2;
	}
	gSysState = buff[0];
	return 0;
}

int CMyEth::OnCmd1(u8 cmd, u8 slen, u8* sbuf, u8 rlen, u8* rbuf)
{
	int rev;
	EnterCriticalSection(&m_cs);
	rev = OnCmd1_Eth(cmd, slen, sbuf, rlen, rbuf);
	LeaveCriticalSection(&m_cs);
	return rev;
}

int CMyEth::OnCmd1_Eth(u8 cmd, u8 slen, u8* sbuf, u8 rlen, u8* rbuf)
{
	char buff[64];
	int i;
	if (EthConnect() != 0)
	{
		return -1;
	}

	buff[0] = slen + 2;
	buff[1] = cmd;
	for (i = 0; i < slen; i++)
	{
		buff[i + 2] = sbuf[i];
	}
	int real_slen = send(m_socket, buff, slen + 2, 0);
	if (real_slen != (slen + 2) )
	{
		return -1;
	}
	if (recv(m_socket, (char*)rbuf, 64, 0) != rlen)
	{
		return -1;
	}
	if (rlen == 1)
	{
		gSysState = rbuf[0];
	}
	return 0;
}

#define MAX_ETH_PACK_SIZE (1400)

int CMyEth::WriteBulk(char *pbBuf, ULONG len)
{
	int nPackSum;
	char rbuf[64];
	int i;
	if (EthConnect() != 0)
	{
		return -1;
	}
	nPackSum = len / MAX_ETH_PACK_SIZE;
	if (len % MAX_ETH_PACK_SIZE != 0)
	{
		nPackSum++;
	}
	for (i = 0; i < nPackSum; i++)
	{
		int real_slen = send(m_socket, (char*)(pbBuf + i*MAX_ETH_PACK_SIZE), MAX_ETH_PACK_SIZE, 0);
		if (real_slen != MAX_ETH_PACK_SIZE)
		{
			return -1;
		}
		int real_rlen = recv(m_socket, (char*)rbuf, 64, 0);
		if (real_rlen != 1)
		{
			return -1;
		}
		gSysState = rbuf[0];
		if (gSysState==READY)
		{
			return ERROR_CANCEL_FILE;
		}
//		Sleep(1);
	}
	return len;
}
