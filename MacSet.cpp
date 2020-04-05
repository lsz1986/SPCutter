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

	m_nLineWidth = 1; //�߿�
	m_nSpEX = 0; //��ͷ�ص�
	m_nSp12EY = 150; //��ͷ���

	m_nSpDDY = 0; //˫�����

	m_nJobEndHeadPos = 0;

	m_nKPDistX = 0; //���ʲ���
	m_nKPDistY = 0;

	m_n1000X = 10000; //��������
	m_n1000Y = 10000; //��������

	m_nSpdCut = 3;
	m_nSpdMove = 3;

	m_nPwmKStart = 20; //������ѹ
	m_nPwmKWork = 20; //������ѹ

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

	if (m_strDataDir.GetLength() == 0) //��һ��
	{
		m_strDataDir.Format( _tcsdup(m_strAppDir + "plot\\") );
	}
	
	strTempDataDir = m_strDataDir;
	if (strTempDataDir.GetAt(strTempDataDir.GetLength()-1) == '\\') //���Ŀ¼������Ҫȥ��
	{
		strTempDataDir.SetAt(strTempDataDir.GetLength()-1, 0);
	}

	if( ( m_strDataDir.GetLength() < 3 )  // Ŀ¼���Ϸ� 
		|| (FALSE == fFind.FindFile(strTempDataDir)) //Ŀ¼������ 
		|| m_strDataDir == m_strAppDir) //Ŀ¼�뵱ǰ����Ŀ¼��ͬ
	{
		m_strDataDir.Format( _tcsdup(m_strAppDir + "plot\\") );
		strTempDataDir = m_strDataDir;
		if (strTempDataDir.GetAt(strTempDataDir.GetLength()-1) == '\\') //���Ŀ¼������Ҫȥ��
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
    HMODULE hInstance = ::GetModuleHandle(NULL);//�õ�����ʵ�����  
	
    HRSRC   hResID = ::FindResource(hInstance, MAKEINTRESOURCE(dwResID), lpszResType); //������Դ
    HGLOBAL hRes   = ::LoadResource(hInstance, hResID); //������Դ  
    LPVOID  pRes   = ::LockResource(hRes); //������Դ  
	
    if (NULL == pRes) //����ʧ��  
    {  
        return FALSE;  
    }  
    DWORD  dwResSize = ::SizeofResource(hInstance, hResID); //�õ����ͷ���Դ�ļ���С  
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
	
    DWORD dwWritten = 0; //д���ļ��Ĵ�С     
    WriteFile(hResFile, pRes, dwResSize, &dwWritten, NULL); //д���ļ�  
    CloseHandle(hResFile); //�ر��ļ����
	
	FreeResource(hRes);
	
    return (dwResSize == dwWritten); //��д���С�����ļ���С�����سɹ�������ʧ��  
}

