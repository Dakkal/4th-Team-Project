// MyForm.cpp : 구현 파일입니다.
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
END_MESSAGE_MAP()

void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();




	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_Font.CreatePointFont(180, L"궁서");

	CRect rect{};

	m_tab.GetClientRect(rect);
	m_tab.InsertItem(0, L"유닛툴");
	m_tab.InsertItem(1, L"맵툴");

	m_tab.SetCurSel(0);

	m_pUnitTool_Tab1 = new CUnitTool_Tab1;
	m_pUnitTool_Tab1->Create(IDD_DIALOG_TAB1, &m_tab);
	m_pUnitTool_Tab1->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_pUnitTool_Tab1->ShowWindow(SW_SHOW);

	m_pMapTool_Tab2 = new CMapTool_Tab2;
	m_pMapTool_Tab2->Create(IDD_DIALOG_TAB2, &m_tab);
	m_pMapTool_Tab2->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_pMapTool_Tab2->ShowWindow(SW_HIDE);

	// GetDlgItem : 다이얼로그에 배치된 리소스를 id값에 따라 얻어오는 함수
}


#pragma region 안봐
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
#pragma endregion 안봐




void CMyForm::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (IDC_TAB1 == pNMHDR->idFrom) { // Tab Control ID명
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
