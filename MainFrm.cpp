// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SpCutter.h"
#include "MainFrm.h"

#include "DlgSetClr.h"
#include "DlgMacPara.h"
#include "HpglFile.h"
#include "DlgSetDir.h"


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
	ON_WM_CLOSE()
	ON_COMMAND(IDM_AUTH_INFO, OnAuthInfo)
	ON_COMMAND(IDM_SUPER_USER, OnSuperUser)
	ON_COMMAND(IDCB_ZOOM_ALL, OnZoomAll)
	ON_COMMAND(ID_FILE_ATF_10x10, OnFILEATF10x10)
	ON_COMMAND(ID_FILE_ATF_20x20, OnFILEATF20x20)
	ON_COMMAND(ID_FILE_ATF_30x30, OnFILEATF30x30)
	ON_COMMAND(ID_FILE_ATF_40x40, OnFILEATF40x40)
	ON_COMMAND(ID_FILE_ATF_50x50, OnFILEATF50x50)
	ON_COMMAND(IDCB_WORK_START, OnWorkStart)
	ON_COMMAND(IDCB_WORK_PAUSE, OnWorkPause)
	ON_COMMAND(IDCB_WORK_CANCEL, OnWorkCancel)
	ON_COMMAND(IDM_LAN_CHS, OnLanChs)
	ON_COMMAND(IDM_LAN_EN, OnLanEn)
	ON_MESSAGE(USER_END_WTHREAD, OnEndWorkThread)
	ON_MESSAGE(USER_SEARCH_PLT, OnSearchNewPltFile)
	ON_MESSAGE(USER_AUTO_START, OnAutoStartWork)
	ON_UPDATE_COMMAND_UI(IDM_LAN_CHS, OnUpdateLanChs)
	ON_UPDATE_COMMAND_UI(IDM_LAN_EN, OnUpdateLanEn)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDCB_DLG_BAR, &CMainFrame::OnIdcbDlgBar)
	ON_UPDATE_COMMAND_UI(IDCB_DLG_BAR, &CMainFrame::OnUpdateIdcbDlgBar)
	ON_UPDATE_COMMAND_UI(IDM_CONNECT_VIA_ETH, &CMainFrame::OnUpdateConnectViaEth)
	ON_UPDATE_COMMAND_UI(IDM_CONNECT_VIA_USB, &CMainFrame::OnUpdateConnectViaUsb)
	ON_COMMAND(IDM_CONNECT_VIA_ETH, &CMainFrame::OnConnectViaEth)
	ON_COMMAND(IDM_CONNECT_VIA_USB, &CMainFrame::OnConnectViaUsb)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	g_pMainfrm = this;
	m_bShowDlgBar = TRUE;
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
	::SetProp(m_hWnd,"SPCutterV7",HANDLE(1));

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
		|CBRS_SIZE_DYNAMIC|CBRS_RIGHT,IDDLG_BAR))
	{
		TRACE0("Failed to create CDataStatus bar!");
		return -1;
	}

	gThreadTimeDetect = AfxBeginThread(ThreadTimeDetect, NULL);
	gThreadAutoConnect = AfxBeginThread(ThreadAutoConnect, NULL);
	gSet.setQueryEnable(TRUE);

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
	gSet.setQueryEnable(TRUE);

	if( (GetDocument()->m_ArrayPage.GetSize() > 0)&& (gSet.getJobAutoStart()) )
	{
		gSet.setWorkStartPause(TRUE);
	}
	gThrdWork = NULL;	
	return true;
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if (m_wndDlgBar.OnCmdMsg(nID,nCode,pExtra,pHandlerInfo))
		return TRUE;
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
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

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CRect cr;
	GetWindowRect( &cr );

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
		if (gSet.getPltPageLen() > 100)
		{
			GetDocument()->SpliteLastPage(gSet.getPltPageLen()*40);//分页;
		}
		if (gSet.getAutoDelPlt())
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
		if (gSet.getPltPageLen() > 100)
		{
			GetDocument()->SpliteLastPage(gSet.getPltPageLen()*40);//分页;
		}
		if (gSet.getAutoDelPlt())
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
	gSet.setQueryEnable(FALSE);
	dlg.DoModal();
	gSet.setQueryEnable(TRUE);
	Invalidate();
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

#include "DlgRegInfo.h"
void CMainFrame::OnAuthInfo() 
{
	u8 sbuf[64];
	u8 rbuf[64];

 	if( (gThrdWork != NULL)|| (READY != (gSysState&0x0f)) )
 	{
 		if (gDispSet.getLanguage() == 0){
 			AfxMessageBox("操作失败");
 		}else{
 			AfxMessageBox("Connect Machine First");
 		}
 		return;
 	}
 
 	gSet.setQueryEnable(FALSE);

	sbuf[0] = 1;
	int rev = gCommu.OnCmd1(CMD1_GET_MCU_ID, 1, sbuf, 4, rbuf);
	if (rev == 0)
	{
		u32 McuCode = *((u32*)(&(rbuf[0])));
		if (McuCode > 0x70000000)
		{
			gSet.setMcuCode(McuCode);
			CString str;
			str.Format("%x", McuCode ^ YHZIntArray[11]);
			gSet.setMcuSn(str);
			CDlgRegInfo dlg;
			dlg.DoModal();
		}
		else
		{
			AfxMessageBox("联机失败!");
		}
	}
	else
	{
		AfxMessageBox("联机失败!");
	}
	gSet.setQueryEnable(TRUE);
	return;
}

#include "DlgSuperUser.h"
void CMainFrame::OnSuperUser() 
{
	u8 sbuf[64];
	u8 rbuf[64];
 	if(gThrdWork != NULL)
 	{
 		if (gDispSet.getLanguage() == 0)
		{
 			AfxMessageBox("操作失败");
 		}
		else
		{
 			AfxMessageBox("Connect Machine First");
 		}
 		return;
 	}
 	
 	gSet.setQueryEnable(FALSE);
	sbuf[0] = 1;
	int rev = gCommu.OnCmd1(CMD1_GET_MCU_ID, 1, sbuf, 4, rbuf);
	u32 McuCode = *( (u32*)(&(rbuf[0]) ) );
	if( (rev == 0) && (McuCode > 0x70000000) )
 	{
 		gSet.setMcuCode(McuCode);
 		CDlgSuperUser dlg;
 		dlg.DoModal();
 	}
 	else
 	{
 		AfxMessageBox("联机失败!");
 	}
 	gSet.setQueryEnable(TRUE);
}

afx_msg LRESULT CMainFrame::OnSearchNewPltFile(WPARAM wParam,LPARAM lParam)
{
	CFileFind filefind;
	BOOL bFindFile;
	CString strPathName;
	bFindFile = filefind.FindFile(gSet.m_strDataDir+"*.*");
	
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
	if (gSet.getPltPageLen() > 100)
	{
		GetDocument()->SpliteLastPage(gSet.getPltPageLen()*40);//分页;
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
	gSet.setToolBarState(TBS_SEL);
	m_pMainView->OnSetViewCursor();
}

void CMainFrame::OnVMove() 
{
	gSet.setToolBarState(TBS_MOVE);	
	m_pMainView->OnSetViewCursor();
}

void CMainFrame::OnUpdateVMove(CCmdUI* pCmdUI) 
{
	if (gSet.getToolBarState() == TBS_MOVE)
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
	if (gSet.getToolBarState() == TBS_SEL)
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
	if (gSet.getJobAutoStart() == FALSE)
		return 0;

	rev = OnStartProcess();
	if ( rev != 0)
	{
		gSet.setQueryEnable(TRUE);
	}
	return 0;
}

int CMainFrame::OnStartProcess()
{
	int rev;
	u8 sbuf[64];
	u8 rbuf[64];
	CString strTemp;
#if (YHZ_DEBUG == 0)
	if( (FALSE == g_bParaRead) || (READY != (gSysState & 0x0f)) )
		return -1;
#endif
	if (GetDocument()->m_ArrayPage.GetSize() <= 0)
		return -1;
	gSet.setThreadMessage(THREAD_MESSAGE_NONE);

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

	if (gSet.getYBlankMm() > 0)
	{
		gWorkingPage.OnAddYMargin(gSet.getYBlankMm()*40);
	}
	if (gSet.getSpAutoClean()) //开始工作前自动清洗喷头功能开启
	{
		gWorkingPage.OnAddSpCleanData();
	}
	if (gSet.getOnlyPlot())
	{
		gWorkingPage.OnSetOnlyPlot();
	}
	gWorkingPage.OnPageAngleAdjust(); //进行垂直度校正
	gWorkingPage.OnRemoveInvalidPoints();
	gWorkingPage.OnCheckPageData();
	gWorkingPage.OnGetPageMaxMin(); //计算当前页的最小，最大值
	gWorkingPage.OnGetSizePlotCut(); //分别获取切割和绘图数据的最大坐标

	sbuf[0] = 1;
	gCommu.OnCmd1(CMD1_GET_ZP_POS, 1, sbuf, 8, rbuf);
	int iZpX = *( (int*)(&rbuf[0]) );
	int iZpY = *((int*)(&rbuf[4]));
	int iKpDistX, iKpDistY;

	if (gSet.getSpType() == 0) //HP45
	{
		iKpDistX = (int)((gSet.getKPDistX()*0.1 + 28)*gSet.getPPMMX() + KP_XXX);
		iKpDistY = (int)((gSet.getKPDistY()*0.1 + gSet.getSpAccDistmm())*gSet.getPPMMY() + KP_YYY);
	}
	else
	{
		iKpDistX = (int)((gSet.getKPDistX()*0.1 + 5)*gSet.getPPMMX() + KP_XXX);
		iKpDistY = (int)((gSet.getKPDistY()*0.1 + gSet.getSpAccDistmm()+5)*gSet.getPPMMY() + KP_YYY);
	}

	double dMaxPP_X = (gSet.getMacSizeX())*gSet.getPPMMX();
	double dMaxPP_Y = gSet.getMacSizeY()*gSet.getPPMMY();

	double dPlotMaxPP_X;
	if (gSet.getSpType() == 0) //HP45
	{
		dPlotMaxPP_X = iZpX + (gWorkingPage.m_nPlotXMax / 40.0+25)*gSet.getPPMMX();
	}
	else
	{
		dPlotMaxPP_X = iZpX + (gWorkingPage.m_nPlotXMax / 40.0+50)*gSet.getPPMMX();
	}

	double dPlotMaxPP_Y = iZpY + (gWorkingPage.m_nPlotYMax / 40.0 + gSet.getSpAccDistmm() )*gSet.getPPMMY();

	double dCutMaxPP_X = iZpX + (gWorkingPage.m_nCutXMax / 40.0)*gSet.getPPMMX() + iKpDistX;
	double dCutMaxPP_Y = iZpY + (gWorkingPage.m_nCutYMax / 40.0)*gSet.getPPMMY() + iKpDistY;
	int rrr = 0;
	if (dPlotMaxPP_X > dMaxPP_X)
	{
		rrr = 1;
	}
	else if (dPlotMaxPP_Y > dMaxPP_Y)
	{
		rrr = 2;
	}
	else if (dCutMaxPP_X > dMaxPP_X)
	{
		rrr = 3;
	}
	else if (dCutMaxPP_Y > dMaxPP_Y)
	{
		rrr = 4;
	}
	if(rrr != 0 )
	{
		CString strTemp;

		if (gDispSet.getLanguage() == 0)
		{
			strTemp.Format("超出幅面（类型%d），请重设原点或重新排料后输出！\n提示：\n类型1-X向喷墨超限\n类型2-Y向喷墨超限\n类型3-X向切割超限\n类型4-Y向切割超限)",rrr);
		}
		else
		{
			strTemp.Format("Out of Size-%d!:(1(PlotXSize),(2(PlotYSize),(3(CutXSize),(4(CutYSize))！", rrr);
		}
		AfxMessageBox(strTemp);
		return -1;
	}

	rev = CreateCncList();
	if (0 != rev)
	{
		AfxMessageBox("切割数据缓冲失败,原因:数据太大");
		return -1;
	}

	gSet.setQueryEnable(FALSE);
	rev = gMyReg.OnCheckRegCode(gSet.getAuthCode());
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

	if(NULL == gThrdWork) //没有绘图线程和切割线程在运行
	{
		gThrdWork = AfxBeginThread(ThreadWork,NULL);
		return 0;
	}
	return -1;
}

void CMainFrame::OnFILEATF10x10() 
{
	CString strFileName;
	GetDocument()->OnRemoveDocAllData();
	strFileName = gSet.m_strAppDir+"TestPlt\\10x10.plt";
	OnPltAddAuto(strFileName,FALSE);
}

void CMainFrame::OnFILEATF20x20() 
{
	CString strFileName;
	GetDocument()->OnRemoveDocAllData();
	strFileName = gSet.m_strAppDir+"TestPlt\\20x20.plt";
	OnPltAddAuto(strFileName,FALSE);
}

void CMainFrame::OnFILEATF30x30() 
{
	CString strFileName;
	GetDocument()->OnRemoveDocAllData();
	strFileName = gSet.m_strAppDir+"TestPlt\\30x30.plt";
	OnPltAddAuto(strFileName,FALSE);	
}

void CMainFrame::OnFILEATF40x40() 
{
	CString strFileName;
	GetDocument()->OnRemoveDocAllData();
	strFileName = gSet.m_strAppDir+"TestPlt\\40x40.plt";
	OnPltAddAuto(strFileName,FALSE);
}

void CMainFrame::OnFILEATF50x50()
{
	CString strFileName;
	GetDocument()->OnRemoveDocAllData();
	strFileName = gSet.m_strAppDir+"TestPlt\\50x50.plt";
	OnPltAddAuto(strFileName,FALSE);
}


void CMainFrame::OnWorkCancel() 
{
	if (IDOK == MessageBox("是否取消？","注意",MB_OKCANCEL|MB_ICONERROR))
	{
		if (gThrdWork == NULL)
		{
			gSet.setQueryEnable(FALSE);
 			gCommu.OnCmd0(CMD0_WCANCEL);
 			GetDocument()->OnRemoveDocAllData();
 			m_pListView->UpdateList();
 			m_pMainView->OnReDraw();
			gSet.setQueryEnable(TRUE);
		}
		else
		{
			gSet.setThreadMessage(THREAD_MESSAGE_CANCEL);
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
			gSet.setQueryEnable(TRUE);
		}
	}
	else if ((gSysState & 0x0f) == WORK_PAUSE)
	{
		gSet.setThreadMessage(THREAD_MESSAGE_RESUME);
	}
	return;
}

void CMainFrame::OnWorkPause() 
{
	if (gThrdWork != NULL)
	{
		gSet.setThreadMessage(THREAD_MESSAGE_PAUSE);
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

int CMainFrame::CreateCncList()
{
	int i;
	CCurve* pCurve;
	for (i = 0; i < gWorkingPage.m_CurveList.GetSize(); i++)
	{
		pCurve = (CCurve*)gWorkingPage.m_CurveList.GetAt(i);
		if (pCurve->m_nPenNum > 1)
		{
			pCurve->OnToCutData();
		}
	}
	if (g_ptrCncList.GetSize() <= 0)
	{
		return 0; //没有切割数据
	}

	CalculateAngles();
	if (gSet.getOverCutLen() > 0)
	{
		AddOverCutData(); //增加角度补偿值
		CalculateAngles();
	}

	GetLongAxialSteps();
	RemoveDupPoints();//20161215利用算法将线段密度稀疏
	CalculateAngles();

	GetLongAxialSteps();
	RemoveDupPoints();//20161215利用算法将线段密度稀疏
	CalculateAngles();

	GetLongAxialSteps();
	RemoveDupPoints();//20161215利用算法将线段密度稀疏
	CalculateAngles();

	GetLongAxialSteps();
	RemoveDupPoints();//20161215利用算法将线段密度稀疏
	CalculateAngles();

	GetLongAxialSteps();
	SetSecType(); //是弧线还是直线
	SetCurveType2();
	getCncMaxSpeed();
	CalculateSecNum();
	CalculateCncEndSpeed();

#ifdef _DEBUG
	dumpCutDataToFile();
#endif

	int	nSize = g_ptrCncList.GetSize();
	if (nSize >= 0xffff) //切割数据大小超过1M
	{
		return -1;
	}
	return 0;
}

void getCncMaxSpeed(void)
{
	int i, nSize;
	ST_CNC_DATA_ALL *pCncData;
	nSize = g_ptrCncList.GetSize();
	if (nSize == 0)
	{
		return;
	}
	for (i = 0; i <= nSize - 1; i++)
	{
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		switch (pCncData->m_cCmdType)
		{
		case TYPE_MOVE:
			pCncData->m_nMaxSpeed = 0;
			break;

		case TYPE_CUT:
			if (pCncData->m_cIsCurve == 1)
			{
				pCncData->m_nMaxSpeed = gSet.getCurveSpd();
			}
			else if (pCncData->m_cIsCurve == 2) //曲率比较高的弧线
			{
				pCncData->m_nMaxSpeed = 4; //20161215
			}
			else if (pCncData->m_cIsCurve == 3) //曲率比较高的弧线
			{
				pCncData->m_nMaxSpeed = 2; //20161215
			}
			else
			{
				pCncData->m_nMaxSpeed = MAX_SPD;
			}
			break;
		}
	}
}

void SetCurveType2(void)
{
	int i, nSize;
	double d;
	ST_CNC_DATA_ALL *pCncData;
	nSize = g_ptrCncList.GetSize();
	if (nSize == 0)
	{
		return;
	}
	for (i = 0; i < nSize; i++)
	{
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		switch (pCncData->m_cCmdType)
		{
		case TYPE_CUT:
			if (pCncData->m_cIsCurve == 1)
			{
				d = fabs(pCncData->m_dDeltaAngle)*100.0 / pCncData->m_nLongAxialStep;
				if( (d > 0.5 )||(pCncData->m_nLongAxialStep < 30) )
				{
					pCncData->m_cIsCurve = 3;
				}
				else if( (d > 0.1)||(pCncData->m_nLongAxialStep < 60 ) )
				{
					pCncData->m_cIsCurve = 2;
				}

			}
			break;

		default:
			break;
		}
	}
}

void SetSecType(void)
{
	int i, nSize;
	ST_CNC_DATA_ALL *pCncData;
	nSize = g_ptrCncList.GetSize();
	if (nSize == 0)
	{
		return;
	}

	for (i = 0; i < nSize; i++) //第一遍，遍历找到每段最大起始速度
	{
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		switch (pCncData->m_cCmdType)
		{
		case TYPE_MOVE:
			pCncData->m_cIsCurve = 0;
			break;

		case TYPE_CUT:
//			if (((fabs(pCncData->m_dDeltaAngle*180.0 / PI) > CURVE_ANGLE) && (pCncData->m_nLongAxialStep < 200)) //
			if (((fabs(pCncData->m_dDeltaAngle*180.0 / PI) > CURVE_ANGLE) && (pCncData->m_nLongAxialStep < 600)) //20161202
					|| (pCncData->m_nLongAxialStep < 20))
			{
				pCncData->m_cIsCurve = 1;
			}
			else
			{
				pCncData->m_cIsCurve = 0;
			}
			break;
		}
	}

	ST_CNC_DATA_ALL *pCncDataPrev;
	ST_CNC_DATA_ALL *pCncDataNext;

	for (i = 1; i < nSize - 1; i++)
	{
		pCncDataPrev = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i - 1);
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		pCncDataNext = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i + 1);
		if ((TYPE_CUT == pCncDataPrev->m_cCmdType)
			&& (TYPE_CUT == pCncData->m_cCmdType)
			&& (TYPE_CUT == pCncDataNext->m_cCmdType))
		{
			if ((pCncDataPrev->m_cIsCurve) && (pCncDataNext->m_cIsCurve) && ((pCncData->m_nLongAxialStep < 300)))
			{
				pCncData->m_cIsCurve = 1;
			}
		}
	}

	ST_CNC_DATA_ALL *pCncDataNextNext;

	for (i = 1; i < nSize - 2; i++)
	{
		pCncDataPrev = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i - 1);
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		pCncDataNext = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i + 1);
		pCncDataNextNext = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i + 2);
		if ((TYPE_CUT == pCncDataPrev->m_cCmdType)
			&& (TYPE_CUT == pCncData->m_cCmdType)
			&& (TYPE_CUT == pCncDataNext->m_cCmdType)
			&& (TYPE_CUT == pCncDataNextNext->m_cCmdType))
		{
			if ((pCncDataPrev->m_cIsCurve) && (pCncDataNextNext->m_cIsCurve))
			{
				if ((pCncData->m_nLongAxialStep + pCncDataNext->m_nLongAxialStep) < 400)
				{
					pCncData->m_cIsCurve = 1;
					pCncDataNext->m_cIsCurve = 1;
				}
			}
		}
	}

	ST_CNC_DATA_ALL *pCncDataNextNextNext;
	for (i = 1; i < nSize - 3; i++)
	{
		pCncDataPrev = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i - 1);
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		pCncDataNext = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i + 1);
		pCncDataNextNext = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i + 2);
		pCncDataNextNextNext = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i + 3);

		if ((TYPE_CUT == pCncDataPrev->m_cCmdType)
			&& (TYPE_CUT == pCncData->m_cCmdType)
			&& (TYPE_CUT == pCncDataNext->m_cCmdType)
			&& (TYPE_CUT == pCncDataNextNext->m_cCmdType)
			&& (TYPE_CUT == pCncDataNextNextNext->m_cCmdType))
		{
			if ((pCncDataPrev->m_cIsCurve) && (pCncDataNextNextNext->m_cIsCurve))
			{
				if ((pCncData->m_nLongAxialStep
					+ pCncDataNext->m_nLongAxialStep
					+ pCncDataNextNextNext->m_nLongAxialStep) < 500)
				{
					pCncData->m_cIsCurve = 1;
					pCncDataNext->m_cIsCurve = 1;
				}
			}
		}
	}
}

void CalculateSecNum()
{
	int i;
	ST_CNC_DATA_ALL *pCncData;
	int nSize;
	int nMaxStep;

	nSize = g_ptrCncList.GetSize();
	if (nSize == 0)
	{
		return;
	}
	for (i = 0; i < nSize; i++)
	{
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		nMaxStep = (abs(pCncData->m_iDeltaX) > abs(pCncData->m_iDeltaY)) ? abs(pCncData->m_iDeltaX) : abs(pCncData->m_iDeltaY);
		pCncData->m_nSecNum = nMaxStep / gSet.getSecLen(); //分段长度60
		if (0 == pCncData->m_nSecNum)
		{
			pCncData->m_nSecNum = 1;
		}
	}
}


void CalculateCncEndSpeed(void)
{
	int i, nSize;
	ST_CNC_DATA_ALL *pCncData;
	ST_CNC_DATA_ALL *pCncDataNext;
	nSize = g_ptrCncList.GetSize();
	if (nSize == 0)
	{
		return;
	}

	pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(nSize - 1);
	pCncData->m_nMaxEndSpeed = 0;

	for (i = nSize - 2; i >= 0; i--)
	{
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		pCncDataNext = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i + 1);
		if (fabs(pCncDataNext->m_dDeltaAngle)*180.0 / PI >= SD0_ANGLE)
		{
			pCncData->m_nMaxEndSpeed = 0;
		}

		else if ((TYPE_CUT == pCncData->m_cCmdType)
			&& (TYPE_CUT == pCncDataNext->m_cCmdType))
		{
//			pCncData->m_nMaxEndSpeed = pCncDataNext->m_nMaxEndSpeed + (pCncDataNext->m_nSecNum - 1);
			pCncData->m_nMaxEndSpeed = pCncDataNext->m_nMaxEndSpeed + (pCncDataNext->m_nSecNum);

			if (fabs(pCncDataNext->m_dDeltaAngle*180.0 / PI) > SD5_ANGLE)
			{
				if (pCncData->m_nMaxEndSpeed > SD5_SPD)
				{
					pCncData->m_nMaxEndSpeed = SD5_SPD;
				}
			}

			if (pCncData->m_nMaxEndSpeed > pCncData->m_nMaxSpeed)
			{
				pCncData->m_nMaxEndSpeed = pCncData->m_nMaxSpeed;
			}
			if (pCncData->m_nMaxEndSpeed > pCncDataNext->m_nMaxSpeed)
			{
				pCncData->m_nMaxEndSpeed = pCncDataNext->m_nMaxSpeed;
			}
		}
		else
		{
			pCncData->m_nMaxEndSpeed = 0;
		}
	}
}


void CMainFrame::OnIdcbDlgBar()
{
	// TODO: 在此添加命令处理程序代码
	if (m_bShowDlgBar)
	{
		ShowControlBar(&m_wndDlgBar, FALSE, FALSE);
		m_bShowDlgBar = FALSE;
	}
	else
	{
		ShowControlBar(&m_wndDlgBar, TRUE, TRUE);
		m_bShowDlgBar = TRUE;
	}
}


void CMainFrame::OnUpdateIdcbDlgBar(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (m_bShowDlgBar)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}


void CMainFrame::OnUpdateConnectViaEth(CCmdUI *pCmdUI)
{
	if (gSet.getConnetViaEth())
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}


void CMainFrame::OnUpdateConnectViaUsb(CCmdUI *pCmdUI)
{
	if (gSet.getConnetViaEth())
	{
		pCmdUI->SetCheck(FALSE);
	}
	else
	{
		pCmdUI->SetCheck(TRUE);
	}
}


void CMainFrame::OnConnectViaEth()
{
	gSet.setConnetViaEth(TRUE);
}


void CMainFrame::OnConnectViaUsb()
{
	gSet.setConnetViaEth(FALSE);
}
