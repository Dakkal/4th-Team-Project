// TileTool_Tab3.cpp : implementation file
//

#include "stdafx.h"
#include "Tool.h"
#include "TileTool_Tab3.h"
#include "afxdialogex.h"
#include "Terrain_Act1.h"
#include "Terrain_Act2.h"
#include "Terrain_Act3.h"
#include "TextureMgr.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "Device.h"

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
	DDX_Control(pDX, IDC_EDIT_TILE, m_Edit_TileDmg);
}


BEGIN_MESSAGE_MAP(CTileTool_Tab3, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TILE, &CTileTool_Tab3::OnPush_Tile)
	ON_BN_CLICKED(IDC_BUTTON2_TILE, &CTileTool_Tab3::OnClear_Tile)
	ON_BN_CLICKED(IDC_BUTTON3_TILE, &CTileTool_Tab3::OnSaveDB_Tile)
	ON_WM_DESTROY()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TILE, &CTileTool_Tab3::OnSet_TileDamage)
	ON_CBN_SELCHANGE(IDC_COMBO_TILE, &CTileTool_Tab3::OnActTileChange)
	ON_LBN_SELCHANGE(IDC_LIST_TILE, &CTileTool_Tab3::OnListTile)
	ON_BN_CLICKED(IDC_BUTTON4_TILE, &CTileTool_Tab3::OnLoadDB_Tile)
END_MESSAGE_MAP()


// CTileTool_Tab3 message handlers
BOOL CTileTool_Tab3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//텍스처 입력
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/00.Tile/Act1/Tile_%d.png", TEX_MULTI, L"Act1Terrain", L"Tile", 325)))
	{
		AfxMessageBox(L"TileTexture Create Failed");
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/00.Tile/Act2/Tile%d.png", TEX_MULTI, L"Act2Terrain", L"Tile", 31)))
	{
		AfxMessageBox(L"TileTexture Create Failed");
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/00.Tile/Act3/Tile_%d.png", TEX_MULTI, L"Act3Terrain", L"Tile", 288)))
	{
		AfxMessageBox(L"TileTexture Create Failed");
		return E_FAIL;
	}

	// 툴뷰 가져오기
	CMainFrame*		pMainFrm = static_cast<CMainFrame*>(AfxGetMainWnd());
	m_pMainView = static_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 0));


	// 초기 콤보
	m_Combo_Tile.AddString(_T("Act 1"));
	m_Combo_Tile.AddString(_T("Act 2"));
	m_Combo_Tile.AddString(_T("Act 3"));

	if (m_Combo_Tile.GetCount() > 0)
	{
		m_Combo_Tile.SetCurSel((int)TERRIAN_TYPE::ACT1);
	}

	// 초기 리스트박스
	if (m_Combo_Tile.GetCurSel() == (int)TERRIAN_TYPE::ACT1)
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
        
		Sort_File(TERRIAN_TYPE::ACT1);
	}

	// 초기 스파인 컨트롤
	m_Spin_Tile.SetRange(0, 10);
	m_Spin_Tile.SetPos(0);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CTileTool_Tab3::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	for_each(m_vecTile_Act1.begin(), m_vecTile_Act1.end(), CDeleteObj());
	m_vecTile_Act1.clear();
	m_vecTile_Act1.shrink_to_fit();

	for_each(m_vecTile_Act2.begin(), m_vecTile_Act2.end(), CDeleteObj());
	m_vecTile_Act2.clear();
	m_vecTile_Act2.shrink_to_fit();

	for_each(m_vecTile_Act3.begin(), m_vecTile_Act3.end(), CDeleteObj());
	m_vecTile_Act3.clear();
	m_vecTile_Act3.shrink_to_fit();
}

void CTileTool_Tab3::Tool_Render(const D3DXVECTOR3& _vWorld)
{
	UpdateData(TRUE);

	TERRIAN_TYPE e_TerrainTYPE = static_cast<TERRIAN_TYPE>(m_Combo_Tile.GetCurSel());

	switch (e_TerrainTYPE)
	{
	case TERRIAN_TYPE::ACT1:
	{
		int iIndex = m_iDrawId_First;
		auto& iter = m_vecTile_Act1[iIndex];

		D3DXMATRIX matWorld, matScale, matRotZ, matTrans;

		D3DXVECTOR3 vPos = iter->vPos + _vWorld; // 

		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, iter->vSize.x, iter->vSize.y, iter->vSize.z);
		D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, vPos.z);

		matWorld = matScale *  matTrans;

		const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Act1Terrain", L"Tile", iter->byDrawID);

		if (nullptr == pTexInfo) return;

		float	fX = pTexInfo->tImgInfo.Width / 2.f;
		float	fY = pTexInfo->tImgInfo.Height / 2.f;

		// 이미지에 행렬을 반영
		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,							// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0 기준으로 출력
			&D3DXVECTOR3(fX, fY, 0.f),			// 출력할 이미지의 중심축에 대한 vector3 주소, null인 경우 이미지의 0, 0이 중심 좌표
			nullptr,							// 위치 좌표에 대한 vector3 주소, null인 경우 스크린 상의 0, 0좌표 출력
			D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 원본 색상 유지
	}
		break;
	case TERRIAN_TYPE::ACT2:
	{
		int iIndex = m_iDrawId_First;
		auto& iter = m_vecTile_Act2[iIndex];

		D3DXMATRIX matWorld, matScale, matRotZ, matTrans;

		D3DXVECTOR3 vPos = iter->vPos + _vWorld; // 

		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, iter->vSize.x, iter->vSize.y, iter->vSize.z);
		D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, vPos.z);

		matWorld = matScale *  matTrans;

		const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Act2Terrain", L"Tile", iter->byDrawID);

		if (nullptr == pTexInfo) return;

		float	fX = pTexInfo->tImgInfo.Width / 2.f;
		float	fY = pTexInfo->tImgInfo.Height / 2.f;

		// 이미지에 행렬을 반영
		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,							// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0 기준으로 출력
			&D3DXVECTOR3(fX, fY, 0.f),			// 출력할 이미지의 중심축에 대한 vector3 주소, null인 경우 이미지의 0, 0이 중심 좌표
			nullptr,							// 위치 좌표에 대한 vector3 주소, null인 경우 스크린 상의 0, 0좌표 출력
			D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 원본 색상 유지
	}
		break;
	case TERRIAN_TYPE::ACT3:
	{
		int iIndex =m_iDrawId_First;
		auto& iter = m_vecTile_Act3[iIndex];

		D3DXMATRIX matWorld, matScale, matRotZ, matTrans;

		D3DXVECTOR3 vPos = iter->vPos + _vWorld; // 

		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, iter->vSize.x, iter->vSize.y, iter->vSize.z);
		D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, vPos.z);

		matWorld = matScale *  matTrans;

		const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Act3Terrain", L"Tile", iter->byDrawID);

		if (nullptr == pTexInfo) return;

		float	fX = pTexInfo->tImgInfo.Width / 2.f;
		float	fY = pTexInfo->tImgInfo.Height / 2.f;

		// 이미지에 행렬을 반영
		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,							// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0 기준으로 출력
			&D3DXVECTOR3(fX, fY, 0.f),			// 출력할 이미지의 중심축에 대한 vector3 주소, null인 경우 이미지의 0, 0이 중심 좌표
			nullptr,							// 위치 좌표에 대한 vector3 주소, null인 경우 스크린 상의 0, 0좌표 출력
			D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 원본 색상 유지
	}
		break;
	default:
		break;
	}

	
	
	UpdateData(FALSE);

	//m_pMainView->Invalidate(FALSE);
}

void CTileTool_Tab3::Set_Ratio(D3DXMATRIX * pOut, float fRatioX, float fRatioY)
{

	pOut->_11 *= fRatioX;
	pOut->_21 *= fRatioX;
	pOut->_31 *= fRatioX;
	pOut->_41 *= fRatioX;

	pOut->_12 *= fRatioY;
	pOut->_22 *= fRatioY;
	pOut->_32 *= fRatioY;
	pOut->_42 *= fRatioY;

}

void CTileTool_Tab3::OnActTileChange()
{
	UpdateData(TRUE);

	m_List_Tile.ResetContent();

	if (m_Combo_Tile.GetCurSel() == (int)TERRIAN_TYPE::ACT1)
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

		Sort_File(TERRIAN_TYPE::ACT1);
	}
	else if (m_Combo_Tile.GetCurSel() == (int)TERRIAN_TYPE::ACT2)
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
				m_List_Tile.AddString(fileName);
			}
		}
		finder.Close();

		Sort_File(TERRIAN_TYPE::ACT2);
	}
	else if (m_Combo_Tile.GetCurSel() == (int)TERRIAN_TYPE::ACT3)
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
				m_List_Tile.AddString(fileName);
			}
		}
		finder.Close();

		Sort_File(TERRIAN_TYPE::ACT3);
	}

	m_iDrawId_First = 0;

	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	m_pMainView->Invalidate(FALSE);
}

void CTileTool_Tab3::OnListTile()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	

	if (m_List_Tile.GetSelCount() > 1) {
		// 선택된 항목들의 인덱스 배열을 저장할 배열 선언
		CArray<int, int> selectedIndices;
		selectedIndices.SetSize(m_List_Tile.GetSelCount());

		// 선택된 항목들의 인덱스 배열을 얻음
		m_List_Tile.GetSelItems(m_List_Tile.GetSelCount(), selectedIndices.GetData());

		// 선택된 항목들의 인덱스 중 첫 번째와 마지막 인덱스를 찾음
		m_iDrawId_First = selectedIndices[0];
		m_iDrawId_Last = selectedIndices[m_List_Tile.GetSelCount() - 1];
	}
	else
	{
		m_iDrawId_First = m_List_Tile.GetCurSel();
		m_iDrawId_Last = 0;
	}
	
	TERRIAN_TYPE e_TerrainTYPE = static_cast<TERRIAN_TYPE>(m_Combo_Tile.GetCurSel());
	switch (e_TerrainTYPE)
	{
	case TERRIAN_TYPE::ACT1:
		m_iTileDamage = m_vecTile_Act1[m_iDrawId_First]->fDamage;
		for (int i = 0; i < 3; ++i)
		{
			m_Check_Tile[i].SetCheck(FALSE);
		}
		if (m_vecTile_Act1[m_iDrawId_First]->byOption == NONETILE)
			m_Check_Tile[0].SetCheck(TRUE);

		if (m_vecTile_Act1[m_iDrawId_First]->byOption & BLOCKTILE)
			m_Check_Tile[1].SetCheck(TRUE);

		if (m_vecTile_Act1[m_iDrawId_First]->byOption & DAMAGETILE)
			m_Check_Tile[2].SetCheck(TRUE);
		break;
	case TERRIAN_TYPE::ACT2:
		m_iTileDamage = m_vecTile_Act2[m_iDrawId_First]->fDamage;
		for (int i = 0; i < 3; ++i)
		{
			m_Check_Tile[i].SetCheck(FALSE);
		}
		if (m_vecTile_Act2[m_iDrawId_First]->byOption == NONETILE)
			m_Check_Tile[0].SetCheck(TRUE);

		if (m_vecTile_Act2[m_iDrawId_First]->byOption & BLOCKTILE)
			m_Check_Tile[1].SetCheck(TRUE);

		if (m_vecTile_Act2[m_iDrawId_First]->byOption & DAMAGETILE)
			m_Check_Tile[2].SetCheck(TRUE);
		break;
	case TERRIAN_TYPE::ACT3:
		m_iTileDamage = m_vecTile_Act3[m_iDrawId_First]->fDamage;
		for (int i = 0; i < 3; ++i)
		{
			m_Check_Tile[i].SetCheck(FALSE);
		}
		if (m_vecTile_Act3[m_iDrawId_First]->byOption == NONETILE)
			m_Check_Tile[0].SetCheck(TRUE);

		if (m_vecTile_Act3[m_iDrawId_First]->byOption & BLOCKTILE)
			m_Check_Tile[1].SetCheck(TRUE);

		if (m_vecTile_Act3[m_iDrawId_First]->byOption & DAMAGETILE)
			m_Check_Tile[2].SetCheck(TRUE);
		break;

	default:
		break;
	}

	UpdateData(FALSE);
	m_pMainView->Invalidate(FALSE);
}

void CTileTool_Tab3::OnSet_TileDamage(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	m_Spin_Tile.SetPos(m_iTileDamage);

	int iValue = pNMUpDown->iPos + pNMUpDown->iDelta;

	if (0 <= iValue && iValue <= 10)
	{
		m_iTileDamage = iValue;
	}

	UpdateData(FALSE);
	*pResult = 0;
}

void CTileTool_Tab3::OnPush_Tile()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_List_Tile.GetSelCount() <= 1)
	{
		TERRIAN_TYPE e_TerrainTYPE = static_cast<TERRIAN_TYPE>(m_Combo_Tile.GetCurSel());
		m_iDrawId_First = m_List_Tile.GetCurSel();
		switch (e_TerrainTYPE)
		{
		case TERRIAN_TYPE::ACT1:
			m_vecTile_Act1[m_iDrawId_First]->fDamage = m_iTileDamage;
			if (m_Check_Tile[0].GetCheck())
				m_vecTile_Act1[m_iDrawId_First]->byOption = NONETILE;
			if (m_Check_Tile[1].GetCheck())
				m_vecTile_Act1[m_iDrawId_First]->byOption |= BLOCKTILE;
			if (m_Check_Tile[2].GetCheck())
				m_vecTile_Act1[m_iDrawId_First]->byOption |= DAMAGETILE;
			break;
		case TERRIAN_TYPE::ACT2:
			m_vecTile_Act2[m_iDrawId_First]->fDamage = m_iTileDamage;
			if (m_Check_Tile[0].GetCheck())
				m_vecTile_Act1[m_iDrawId_First]->byOption = NONETILE;
			if (m_Check_Tile[1].GetCheck())
				m_vecTile_Act2[m_iDrawId_First]->byOption |= BLOCKTILE;
			if (m_Check_Tile[2].GetCheck())
				m_vecTile_Act2[m_iDrawId_First]->byOption |= DAMAGETILE;
			break;
		case TERRIAN_TYPE::ACT3:
			m_vecTile_Act3[m_iDrawId_First]->fDamage = m_iTileDamage;
			if (m_Check_Tile[0].GetCheck())
				m_vecTile_Act1[m_iDrawId_First]->byOption = NONETILE;
			if (m_Check_Tile[1].GetCheck())
				m_vecTile_Act3[m_iDrawId_First]->byOption |= BLOCKTILE;
			if (m_Check_Tile[2].GetCheck())
				m_vecTile_Act3[m_iDrawId_First]->byOption |= DAMAGETILE;
			break;

		default:
			break;
		}
	}
	
	else
	{
		if (m_List_Tile.GetSelCount() > 1) {
			// 선택된 항목들의 인덱스 배열을 저장할 배열 선언
			CArray<int, int> selectedIndices;
			selectedIndices.SetSize(m_List_Tile.GetSelCount());

			// 선택된 항목들의 인덱스 배열을 얻음
			m_List_Tile.GetSelItems(m_List_Tile.GetSelCount(), selectedIndices.GetData());

			// 선택된 항목들의 인덱스 중 첫 번째와 마지막 인덱스를 찾음
			m_iDrawId_First = selectedIndices[0];
			m_iDrawId_Last = selectedIndices[m_List_Tile.GetSelCount() - 1];
		}

		TERRIAN_TYPE e_TerrainTYPE = static_cast<TERRIAN_TYPE>(m_Combo_Tile.GetCurSel());

		switch (e_TerrainTYPE)
		{
		case TERRIAN_TYPE::ACT1:
			for (int i = m_iDrawId_First; i <= m_iDrawId_Last; ++i)
			{
				m_vecTile_Act1[i]->fDamage = m_iTileDamage;
				if (m_Check_Tile[0].GetCheck())
					m_vecTile_Act1[i]->byOption = NONETILE;
				if (m_Check_Tile[1].GetCheck())
					m_vecTile_Act1[i]->byOption |= BLOCKTILE;
				if (m_Check_Tile[2].GetCheck())
					m_vecTile_Act1[i]->byOption |= DAMAGETILE;
			}
			break;
		case TERRIAN_TYPE::ACT2:
			for (int i = m_iDrawId_First; i <= m_iDrawId_Last; ++i)
			{
				m_vecTile_Act2[i]->fDamage = m_iTileDamage;
				if (m_Check_Tile[0].GetCheck())
					m_vecTile_Act2[i]->byOption = NONETILE;
				if (m_Check_Tile[1].GetCheck())
					m_vecTile_Act2[i]->byOption |= BLOCKTILE;
				if (m_Check_Tile[2].GetCheck())
					m_vecTile_Act2[i]->byOption |= DAMAGETILE;
			}
			break;
		case TERRIAN_TYPE::ACT3:
			for (int i = m_iDrawId_First; i <= m_iDrawId_Last; ++i)
			{
				m_vecTile_Act3[i]->fDamage = m_iTileDamage;
				if (m_Check_Tile[0].GetCheck())
					m_vecTile_Act3[i]->byOption = NONETILE;
				if (m_Check_Tile[1].GetCheck())
					m_vecTile_Act3[i]->byOption |= BLOCKTILE;
				if (m_Check_Tile[2].GetCheck())
					m_vecTile_Act3[i]->byOption |= DAMAGETILE;
			}
			break;
		default:
			break;
		}
	}

	// 첫 번째 선택지와 마지막 선택지의 인덱스를 얻기 위한 변수 선언

	UpdateData(FALSE);
}

void CTileTool_Tab3::OnClear_Tile()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	TERRIAN_TYPE eTerrainType = static_cast<TERRIAN_TYPE>(m_Combo_Tile.GetCurSel());

	switch (eTerrainType)
	{
	case TERRIAN_TYPE::ACT1:
		for (auto& iter : m_vecTile_Act1)
		{
			iter->vSize = { 1.f, 1.f , 1.f };
			iter->byOption = NONETILE;
			iter->fDamage = 0;
		}
		break;
	case TERRIAN_TYPE::ACT2:
		for (auto& iter : m_vecTile_Act2)
		{
			iter->vSize = { 1.f, 1.f , 1.f };
			iter->byOption = NONETILE;
			iter->fDamage = 0;
		}
		break;
	case TERRIAN_TYPE::ACT3:
		for (auto& iter : m_vecTile_Act3)
		{
			iter->vSize = { 1.f, 1.f , 1.f };
			iter->byOption = NONETILE;
			iter->fDamage = 0;
		}
		break;
	default:
		break;
	}

	for (int i = 0; i < 3; ++i)
	{
		m_Check_Tile[i].SetCheck(FALSE);
	}
	m_Check_Tile[0].SetCheck(TRUE);
	m_iTileDamage = 0;
	
	UpdateData(FALSE);
}

void CTileTool_Tab3::OnSaveDB_Tile()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	TERRIAN_TYPE e_TerrainTYPE = static_cast<TERRIAN_TYPE>(m_Combo_Tile.GetCurSel());

	switch (e_TerrainTYPE)
	{
		case TERRIAN_TYPE::ACT1:
		{
			CFileDialog		Dlg(FALSE,	// TRUE(열기), FALSE(다른 이름으로 저장) 모드 지정	
				L"dat", // defaule 파일 확장자명
				L"Save_Act1Tile.dat", // 대화 상자에 표시될 최초 파일명
				OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(읽기전용 체크박스 숨김), OFN_OVERWRITEPROMPT(중복파일 저장 시 경고메세지 띄우기)
				L"Data Files(*.dat) | *.dat||",  // 대화 상자에 표시될 파일 형식 '콤보 박스에 출력될 문자열 | 실제 사용할 필터링 문자열 ||'
				this); // 부모 윈도우 주소
	
			TCHAR	szPath[MAX_PATH] = L"";
	
			GetCurrentDirectory(MAX_PATH, szPath);
			PathRemoveFileSpec(szPath);
			lstrcat(szPath, L"\\Data");
			Dlg.m_ofn.lpstrInitialDir = szPath;
	
			if (IDOK == Dlg.DoModal())
			{
				CString		strTemp = Dlg.GetPathName().GetString();
				const TCHAR* pGetPath = strTemp.GetString();
	
				HANDLE hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	
				if (INVALID_HANDLE_VALUE == hFile)
					return;
	
				DWORD	dwByte = 0;
	
				for (auto& iter : m_vecTile_Act1)
					WriteFile(hFile, iter, sizeof(TILE), &dwByte, nullptr);
	
				CloseHandle(hFile);
			}
		}
			break;
		case TERRIAN_TYPE::ACT2:
		{
			CFileDialog		Dlg(FALSE,	// TRUE(열기), FALSE(다른 이름으로 저장) 모드 지정	
				L"dat", // defaule 파일 확장자명
				L"Save_Act2Tile.dat", // 대화 상자에 표시될 최초 파일명
				OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(읽기전용 체크박스 숨김), OFN_OVERWRITEPROMPT(중복파일 저장 시 경고메세지 띄우기)
				L"Data Files(*.dat) | *.dat||",  // 대화 상자에 표시될 파일 형식 '콤보 박스에 출력될 문자열 | 실제 사용할 필터링 문자열 ||'
				this); // 부모 윈도우 주소
	
			TCHAR	szPath[MAX_PATH] = L"";
	
			GetCurrentDirectory(MAX_PATH, szPath);
			PathRemoveFileSpec(szPath);
			lstrcat(szPath, L"\\Data");
			Dlg.m_ofn.lpstrInitialDir = szPath;
	
			if (IDOK == Dlg.DoModal())
			{
				CString		strTemp = Dlg.GetPathName().GetString();
				const TCHAR* pGetPath = strTemp.GetString();
	
				HANDLE hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	
				if (INVALID_HANDLE_VALUE == hFile)
					return;
	
				DWORD	dwByte = 0;
	
				for (auto& iter : m_vecTile_Act2)
					WriteFile(hFile, iter, sizeof(TILE), &dwByte, nullptr);
	
				CloseHandle(hFile);
			}
		}
			break;
		case TERRIAN_TYPE::ACT3:
		{
			CFileDialog		Dlg(FALSE,	// TRUE(열기), FALSE(다른 이름으로 저장) 모드 지정	
				L"dat", // defaule 파일 확장자명
				L"Save_Act3Tile.dat", // 대화 상자에 표시될 최초 파일명
				OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(읽기전용 체크박스 숨김), OFN_OVERWRITEPROMPT(중복파일 저장 시 경고메세지 띄우기)
				L"Data Files(*.dat) | *.dat||",  // 대화 상자에 표시될 파일 형식 '콤보 박스에 출력될 문자열 | 실제 사용할 필터링 문자열 ||'
				this); // 부모 윈도우 주소
	
			TCHAR	szPath[MAX_PATH] = L"";
	
			GetCurrentDirectory(MAX_PATH, szPath);
			PathRemoveFileSpec(szPath);
			lstrcat(szPath, L"\\Data");
			Dlg.m_ofn.lpstrInitialDir = szPath;
	
			if (IDOK == Dlg.DoModal())
			{
				CString		strTemp = Dlg.GetPathName().GetString();
				const TCHAR* pGetPath = strTemp.GetString();
	
				HANDLE hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	
				if (INVALID_HANDLE_VALUE == hFile)
					return;
	
				DWORD	dwByte = 0;
	
				for (auto& iter : m_vecTile_Act3)
					WriteFile(hFile, iter, sizeof(TILE), &dwByte, nullptr);
	
				CloseHandle(hFile);
			}
		}
			break;
	
	}

	UpdateData(FALSE);
}

void CTileTool_Tab3::OnLoadDB_Tile()
{
	UpdateData(TRUE);

	TERRIAN_TYPE e_TerrainTYPE = static_cast<TERRIAN_TYPE>(m_Combo_Tile.GetCurSel());
	switch (e_TerrainTYPE)
	{
	case TERRIAN_TYPE::ACT1:
		if (!m_vecTile_Act1.empty())
		{
			for_each(m_vecTile_Act1.begin(), m_vecTile_Act1.end(), CDeleteObj());
			m_vecTile_Act1.clear();
			m_vecTile_Act1.shrink_to_fit();
		}
		{
			CFileDialog		Dlg(TRUE,
				L"dat",
				L"Save_Act1Tile.dat",
				OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
				L"Data Files(*.dat) | *.dat||",
				this);

			TCHAR	szPath[MAX_PATH] = L"";

			GetCurrentDirectory(MAX_PATH, szPath);

			PathRemoveFileSpec(szPath);

			lstrcat(szPath, L"\\Data");
			Dlg.m_ofn.lpstrInitialDir = szPath;

			if (IDOK == Dlg.DoModal())
			{
				CString		strTemp = Dlg.GetPathName().GetString();
				const TCHAR* pGetPath = strTemp.GetString();

				HANDLE hFile = CreateFile(pGetPath, GENERIC_READ,
					0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

				if (INVALID_HANDLE_VALUE == hFile)
					return;

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

					m_vecTile_Act1.push_back(pTile);
				}

				CloseHandle(hFile);
			}
		}
		{
			m_iTileDamage = m_vecTile_Act1[m_iDrawId_First]->fDamage;
			for (int i = 0; i < 3; ++i)
			{
				m_Check_Tile[i].SetCheck(FALSE);
			}
			if (m_vecTile_Act1[m_iDrawId_First]->byOption == NONETILE)
				m_Check_Tile[0].SetCheck(TRUE);

			if (m_vecTile_Act1[m_iDrawId_First]->byOption & BLOCKTILE)
				m_Check_Tile[1].SetCheck(TRUE);

			if (m_vecTile_Act1[m_iDrawId_First]->byOption & DAMAGETILE)
				m_Check_Tile[2].SetCheck(TRUE);
		}
	break;
	case TERRIAN_TYPE::ACT2:
		if (!m_vecTile_Act2.empty())
		{
			for_each(m_vecTile_Act2.begin(), m_vecTile_Act2.end(), CDeleteObj());
			m_vecTile_Act2.clear();
			m_vecTile_Act2.shrink_to_fit();
		}
		{
			CFileDialog		Dlg(TRUE,
				L"dat",
				L"Save_Act2Tile.dat",
				OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
				L"Data Files(*.dat) | *.dat||",
				this);

			TCHAR	szPath[MAX_PATH] = L"";

			GetCurrentDirectory(MAX_PATH, szPath);

			PathRemoveFileSpec(szPath);

			lstrcat(szPath, L"\\Data");
			Dlg.m_ofn.lpstrInitialDir = szPath;

			if (IDOK == Dlg.DoModal())
			{
				CString		strTemp = Dlg.GetPathName().GetString();
				const TCHAR* pGetPath = strTemp.GetString();

				HANDLE hFile = CreateFile(pGetPath, GENERIC_READ,
					0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

				if (INVALID_HANDLE_VALUE == hFile)
					return;

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

					m_vecTile_Act3.push_back(pTile);
				}

				CloseHandle(hFile);
			}
		}
		{
			m_iTileDamage = m_vecTile_Act2[m_iDrawId_First]->fDamage;
			for (int i = 0; i < 3; ++i)
			{
				m_Check_Tile[i].SetCheck(FALSE);
			}
			if (m_vecTile_Act2[m_iDrawId_First]->byOption == NONETILE)
				m_Check_Tile[0].SetCheck(TRUE);

			if (m_vecTile_Act2[m_iDrawId_First]->byOption & BLOCKTILE)
				m_Check_Tile[1].SetCheck(TRUE);

			if (m_vecTile_Act2[m_iDrawId_First]->byOption & DAMAGETILE)
				m_Check_Tile[2].SetCheck(TRUE);
		}
		break;
	case TERRIAN_TYPE::ACT3:
		if (!m_vecTile_Act3.empty())
		{
			for_each(m_vecTile_Act3.begin(), m_vecTile_Act3.end(), CDeleteObj());
			m_vecTile_Act3.clear();
			m_vecTile_Act3.shrink_to_fit();
		}
		{
			CFileDialog		Dlg(TRUE,
				L"dat",
				L"Save_Act3Tile.dat",
				OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
				L"Data Files(*.dat) | *.dat||",
				this);

			TCHAR	szPath[MAX_PATH] = L"";

			GetCurrentDirectory(MAX_PATH, szPath);

			PathRemoveFileSpec(szPath);

			lstrcat(szPath, L"\\Data");
			Dlg.m_ofn.lpstrInitialDir = szPath;

			if (IDOK == Dlg.DoModal())
			{
				CString		strTemp = Dlg.GetPathName().GetString();
				const TCHAR* pGetPath = strTemp.GetString();

				HANDLE hFile = CreateFile(pGetPath, GENERIC_READ,
					0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

				if (INVALID_HANDLE_VALUE == hFile)
					return;

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

					m_vecTile_Act3.push_back(pTile);
				}

				CloseHandle(hFile);
			}
		}
		{
			m_iTileDamage = m_vecTile_Act3[m_iDrawId_First]->fDamage;
			for (int i = 0; i < 3; ++i)
			{
				m_Check_Tile[i].SetCheck(FALSE);
			}
			if (m_vecTile_Act3[m_iDrawId_First]->byOption == NONETILE)
				m_Check_Tile[0].SetCheck(TRUE);

			if (m_vecTile_Act3[m_iDrawId_First]->byOption & BLOCKTILE)
				m_Check_Tile[1].SetCheck(TRUE);

			if (m_vecTile_Act3[m_iDrawId_First]->byOption & DAMAGETILE)
				m_Check_Tile[2].SetCheck(TRUE);
		}
		break;
	default:
		break;
	}

	
	UpdateData(FALSE);
}

void CTileTool_Tab3::Sort_File(TERRIAN_TYPE _eTerrainType)
{
	UpdateData(TRUE);

	RECT	rc{};
	m_pMainView->GetClientRect(&rc);
	float CX = float(rc.right - rc.left);
	float CY = float(rc.bottom - rc.top);

	switch (_eTerrainType)
	{
	case TERRIAN_TYPE::ACT1:
		if (m_vecTile_Act1.empty())
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
			int iDrawIdCount = 0;

			for (const CString& fileName : fileList)
			{
				m_List_Tile.AddString(fileName);

				TILE*	pTile = new TILE;

				pTile->vPos = { 0.f, 0.f, 0.f };
				pTile->vSize = { 1.f, 1.f , 1.f };
				pTile->byOption = NONETILE;
				pTile->fDamage = 0;
				pTile->byDrawID = iDrawIdCount;
				iDrawIdCount++;

				m_vecTile_Act1.push_back(pTile);
			}
		}
		else
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
		break;
	case TERRIAN_TYPE::ACT2:
		if (m_vecTile_Act2.empty())
		{
			vector<CString> fileList;
			for (int i = 0; i < m_List_Tile.GetCount(); i++)
			{
				CString fileName;
				m_List_Tile.GetText(i, fileName);
				fileList.push_back(fileName);
			}

			sort(fileList.begin(), fileList.end(), [](const CString& str1, const CString& str2) {
				CString numStr1 = str1.Mid(4, str1.GetLength() - (4 * sizeof(TCHAR)));
				int num1 = _wtoi(numStr1);

				CString numStr2 = str2.Mid(4, str2.GetLength() - (4 * sizeof(TCHAR)));
				int num2 = _wtoi(numStr2);

				return num1 < num2;
			});

			m_List_Tile.ResetContent();
			int iDrawIdCount = 0;

			for (const CString& fileName : fileList)
			{
				m_List_Tile.AddString(fileName);

				TILE*	pTile = new TILE;

				pTile->vPos = { 0.f, 0.f, 0.f };
				pTile->vSize = { 1.f, 1.f , 1.f };
				pTile->byOption = NONETILE;
				pTile->fDamage = 0;
				pTile->byDrawID = iDrawIdCount;
				iDrawIdCount++;

				m_vecTile_Act2.push_back(pTile);
			}
		}
		else
		{
			vector<CString> fileList;
			for (int i = 0; i < m_List_Tile.GetCount(); i++)
			{
				CString fileName;
				m_List_Tile.GetText(i, fileName);
				fileList.push_back(fileName);
			}

			sort(fileList.begin(), fileList.end(), [](const CString& str1, const CString& str2) {
				CString numStr1 = str1.Mid(4, str1.GetLength() - (4 * sizeof(TCHAR)));
				int num1 = _wtoi(numStr1);

				CString numStr2 = str2.Mid(4, str2.GetLength() - (4 * sizeof(TCHAR)));
				int num2 = _wtoi(numStr2);

				return num1 < num2;
			});

			m_List_Tile.ResetContent();
			for (const CString& fileName : fileList)
			{
				m_List_Tile.AddString(fileName);
			}
		}
		break;
	case TERRIAN_TYPE::ACT3:
		if (m_vecTile_Act3.empty())
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
			int iDrawIdCount = 0;

			for (const CString& fileName : fileList)
			{
				m_List_Tile.AddString(fileName);

				TILE*	pTile = new TILE;

				pTile->vPos = { 0.f, 0.f, 0.f };
				pTile->vSize = { 1.f, 1.f , 1.f };
				pTile->byOption = NONETILE;
				pTile->fDamage = 0;
				pTile->byDrawID = iDrawIdCount;
				iDrawIdCount++;

				m_vecTile_Act3.push_back(pTile);
			}
		}
		else
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
		break;
	default:
		break;
	}

	UpdateData(FALSE);
}














