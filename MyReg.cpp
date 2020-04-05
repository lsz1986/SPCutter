// MyReg.cpp: implementation of the CMyReg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyReg.h"
#include "Global.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyReg::CMyReg()
{

}

CMyReg::~CMyReg()
{

}

int CMyReg::OnReadMbV2RegCode(CString str)
{
	int i;
	int DashSum=0;
	char tempch;
	if (str.GetLength() < 20)
	{
		return -1;
	}

	unsigned int codeSec1,codeSec2,codeSec3; //MCU CODE,终止时间,校验码
	codeSec1 = codeSec2 = codeSec3 = 0;
	for (i=0;i<str.GetLength();i++)
	{
		tempch = str.GetAt(i);
		if ('-' == 	tempch)
		{
			DashSum++;
			if (DashSum > 3)
			{
				return -1;
			}
			continue;
		}
		else if( (tempch < '0' ) || (tempch > '9') )
		{
			return -1;
		}
		
		switch (DashSum)
		{
		case 0:
			codeSec1 = codeSec1*10+tempch-'0';
			break;
			
		case 1:
			codeSec2 = codeSec2*10+tempch-'0';
			break;
			
		case 2:
			codeSec3 = codeSec3*10+tempch-'0';
			break;
		}
	}
	if (DashSum != 2 )
	{
		return -1;
	}

	m_nV2McuCode = codeSec1;
	m_nV2EndTime = codeSec2^YHZIntArray[codeSec1%13];
	if(codeSec3 == (m_nV2McuCode+m_nV2EndTime)/2 )
	{
		return 0;
	}
	m_nV2McuCode = 0;
	m_nV2EndTime = 0;
	return -1;
}

int CMyReg::OnCheckRegCode(CString strRegCode)
{
	int McuCode;
	int debCode;
	int Temp;
	if (gMacSet.getMachineLocked()) //打开程序后，时间往(从"前")调整导致的锁定
	{
		return -200;
	}
	McuCode = gUSB.OnGetChipID();
	if ( (McuCode < 0x70000000) || (McuCode > 0xe0000000) )
	{
		return -100;
	}

	gMacSet.setMcuCode(McuCode);
	Temp =  (int)(McuCode^0x66543688);
	debCode = gUSB.OnGetDeblockCode();
	if (debCode == Temp )
	{
		return 0;
	}

	if (0 != OnReadMbV2RegCode(strRegCode)){
		return -1;
	}

	if (m_nV2McuCode != (u32)(gMacSet.getMcuCode()) )
	{
		return -2;
	}

	CTime timeNow = CTime::GetCurrentTime();
	int iicLastTime = gUSB.OnGetLastTime(); //IIC中保存的LastTime
	if( (timeNow.GetTime()-iicLastTime) > 300) //超过5分钟
	{
		gUSB.OnSetLastTime( (u32)(timeNow.GetTime()) );
		delayus(1000); //等待iic写入完毕
	}
	else if( (timeNow.GetTime() - iicLastTime) < 0 )
	{
		return -3;
	}

	CTime EndTime = m_nV2EndTime;
	if ( timeNow.GetTime() > EndTime.GetTime() )
	{
		return -4;
	}
	return 0;
}

