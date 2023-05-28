#include "stdafx.h"
#include "Terrain_Act1.h"
#include "TextureMgr.h"
#include "Device.h"
#include "ToolView.h"

CTerrain_Act1::CTerrain_Act1()
{
}


CTerrain_Act1::~CTerrain_Act1()
{
	Release();
}

HRESULT CTerrain_Act1::Initialize()
{
	m_eType = OBJ_TYPE::TERRAIN;

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/00.Tile/Act1/Tile_%d.png", TEX_MULTI, L"Terrain", L"Act1Tile", 325)))
	{
		AfxMessageBox(L"TileTexture Create Failed");
		return E_FAIL;
	}

	
	for (int i = 0; i < 325; ++i)
	{
		TILE* pTile = new TILE;

		pTile->vSize = { TILECX, TILECY, 0.f };
		pTile->byOption = NONETILE;
		pTile->byDrawID = i;

		m_vecTile.push_back(pTile);
	}
	
	return S_OK;
}

int CTerrain_Act1::Update()
{
	return 0;
}

void CTerrain_Act1::Late_Update()
{
}

void CTerrain_Act1::Render()
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	TCHAR		szBuf[MIN_STR] = L"";
	int			iIndex = 0;

	RECT	rc{};

	// GetClientRect : 현재 클라이언트 영역의 rect 정보를 얻어옴
	GetClientRect(m_pMainView->m_hWnd, &rc);

	float	fX = WINCX / float(rc.right - rc.left);
	float	fY = WINCY / float(rc.bottom - rc.top);


	for (auto iter : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			iter->vPos.x - m_pMainView->GetScrollPos(0), // 0일 경우 x 스크롤 값 얻어옴
			iter->vPos.y - m_pMainView->GetScrollPos(1), // 1일 경우 y 스크롤 값 얻어옴
			0.f);

		matWorld = matScale * matTrans;

		Set_Ratio(&matWorld, fX, fY);

		const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Act1Tile", iter->byDrawID);

		float	fX = pTexInfo->tImgInfo.Width / 2.f;
		float	fY = pTexInfo->tImgInfo.Height / 2.f;

		// 이미지에 행렬을 반영
		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,							// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0 기준으로 출력
			&D3DXVECTOR3(fX, fY, 0.f),			// 출력할 이미지의 중심축에 대한 vector3 주소, null인 경우 이미지의 0, 0이 중심 좌표
			nullptr,							// 위치 좌표에 대한 vector3 주소, null인 경우 스크린 상의 0, 0좌표 출력
			D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 원본 색상 유지


	/*	swprintf_s(szBuf, L"%d", iIndex);

		CDevice::Get_Instance()->Get_Font()->DrawTextW(CDevice::Get_Instance()->Get_Sprite(),
			szBuf,
			lstrlen(szBuf),
			nullptr,
			DT_CENTER,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		++iIndex;*/
	}
}

void CTerrain_Act1::Release()
{
}


void CTerrain_Act1::Set_Ratio(D3DXMATRIX * pOut, float fRatioX, float fRatioY)
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
