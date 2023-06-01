#include "stdafx.h"
#include "MyTerrain.h"
#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"


CMyTerrain::CMyTerrain()
{
}

CMyTerrain::~CMyTerrain()
{
	Release();
}

HRESULT CMyTerrain::Initialize(void)
{
	return S_OK;
}

HRESULT CMyTerrain::Set_Act(TERRIAN_TYPE _eType)
{
	switch (_eType)
	{
	case TERRIAN_TYPE::ACT1:
	{
		if (FAILED(LoadTile(L"../Data/Map_Scene1.dat")))
			return E_FAIL;

		m_wstrObjKey = L"Tile";
		m_wstrStateKey = L"Act1";
	}
	break;
	case TERRIAN_TYPE::ACT2:
	{
		if (FAILED(LoadTile(L"../Data/Map_Scene1.dat")))
			return E_FAIL;

		m_wstrObjKey = L"Tile";
		m_wstrStateKey = L"Act2";
	}
	break;
	case TERRIAN_TYPE::ACT3:
	{
		if (FAILED(LoadTile(L"../Data/Map_Scene1.dat")))
			return E_FAIL;

		m_wstrObjKey = L"Tile";
		m_wstrStateKey = L"Act3";
	}
	break;
	default:
		break;
	}

	return S_OK;
}

int CMyTerrain::Update(void)
{
	Move_Frame();

	if (0.f >= __super::m_vScroll.x)
	{
		if (10.f > ::Get_Mouse().x)
			__super::m_vScroll.x += SCROLL_SPEED * CTimeMgr::Get_Instance()->Get_TimeDelta();

		if (WINCX - 10 < ::Get_Mouse().x)
			__super::m_vScroll.x -= SCROLL_SPEED * CTimeMgr::Get_Instance()->Get_TimeDelta();

		if (0.f < __super::m_vScroll.x)
			__super::m_vScroll.x = 0.f;
	}

	if (0.f >= __super::m_vScroll.y)
	{
		if (10.f > ::Get_Mouse().y)
			__super::m_vScroll.y += SCROLL_SPEED * CTimeMgr::Get_Instance()->Get_TimeDelta();

		if (WINCY - 10 < ::Get_Mouse().y)
			__super::m_vScroll.y -= SCROLL_SPEED * CTimeMgr::Get_Instance()->Get_TimeDelta();

		if (0.f < __super::m_vScroll.y)
			__super::m_vScroll.y = 0.f;
	}

	return 0;
}

void CMyTerrain::Late_Update(void)
{
}

void CMyTerrain::Render(void)
{
	D3DXMATRIX		matWorld,matTrans;

	int iScrollX = (int)__super::m_vScroll.x;


	int		iCullX = int(-m_vScroll.x) / TILECX;
	int		iCullY = int(-m_vScroll.y) / (TILECY / 2);

	int		iCullEndX = WINCX / (TILECX) + 3;
	int		iCullEndY = WINCY / (TILECY / 2) + 3;

	for (int i = iCullY; i < iCullY + iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullX + iCullEndX; ++j)
		{
			int		iIndex = i * m_iRow + j;

			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
				continue;

			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixTranslation(&matTrans,
				m_vecTile[iIndex]->vPos.x + m_vScroll.x,
				m_vecTile[iIndex]->vPos.y + m_vScroll.y,
				m_vecTile[iIndex]->vPos.z);

			matWorld = matTrans;

			if (m_vecTile[iIndex]->eType == TERRIAN_TYPE::TYPEEND)
				continue;

			switch (m_vecTile[iIndex]->eType)
			{
			case TERRIAN_TYPE::ACT1:
				m_wstrStateKey = L"Act1";
				break;
			case TERRIAN_TYPE::ACT2:
				m_wstrStateKey = L"Act2";
				break;
			case TERRIAN_TYPE::ACT3:
				m_wstrStateKey = L"Act3";
				break;
			default:
				break;
			}


			const TEXINFO*		pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), m_vecTile[iIndex]->byDrawID);
			if (nullptr == pTexInfo)
				return;
			

			float		fX = pTexInfo->tImgInfo.Width / 2.f;
			float		fY = pTexInfo->tImgInfo.Height / 2.f;

			CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

			CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
				nullptr,
				&D3DXVECTOR3(fX, fY, 0.f),
				nullptr,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CMyTerrain::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

HRESULT CMyTerrain::LoadTile(const TCHAR* pTilePath)
{
	HANDLE	hFile = CreateFile(pTilePath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	TILE*	pTile = nullptr;

	int		iCount = 0;
	UINT	iRow = 0;
	UINT	iCol = 0;
	DWORD	dwByte = 0;

	while (true)
	{
		if (iCount == 0)
		{
			ReadFile(hFile, &iRow, sizeof(UINT), &dwByte, nullptr);
		}
		else if (iCount == 1)
		{
			ReadFile(hFile, &iCol, sizeof(UINT), &dwByte, nullptr);
		}
		else if (iCount >= 2)
		{
			TILE* pTile = new TILE;

			ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

			/*if (pTile->eType == TERRIAN_TYPE::TYPEEND)
			{
				Safe_Delete(pTile);
				continue;
			}	*/
			if (0 == dwByte)
			{
				Safe_Delete(pTile);
				break;
			}

			m_vecTile.push_back(pTile);
		}

		++iCount;
	}

	m_iRow = iRow;
	m_iCol = iCol;

	CloseHandle(hFile);

	return S_OK;
}


