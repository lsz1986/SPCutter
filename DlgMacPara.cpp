// DlgMacPara.cpp : implementation file
//

#include "stdafx.h"
#include "SpCutter.h"
#include "DlgMacPara.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMacPara dialog


CDlgMacPara::CDlgMacPara(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMacPara::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMacPara)
	m_bSp1 = FALSE;
	m_bSp2 = FALSE;
	m_nLineWidth = 0;
	m_nJobEndHeadPos = 0;
	m_nKPDistX = 0;
	m_nKPDistY = 0;
	m_n10000X = 10000;
	m_n10000Y = 10000;
	m_nSpEx = 0;
	m_nSp12EY = 0;
	m_nSpDDy = 0;
	m_nKVolt_Start = 30;
	m_nKVolt_Work = 30;
	m_iAngleAdjust = 0;
	m_nAutoCutLen = 0;
	m_nOverCutLen = 0;
	m_nJobEndPosXmm = 0;
	m_nJobEndPosYmm = 0;
	m_nSp1LrDot = 0;
	m_nSp2LrDot = 0;
	m_bBiDir = FALSE;
	m_nLedLan = 0;
	//}}AFX_DATA_INIT
}

void CDlgMacPara::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMacPara)
	DDX_Control(pDX, IDC_COMBO_SP_TYPE, m_ComboSpType);
	DDX_Control(pDX, IDCMB_END_POS, m_ctrlComboEndPos);
	DDX_Check(pDX, IDCHK_SP1, m_bSp1);
	DDX_Check(pDX, IDCHK_SP2, m_bSp2);
	DDX_Text(pDX, IDCE_LINE_WIDTH, m_nLineWidth);
	DDV_MinMaxInt(pDX, m_nLineWidth, 1, 9);
	DDX_Text(pDX, IDCE_KPX, m_nKPDistX);
	DDV_MinMaxInt(pDX, m_nKPDistX, 0, 200);
	DDX_Text(pDX, IDCE_KPY, m_nKPDistY);
	DDV_MinMaxInt(pDX, m_nKPDistY, 0, 200);
	DDX_Text(pDX, IDCE_10000X, m_n10000X);
	DDV_MinMaxInt(pDX, m_n10000X, 9900, 10100);
	DDX_Text(pDX, IDCE_10000Y, m_n10000Y);
	DDV_MinMaxInt(pDX, m_n10000Y, 9900, 10100);
	DDX_Text(pDX, IDCE_SPEX, m_nSpEx);
	DDV_MinMaxInt(pDX, m_nSpEx, 0, 20);
	DDX_Text(pDX, IDCE_SP12EY, m_nSp12EY);
	DDV_MinMaxInt(pDX, m_nSp12EY, 110, 190);
	DDX_Text(pDX, IDCE_SPDDY, m_nSpDDy);
	DDV_MinMaxInt(pDX, m_nSpDDy, 0, 10);
	DDX_Text(pDX, IDCE_KVOLT_START, m_nKVolt_Start);
	DDV_MinMaxInt(pDX, m_nKVolt_Start, 10, 90);
	DDX_Text(pDX, IDCE_KVOLT_WORK, m_nKVolt_Work);
	DDV_MinMaxInt(pDX, m_nKVolt_Work, 10, 90);
	DDX_Text(pDX, IDCE_ANGLE_ADJUST, m_iAngleAdjust);
	DDV_MinMaxInt(pDX, m_iAngleAdjust, 50, 150);
	DDX_Text(pDX, IDCE_AUTO_CUT_LEN, m_nAutoCutLen);
	DDV_MinMaxInt(pDX, m_nAutoCutLen, 0, 200000);
	DDX_Text(pDX, IDCE_OVERCUT_LEN, m_nOverCutLen);
	DDV_MinMaxUInt(pDX, m_nOverCutLen, 0, 200);
	DDX_Text(pDX, IDCE_ENDPOS_X, m_nJobEndPosXmm);
	DDX_Text(pDX, IDCE_ENDPOS_Y, m_nJobEndPosYmm);
	DDX_Text(pDX, IDCE_SP_LRDOT1, m_nSp1LrDot);
	DDV_MinMaxUInt(pDX, m_nSp1LrDot, 20, 30);
	DDX_Text(pDX, IDCE_SP_LRDOT2, m_nSp2LrDot);
	DDV_MinMaxUInt(pDX, m_nSp2LrDot, 20, 30);
	DDX_Check(pDX, IDCHK_BIDIR, m_bBiDir);
	DDX_Text(pDX, IDCE_LED_LAN, m_nLedLan);
	DDV_MinMaxUInt(pDX, m_nLedLan, 0, 1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMacPara, CDialog)
	//{{AFX_MSG_MAP(CDlgMacPara)
	ON_BN_CLICKED(IDCHK_SP1, OnCheck1)
	ON_BN_CLICKED(IDCHK_SP2, OnCheck2)
	ON_BN_CLICKED(IDCB_PROTECT_PARA, OnProtectPara)
	ON_BN_CLICKED(IDCB_PARA_SAVE, OnParaSave)
	ON_BN_CLICKED(IDCB_PARA_RESTORE, OnParaRestore)
	ON_BN_CLICKED(IDCB_PARA_DEFAULT, OnParaDefault)
	ON_COMMAND(IDM_1209, On1209)
	ON_COMMAND(IDM_1509, On1509)
	ON_COMMAND(IDM_1510, On1510)
	ON_COMMAND(IDM_1512, On1512)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMacPara message handlers

BOOL CDlgMacPara::OnInitDialog() 
{
	CDialog::OnInitDialog();
// TODO: Add extra initialization here
	if (gDispSet.getLanguage() == 0) {
		m_ctrlComboEndPos.AddString("图形右下角");
		m_ctrlComboEndPos.AddString("指定坐标");
	}else{
		m_ctrlComboEndPos.AddString("X Max Y Min Of The Page");
		m_ctrlComboEndPos.AddString("Specified coordinates");
	}

	m_ComboSpType.AddString("HP45");
	m_ComboSpType.AddString("IUT308");

	OnUpdateParaToCtrl();

	if(g_bParaRead == FALSE)
	{
		GetDlgItem(IDCHK_SP1)->EnableWindow(FALSE); //喷头1
		GetDlgItem(IDCHK_SP2)->EnableWindow(FALSE); //喷头2
		GetDlgItem(IDCHK_BIDIR)->EnableWindow(FALSE); //双向打印
		GetDlgItem(IDC_COMBO_SP_TYPE)->EnableWindow(FALSE); //墨盒类型

		GetDlgItem(IDCE_OVERCUT_LEN)->EnableWindow(FALSE);
		GetDlgItem(IDCE_KVOLT_START)->EnableWindow(FALSE);
		GetDlgItem(IDCE_KVOLT_WORK)->EnableWindow(FALSE);

		GetDlgItem(IDCE_10000X)->EnableWindow(FALSE);
		GetDlgItem(IDCE_10000Y)->EnableWindow(FALSE);

		GetDlgItem(IDCE_SP_LRDOT1)->EnableWindow(FALSE);
		GetDlgItem(IDCE_SP_LRDOT2)->EnableWindow(FALSE);
		
		GetDlgItem(IDCE_ANGLE_ADJUST)->EnableWindow(FALSE);

		GetDlgItem(IDCE_KPX)->EnableWindow(FALSE);
		GetDlgItem(IDCE_KPY)->EnableWindow(FALSE);
		GetDlgItem(IDCE_SPEX)->EnableWindow(FALSE);
		GetDlgItem(IDCE_SP12EY)->EnableWindow(FALSE);

		GetDlgItem(IDCE_SPDDY)->EnableWindow(FALSE);
		GetDlgItem(IDCE_AUTO_CUT_LEN)->EnableWindow(FALSE);

		GetDlgItem(IDCMB_END_POS)->EnableWindow(FALSE);
		GetDlgItem(IDCE_ENDPOS_X)->EnableWindow(FALSE);
		GetDlgItem(IDCE_ENDPOS_Y)->EnableWindow(FALSE);

		GetDlgItem(IDCE_LED_LAN)->EnableWindow(FALSE);

		GetDlgItem(IDCB_PROTECT_PARA)->EnableWindow(FALSE);
		GetDlgItem(IDCB_PARA_SAVE)->EnableWindow(FALSE);
//		GetDlgItem(IDCB_PARA_RESTORE)->EnableWindow(FALSE);
		
		GetDlgItem(IDCE_LINE_WIDTH)->EnableWindow(FALSE);
		GetDlgItem(IDOK)->EnableWindow(FALSE);		
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMacPara::OnOK() 
{
// TODO: Add extra validation here
	UpdateData(TRUE);
	gMacSet.setLineWidth(m_nLineWidth);
	gMacSet.setOverCutLen(m_nOverCutLen);
	gMacSet.setBiDir(m_bBiDir);
	m_nSpType = m_ComboSpType.GetCurSel();
	gMacSet.setSpType(m_nSpType);

	gMacSet.set10000X(m_n10000X);
	gMacSet.set10000Y(m_n10000Y);

	gMacSet.setSP1DOTLR(m_nSp1LrDot);
	gMacSet.setSP2DOTLR(m_nSp2LrDot);

	m_nJobEndHeadPos = m_ctrlComboEndPos.GetCurSel();
	gMacSet.setJobEndHeadPos(m_nJobEndHeadPos);

	gMacSet.setJobEndPosXmm(m_nJobEndPosXmm);
	gMacSet.setJobEndPosYmm(m_nJobEndPosYmm);

	gMacSet.setKPDistX(m_nKPDistX);
	gMacSet.setKPDistY(m_nKPDistY);
	gMacSet.setSpEX(m_nSpEx);
	gMacSet.setSp12EY(m_nSp12EY);
	gMacSet.setBiDir(m_bBiDir);
	gMacSet.setSpDDY(m_nSpDDy);
	gMacSet.setLedLan(m_nLedLan);

	gMacSet.setPwmKStart(m_nKVolt_Start);
	gMacSet.setPwmKWork(m_nKVolt_Work);

	gMacSet.setAngleAdjust(m_iAngleAdjust);
	gMacSet.setCutEndPosYmm(m_nAutoCutLen);

	if( (m_bSp1 == TRUE)&&(m_bSp2 == FALSE) )
	{
		gMacSet.setSpStat(1);
	}
	else if( (m_bSp1 == FALSE)&&(m_bSp2 == TRUE) )
	{
		gMacSet.setSpStat(2);
	}
	else
	{
		gMacSet.setSpStat(0);
	}

	if(g_bParaRead == TRUE)
	{
		WritePlotPara();
	}

	CDialog::OnOK();
}

void CDlgMacPara::OnCheck1() 
{
	m_bSp1 = !m_bSp1;
	if( (m_bSp1 == FALSE) && (m_bSp2 == FALSE) )
	{
		m_bSp2 = TRUE;
	}
	UpdateData(FALSE);
}

void CDlgMacPara::OnCheck2() 
{
	m_bSp2 = !m_bSp2;
	if( (m_bSp1 == FALSE) && (m_bSp2 == FALSE) )
	{
		m_bSp1 = TRUE;
	}
	UpdateData(FALSE);
}

#include "DlgProtectPara.h"
void CDlgMacPara::OnProtectPara() 
{
	// TODO: Add your control notification handler code here
	CDlgProtectPara dlg;
	dlg.DoModal();
}

void CDlgMacPara::OnUpdateParaToCtrl()
{
	m_nLineWidth = gMacSet.getLineWidth();
	m_ctrlComboEndPos.SetCurSel(gMacSet.getJobEndHeadPos());
	m_ComboSpType.SetCurSel(gMacSet.getSpType());
	
	m_nJobEndHeadPos = gMacSet.getJobEndHeadPos();
	m_nJobEndPosXmm = gMacSet.getJobEndPosXmm();
	m_nJobEndPosYmm = gMacSet.getJobEndPosYmm();
	
	m_nKPDistX = gMacSet.getKPDistX();
	m_nKPDistY = gMacSet.getKPDistY();
	
	m_n10000X = gMacSet.get10000X();
	m_n10000Y = gMacSet.get10000Y();
	
	m_nSp1LrDot = gMacSet.getSP1DOTLR();
	m_nSp2LrDot = gMacSet.getSP2DOTLR();
	
	m_nSpEx = gMacSet.getSpEX();
	
	m_nSp12EY = gMacSet.getSp12EY();
	
	m_nSpDDy = gMacSet.getSpDDY();
	
	m_nOverCutLen = gMacSet.getOverCutLen();
	
	m_iAngleAdjust = gMacSet.getAngleAdjust();
	
	m_nKVolt_Start = gMacSet.getPwmKStart();
	m_nKVolt_Work = gMacSet.getPwmKWork();
	
	m_nAutoCutLen = gMacSet.getCutEndPosYmm();
	
	m_bBiDir = gMacSet.getBiDir();

	m_nLedLan = gMacSet.getLedLan();

	switch (gMacSet.getSpStat())
	{
	case 1:
		m_bSp1 = TRUE;
		m_bSp2 = FALSE;
		break;
		
	case 2:
		m_bSp1 = FALSE;
		m_bSp2 = TRUE;
		break;
		
	default:
		m_bSp1 = TRUE;
		m_bSp2 = TRUE;
		break;
	}
	
	UpdateData(FALSE);
}


void CDlgMacPara::OnParaDefault() 
{
	CMenu menu;
	menu.LoadMenu(IDR_MENU_PARA_DEF);
	CPoint pt;
	GetCursorPos(&pt);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, pt.x, pt.y, this);
	return;	
}

void CDlgMacPara::On1209() 
{
	OnRestorePara(gMacSet.m_strAppDir+"para\\出厂1209.v6scp");	
}

void CDlgMacPara::On1509() 
{
	OnRestorePara(gMacSet.m_strAppDir+"para\\出厂1509.v6scp");
}

void CDlgMacPara::On1510()
{
	OnRestorePara(gMacSet.m_strAppDir+"para\\出厂1510.v6scp");
}

void CDlgMacPara::On1512() 
{
	OnRestorePara(gMacSet.m_strAppDir+"para\\出厂1512.v6scp");
}

void CDlgMacPara::OnRestorePara(CString ParaFileName)
{
	CFile scpFile;
	if (FALSE == scpFile.Open(ParaFileName,CFile::modeRead|CFile::typeBinary))
	{
		if (gDispSet.getLanguage() == 0){
			AfxMessageBox("打开文件失败");
		}else{
			AfxMessageBox("Failed To Open File");
		}
		return;
	}
	UNION_MAC_PARA tepmPara;
	scpFile.Read(&tepmPara.charBuff[0],MAC_PARA_SIZE);
	scpFile.Close();
	gPara = tepmPara.stBuff;
	gParaTogSet();
	
	gMacSet.setOverCutLen(0); //恢复参数时
	gMacSet.setLineWidth(1); //恢复参数时
	OnUpdateParaToCtrl();
	return;	
}

void CDlgMacPara::OnParaSave() 
{
	char Custer[80] = "喷切参数文件(*.v6scp)\0*.v6scp\0\0\0";
	CFileDialog dlg(FALSE);
	dlg.m_ofn.lpstrFilter = Custer;
	
	if(dlg.DoModal() == IDOK)
	{
		CString strFileName = dlg.GetPathName();
		CFile scpFile;
		
		int nFileNameLen = strFileName.GetLength();
		if (nFileNameLen<7)
		{
			strFileName += ".v6scp";
		}
		else
		{
			if( (strFileName.GetAt(nFileNameLen-6) == '.' ) &&
				(toupper(strFileName.GetAt(nFileNameLen-5)) == 'V' ) &&
				(toupper(strFileName.GetAt(nFileNameLen-4)) == '6' ) &&
				(toupper(strFileName.GetAt(nFileNameLen-3)) == 'S' ) &&
				(toupper(strFileName.GetAt(nFileNameLen-2)) == 'C' ) &&
				(toupper(strFileName.GetAt(nFileNameLen-1)) == 'P' ) 
				)
			{
			}
			else
			{
				strFileName += ".v6scp";
			}
		}
		
		scpFile.Open(strFileName,CFile::modeCreate|CFile::modeReadWrite|CFile::typeBinary);
		UNION_MAC_PARA tepmPara;
		tepmPara.stBuff = gPara;
		scpFile.Write(&tepmPara.charBuff[0],MAC_PARA_SIZE);
		scpFile.Close();
	}
}

void CDlgMacPara::OnParaRestore() 
{
	char Custer[80] = "喷切参数文件(*.v6scp)\0*.v6scp\0\0\0";
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrFilter = Custer;
	
	if(dlg.DoModal() == IDOK)
	{
		CString strFileName = dlg.GetPathName();
		OnRestorePara(strFileName);
	}
}

