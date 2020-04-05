// CutPlotter.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SpCutter.h"

#include "MainFrm.h"
#include "SpCutterDoc.h"
#include "SpCutterView.h"

#include "Global.h"
#include "Hyperlink.h"
#include "DlgAboutGm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpCutterApp

BEGIN_MESSAGE_MAP(CSpCutterApp, CWinApp)
	//{{AFX_MSG_MAP(CSpCutterApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpCutterApp construction

CSpCutterApp::CSpCutterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSpCutterApp object

CSpCutterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSpCutterApp initialization

BOOL CSpCutterApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

    HANDLE hMutex = CreateMutex(NULL, FALSE, "SpCutterMutex");
    // �������������ʵ�������У���GetLastError()����ERROR_ALREADY_EXISTS
    if(GetLastError() == ERROR_ALREADY_EXISTS)
    {
        CloseHandle(hMutex); //�رջ����������
        //��ȡ���洰�ڵ�һ���Ӵ��ڡ�
        HWND hWndPrev =::GetWindow(::GetDesktopWindow(), GW_CHILD);
        // ö�ٵ�ǰ���ڣ����ұ����������е�ʵ��
        while(::IsWindow(hWndPrev))
        {
//���У�����Ҫ������������ʵ���Ĵ��ڣ����������
//            if(::GetProp(hWndPrev, AfxGetApp()->m_pszExeName))
            if(::GetProp(hWndPrev, "YHZ_SP_Cutter"))
            {
                //�������������С������ָ����С��
                if (::IsIconic(hWndPrev))
                    ::ShowWindow(hWndPrev, SW_RESTORE);
				::ShowWindow(hWndPrev,SW_SHOW);
                //����Ӧ�ó����������
                ::SetForegroundWindow(hWndPrev);
                return FALSE; //�˳���ʵ��
            }
            //����Ѱ����һ�����ڡ�
            hWndPrev = ::GetWindow(hWndPrev, GW_HWNDNEXT);
        }
        AfxMessageBox("Application running", MB_OK | MB_ICONINFORMATION, NULL);
        return FALSE; //�˳���ʵ��
    }

	AfxEnableControlContainer();
	ReadSettings(); //��ini�ļ��ж�ȡϵͳ����
	SetLanguage();
	gMacSet.checkDataDir(); //�����ʱĿ¼

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.

//-----------------------------------------------------------
//by YHZ ɾ�����������ʹ��ini�ļ�������ʹ�õ���ע����ļ�
//	SetRegistryKey(_T("YHZ_SP_CUTTER"));
//	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
//-----------------------------------------------------------

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSpCutterDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CSpCutterView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

//	ReadSettings(); //��ini�ļ��ж�ȡϵͳ����

//	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CSpCutterApp::OnAppAbout()
{
#if (CUSTOMER_TYPE == C_ALL)
	CAboutDlg aboutDlg;
#endif
#if (CUSTOMER_TYPE == C_GM)
	CDlgAboutGm aboutDlg;
#endif
	aboutDlg.DoModal();

}

/////////////////////////////////////////////////////////////////////////////
// CSpCutterApp message handlers
void CSpCutterApp::WriteSettings()
{
	WriteProfileInt(_T("Para"), _T("BGColor"), (int)gDispSet.getClrBG());
	WriteProfileInt(_T("Para"), _T("FRColor"), (int)gDispSet.getClrFR());
	WriteProfileInt(_T("Para"), _T("PenColor"), (int)gDispSet.getClrPen());
	WriteProfileInt(_T("Para"), _T("K1Color"), (int)gDispSet.getClrCut());

	WriteProfileInt(_T("Para"), _T("DispSizeX"), gDispSet.getDispSizeX());
	WriteProfileInt(_T("Para"), _T("DispSizeY"), gDispSet.getDispSizeY());
	WriteProfileInt(_T("Para"), _T("Language"), gDispSet.getLanguage());

	WriteProfileInt(_T("Para"), _T("��ͼ�߿�"), gMacSet.getLineWidth()); //�߿�
	WriteProfileInt(_T("Para"), _T("ת�ǲ���"), gMacSet.getOverCutLen()); //ת�ǲ���

	WriteProfileInt(_T("Para"), _T("AutoDelPlt"), (int)gMacSet.getAutoDelPlt()); //�Զ�ɾ��Plt
	WriteProfileInt(_T("Para"), _T("�Զ�����"), (int)gMacSet.getJobAutoStart()); //�Զ�����
	WriteProfileInt(_T("Para"), _T("ֻ�治��"), (int)gMacSet.getOnlyPlot()); //ֻ�治��

	WriteProfileInt(_T("Para"), _T("FirstPageConfirm"), (int)gMacSet.getFirstPageConfirm()); //��һҳ��ȷ����ť

	WriteProfileString(_T("Para"), _T("DataDir"), gMacSet.m_strDataDir);
	WriteProfileString(_T("Para"), _T("ע����"), gMacSet.getAuthCode());

	WriteProfileInt(_T("Para"), _T("PLTSCALE"), (int)gMacSet.getPltScale());
	WriteProfileInt(_T("Para"), _T("PLT�ļ�ҳ��"), (int)gMacSet.getPltPageLen());
	WriteProfileInt(_T("Para"), _T("�����ܶ�"), (int)gMacSet.getCurveLen());
	
	WriteProfileInt(_T("Para"), _T("AutoCleanSP"), (int)gMacSet.getSpAutoClean()); //��ʼ����ǰ��ϴ��ͷ
	WriteProfileInt(_T("Para"), _T("DisplayStartAndDir"), (int)gMacSet.getDisplayStartAndDir());
	WriteProfileInt(_T("Para"), _T("DisplaySequence"), (int)gMacSet.getDisplaySequence());
	WriteProfileInt(_T("Para"), _T("�б���ʾ����"), (int)gMacSet.getListDispLeft());
	WriteProfileInt(_T("Para"), _T("����ƽ��"), (int)gMacSet.getAutoMoveToLeft());
	WriteProfileInt(_T("Para"), _T("����ƽ��"), (int)gMacSet.getAutoMoveToBottom());
	WriteProfileInt(_T("Para"), _T("˫���ӡ"), (int)gMacSet.getBiDir());

	WriteProfileInt(_T("Para"), _T("Y��߾�"), (int)gMacSet.getYBlankMm());
	WriteProfileInt(_T("Para"), _T("X��������"), (int)gMacSet.getPltSaveScaleX());
	WriteProfileInt(_T("Para"), _T("Y��������"), (int)gMacSet.getPltSaveScaleY());

	WriteProfileInt(_T("Para"), _T("�Զ�ʶ������"), gMacSet.getFindOutLine());

// 	DeleteFile(gMacSet.m_strFonHz);
// 	DeleteFile(gMacSet.m_strFonEn);
}

void CSpCutterApp::ReadSettings()
{
	gMacSet.getAppDir();
	free((void*)m_pszProfileName);
	m_pszProfileName = _tcsdup(gMacSet.m_strAppDir + "setting.ini");

	gDispSet.setClrBG( GetProfileInt(_T("Para"), _T("BGColor"),RGB(0,0,0)) );
	gDispSet.setClrFR( GetProfileInt(_T("Para"), _T("FRColor"),RGB(0,255,0)) );
	gDispSet.setClrPen( GetProfileInt(_T("Para"), _T("PenColor"),RGB(0,0,255)) );
	gDispSet.setClrCut( GetProfileInt(_T("Para"), _T("K1Color"),RGB(255,0,0)) );

	gDispSet.setDispSizeX(GetProfileInt(_T("Para"), _T("DispSizeX"),1200));
	gDispSet.setDispSizeY(GetProfileInt(_T("Para"), _T("DispSizeY"),900));

	gDispSet.setLanguage(GetProfileInt(_T("Para"), _T("Language"),0));

	gMacSet.setLineWidth(GetProfileInt(_T("Para"), _T("��ͼ�߿�"),1));
	gMacSet.setOverCutLen(GetProfileInt(_T("Para"), _T("ת�ǲ���"),50));

	gMacSet.setAutoDelPlt(GetProfileInt(_T("Para"), _T("AutoDelPlt"),0));
	gMacSet.setJobAutoStart(GetProfileInt(_T("Para"), _T("�Զ�����"),0));
	gMacSet.setOnlyPlot(GetProfileInt(_T("Para"), _T("ֻ�治��"),0));

	gMacSet.setFirstPageConfirm(GetProfileInt(_T("Para"), _T("FirstPageConfirm"),0));

	gMacSet.setDataDir(GetProfileString(_T("Para"), _T("DataDir")));
	gMacSet.setAuthCode(GetProfileString(_T("Para"), _T("ע����")));
	gMacSet.setPltScale(GetProfileInt(_T("Para"), _T("PLTSCALE"),1000));
	gMacSet.setPltPageLen(GetProfileInt(_T("Para"), _T("PLT�ļ�ҳ��"),0));
	gMacSet.setCurveLen(GetProfileInt(_T("Para"), _T("�����ܶ�"),1));

	gMacSet.setSpAutoClean(GetProfileInt(_T("Para"), _T("AutoCleanSP"),0));
	gMacSet.setDisplayStartAndDir(GetProfileInt(_T("Para"), _T("DisplayStartAndDir"),1));
	gMacSet.setDisplaySequence(GetProfileInt(_T("Para"), _T("DisplaySequence"),1));


	gMacSet.setListDispLeft(GetProfileInt(_T("Para"), _T("�б���ʾ����"),1));
	gMacSet.setAutoMoveToLeft(GetProfileInt(_T("Para"), _T("����ƽ��"),1));
	gMacSet.setAutoMoveToBottom(GetProfileInt(_T("Para"), _T("����ƽ��"),1));
	gMacSet.setBiDir(GetProfileInt(_T("Para"), _T("˫���ӡ"),1));
	gMacSet.setYBlankMm(GetProfileInt(_T("Para"), _T("Y��߾�"),0));

	gMacSet.setPltSaveScaleX(GetProfileInt(_T("Para"), _T("X��������"),1000));
	gMacSet.setPltSaveScaleY(GetProfileInt(_T("Para"), _T("Y��������"),1000));

	gMacSet.setFindOutLine(GetProfileInt(_T("Para"), _T("�Զ�ʶ������"),0)); //ʶ������

}


int CSpCutterApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	WriteSettings();
	return CWinApp::ExitInstance();
}

void CSpCutterApp::SetLanguage()
{
	HINSTANCE hEngDLL;
    hEngDLL =::LoadLibrary("DLL_EN.dll");
    if( hEngDLL == NULL)
	{
		AfxMessageBox("����Ӣ�����԰�ʧ��!");
	}
	else
	{
		switch (gDispSet.getLanguage())
		{
		case 0:
			AfxSetResourceHandle(AfxGetInstanceHandle());
			break;
			
		case 1:
			AfxSetResourceHandle(hEngDLL);
			break;
		}
	}
}