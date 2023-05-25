// UnitTool_Tab1.cpp : implementation file
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool_Tab1.h"
#include "afxdialogex.h"


// CUnitTool_Tab1 dialog

IMPLEMENT_DYNAMIC(CUnitTool_Tab1, CDialogEx)

CUnitTool_Tab1::CUnitTool_Tab1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TAB1, pParent)
{

}

CUnitTool_Tab1::~CUnitTool_Tab1()
{
	Safe_Delete(pDlgPlayer);
	Safe_Delete(pDlgMonster);
	Safe_Delete(pDlgItme);
}

void CUnitTool_Tab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_UNIT, m_tab);
}


BEGIN_MESSAGE_MAP(CUnitTool_Tab1, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_UNIT, &CUnitTool_Tab1::OnSelchangeTabUnit)
	ON_WM_DESTROY()
	ON_WM_DELETEITEM()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CUnitTool_Tab1 message handlers


void CUnitTool_Tab1::OnSelchangeTabUnit(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (IDC_TAB_UNIT == pNMHDR->idFrom) { // Tab Control ID¸í
		int select = m_tab.GetCurSel();
		switch (select) {
		case 0:
			pDlgPlayer->ShowWindow(SW_SHOW);
			pDlgMonster->ShowWindow(SW_HIDE);
			pDlgItme->ShowWindow(SW_HIDE);
			break;
		case 1:
			pDlgPlayer->ShowWindow(SW_HIDE);
			pDlgMonster->ShowWindow(SW_SHOW);
			pDlgItme->ShowWindow(SW_HIDE);
			break;
		case 2:
			pDlgPlayer->ShowWindow(SW_HIDE);
			pDlgMonster->ShowWindow(SW_HIDE);
			pDlgItme->ShowWindow(SW_SHOW);

			break;
		}
	}
	*pResult = 0;
}


BOOL CUnitTool_Tab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	CRect rect{};

	m_tab.GetClientRect(rect);
	m_tab.InsertItem(0, L"Player");
	m_tab.InsertItem(1, L"Monster");
	m_tab.InsertItem(2, L"Item");

	m_tab.SetCurSel(0);

	pDlgPlayer = new UnitTool_Player;
	pDlgPlayer->Create(IDD_UNIT_PLAYER, &m_tab);
	pDlgPlayer->MoveWindow(0, TAB_HEIGHT, rect.Width(), rect.Height());
	pDlgPlayer->ShowWindow(SW_SHOW);

	pDlgMonster = new UnitTool_Monster;
	pDlgMonster->Create(IDD_UNIT_MONSTER, &m_tab);
	pDlgMonster->MoveWindow(0, TAB_HEIGHT, rect.Width(), rect.Height());
	pDlgMonster->ShowWindow(SW_HIDE);

	pDlgItme = new UnitTool_Item;
	pDlgItme->Create(IDD_UNIT_ITEM, &m_tab);
	pDlgItme->MoveWindow(0, TAB_HEIGHT, rect.Width(), rect.Height());
	pDlgItme->ShowWindow(SW_HIDE);

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}



