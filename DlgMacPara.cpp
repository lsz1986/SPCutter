// DlgMacPara.cpp : implementation file
//

#include "stdafx.h"
#include "SpCutter.h"
#include "DlgMacPara.h"
extern CWinThread* gThrdWork;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMacPara dialog


CDlgMacPara::CDlgMacPara(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMacPara::IDD, pParent)
	, m_bJobAutoStart(FALSE)
{
	//{{AFX_DATA_INIT(CDlgMacPara)
	m_bSp1 = FALSE;
	m_bSp2 = FALSE;
	m_nBlankMM = 0;
	m_bPlotOnly = FALSE;
	m_bAutoClean = FALSE;
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
	m_iAngleAdjust = 100;
	m_nCutPaperStart = 0;
	m_nCutPaperEnd = 0;
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
	DDV_MinMaxInt(pDX, m_nKPDistX, 0, 100);
	DDX_Text(pDX, IDCE_KPY, m_nKPDistY);
	DDV_MinMaxInt(pDX, m_nKPDistY, 0, 100);
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
	DDX_Text(pDX, IDCE_CUT_PAPER_STSRT, m_nCutPaperStart);
	DDV_MinMaxInt(pDX, m_nCutPaperStart, 0, 200000);
	DDX_Text(pDX, IDCE_CUT_PAPER_END, m_nCutPaperEnd);
	DDV_MinMaxInt(pDX, m_nCutPaperEnd, 0, 200000);
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
	DDX_Control(pDX, IDTXT_DATADIR, m_hyperLinkDataDir);
	DDX_Text(pDX, IDCE_BLANKMM, m_nBlankMM);
	DDV_MinMaxInt(pDX, m_nBlankMM, 0, 100);
	DDX_Check(pDX, IDCHK_ONLYPLOT, m_bPlotOnly);
	DDX_Check(pDX, IDCHK_CLEANSP, m_bAutoClean);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDCHK_JOB_AUTO_START, m_bJobAutoStart);
	DDX_Control(pDX, IDC_IPADDR, m_ctrlMachineAddr);
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
	ON_BN_CLICKED(IDCB_SET_AUTO_DIR, &CDlgMacPara::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDlgMacPara::OnBnClickedOk)
	ON_BN_CLICKED(IDCB_IP_DEFAULT, &CDlgMacPara::OnBnClickedIpDefault)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMacPara message handlers

BOOL CDlgMacPara::OnInitDialog() 
{
	CDialog::OnInitDialog();
	unsigned char IpSec[4];
	
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

	IpSec[0] = m_nIpAddr & 0xff;
	IpSec[1] = (m_nIpAddr >> 8) & 0xff;
	IpSec[2] = (m_nIpAddr >> 16) & 0xff;
	IpSec[3] = (m_nIpAddr >> 24) & 0xff;

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
		GetDlgItem(IDCE_CUT_PAPER_STSRT)->EnableWindow(FALSE);
		GetDlgItem(IDCE_CUT_PAPER_END)->EnableWindow(FALSE);

		GetDlgItem(IDCMB_END_POS)->EnableWindow(FALSE);
		GetDlgItem(IDCE_ENDPOS_X)->EnableWindow(FALSE);
		GetDlgItem(IDCE_ENDPOS_Y)->EnableWindow(FALSE);

		GetDlgItem(IDCE_LED_LAN)->EnableWindow(FALSE);

//		GetDlgItem(IDCB_PROTECT_PARA)->EnableWindow(FALSE);
		GetDlgItem(IDCB_PARA_SAVE)->EnableWindow(FALSE);

		GetDlgItem(IDCE_LINE_WIDTH)->EnableWindow(FALSE);
//		GetDlgItem(IDOK)->EnableWindow(FALSE);		
	}
	m_ctrlMachineAddr.SetAddress(IpSec[0], IpSec[1], IpSec[2], IpSec[3]);

	GetDlgItem(IDTXT_DATADIR)->SetWindowText(gSet.m_strDataDir);
	m_hyperLinkDataDir.SetURL(gSet.m_strDataDir);
	m_strTempDataDir = gSet.m_strDataDir;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
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

#include "DlgPwdInput.h"
#include "DlgProtectPara.h"
void CDlgMacPara::OnProtectPara() 
{
	CDlgPwdInput dlg;
	if (IDOK == dlg.DoModal())
	{
		if (dlg.m_strPwd == "gm")
		{
			CDlgProtectPara dlg;
			dlg.DoModal();
		}
		else
		{
			AfxMessageBox("密码错误");
		}
	}
}

void CDlgMacPara::OnUpdateParaToCtrl()
{
	m_bJobAutoStart = gSet.getJobAutoStart();
	m_bBiDir = gSet.getBiDir();
	m_bPlotOnly = gSet.getOnlyPlot();
	m_bAutoClean = gSet.getSpAutoClean();

	m_nLineWidth = gSet.getLineWidth();
	m_ctrlComboEndPos.SetCurSel(gSet.getJobEndHeadPos());
	m_ComboSpType.SetCurSel(gSet.getSpType());
	
	m_nJobEndHeadPos = gSet.getJobEndHeadPos();
	m_nJobEndPosXmm = gSet.getJobEndPosXmm();
	m_nJobEndPosYmm = gSet.getJobEndPosYmm();
	
	m_nKPDistX = gSet.getKPDistX();
	m_nKPDistY = gSet.getKPDistY();
	
	m_n10000X = gSet.get10000X();
	m_n10000Y = gSet.get10000Y();
	
	m_nSp1LrDot = gSet.getSP1DOTLR();
	m_nSp2LrDot = gSet.getSP2DOTLR();
	
	m_nSpEx = gSet.getSpEX();
	
	m_nSp12EY = gSet.getSp12EY();
	
	m_nSpDDy = gSet.getSpDDY();
	
	m_nOverCutLen = gSet.getOverCutLen();
	
	m_iAngleAdjust = gSet.getAngleAdjust();
	
	m_nKVolt_Start = gSet.getPwmKStart();
	m_nKVolt_Work = gSet.getPwmKWork();
	
	m_nCutPaperStart = gSet.getCutPaperStartYmm();
	m_nCutPaperEnd = gSet.getCutPaperEndYmm();

	m_nLedLan = gSet.getLedLan();
	m_nBlankMM = gSet.getYBlankMm();

	switch (gSet.getSpStat())
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
	m_nIpAddr = gSet.getMachineIpAddr();
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
	OnRestorePara(gSet.m_strAppDir+"para\\出厂1209.v6scp");	
}

void CDlgMacPara::On1509() 
{
	OnRestorePara(gSet.m_strAppDir+"para\\出厂1509.v6scp");
}

void CDlgMacPara::On1510()
{
	OnRestorePara(gSet.m_strAppDir+"para\\出厂1510.v6scp");
}

void CDlgMacPara::On1512() 
{
	OnRestorePara(gSet.m_strAppDir+"para\\出厂1512.v6scp");
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

	scpFile.Read(&gPara,MAC_PARA_SIZE);
	scpFile.Close();
	gParaTogSet();
	
	gSet.setOverCutLen(0); //恢复参数时
	gSet.setLineWidth(1); //恢复参数时
	gSet.setYBlankMm(0);
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
		scpFile.Write(&gPara,MAC_PARA_SIZE);
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

void CDlgMacPara::OnBnClickedButton1()
{
	CString str;
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = GetSafeHwnd();
	bi.pszDisplayName = name;
	str.Format("选择绘图文件存放的目录");
	bi.lpszTitle = str;//"选择绘图文件存放的目录";
	bi.ulFlags = 0;

	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (idl == NULL)
		return;

	SHGetPathFromIDList(idl, str.GetBuffer(MAX_PATH));
	str.ReleaseBuffer();
	str += "\\";

	if ((str == gSet.m_strAppDir) || (str.GetLength() < 3))
	{
		CString str;
		str.Format("非法的临时文件目录");
		MessageBox(str);
	}
	else
	{
		if (FALSE == DirIsEmpty(str)) //当前目录非空
		{
			if (IDOK == MessageBox("当前设置的目录非空，\n如果设置成自动绘图目录，\n当前目录下的文件将被删除。\n是否继续？", "警告！！！", MB_ICONWARNING | MB_OKCANCEL))
			{
				m_strTempDataDir = str;
				if (str.GetAt(str.GetLength() - 1) != '\\')
					m_strTempDataDir += "\\";
			}
		}
		else
		{
			m_strTempDataDir = str;
			if (str.GetAt(str.GetLength() - 1) != '\\')
				m_strTempDataDir += "\\";
		}
	}
	GetDlgItem(IDTXT_DATADIR)->SetWindowText(m_strTempDataDir);
	m_hyperLinkDataDir.SetURL(m_strTempDataDir);
	gSet.m_strDataDir = m_strTempDataDir;
	Invalidate();
}

BOOL CDlgMacPara::DirIsEmpty(CString strDir)
{
	BOOL bFindFile;
	CFileFind fileFind;
	bFindFile = fileFind.FindFile(strDir + "*.*");
	if (FALSE == bFindFile)
	{
		return TRUE;
	}

	while (TRUE == bFindFile)
	{
		bFindFile = fileFind.FindNextFile();
		if ((!fileFind.IsDirectory()) && (!fileFind.IsDots()))
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CDlgMacPara::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned char IpSec[4];
	UpdateData(TRUE);
	gSet.setBiDir(m_bBiDir);
	gSet.setJobAutoStart(m_bJobAutoStart);

	gSet.setOverCutLen(m_nOverCutLen);
	m_nSpType = m_ComboSpType.GetCurSel();
	gSet.setSpType(m_nSpType);

	gSet.set10000X(m_n10000X);
	gSet.set10000Y(m_n10000Y);

	gSet.setSP1DOTLR(m_nSp1LrDot);
	gSet.setSP2DOTLR(m_nSp2LrDot);

	m_nJobEndHeadPos = m_ctrlComboEndPos.GetCurSel();
	gSet.setJobEndHeadPos(m_nJobEndHeadPos);

	gSet.setJobEndPosXmm(m_nJobEndPosXmm);
	gSet.setJobEndPosYmm(m_nJobEndPosYmm);

	gSet.setKPDistX(m_nKPDistX);
	gSet.setKPDistY(m_nKPDistY);
	gSet.setSpEX(m_nSpEx);
	gSet.setSp12EY(m_nSp12EY);
	gSet.setBiDir(m_bBiDir);
	gSet.setSpDDY(m_nSpDDy);
	gSet.setLedLan(m_nLedLan);

	gSet.setPwmKStart(m_nKVolt_Start);
	gSet.setPwmKWork(m_nKVolt_Work);

	gSet.setAngleAdjust(m_iAngleAdjust);
	gSet.setCutPaperStartYmm(m_nCutPaperStart);
	gSet.setCutPaperEndYmm(m_nCutPaperEnd);

	m_ctrlMachineAddr.GetAddress(IpSec[0], IpSec[1], IpSec[2], IpSec[3]);
	m_nIpAddr = IpSec[0] | (IpSec[1] << 8) | (IpSec[2] << 16) | (IpSec[3] << 24);
	gSet.setMachineIpAddr(m_nIpAddr);

	if ((m_bSp1 == TRUE) && (m_bSp2 == FALSE))
	{
		gSet.setSpStat(1);
	}
	else if ((m_bSp1 == FALSE) && (m_bSp2 == TRUE))
	{
		gSet.setSpStat(2);
	}
	else
	{
		gSet.setSpStat(0);
	}

	if ((gSysState & 0x0f) == READY)
	{
		gSet.setQueryEnable(FALSE);
		WritePlotPara();
		gSet.setQueryEnable(TRUE);
	}
	else if (gThrdWork != NULL)
	{
		gSet.setParaUpdateFlag(TRUE);
	}

	//-----------------------仅输出中心保存的参数0
	gSet.setSpAutoClean(m_bAutoClean);
	gSet.setOnlyPlot(m_bPlotOnly);
	gSet.setYBlankMm(m_nBlankMM);
	gSet.setLineWidth(m_nLineWidth);
	//------------------------

	CDialog::OnOK();
}


void CDlgMacPara::OnBnClickedIpDefault()
{
	m_ctrlMachineAddr.SetAddress(192, 168, 1, 218);
}
