// MyForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"
#include "UnitTool_Tab1.h"
#include "MapTool_Tab2.h"

// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMyForm::OnSelchangeTab1)
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();




	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_Font.CreatePointFont(180, L"�ü�");

	CRect rect{};

	m_tab.GetClientRect(rect);
	m_tab.InsertItem(0, L"Unit Tool");
	m_tab.InsertItem(1, L"Map Tool");

	m_tab.SetCurSel(0);

	m_pUnitTool_Tab1 = new CUnitTool_Tab1;
	m_pUnitTool_Tab1->Create(IDD_DIALOG_TAB1, &m_tab);
	m_pUnitTool_Tab1->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_pUnitTool_Tab1->ShowWindow(SW_SHOW);

	m_pMapTool_Tab2 = new CMapTool_Tab2;
	m_pMapTool_Tab2->Create(IDD_DIALOG_TAB2, &m_tab);
	m_pMapTool_Tab2->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_pMapTool_Tab2->ShowWindow(SW_HIDE);

	// GetDlgItem : ���̾�α׿� ��ġ�� ���ҽ��� id���� ���� ������ �Լ�
}


#pragma region �Ⱥ�
#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG
#pragma endregion �Ⱥ�




void CMyForm::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (IDC_TAB1 == pNMHDR->idFrom) { // Tab Control ID��
		int select = m_tab.GetCurSel();
		switch (select) {
		case 0:
			m_pUnitTool_Tab1->ShowWindow(SW_SHOW);
			m_pMapTool_Tab2->ShowWindow(SW_HIDE);
			break;
		case 1:
			m_pUnitTool_Tab1->ShowWindow(SW_HIDE);
			m_pMapTool_Tab2->ShowWindow(SW_SHOW);

			break;
		}
	}
	*pResult = 0;
}


void CMyForm::OnDestroy()
{
	CFormView::OnDestroy();

	Safe_Delete(m_pUnitTool_Tab1);
	Safe_Delete(m_pMapTool_Tab2);

	// TODO: Add your message handler code here
}


void CMyForm::OnSize(UINT nType, int cx, int cy)
{

	CFormView::OnSize(nType, cx, cy);
	if (::IsWindow(m_hWnd))
	{
		CRect rectClient{};
		GetClientRect(&rectClient);

		// ��Ʈ�ѵ��� ID�� ����Ͽ� ��ġ�� ũ�⸦ ����
		CWnd* pCtrl = GetDlgItem(IDC_TAB1);
		if (pCtrl != nullptr)
		{
			pCtrl->MoveWindow(rectClient);

		}

		if (m_pUnitTool_Tab1 != nullptr)
		{
			m_pUnitTool_Tab1->MoveWindow(0, 30, rectClient.Width(), rectClient.Height());
		}

		if (m_pMapTool_Tab2 != nullptr)
		{
			m_pMapTool_Tab2->MoveWindow(0, 30, rectClient.Width(), rectClient.Height());
		}
	}
	// TODO: Add your message handler code here
}
