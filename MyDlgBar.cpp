// MyDlgBar.cpp : implementation file
//

#include "stdafx.h"
#include "spcutter.h"
#include "MyDlgBar.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBar dialog


CMyDlgBar::CMyDlgBar(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CMyDlgBar)
	m_bJobAutoStart = FALSE;
	m_bOnlyPlot = FALSE;
	m_bAutoCleanOn = FALSE;
	m_nYBlankMm = 0;
	//}}AFX_DATA_INIT
}


void CMyDlgBar::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CMyDlgBar)
	DDX_Control(pDX, IDTXT_DATADIR, m_hyperLinkDataDir);
	DDX_Check(pDX, IDCHK_AUTO_WORK, m_bJobAutoStart);
	DDX_Check(pDX, IDCHK_ONLYPLOT, m_bOnlyPlot);
	DDX_Check(pDX, IDCHK_AUTO_CLEANSP, m_bAutoCleanOn);
	DDX_Text(pDX, IDCE_BLANK_MM, m_nYBlankMm);
	DDV_MinMaxInt(pDX, m_nYBlankMm, 0, 500);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlgBar, CDialogBar)
	//{{AFX_MSG_MAP(CMyDlgBar)
	ON_BN_CLICKED(IDCB_SET_AUTO_DIR, OnSetAutoDir)
	ON_BN_CLICKED(IDCHK_ONLYPLOT, OnOnlyplot)
	ON_BN_CLICKED(IDCHK_AUTO_WORK, OnAutoWork)
	ON_BN_CLICKED(IDCHK_AUTO_CLEANSP, OnAutoCleansp)
	ON_MESSAGE(WM_INITDIALOG,OnInitDialog)
	ON_BN_CLICKED(IDCB_APPLY_BLANK_MM, OnApplyBlankMm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBar message handlers

BOOL CMyDlgBar::DirIsEmpty(CString strDir)
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

LRESULT CMyDlgBar::OnInitDialog(UINT wParam,LONG lParam) 
{
	BOOL bRet = HandleInitDialog(wParam,lParam);
	if (!UpdateData(FALSE))
	{
		TRACE("InitCDataStatus Failed！");
	}

	GetDlgItem(IDTXT_DATADIR)->SetWindowText(gMacSet.m_strDataDir);
	m_hyperLinkDataDir.SetURL(gMacSet.m_strDataDir);
	m_strTempDataDir = gMacSet.m_strDataDir;
	m_bJobAutoStart = gMacSet.getJobAutoStart();
	m_bOnlyPlot = gMacSet.getOnlyPlot();
	m_bAutoCleanOn = gMacSet.getSpAutoClean();
	m_nYBlankMm = gMacSet.getYBlankMm();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyDlgBar::OnOnlyplot() 
{
	UpdateData(TRUE);
	gMacSet.setOnlyPlot(m_bOnlyPlot);
}

void CMyDlgBar::OnAutoWork() 
{
	UpdateData(TRUE);
	gMacSet.setJobAutoStart(m_bJobAutoStart);
}

void CMyDlgBar::OnAutoCleansp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	gMacSet.setSpAutoClean(m_bAutoCleanOn);
}

void CMyDlgBar::OnSetAutoDir() 
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
    if(idl == NULL)
        return;
	
    SHGetPathFromIDList(idl, str.GetBuffer(MAX_PATH));
    str.ReleaseBuffer();
	str += "\\";
	
	if( (str == gMacSet.m_strAppDir)||(str.GetLength()<3) )
	{
		CString str;
		str.Format("非法的临时文件目录");
		MessageBox(str);
	}
	else
	{
		if (FALSE == DirIsEmpty(str)) //当前目录非空
		{
			if (IDOK == MessageBox("当前设置的目录非空，\n如果设置成自动绘图目录，\n当前目录下的文件将被删除。\n是否继续？","警告！！！",MB_ICONWARNING | MB_OKCANCEL))
			{
				m_strTempDataDir = str;
				if(str.GetAt(str.GetLength() - 1) != '\\')
					m_strTempDataDir += "\\";
			}
		}
		else
		{
			m_strTempDataDir = str;
			if(str.GetAt(str.GetLength() - 1) != '\\')
				m_strTempDataDir += "\\";
		}
	}
	
	GetDlgItem(IDTXT_DATADIR)->SetWindowText(m_strTempDataDir);
	m_hyperLinkDataDir.SetURL(m_strTempDataDir);
	gMacSet.m_strDataDir = m_strTempDataDir;
	Invalidate();
}


void CMyDlgBar::OnApplyBlankMm() 
{
	UpdateData(TRUE);
	gMacSet.setYBlankMm(m_nYBlankMm);
}
