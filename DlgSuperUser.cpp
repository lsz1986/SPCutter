// DlgSuperUser.cpp : implementation file
//

#include "stdafx.h"
#include "SpCutter.h"
#include "DlgSuperUser.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSuperUser dialog


CDlgSuperUser::CDlgSuperUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSuperUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSuperUser)
	m_strRandCode = _T("");
	m_nRandPw = 0;
	//}}AFX_DATA_INIT
}


void CDlgSuperUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSuperUser)
	DDX_Text(pDX, IDTXT_RAND_CODE, m_strRandCode);
	DDX_Text(pDX, IDCE_RANDPW, m_nRandPw);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSuperUser, CDialog)
	//{{AFX_MSG_MAP(CDlgSuperUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSuperUser message handlers


BOOL CDlgSuperUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CTime time=CTime::GetCurrentTime();
	srand(time.GetSecond()*13+time.GetHour()*29);
	int a=rand();
	m_nRandSN = a%0x0fff;
	m_nRandSN += 0x1000;
	int MBSN1;
	int MBSN2;
	unsigned int MBSNALL = gSet.getMcuCode();
	MBSN1 = MBSNALL&0xffff;
	MBSN2 = (MBSNALL>>8)&0xffff;
	m_strRandCode.Format("%d+%d",MBSN1+MBSN2,m_nRandSN);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSuperUser::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	int MBSN1;
	int MBSN2;
	int mmccuu;

	u8 sbuf[64];
	u8 rbuf[64];

	unsigned int MBSNALL = gSet.getMcuCode();
	MBSN1 = MBSNALL&0xffff;
	MBSN2 = (MBSNALL>>8)&0xffff;
	int MBSN12 = MBSN1+MBSN2; 
	if( MBSN12/5+YHZIntArray[MBSN12%16]/13+YHZIntArray[m_nRandSN%16]/17+m_nRandSN*7 == m_nRandPw)
	{
		CTime timeNow = CTime::GetCurrentTime();
		*((int*)(&sbuf[0])) = (u32)(timeNow.GetTime());
		if (0 == gCommu.OnCmd1(CMD1_SET_LASTTIME, 4, sbuf, 1, rbuf)) // ((u32)(timeNow.GetTime())))
		{
 			AfxMessageBox("OK");
 			CDialog::OnOK();
 		}
	}
	else if( MBSN12/7+YHZIntArray[MBSN12%13]/13+YHZIntArray[m_nRandSN%16]/19+m_nRandSN*5 == m_nRandPw)
	{
		mmccuu = gSet.getMcuCode();
		*( (int*)(&sbuf[0])) = (int)(mmccuu ^ 0x66543688);
		int rev = gCommu.OnCmd1(CMD1_SET_UL_CODE, 4, sbuf, 1, rbuf);
		if (0 == rev)
 		{
 			AfxMessageBox("Deblocked");
 			CDialog::OnOK();
 		}
	}
	else if(334433 == m_nRandPw)
	{
		*((int*)(&sbuf[0])) = (int)(0x1234);
		int rev = gCommu.OnCmd1(CMD1_SET_UL_CODE, 4, sbuf, 1, rbuf); //
		if (0 == rev)
 		{
 			AfxMessageBox("Block enabled");
 			CDialog::OnOK();
 		}
	}
	else
	{
		AfxMessageBox("认证码不正确");
	}
}
