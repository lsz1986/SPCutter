// DlgRegInfo.cpp : implementation file
//

#include "stdafx.h"
#include "SpCutter.h"
#include "DlgRegInfo.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRegInfo dialog


CDlgRegInfo::CDlgRegInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRegInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRegInfo)
	m_strPasswd = _T("");
	m_strAuthCode = _T("");
	m_strAuthSn = _T("");
	m_strEndDate = _T("");
	//}}AFX_DATA_INIT
}


void CDlgRegInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRegInfo)
	DDX_Text(pDX, IDCE_PASSWORD, m_strPasswd);
	DDV_MaxChars(pDX, m_strPasswd, 20);
	DDX_Text(pDX, IDCE_CODE, m_strAuthCode);
	DDX_Text(pDX, IDCE_SN, m_strAuthSn);
	DDX_Text(pDX, IDCE_END_DATE, m_strEndDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRegInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgRegInfo)
	ON_BN_CLICKED(IDCB_INPUT_REGCODE, OnInputRegCode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRegInfo message handlers

BOOL CDlgRegInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	GetDlgItem(IDCE_END_DATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCE_SN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCE_CODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TXT1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TXT2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCB_INPUT_REGCODE)->ShowWindow(SW_HIDE);
	m_strAuthCode = gSet.getAuthCode();
	m_strAuthSn = gSet.getMcuSn();

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRegInfo::OnOK()  //�������룬��ȷ����ť
{
	CString str1="gm";
	CString str2="83566125";
	CString str3="gm83566125";
	CString str4="gm02783566125";
	UpdateData(TRUE);
	if( (m_strPasswd.CompareNoCase(str1) == 0) 
		|| (m_strPasswd.CompareNoCase(str2) == 0) 
		|| (m_strPasswd.CompareNoCase(str3) == 0) 
		|| (m_strPasswd.CompareNoCase(str4) == 0) 
		)
	{
		GetDlgItem(IDCE_PASSWORD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TXT_PW)->ShowWindow(SW_HIDE);

		GetDlgItem(IDCE_END_DATE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDCE_SN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDCE_CODE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TXT1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TXT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDCB_INPUT_REGCODE)->ShowWindow(SW_SHOW);
	}
}

void CDlgRegInfo::OnInputRegCode() 
{
	int rev;
	CString strTemp;
	UpdateData();
	rev = gMyReg.OnCheckRegCode(m_strAuthCode);
	if( 0 == rev )
	{
		CTime EndTime;
		EndTime = gMyReg.m_nV2EndTime;
		m_strEndDate.Format("���³ɹ�Code:%d-%d-%d",EndTime.GetMonth(),EndTime.GetDay(),EndTime.GetYear()-2000);
		gSet.setAuthCode(m_strAuthCode);
	}
	else
	{
		switch(rev)
		{
		case -4:
			if (gDispSet.getLanguage() == 0){
				AfxMessageBox("ϵͳ��Ҫά��,������һ��δ֪���ڴ����,��ַ0x8356\n����ϵ���ؾ����̻���ֱ���µ���������\n�人�������ϿƼ����޹�˾\n�绰027-83566125");
			} else {
				AfxMessageBox("Authentication finished");
			}
			break;
			
		default:
			strTemp.Format("Auth Error%d",rev);
			AfxMessageBox(strTemp);
			break;
		}
	}
	UpdateData(FALSE);
}
