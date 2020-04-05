// CSetMac.cpp: implementation of the CSettings class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpCutter.h"
#include "MacSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BOOL FreeResFile(DWORD dwResID, LPCTSTR lpszResType, LPCTSTR lpszFilePathName);

CSetMac::CSetMac()
{
	m_bJobAutoStart = FALSE;
	m_bWorkStartPause = FALSE;
	m_bMachineLocked = FALSE;

	m_dPPMMX = 104.1111150;
	m_dPPMMY = 104.1111150;

	m_nLineWidth = 1; //线宽
	m_nSpEX = 0; //喷头重叠
	m_nSp12EY = 150; //喷头间距

	m_nSpDDY = 0; //双向误差

	m_nJobEndHeadPos = 0;

	m_nKPDistX = 0; //刀笔补偿
	m_nKPDistY = 0;

	m_n1000X = 10000; //比例调整
	m_n1000Y = 10000; //比例调整

	m_nSpdCut = 3;
	m_nSpdMove = 3;

	m_nPwmKStart = 20; //启动刀压
	m_nPwmKWork = 20; //工作刀压

	m_nToolBarState = TBS_SEL;
}

CSetMac::~CSetMac()
{
}

void CSetMac::getAppDir()
{
    TCHAR szFullPath[_MAX_PATH];
    TCHAR szDir[_MAX_DIR];
    TCHAR szDrive[_MAX_DRIVE];
    ::GetModuleFileName(NULL, szFullPath, _MAX_PATH);

    _splitpath(szFullPath, szDrive, szDir, NULL, NULL);
	m_strAppDir.Format(_T("%s%s"), szDrive, szDir);

	TCHAR szTempPath[_MAX_PATH];
	CString strTempPath;
	GetTempPath(MAX_PATH, szTempPath);
	strTempPath.Format( _T("%s"), szTempPath );

	m_strFonHz.Format( _tcsdup(strTempPath + "fon_hz.bin") );
	m_strFonEn.Format( _tcsdup(strTempPath + "fon_en.bin") );

	DeleteFile(m_strFonHz);
	DeleteFile(m_strFonEn);
	FreeResFile(IDR_FON_EN, "fon", m_strFonEn);
	FreeResFile(IDR_FON_HZ, "fon", m_strFonHz);
}

void CSetMac::checkDataDir()
{
	CFileFind fFind;
	CString strTempDataDir;
	SECURITY_ATTRIBUTES attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength = sizeof(SECURITY_ATTRIBUTES); 

	if (m_strDataDir.GetLength() == 0) //第一次
	{
		m_strDataDir.Format( _tcsdup(m_strAppDir + "plot\\") );
	}
	
	strTempDataDir = m_strDataDir;
	if (strTempDataDir.GetAt(strTempDataDir.GetLength()-1) == '\\') //检测目录存在需要去掉
	{
		strTempDataDir.SetAt(strTempDataDir.GetLength()-1, 0);
	}

	if( ( m_strDataDir.GetLength() < 3 )  // 目录不合法 
		|| (FALSE == fFind.FindFile(strTempDataDir)) //目录不存在 
		|| m_strDataDir == m_strAppDir) //目录与当前程序目录相同
	{
		m_strDataDir.Format( _tcsdup(m_strAppDir + "plot\\") );
		strTempDataDir = m_strDataDir;
		if (strTempDataDir.GetAt(strTempDataDir.GetLength()-1) == '\\') //检测目录存在需要去掉
		{
			strTempDataDir.SetAt(strTempDataDir.GetLength()-1, 0);
		}
		if (FALSE == fFind.FindFile(strTempDataDir) )
		{
			CreateDirectory(strTempDataDir,&attrib);
		}
	}
}

BOOL FreeResFile(DWORD dwResID, LPCTSTR lpszResType, LPCTSTR lpszFilePathName)  
{     
    HMODULE hInstance = ::GetModuleHandle(NULL);//得到自身实例句柄  
	
    HRSRC   hResID = ::FindResource(hInstance, MAKEINTRESOURCE(dwResID), lpszResType); //查找资源
    HGLOBAL hRes   = ::LoadResource(hInstance, hResID); //加载资源  
    LPVOID  pRes   = ::LockResource(hRes); //锁定资源  
	
    if (NULL == pRes) //锁定失败  
    {  
        return FALSE;  
    }  
    DWORD  dwResSize = ::SizeofResource(hInstance, hResID); //得到待释放资源文件大小  
    HANDLE hResFile  = CreateFile(
		lpszFilePathName,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);   
    if (INVALID_HANDLE_VALUE == hResFile)  
    {  
        return FALSE;  
    }  
	
    DWORD dwWritten = 0; //写入文件的大小     
    WriteFile(hResFile, pRes, dwResSize, &dwWritten, NULL); //写入文件  
    CloseHandle(hResFile); //关闭文件句柄
	
	FreeResource(hRes);
	
    return (dwResSize == dwWritten); //若写入大小等于文件大小，返回成功，否则失败  
}

