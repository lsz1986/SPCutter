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
	////��ʼ������
    myListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	myListCtrl.SetBkColor(RGB(255,255,255));
	myListCtrl.SetTextBkColor(RGB(255,255,255));
	myListCtrl.SetTextColor(RGB(0,0,255));


    LONG lStyle;
    lStyle = GetWindowLong(myListCtrl.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
    lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
    lStyle |= LVS_REPORT; //����style
    SetWindowLong(myListCtrl.m_hWnd, GWL_STYLE, lStyle);//����style

	if (gDispSet.getLanguage() == 0)
	{
		myListCtrl.InsertColumn(0,_T("���"),LVCFMT_CENTER,80);//������
		myListCtrl.InsertColumn(1,_T("����(Xmm*Ymm)"),LVCFMT_CENTER,220);
		myListCtrl.InsertColumn(2,_T("ԭʼ�ļ���---ҳ��"),LVCFMT_CENTER,600);
	}
	else
	{
		myListCtrl.InsertColumn(0,_T("No."),LVCFMT_CENTER,80);//������
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
	for(nPageIndex=0; nPageIndex<nPageSum; nPageIndex++)//��ȡ��ǰ�Ѳ��������
	{
		COnePage* pPage = (COnePage*)(pDoc->m_ArrayPage.GetAt(nPageIndex));

		myListCtrl.InsertItem(nPageIndex, _T(""));//����һ��

		str.Format("%03d",nPageIndex+1);
		myListCtrl.SetItemText(nPageIndex, 0, str);//��һ��

		Xmm = (pPage->m_nXmax - pPage->m_nXmin)/40;
		Ymm = (pPage->m_nYmax - pPage->m_nYmin)/40;
		str.Format("%d*%d",Xmm,Ymm);
		myListCtrl.SetItemText(nPageIndex, 1, str);//�ڶ���
		
		str.Format("---��%03dҳ",pPage->m_nOrgPageNum);
		str = pPage->m_strFileName+str;
		myListCtrl.SetItemText(nPageIndex, 2, str);//������
	}
}

void CMyListView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu menu ,* pSubMenu; //��������Ҫ�õ���cmenu����
	menu.LoadMenu(IDR_POPMENU_LIST); //װ���Զ�����Ҽ��˵� IDR_POPMENU�����˵���ID

	//��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵�
	pSubMenu = menu.GetSubMenu(0);

	CPoint oPoint; //����һ������ȷ�����λ�õ�λ��
	GetCursorPos( &oPoint); //��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����11
	pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //��ʾ�˵������ĸ�Ϊ���ݵĲ���
	*pResult = 0;
}

void CMyListView::OnListClean() 
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(gThrdWork != NULL) //����б�ʱ
	{
		if (gDispSet.getLanguage() == 0) {
			AfxMessageBox("���ڹ���,�������!");
		}else {
			AfxMessageBox("Can not remove file while working!");
		}
		return;
	}
	if (IDOK == MessageBox("�Ƿ�����б�?","��ʾ",MB_OKCANCEL|MB_ICONWARNING))
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
	if(gThrdWork != NULL) //ɾ��ҳ��ʱ
	{
		if (nIndex == 0)
		{
			AfxMessageBox("����ɾ�����ڼӹ���ҳ��");
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

	if(gThrdWork != NULL) //�ļ����Ƶ���ʱ
	{
		pDoc->m_ArrayPage.InsertAt(1,pPage);
	}
	else
	{
		pDoc->m_ArrayPage.InsertAt(0,pPage);
	}
	UpdateList();
}
