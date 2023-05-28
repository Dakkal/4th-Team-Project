// MapTool_Tab2.cpp : implementation file
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool_Tab2.h"
#include "afxdialogex.h"
#include "TextureMgr.h"

// CMapTool_Tab2 dialog

IMPLEMENT_DYNAMIC(CMapTool_Tab2, CDialogEx)

CMapTool_Tab2::CMapTool_Tab2(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TAB2, pParent)
{

}

CMapTool_Tab2::~CMapTool_Tab2()
{
}

void CMapTool_Tab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1_MAP, m_ListTile);
	DDX_Control(pDX, IDC_STATIC4_MAP, m_Texture_Tile);
	DDX_Control(pDX, IDC_COMBO1_MAP, m_ComboTile);

}


BEGIN_MESSAGE_MAP(CMapTool_Tab2, CDialogEx)
	ON_WM_DESTROY()
	ON_LBN_SELCHANGE(IDC_LIST1_MAP, &CMapTool_Tab2::OnList_Tile)
	ON_CBN_SELCHANGE(IDC_COMBO1_MAP, &CMapTool_Tab2::OnCombo_ChangeAct)
	ON_BN_CLICKED(IDC_BUTTON1_MAP, &CMapTool_Tab2::OnButton_ReloadTile)
END_MESSAGE_MAP()


// CMapTool_Tab2 message handlers


BOOL CMapTool_Tab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

#pragma region Jun
	Load_TileList();

	m_ComboTile.AddString(_T("Act 1"));
	m_ComboTile.AddString(_T("Act 2"));
	m_ComboTile.AddString(_T("Act 3"));

	if (m_ComboTile.GetCount() > 0)
	{
		m_ComboTile.SetCurSel((int)TERRIAN_TYPE::ACT1);
	}
	if (m_ComboTile.GetCurSel() == (int)TERRIAN_TYPE::ACT1)
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
				m_ListTile.AddString(L"Act1_" + fileName);

				auto	iter = m_TilePngImg.find(fileName);

				if (iter == m_TilePngImg.end())
				{
					CImage*	pPngImg = new CImage;
					pPngImg->Load(finder.GetFilePath());

					m_TilePngImg.insert({ fileName, pPngImg });
				}
			}
		}
		finder.Close();

		Sort_TileList(TERRIAN_TYPE::ACT1);
	}
#pragma endregion


#pragma region Chan

#pragma endregion




	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CMapTool_Tab2::OnDestroy()
{
	CDialogEx::OnDestroy();

#pragma region Jun
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();

	for_each(m_TilePngImg.begin(), m_TilePngImg.end(),
		[](auto& MyPair)
	{
		MyPair.second->Destroy();
		Safe_Delete(MyPair.second);
	});

	m_TilePngImg.clear();

#pragma endregion


#pragma region Chan

#pragma endregion

}

#pragma region Jun

void CMapTool_Tab2::OnList_Tile()
{
	UpdateData(TRUE);

	int	iSelect = m_ListTile.GetCurSel();

	if (LB_ERR == iSelect)
		return;

	for (auto& iter : m_vecTile)
	{
		TERRIAN_TYPE tCurAct = static_cast<TERRIAN_TYPE>(m_ComboTile.GetCurSel());

		switch (tCurAct)
		{
		case TERRIAN_TYPE::ACT1:
			if (iter->eType == TERRIAN_TYPE::ACT1 &&
				iter->byDrawID == iSelect)
			{
				m_tSelectTile = iter;

				int	iSelect = m_ListTile.GetCurSel();

				if (LB_ERR == iSelect)
					return;
				
				CString strSelectName;
				m_ListTile.GetText(iSelect, strSelectName);

				auto Imgiter = m_TilePngImg.find(strSelectName.Mid(5, strSelectName.GetLength()));

				if (Imgiter == m_TilePngImg.end())
					return;

				m_Texture_Tile.SetBitmap(*(Imgiter->second));
			}
			break;
		case TERRIAN_TYPE::ACT2:
			if (iter->eType == TERRIAN_TYPE::ACT2 &&
				iter->byDrawID == iSelect)
			{
				m_tSelectTile = iter;

				int	iSelect = m_ListTile.GetCurSel();

				if (LB_ERR == iSelect)
					return;

				CString strSelectName;
				m_ListTile.GetText(iSelect, strSelectName);

				auto Imgiter = m_TilePngImg.find(strSelectName.Mid(5, strSelectName.GetLength()));

				if (Imgiter == m_TilePngImg.end())
					return;

				m_Texture_Tile.SetBitmap(*(Imgiter->second));
			}
			break;
		case TERRIAN_TYPE::ACT3:
			if (iter->eType == TERRIAN_TYPE::ACT3 &&
				iter->byDrawID == iSelect)
			{
				m_tSelectTile = iter;

				int	iSelect = m_ListTile.GetCurSel();

				if (LB_ERR == iSelect)
					return;

				CString strSelectName;
				m_ListTile.GetText(iSelect, strSelectName);

				auto Imgiter = m_TilePngImg.find(strSelectName.Mid(5, strSelectName.GetLength()));

				if (Imgiter == m_TilePngImg.end())
					return;

				m_Texture_Tile.SetBitmap(*(Imgiter->second));
			}
			break;
		default:
			break;
		}

	}

	UpdateData(FALSE);
}

void CMapTool_Tab2::Load_TileList()
{
	UpdateData(TRUE);

	if (m_vecTile.empty())
	{
		HANDLE	hFile = CreateFile(L"../Data/Save_Tile.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		DWORD	dwByte = 0;

		while (true)
		{
			TILE* pTile = new TILE;

			ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

			if (0 == dwByte)
			{
				Safe_Delete(pTile);
				break;
			}

			m_vecTile.push_back(pTile);

			
		}

		CloseHandle(hFile);
	}

	UpdateData(FALSE);
}

void CMapTool_Tab2::OnCombo_ChangeAct()
{
	UpdateData(TRUE);

	m_ListTile.ResetContent();

	if (m_ComboTile.GetCurSel() == (int)TERRIAN_TYPE::ACT1)
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
				m_ListTile.AddString(L"Act1_" + fileName);

				auto	iter = m_TilePngImg.find(fileName);

				if (iter == m_TilePngImg.end())
				{
					CImage*	pPngImg = new CImage;
					pPngImg->Load(finder.GetFilePath());

					m_TilePngImg.insert({ fileName, pPngImg });
				}
			}
		}
		finder.Close();

		Sort_TileList(TERRIAN_TYPE::ACT1);
	}
	else if (m_ComboTile.GetCurSel() == (int)TERRIAN_TYPE::ACT2)
	{
		TCHAR szPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, szPath);
		PathRemoveFileSpec(szPath);
		lstrcat(szPath, L"\\Texture\\00.Tile\\Act2\\");
		CString strPath = szPath;

		CFileFind finder;
		BOOL bWorking = finder.FindFile(strPath + _T("*.png"));
		while (bWorking)
		{
			bWorking = finder.FindNextFile();

			if (!finder.IsDots() && !finder.IsDirectory())
			{
				CString fileName = finder.GetFileName();
				m_ListTile.AddString(L"Act2_" + fileName);

				auto	iter = m_TilePngImg.find(fileName);

				if (iter == m_TilePngImg.end())
				{
					CImage*	pPngImg = new CImage;
					pPngImg->Load(finder.GetFilePath());

					m_TilePngImg.insert({ fileName, pPngImg });
				}
			}
		}
		finder.Close();

		Sort_TileList(TERRIAN_TYPE::ACT2);
	}
	else if (m_ComboTile.GetCurSel() == (int)TERRIAN_TYPE::ACT3)
	{
		TCHAR szPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, szPath);
		PathRemoveFileSpec(szPath);
		lstrcat(szPath, L"\\Texture\\00.Tile\\Act3\\");
		CString strPath = szPath;

		CFileFind finder;
		BOOL bWorking = finder.FindFile(strPath + _T("*.png"));
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (!finder.IsDots() && !finder.IsDirectory())
			{
				CString fileName = finder.GetFileName();
				m_ListTile.AddString(L"Act3_" + fileName);

				auto	iter = m_TilePngImg.find(fileName);

				if (iter == m_TilePngImg.end())
				{
					CImage*	pPngImg = new CImage;
					pPngImg->Load(finder.GetFilePath());

					m_TilePngImg.insert({ fileName, pPngImg });
				}
			}
		}
		finder.Close();

		Sort_TileList(TERRIAN_TYPE::ACT3);
	}

	UpdateData(FALSE);
}

void CMapTool_Tab2::Sort_TileList(TERRIAN_TYPE _eType)
{
	UpdateData(TRUE);

	switch (_eType)
	{
	case TERRIAN_TYPE::ACT1:
	{
		vector<CString> fileList;
		for (int i = 0; i < m_ListTile.GetCount(); ++i)
		{
			CString fileName;
			m_ListTile.GetText(i, fileName);
			fileList.push_back(fileName);
		}

		sort(fileList.begin(), fileList.end(), [](const CString& str1, const CString& str2) {
			CString numStr1 = str1.Mid(10, str1.GetLength() - (4 * sizeof(TCHAR)));
			int num1 = _wtoi(numStr1);

			CString numStr2 = str2.Mid(10, str2.GetLength() - (4 * sizeof(TCHAR)));
			int num2 = _wtoi(numStr2);

			return num1 < num2;
		});

		m_ListTile.ResetContent();
		for (const CString& fileName : fileList)
		{
			m_ListTile.AddString(fileName);
		}
	}
	break;
	case TERRIAN_TYPE::ACT2:
	{
		vector<CString> fileList;
		for (int i = 0; i < m_ListTile.GetCount(); ++i)
		{
			CString fileName;
			m_ListTile.GetText(i, fileName);
			fileList.push_back(fileName);
		}

		sort(fileList.begin(), fileList.end(), [](const CString& str1, const CString& str2) {
			CString numStr1 = str1.Mid(9, str1.GetLength() - (4 * sizeof(TCHAR)));
			int num1 = _wtoi(numStr1);

			CString numStr2 = str2.Mid(9, str2.GetLength() - (4 * sizeof(TCHAR)));
			int num2 = _wtoi(numStr2);

			return num1 < num2;
		});

		m_ListTile.ResetContent();

		for (const CString& fileName : fileList)
		{
			m_ListTile.AddString(fileName);
		}
	}
	break;
	case TERRIAN_TYPE::ACT3:
	{
		vector<CString> fileList;
		for (int i = 0; i < m_ListTile.GetCount(); ++i)
		{
			CString fileName;
			m_ListTile.GetText(i, fileName);
			fileList.push_back(fileName);
		}

		sort(fileList.begin(), fileList.end(), [](const CString& str1, const CString& str2) {
			CString numStr1 = str1.Mid(10, str1.GetLength() - (4 * sizeof(TCHAR)));
			int num1 = _wtoi(numStr1);

			CString numStr2 = str2.Mid(10, str2.GetLength() - (4 * sizeof(TCHAR)));
			int num2 = _wtoi(numStr2);

			return num1 < num2;
		});

		m_ListTile.ResetContent();
		for (const CString& fileName : fileList)
		{
			m_ListTile.AddString(fileName);
		}
	}
	break;
	default:
		break;
	}

	UpdateData(FALSE);
}

void CMapTool_Tab2::OnButton_ReloadTile()
{
	UpdateData(TRUE);

	if (!m_vecTile.empty())
	{
		for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
		m_vecTile.clear();
		m_vecTile.shrink_to_fit();
	}
	if (m_vecTile.empty())
	{
		HANDLE	hFile = CreateFile(L"../Data/Save_Tile.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		DWORD	dwByte = 0;

		while (true)
		{
			TILE* pTile = new TILE;

			ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

			if (0 == dwByte)
			{
				Safe_Delete(pTile);
				break;
			}

			m_vecTile.push_back(pTile);


		}

		CloseHandle(hFile);
	}


	UpdateData(FALSE);
}


#pragma endregion

#pragma region Chan

#pragma endregion











