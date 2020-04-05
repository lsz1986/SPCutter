// MyListView.cpp : implementation file
//

#include "stdafx.h"
#include "SpCutter.h"
#include "MyListView.h"
#include "Global.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListView

IMPLEMENT_DYNCREATE(CMyListView, CListView)

CMyListView::CMyListView()
{
}

CMyListView::~CMyListView()
{
}


BEGIN_MESSAGE_MAP(CMyListView, CListView)
	//{{AFX_MSG_MAP(CMyListView)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(IDM_LIST_CLEAN, OnListClean)
	ON_COMMAND(IDM_LIST_DEL, OnListDel)
	ON_WM_KEYUP()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_COMMAND(IDM_LIST_TOP, OnListTop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListView drawing

void CMyListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyListView diagnostics

#ifdef _DEBUG
void CMyListView::AssertValid() const
{
	CListView::AssertValid();
}

void CMyListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyListView message handlers

void CMyListView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	CListCtrl& myListCtrl = (CListCtrl&)GetListCtrl();
	////初始化界面
    myListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	myListCtrl.SetBkColor(RGB(255,255,255));
	myListCtrl.SetTextBkColor(RGB(255,255,255));
	myListCtrl.SetTextColor(RGB(0,0,255));


    LONG lStyle;
    lStyle = GetWindowLong(myListCtrl.m_hWnd, GWL_STYLE);//获取当前窗口style
    lStyle &= ~LVS_TYPEMASK; //清除显示方式位
    lStyle |= LVS_REPORT; //设置style
    SetWindowLong(myListCtrl.m_hWnd, GWL_STYLE, lStyle);//设置style

	if (gDispSet.getLanguage() == 0)
	{
		myListCtrl.InsertColumn(0,_T("序号"),LVCFMT_CENTER,80);//插入列
		myListCtrl.InsertColumn(1,_T("幅面(Xmm*Ymm)"),LVCFMT_CENTER,220);
		myListCtrl.InsertColumn(2,_T("原始文件名---页号"),LVCFMT_CENTER,600);
	}
	else
	{
		myListCtrl.InsertColumn(0,_T("No."),LVCFMT_CENTER,80);//插入列
		myListCtrl.InsertColumn(1,_T("Size(Xmm*Ymm)"),LVCFMT_CENTER,220);
		myListCtrl.InsertColumn(2,_T("File Name---Page No."),LVCFMT_CENTER,600);
	}

}

void CMyListView::UpdateList()
{
	CSpCutterDoc* pDoc = (CSpCutterDoc*)GetDocument();
	CListCtrl& myListCtrl = (CListCtrl&)GetListCtrl();
	int nPageIndex,nPageSum;
	CString str;
	int Xmm,Ymm;
	myListCtrl.DeleteAllItems();
	nPageSum = pDoc->m_ArrayPage.GetSize();
	if (0 == nPageSum)
	{
		return;
	}
	for(nPageIndex=0; nPageIndex<nPageSum; nPageIndex++)//获取当前已插入的行数
	{
		COnePage* pPage = (COnePage*)(pDoc->m_ArrayPage.GetAt(nPageIndex));

		myListCtrl.InsertItem(nPageIndex, _T(""));//插入一行

		str.Format("%03d",nPageIndex+1);
		myListCtrl.SetItemText(nPageIndex, 0, str);//第一列

		Xmm = (pPage->m_nXmax - pPage->m_nXmin)/40;
		Ymm = (pPage->m_nYmax - pPage->m_nYmin)/40;
		str.Format("%d*%d",Xmm,Ymm);
		myListCtrl.SetItemText(nPageIndex, 1, str);//第二列
		
		str.Format("---第%03d页",pPage->m_nOrgPageNum);
		str = pPage->m_strFileName+str;
		myListCtrl.SetItemText(nPageIndex, 2, str);//第三列
	}
}

void CMyListView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu menu ,* pSubMenu; //定义下面要用到的cmenu对象
	menu.LoadMenu(IDR_POPMENU_LIST); //装载自定义的右键菜单 IDR_POPMENU弹出菜单的ID

	//获取第一个弹出菜单，所以第一个菜单必须有子菜单
	pSubMenu = menu.GetSubMenu(0);

	CPoint oPoint; //定义一个用于确定光标位置的位置
	GetCursorPos( &oPoint); //获取当前光标的位置，以便使得菜单可以跟随光标11
	pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //显示菜单，第四个为传递的参数
	*pResult = 0;
}

void CMyListView::OnListClean() 
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(gThrdWork != NULL) //清空列表时
	{
		if (gDispSet.getLanguage() == 0) {
			AfxMessageBox("正在工作,不能清空!");
		}else {
			AfxMessageBox("Can not remove file while working!");
		}
		return;
	}
	if (IDOK == MessageBox("是否清空列表?","提示",MB_OKCANCEL|MB_ICONWARNING))
	{
		CSpCutterDoc* pDoc = (CSpCutterDoc*)GetDocument();
		pDoc->OnRemoveDocAllData();
		UpdateList();
		m_pMainView->SetCurrentDrawPage(0);
		m_pMainView->OnReDraw();	
	}
}

void CMyListView::OnListDel() 
{
	CListCtrl& myListCtrl = (CListCtrl&)GetListCtrl();

	POSITION pos = myListCtrl.GetFirstSelectedItemPosition();
	int   nIndex = myListCtrl.GetNextSelectedItem(pos);  
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(gThrdWork != NULL) //删除页面时
	{
		if (nIndex == 0)
		{
			AfxMessageBox("不能删除正在加工的页！");
			return;
		}
	}

	if (nIndex>=0)
	{
		CSpCutterDoc* pDoc = (CSpCutterDoc*)GetDocument();
		pDoc->OnRemoveOnePageData(nIndex);
		UpdateList();

		if ( myListCtrl.GetItemCount() > 0)
		{
			if (nIndex < myListCtrl.GetItemCount())
			{
				myListCtrl.SetItemState(nIndex,LVNI_SELECTED,LVNI_SELECTED); 
				m_pMainView->SetCurrentDrawPage(nIndex);
			}
			else
			{
				myListCtrl.SetItemState(nIndex-1,LVNI_SELECTED,LVNI_SELECTED); 
				m_pMainView->SetCurrentDrawPage(nIndex-1);
			}
			myListCtrl.SetFocus();
		}
		m_pMainView->OnReDraw();
	}
}

void CMyListView::OnSelChg()
{
	CListCtrl& myListCtrl = (CListCtrl&)GetListCtrl();
	POSITION pos = myListCtrl.GetFirstSelectedItemPosition();
	int   nIndex = myListCtrl.GetNextSelectedItem(pos);  
	m_pMainView->SetCurrentDrawPage(nIndex);
	myListCtrl.SetFocus();
}

void CMyListView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
		case VK_DELETE:
		OnListDel();
		break;

		case VK_UP:
		case VK_DOWN:
		OnSelChg();
		break;
	}
	CListView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMyListView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CListCtrl& myListCtrl = (CListCtrl&)GetListCtrl();

	POSITION pos = myListCtrl.GetFirstSelectedItemPosition();
	int   nIndex = myListCtrl.GetNextSelectedItem(pos);  
	
	m_pMainView->SetCurrentDrawPage(nIndex);
	*pResult = 0;
}

void CMyListView::OnListTop() 
{
	CListCtrl& myListCtrl = (CListCtrl&)GetListCtrl();

	POSITION pos = myListCtrl.GetFirstSelectedItemPosition();
	int   nIndex = myListCtrl.GetNextSelectedItem(pos);
	if (nIndex <= 0)
	{
		return;
	}

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	COnePage* pPage;
	CSpCutterDoc* pDoc = (CSpCutterDoc*)GetDocument();
	pPage = (COnePage*)( pDoc->m_ArrayPage.GetAt(nIndex) );
	pDoc->m_ArrayPage.RemoveAt(nIndex);

	if(gThrdWork != NULL) //文件上移到顶时
	{
		pDoc->m_ArrayPage.InsertAt(1,pPage);
	}
	else
	{
		pDoc->m_ArrayPage.InsertAt(0,pPage);
	}
	UpdateList();
}
