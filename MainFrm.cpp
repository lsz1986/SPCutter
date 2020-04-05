// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SpCutter.h"
#include "MainFrm.h"

#include "DlgSetClr.h"
#include "DlgMacPara.h"
#include "HpglFile.h"
#include "DlgSetDir.h"

#include "DLgManCtrl.h"

UINT ThreadTimeDetect(LPVOID pParam);
UINT ThreadAutoConnect(LPVOID pParam); //自动连接机器并开始服务

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_SET_DISP, OnSetClr)
	ON_COMMAND(IDM_SET_DIR, OnSetDir)
	ON_WM_PAINT()
	ON_MESSAGE(USER_SHOWTASK,onShowTask)
	ON_COMMAND(ID_APP_TO_TRAY, OnAppToTray)
	ON_COMMAND(IDCB_PLT_OPEN, OnPltOpen)
	ON_COMMAND(IDCB_PLT_ADD, OnPltAdd)
	ON_COMMAND(IDCB_PLT_SAVE, OnPltSave)
	ON_COMMAND(IDCB_PARA_SET, OnParaSet)
	ON_COMMAND(IDCB_MANUAL_CTRL, OnManualCtrl)
	ON_WM_CLOSE()
	ON_COMMAND(IDCB_SP_CLEAN, OnSpClean)
	ON_COMMAND(IDM_AUTH_INFO, OnAuthInfo)
	ON_COMMAND(IDM_SUPER_USER, OnSuperUser)
	ON_COMMAND(IDCB_ZOOM_IN, OnZoomIn)
	ON_COMMAND(IDCB_ZOOM_OUT, OnZoomOut)
	ON_COMMAND(IDCB_ZOOM_ALL, OnZoomAll)
	ON_COMMAND(IDCB_V_SEL, OnVSel)
	ON_COMMAND(IDCB_V_MOVE, OnVMove)
	ON_UPDATE_COMMAND_UI(IDCB_V_MOVE, OnUpdateVMove)
	ON_UPDATE_COMMAND_UI(IDCB_V_SEL, OnUpdateVSel)
	ON_COMMAND(ID_FILE_ATF_10x10, OnFILEATF10x10)
	ON_COMMAND(ID_FILE_ATF_20x20, OnFILEATF20x20)
	ON_COMMAND(ID_FILE_ATF_30x30, OnFILEATF30x30)
	ON_COMMAND(ID_FILE_ATF_40x40, OnFILEATF40x40)
	ON_COMMAND(ID_FILE_ATF_50x50, OnFILEATF50x50)
	ON_COMMAND(IDCB_WORK_START, OnWorkStart)
	ON_COMMAND(IDCB_WORK_PAUSE, OnWorkPause)
	ON_COMMAND(IDCB_WORK_CANCEL, OnWorkCancel)
	ON_UPDATE_COMMAND_UI(IDCB_WORK_PAUSE, OnUpdateWorkPause)
	ON_UPDATE_COMMAND_UI(IDCB_WORK_START, OnUpdateWorkStart)
	ON_UPDATE_COMMAND_UI(IDCB_WORK_CANCEL, OnUpdateWorkCancel)
	ON_UPDATE_COMMAND_UI(IDCB_MANUAL_CTRL, OnUpdateManualCtrl)
	ON_UPDATE_COMMAND_UI(IDCB_SP_CLEAN, OnUpdateSpClean)
	ON_COMMAND(IDM_LAN_CHS, OnLanChs)
	ON_COMMAND(IDM_LAN_EN, OnLanEn)
	ON_MESSAGE(USER_END_WTHREAD, OnEndWorkThread)
	ON_MESSAGE(USER_DISP_STAT, OnDispSysStatus)
	ON_MESSAGE(USER_SEARCH_PLT, OnSearchNewPltFile)
	ON_MESSAGE(USER_AUTO_START, OnAutoStartWork)
	ON_UPDATE_COMMAND_UI(IDM_LAN_CHS, OnUpdateLanChs)
	ON_UPDATE_COMMAND_UI(IDM_LAN_EN, OnUpdateLanEn)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDS_SYS_STATE,OnUpdateCmdUISysState)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	IDS_SYS_STATE,
	IDS_PROGRESS
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

CSpCutterDoc* CMainFrame::GetDocument()
{
	return (CSpCutterDoc*)(GetActiveView()->GetDocument());
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	::SetProp(m_hWnd,"YHZ_SP_Cutter",HANDLE(1));

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	if (!m_wndDlgBar.Create(this,IDDLG_BAR,WS_VISIBLE|WS_CHILD
		|CBRS_SIZE_DYNAMIC|CBRS_BOTTOM,IDDLG_BAR))
	{
		TRACE0("Failed to create CDataStatus bar!");
		return -1;
	}

	gParaTimeDetect.m_pWnd = this;
	gParaAutoConnect.m_pWnd = this;
	gThreadTimeDetect = AfxBeginThread(ThreadTimeDetect,&gParaTimeDetect);
	gThreadAutoConnect = AfxBeginThread(ThreadAutoConnect,&gParaAutoConnect);
	gMacSet.setQueryEnable(TRUE);

	gThrdWork = NULL;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.cx = 800;
	cs.cy = 600;
	cs.lpszName = "SpCutter";
	cs.style &= ~FWS_ADDTOTITLE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	int nIndex;

	nIndex= m_wndStatusBar.CommandToIndex(IDS_PROGRESS);
	m_wndStatusBar.SetPaneInfo(nIndex,IDS_PROGRESS,SBPS_NORMAL,600);
	m_wndStatusBar.GetItemRect(nIndex,&rect);
	
	if(!m_wndProgress.m_hWnd)
	{
		m_wndProgress.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTH, rect,&m_wndStatusBar,123);
	}
	else
		m_wndProgress.MoveWindow(rect);
}

LRESULT CMainFrame::OnEndWorkThread(WPARAM wParam, LPARAM lParam)
{
	GetDocument()->OnRemoveOnePageData(0);
	if (wParam == 2) //全部清空
	{
		GetDocument()->OnRemoveDocAllData();
	}
	m_pListView->UpdateList();
	m_pMainView->SetCurrentDrawPage(0);
	m_pMainView->OnReDraw();
	gMacSet.setQueryEnable(TRUE);

	if( (GetDocument()->m_ArrayPage.GetSize() > 0)&& (gMacSet.getJobAutoStart()) )
	{
		gMacSet.setWorkStartPause(TRUE);
	}
	gThrdWork = NULL;	
	OnDispSysStatus(NULL,NULL);
	return true;
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if (m_wndDlgBar.OnCmdMsg(nID,nCode,pExtra,pHandlerInfo))
		return TRUE;
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

LRESULT CMainFrame::OnDispSysStatus(WPARAM wParam, LPARAM lParam)
{
	CString strText;
	int nIndex;
	CSize sizeText;
	CWindowDC dc(&m_wndStatusBar);
	if (g_bParaRead)
	{
		switch(gSysState)
		{
			case SYS_INIT:
			if (gDispSet.getLanguage() == 0){
				strText.Format("系统正在初始化...");
			}else{
				strText.Format("Rebooting...");
			}
			break;

			case CHECK_SRAM:
			if (gDispSet.getLanguage() == 0){
			strText.Format("内存检查...");
			}else{
				strText.Format("Testing Memory...");
			}
			break;

			case SEEK_ZP:
			if (gDispSet.getLanguage() == 0){
				strText.Format("正在寻找原点...");
			}else{
				strText.Format("Finding ZP...");
			}
			break;

			case READY:
			m_wndProgress.SetPos(0);
			if (gDispSet.getLanguage() == 0){
				strText.Format("准备就绪");
			}else{
				strText.Format("Ready");
			}
			break;

			case WORKING:
			switch(gWorkType)
			{
				case WT_NONE:
				strText.Format("Waiting");
				break;

				case WT_START:
				break;

				case WT_END:
				if (gDispSet.getLanguage() == 0){
					strText.Format("任务完成中...");
				}else {
					strText.Format("Ending...");
				}
				break;

				case WT_CANCEL:
				if (gDispSet.getLanguage() == 0){
					strText.Format("任务删除中....");
				}else{
					strText.Format("Cancel....");
				}
				break;

				case WT_PLOTTING:
				if (gDispSet.getLanguage() == 0){
					strText.Format("正在绘图%d/%d",wParam,lParam);
				}else{
					strText.Format("Plotting%d/%d",wParam,lParam);
				}
				if (lParam != 0)
				{
					m_wndProgress.SetPos(wParam*100/lParam);
				}
				break;

				case WT_CUTTING:
				m_wndProgress.SetPos(0);
				if (gDispSet.getLanguage() == 0){
					strText.Format("正在切割");
				}else{
					strText.Format("Cutting");
				}
				break;
			}
			break;

			case WORK_PAUSE:
			if (gDispSet.getLanguage() == 0){
			strText.Format("暂停工作");
			}else{
				strText.Format("Pause");
			}
			break;

			case PRT_TEST:
			if (gDispSet.getLanguage() == 0){
				strText.Format("正在清洗喷头...");
			}else{
				strText.Format("Clean spray...");
			}
			break;

			case ERROR_SRAM:
			strText.Format("RAM ERROR");
			break;

			case STEPM_LOST:
			if (gDispSet.getLanguage() == 0){
				strText.Format("电机丢步，可能卡纸");
			}else{
				strText.Format("Step motor out of pace,maybe jammed");
			}
			break;

			default:
			m_wndProgress.SetPos(0);
			strText.Format("Error %d",gSysState);
			break;
		}
	}
	else
	{
		m_wndProgress.SetPos(0);
		if (gDispSet.getLanguage() == 0)
		{
			strText.Format("USB未连接");
		}else {
			strText.Format("USB Not Connected");
		}
	}

	nIndex= m_wndStatusBar.CommandToIndex(IDS_SYS_STATE);
	m_wndStatusBar.SetPaneText(nIndex,strText);
	sizeText = dc.GetTextExtent(strText);
	m_wndStatusBar.SetPaneInfo(nIndex,IDS_SYS_STATE,SBPS_NORMAL,sizeText.cx);
	return 0;
}

LRESULT CMainFrame::onShowTask(WPARAM wParam,LPARAM lParam) 
{ 
	if(wParam!=IDR_MAINFRAME) 
		return 1; 
	switch(lParam) 
	{
		case WM_LBUTTONDBLCLK://双击左键的处理 
		{ 
			NOTIFYICONDATA nid; 
			nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); 
			nid.hWnd=this->m_hWnd; 
			nid.uID=IDR_MAINFRAME; 
			nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
			nid.uCallbackMessage=USER_SHOWTASK;//自定义的消息名称 
			nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
			strcpy(nid.szTip,"计划任务提醒");    //信息提示条为“计划任务提醒” 
			Shell_NotifyIcon(NIM_DELETE,&nid);
			this->ShowWindow(SW_SHOW);//简单的显示主窗口完事儿 
		} 
		break; 
	}
	return 0; 
}

void CMainFrame::OnUpdateCmdUISysState(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CRect cr;
	GetWindowRect( &cr );

	if(gMacSet.getListDispLeft())
	{
		// Create the main splitter with 1 row and 2 columns
		if ( !m_wndSplitter.CreateStatic( this, 1, 2 ) )
		{
			MessageBox( "Error setting up m_mainSplitter", "ERROR", MB_OK | MB_ICONERROR );
			return FALSE;
		}
		
		// The views for each pane must be created 
		if ( !m_wndSplitter.CreateView( 0, 0, RUNTIME_CLASS(CMyListView),
			CSize(cr.Width()/3, cr.Height()), pContext ) )
		{
			MessageBox( "Error setting up splitter view", "ERROR", MB_OK | MB_ICONERROR );
			return FALSE;
		}
		
		if ( !m_wndSplitter.CreateView( 0, 1, RUNTIME_CLASS(CSpCutterView),
			CSize(cr.Width()*2/3, cr.Height()), pContext ) )
		{
			MessageBox( "Error setting up splitter view", "ERROR", MB_OK | MB_ICONERROR );
			return FALSE;
		}
		m_pListView = (CMyListView*)m_wndSplitter.GetPane(0,0) ;
		m_pMainView = (CSpCutterView*)m_wndSplitter.GetPane(0,1) ;
		m_pListView->m_pMainView = m_pMainView;
	}
	else
	{
		// Create the main splitter with 1 row and 2 columns
		if ( !m_wndSplitter.CreateStatic( this, 2, 1 ) )
		{
			MessageBox( "Error setting up m_mainSplitter", "ERROR", MB_OK | MB_ICONERROR );
			return FALSE;
		}
		
		// The views for each pane must be created 
		if ( !m_wndSplitter.CreateView( 0, 0, RUNTIME_CLASS(CMyListView),
			CSize(cr.Width(), 200), pContext ) )
		{
			MessageBox( "Error setting up splitter view", "ERROR", MB_OK | MB_ICONERROR );
			return FALSE;
		}
		
		if ( !m_wndSplitter.CreateView( 1, 0, RUNTIME_CLASS(CSpCutterView),
			CSize(cr.Width(), cr.Height()-200), pContext ) )
		{
			MessageBox( "Error setting up splitter view", "ERROR", MB_OK | MB_ICONERROR );
			return FALSE;
		}
		m_pListView = (CMyListView*)m_wndSplitter.GetPane(0,0) ;
		m_pMainView = (CSpCutterView*)m_wndSplitter.GetPane(1,0) ;
		m_pListView->m_pMainView = m_pMainView;
	}
	return TRUE;
}

void CMainFrame::OnPltOpen() 
{
	if(gThrdWork != NULL)
	{
		if (gDispSet.getLanguage() == 0) {
			AfxMessageBox("正在工作,不能打开新文件!");
		}else {
			AfxMessageBox("Can not open new file while working,Use \"Add File\" Function !");
		}
		return;
	}

	char Custer[80] = "HP-GL(*.plt)\0*.plt\0All file(*.*)\0*.*\0\0";
	
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrFilter = Custer;
	CHpglFile myHpglFile;
	
	if(dlg.DoModal() == IDOK)
	{
		CString strFileName = dlg.GetPathName();
		myHpglFile.m_strPathAndName = strFileName;
		if (0 != myHpglFile.OpenPltFile())
		{
			AfxMessageBox("文件打开失败!");
			return;
		}
		GetDocument()->OnRemoveDocAllData();
		
		myHpglFile.HpglCmdToDoc(GetDocument());
		GetDocument()->CheckDocData();
		if (gMacSet.getPltPageLen() > 100)
		{
			GetDocument()->SpliteLastPage(gMacSet.getPltPageLen()*40);//分页;
		}
		if (gMacSet.getAutoDelPlt())
		{
			DeleteFile(strFileName);
		}
	}
	
	m_pListView->UpdateList();
	m_pMainView->SetCurrentDrawPage(0);
}

void CMainFrame::OnPltAdd() 
{
	char Custer[80] = "HP-GL(*.plt)\0*.plt\0All file(*.*)\0*.*\0\0";
	
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrFilter = Custer;
	CHpglFile myHpglFile;
	
	if(dlg.DoModal() == IDOK)
	{
		CString strFileName = dlg.GetPathName();
		myHpglFile.m_strPathAndName = strFileName;
		if (0 != myHpglFile.OpenPltFile())
		{
			AfxMessageBox("文件打开失败!");
			return;
		}
		myHpglFile.HpglCmdToDoc(GetDocument());
		GetDocument()->CheckDocData();
		if (gMacSet.getPltPageLen() > 100)
		{
			GetDocument()->SpliteLastPage(gMacSet.getPltPageLen()*40);//分页;
		}
		if (gMacSet.getAutoDelPlt())
		{
			DeleteFile(strFileName);
		}
	}
	
	m_pListView->UpdateList();
	m_pMainView->SetCurrentDrawPage(0);
}

void CMainFrame::OnPltSave() 
{
	char Custer[80] = "HP-GL(*.plt)\0*.plt\0All file(*.*)\0*.*\0\0";
	CString str,str1;
	CFileDialog dlg(FALSE);
	
	dlg.m_ofn.lpstrFilter = Custer;
	if(dlg.DoModal() == IDOK)
	{
		CString strFileName = dlg.GetPathName();
		int nFileNameLen = strFileName.GetLength();
		if (nFileNameLen<5)
		{
			strFileName += ".plt";
		}
		else
		{
			if( (strFileName.GetAt(nFileNameLen-4) == '.' ) &&
				(toupper(strFileName.GetAt(nFileNameLen-3)) == 'P' ) &&
				(toupper(strFileName.GetAt(nFileNameLen-2)) == 'L' ) &&
				(toupper(strFileName.GetAt(nFileNameLen-1)) == 'T' ) 
				)
			{
			}
			else
			{
				strFileName += ".plt";
			}
		}
		GetDocument()->OnSaveAsPlt(strFileName);
	}
}

void CMainFrame::OnParaSet() 
{
	CDlgMacPara dlg;
	if(gThrdWork != NULL)
	{
		AfxMessageBox("正在工作，不能设置参数");
		return;
	}
	gMacSet.setQueryEnable(FALSE);
	ReadMacPara(); //进入参数设置界面之前读取
	gMacSet.setQueryEnable(TRUE);
	if (FALSE == g_bParaRead)
	{
		if (gDispSet.getLanguage() == 0)
		{
			AfxMessageBox("没有开机或者没有连接USB电缆，读取参数失败！");
		}
		else
		{
			AfxMessageBox("Read Parameter Failed!");
		}
	}
	gMacSet.setQueryEnable(FALSE);
	dlg.DoModal();
	gMacSet.setQueryEnable(TRUE);
	Invalidate();
}


void CMainFrame::OnUpdateManualCtrl(CCmdUI* pCmdUI) 
{
	if( gSysState == READY)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnManualCtrl() 
{
	gMacSet.setQueryEnable(FALSE);
	CDlgManCtrl dlg;
	dlg.DoModal();
	gMacSet.setQueryEnable(TRUE);
	return;
}

void CMainFrame::OnZoomAll() 
{
	m_pMainView->OnZoomAll();
}

void CMainFrame::OnAppToTray() 
{
	NOTIFYICONDATA nid; 
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); 
	nid.hWnd=this->m_hWnd; 
	nid.uID=IDR_MAINFRAME; 
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
	nid.uCallbackMessage = USER_SHOWTASK;//自定义的消息名称 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	strcpy(nid.szTip,"计划任务提醒");    //信息提示条为“计划任务提醒” 
	Shell_NotifyIcon(NIM_ADD,&nid);    //在托盘区添加图标 
	ShowWindow(SW_HIDE);    //隐藏主窗口 	
}

void CMainFrame::OnSetClr() 
{
	CDlgSetClr dlg;
	dlg.DoModal();
	Invalidate();
}

void CMainFrame::OnSetDir() 
{
	CDlgSetDir dlg;
	dlg.DoModal();
}

void CMainFrame::OnClose()
{
	if(gThrdWork != NULL)
	{
		if(IDOK != MessageBox("机器正在运行,强行关闭可能造成死机!\n是否继续?","提示",MB_OKCANCEL) )
		{
			return;
		}
	}

	gWorkingPage.OnRemoveAllData();
	ReleaseCncDataBuffer();
	CFrameWnd::OnClose();
}

void CMainFrame::OnUpdateSpClean(CCmdUI* pCmdUI) 
{
	if( gSysState == READY)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}	
}

void CMainFrame::OnSpClean() 
{
	gMacSet.setQueryEnable(FALSE);
	if (0 != gUSB.OnSpClean())
	{
		if (gDispSet.getLanguage() == 0)
		{
			AfxMessageBox("发送命令失败");
		}
		else
		{
			AfxMessageBox("Send Command Failed");
		}
	}
	gMacSet.setQueryEnable(TRUE);
	return;
}

#include "DlgRegInfo.h"
void CMainFrame::OnAuthInfo() 
{
	if( (gThrdWork != NULL)|| (READY != gSysState) )
	{
		if (gDispSet.getLanguage() == 0){
			AfxMessageBox("操作失败");
		}else{
			AfxMessageBox("Connect Machine First");
		}
		return;
	}

	gMacSet.setQueryEnable(FALSE);
	u32 McuCode = gUSB.OnGetChipID(); //进入授权更新界面时
	if (McuCode > 0x70000000)
	{
		gMacSet.setMcuCode(McuCode);
		CString str;
		str.Format("%x",McuCode ^ YHZIntArray[11]);
		gMacSet.setMcuSn(str);
		CDlgRegInfo dlg;
		dlg.DoModal();
	}
	else
	{
		AfxMessageBox("联机失败!");
	}
	gMacSet.setQueryEnable(TRUE);
	return;
}

#include "DlgSuperUser.h"
void CMainFrame::OnSuperUser() 
{
	if(gThrdWork != NULL)
	{
		if (gDispSet.getLanguage() == 0){
			AfxMessageBox("操作失败");
		}else{
			AfxMessageBox("Connect Machine First");
		}
		return;
	}
	
	gMacSet.setQueryEnable(FALSE);
	u32 McuCode = gUSB.OnGetChipID();
	if (McuCode > 0x70000000)
	{
		gMacSet.setMcuCode(McuCode);
		CDlgSuperUser dlg;
		dlg.DoModal();
	}
	else
	{
		AfxMessageBox("联机失败!");
	}
	gMacSet.setQueryEnable(TRUE);
}

afx_msg LRESULT CMainFrame::OnSearchNewPltFile(WPARAM wParam,LPARAM lParam)
{
	CFileFind filefind;
	BOOL bFindFile;
	CString strPathName;
	bFindFile = filefind.FindFile(gMacSet.m_strDataDir+"*.*");
	
	CString str;
	while(bFindFile == TRUE)
	{
		bFindFile = filefind.FindNextFile();
        if ((!filefind.IsDirectory()) && (!filefind.IsDots()))
		{
			strPathName = filefind.GetFilePath();
			OnPltAddAuto(strPathName,TRUE);
		}
	}
	return 0;
}

void CMainFrame::OnPltAddAuto(CString strFileName,BOOL bDeleteFile)
{
	CHpglFile myHpglFile;
	myHpglFile.m_strPathAndName = strFileName;
	int aa = myHpglFile.OpenPltFile();
	if (aa < 0 )
	{
		if (bDeleteFile)
		{
			DeleteFile(strFileName);
		}
	}
	if (aa != 0)
	{
		return;
	}

	myHpglFile.HpglCmdToDoc(GetDocument());
	GetDocument()->CheckDocData();
	if (gMacSet.getPltPageLen() > 100)
	{
		GetDocument()->SpliteLastPage(gMacSet.getPltPageLen()*40);//分页;
	}
	if (bDeleteFile)
	{
		DeleteFile(strFileName);
	}
	
	m_pListView->UpdateList();
	m_pMainView->SetCurrentDrawPage(0);
}


void CMainFrame::OnZoomIn() 
{
	m_pMainView->ZoomIn();
}

void CMainFrame::OnZoomOut() 
{
	m_pMainView->ZoomOut();
}

void CMainFrame::OnVSel() 
{
	gMacSet.setToolBarState(TBS_SEL);
	m_pMainView->OnSetViewCursor();
}

void CMainFrame::OnVMove() 
{
	gMacSet.setToolBarState(TBS_MOVE);	
	m_pMainView->OnSetViewCursor();
}

void CMainFrame::OnUpdateVMove(CCmdUI* pCmdUI) 
{
	if (gMacSet.getToolBarState() == TBS_MOVE)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}

void CMainFrame::OnUpdateVSel(CCmdUI* pCmdUI) 
{
	if (gMacSet.getToolBarState() == TBS_SEL)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}

afx_msg LRESULT CMainFrame::OnAutoStartWork(WPARAM wParam,LPARAM lParam)
{
	int rev;
	if(NULL != gThrdWork)
		return 0;
	rev = OnStartProcess();
	if ( rev != 0)
	{
		gMacSet.setQueryEnable(TRUE);
	}
	return 0;
}

int CMainFrame::OnStartProcess()
{
	int rev;
	CString strTemp;
#if (YHZ_DEBUG == 0)
	if( (FALSE == g_bParaRead) || (READY != gSysState) )
		return -1;
#endif
	if (GetDocument()->m_ArrayPage.GetSize() <= 0)
		return -1;
	gMacSet.setThreadMessage(THREAD_MESSAGE_NONE);

	COnePage* pPage = GetDocument()->m_ArrayPage.GetAt(0);
	gWorkingPage.OnRemoveAllData();
	ReleaseCncDataBuffer();
	gWorkingPage = *pPage;
	if (gWorkingPage.m_CurveList.GetSize() <= 0)
	{
		delete pPage;
		GetDocument()->m_ArrayPage.RemoveAt(0);
		m_pListView->UpdateList();
		m_pMainView->OnReDraw();
		return -1;
	}

	if (gMacSet.getYBlankMm() > 0)
	{
		gWorkingPage.OnAddYMargin(gMacSet.getYBlankMm()*40);
	}
	if (gMacSet.getSpAutoClean()) //开始工作前自动清洗喷头功能开启
	{
		gWorkingPage.OnAddSpCleanData();
	}
	if (gMacSet.getOnlyPlot())
	{
		gWorkingPage.OnSetOnlyPlot();
	}
	gWorkingPage.OnPageAngleAdjust(); //进行垂直度校正
	gWorkingPage.OnRemoveInvalidPoints();
	gWorkingPage.OnCheckPageData();
	gWorkingPage.OnGetPageMaxMin(); //计算当前页的最小，最大值
	gWorkingPage.OnGetSizePlotCut(); //分别获取切割和绘图数据的最大坐标


	rev = CreateCncList();
	if (0 != rev)
	{
		AfxMessageBox("切割数据太大,发送失败");
		return -1;
	}

	gMacSet.setQueryEnable(FALSE);
	rev = gMyReg.OnCheckRegCode(gMacSet.getAuthCode());
	if( 0 != rev )
	{
		gWorkingPage.OnRemoveAllData();
		GetDocument()->OnRemoveDocAllData();
		m_pMainView->OnReDraw();
		m_pListView->UpdateList();
		switch(rev)
		{
			case -4:
			AfxMessageBox("系统内存错误,地址0xA786,请联系当地经销商或致电生产厂家\n武汉格美联合科技有限公司\n电话027-83566125");
			break;

			default:
			strTemp.Format("Auth error%d",rev);
			AfxMessageBox(strTemp);
			break;
		}
		return -1;
	}
	gParaWork.m_pWnd = this;
	if(NULL == gThrdWork) //没有绘图线程和切割线程在运行
	{
		gThrdWork = AfxBeginThread(ThreadWork,&gParaWork);
		return 0;
	}
	return -1;
}

int CMainFrame::CreateCncList()
{
	int i;
	CCurve* pCurve;
	for (i=0;i<gWorkingPage.m_CurveList.GetSize();i++)
	{
		pCurve = (CCurve*)gWorkingPage.m_CurveList.GetAt(i);
		if (pCurve->m_nPenNum > 1)
		{
			pCurve->OnToCutData();
		}
	}
	if (g_ptrCncList.GetSize() <=0)
	{
		return 0; //没有切割数据
	}
	
	CalculateAngles();
	AddOverCutData(); //增加角度补偿值
	CalculateAngles();
	GetLongAxialSteps();
	CalcCurvature();

	setSpdLimit(gMacSet.getSpdDownType()); //
	CalcCncSpeed();
	CalcSdPercent();

	GetCncMaxPulse();
//	dumpCutDataToFile();

	int	nSize = g_ptrCncList.GetSize();
	if (nSize >= 0xffff) //切割数据大小超过1M
	{
		return -1;
	}
	return 0;
}

void CMainFrame::OnFILEATF10x10() 
{
	CString strFileName;
	GetDocument()->OnRemoveDocAllData();
	strFileName = gMacSet.m_strAppDir+"TestPlt\\10x10.plt";
	OnPltAddAuto(strFileName,FALSE);
}

void CMainFrame::OnFILEATF20x20() 
{
	CString strFileName;
	GetDocument()->OnRemoveDocAllData();
	strFileName = gMacSet.m_strAppDir+"TestPlt\\20x20.plt";
	OnPltAddAuto(strFileName,FALSE);
}

void CMainFrame::OnFILEATF30x30() 
{
	CString strFileName;
	GetDocument()->OnRemoveDocAllData();
	strFileName = gMacSet.m_strAppDir+"TestPlt\\30x30.plt";
	OnPltAddAuto(strFileName,FALSE);	
}

void CMainFrame::OnFILEATF40x40() 
{
	CString strFileName;
	GetDocument()->OnRemoveDocAllData();
	strFileName = gMacSet.m_strAppDir+"TestPlt\\40x40.plt";
	OnPltAddAuto(strFileName,FALSE);
}

void CMainFrame::OnFILEATF50x50()
{
	CString strFileName;
	GetDocument()->OnRemoveDocAllData();
	strFileName = gMacSet.m_strAppDir+"TestPlt\\50x50.plt";
	OnPltAddAuto(strFileName,FALSE);
}

void CMainFrame::OnUpdateWorkStart(CCmdUI* pCmdUI) 
{
#if (YHZ_DEBUG == 0)
	if( (GetDocument()->m_ArrayPage.GetSize() > 0) &&
		( (gSysState==READY) || (gSysState == WORK_PAUSE) ) )
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
#endif
}

void CMainFrame::OnUpdateWorkPause(CCmdUI* pCmdUI) 
{
	if( ( gSysState == WORKING )&& (gThrdWork != NULL) )
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}


void CMainFrame::OnUpdateWorkCancel(CCmdUI* pCmdUI) 
{
	if( (gSysState == WORKING) || (gSysState == WORK_PAUSE) )
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnWorkCancel() 
{
	if (IDOK == MessageBox("是否取消？","注意",MB_OKCANCEL|MB_ICONERROR))
	{
		if (gThrdWork == NULL)
		{
			gMacSet.setQueryEnable(FALSE);
			gUSB.OnWorkCtrl(WORKCMD_CANCEL);
			GetDocument()->OnRemoveDocAllData();
			m_pListView->UpdateList();
			m_pMainView->OnReDraw();
			gMacSet.setQueryEnable(TRUE);
		}
		else
		{
			gMacSet.setThreadMessage(THREAD_MESSAGE_CANCEL);
		}
	}
	return;
}

void CMainFrame::OnWorkStart() 
{
	if(NULL == gThrdWork)
	{
		if (OnStartProcess() != 0)
		{
			gMacSet.setQueryEnable(TRUE);
		}
	}
	else if (gSysState == WORK_PAUSE)
	{
		gMacSet.setThreadMessage(THREAD_MESSAGE_RESUME);
	}
	return;
}

void CMainFrame::OnWorkPause() 
{
	if (gThrdWork != NULL)
	{
		gMacSet.setThreadMessage(THREAD_MESSAGE_PAUSE);
	}
}


void CMainFrame::OnLanChs() 
{
	if (gDispSet.getLanguage() != 0)
	{
		gDispSet.setLanguage(0);
		AfxMessageBox("语言设置改变，重启程序生效");
	}
}

void CMainFrame::OnLanEn() 
{
	if (gDispSet.getLanguage() != 1)
	{
		gDispSet.setLanguage(1);
		AfxMessageBox("You Changed the language settings,please restart the Application");
	}
}

void CMainFrame::OnUpdateLanChs(CCmdUI* pCmdUI) 
{
	if (gDispSet.getLanguage() == 0)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CMainFrame::OnUpdateLanEn(CCmdUI* pCmdUI) 
{
	if (gDispSet.getLanguage() == 1)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}	
}
