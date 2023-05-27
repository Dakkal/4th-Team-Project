// TileTool_Tab3.cpp : implementation file
//

#include "stdafx.h"
#include "Tool.h"
#include "TileTool_Tab3.h"
#include "afxdialogex.h"
#include "Terrain_Act1.h"
#include "Terrain_Act2.h"
#include "Terrain_Act3.h"

// CTileTool_Tab3 dialog

IMPLEMENT_DYNAMIC(CTileTool_Tab3, CDialogEx)

CTileTool_Tab3::CTileTool_Tab3(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TILETOOL, pParent)
	, m_iTileDamage(0)
	, m_iDrawId_First(0)
	, m_iDrawId_Last(0)
{

}

CTileTool_Tab3::~CTileTool_Tab3()
{
}

void CTileTool_Tab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TILE, m_Combo_Tile);
	DDX_Control(pDX, IDC_LIST_TILE, m_List_Tile);
	DDX_Control(pDX, IDC_CHECK1_TILE, m_Check_Tile[0]);
	DDX_Control(pDX, IDC_CHECK2_TILE, m_Check_Tile[1]);
	DDX_Control(pDX, IDC_CHECK3_TILE, m_Check_Tile[2]);
	DDX_Control(pDX, IDC_SPIN_TILE, m_Spin_Tile);

	DDX_Text(pDX, IDC_EDIT_TILE, m_iTileDamage);
	DDX_Text(pDX, IDC_EDIT1_TILE, m_iDrawId_First);
	DDX_Text(pDX, IDC_EDIT2_TILE, m_iDrawId_Last);
}


BEGIN_MESSAGE_MAP(CTileTool_Tab3, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TILE, &CTileTool_Tab3::OnPush_Tile)
	ON_BN_CLICKED(IDC_BUTTON2_TILE, &CTileTool_Tab3::OnClear_Tile)
	ON_BN_CLICKED(IDC_BUTTON3_TILE, &CTileTool_Tab3::OnSaveDB_Tile)
	ON_WM_DESTROY()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TILE, &CTileTool_Tab3::OnSet_TileDamage)
	ON_CBN_SELCHANGE(IDC_COMBO_TILE, &CTileTool_Tab3::OnActTileChange)
END_MESSAGE_MAP()


// CTileTool_Tab3 message handlers
BOOL CTileTool_Tab3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	// 초기 콤보박스
	m_Combo_Tile.AddString(_T("Act 1"));
	m_Combo_Tile.AddString(_T("Act 2"));
	m_Combo_Tile.AddString(_T("Act 3"));

	if (m_Combo_Tile.GetCount() > 0)
	{
		m_Combo_Tile.SetCurSel(0);
	}

	if (m_Combo_Tile.GetCurSel() == 0)
	{
		TCHAR szPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, szPath);
		PathRemoveFileSpec(szPath);
		lstrcat(szPath, L"\\Texture\\00.Tile\\Act1\\");
		CString strPath = szPath;

		CFileFind finder;
		BOOL bWorking = finder.FindFile(strPath + _T("*.png"));
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (!finder.IsDots() && !finder.IsDirectory())
			{
				CString fileName = finder.GetFileName();
				m_List_Tile.AddString(fileName);
			}
		}
		finder.Close();
        
		Sort_File();
	}






	m_Check_Tile[0].SetCheck(TRUE);








	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CTileTool_Tab3::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}

void CTileTool_Tab3::OnActTileChange()
{
	// TODO: Add your control notification handler code here
}

void CTileTool_Tab3::Sort_File()
{
	vector<CString> fileList;
	for (int i = 0; i < m_List_Tile.GetCount(); i++)
	{
		CString fileName;
		m_List_Tile.GetText(i, fileName);
		fileList.push_back(fileName);
	}

	sort(fileList.begin(), fileList.end(), [](const CString& str1, const CString& str2) {
		CString numStr1 = str1.Mid(5, str1.GetLength() - (4 * sizeof(TCHAR)));
		int num1 = _wtoi(numStr1);

		CString numStr2 = str2.Mid(5, str2.GetLength() - (4 * sizeof(TCHAR)));
		int num2 = _wtoi(numStr2);

		return num1 < num2;
	});

	m_List_Tile.ResetContent();
	for (const CString& fileName : fileList)
	{
		m_List_Tile.AddString(fileName);
	}
}




void CTileTool_Tab3::OnSet_TileDamage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CTileTool_Tab3::OnPush_Tile()
{
	// TODO: Add your control notification handler code here
}


void CTileTool_Tab3::OnClear_Tile()
{
	// TODO: Add your control notification handler code here
}


void CTileTool_Tab3::OnSaveDB_Tile()
{
	// TODO: Add your control notification handler code here
}











