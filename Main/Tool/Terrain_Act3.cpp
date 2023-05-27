#include "stdafx.h"
#include "Terrain_Act3.h"
#include "TextureMgr.h"
#include "Device.h"
#include "ToolView.h"

CTerrain_Act3::CTerrain_Act3()
{
}


CTerrain_Act3::~CTerrain_Act3()
{
	Release();
}

HRESULT CTerrain_Act3::Initialize()
{
	m_eType = OBJ_TYPE::TERRAIN;

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/00.Tile/Act3/Tile_%d.png", TEX_MULTI, L"Terrain", L"Act3Tile", 288)))
	{
		AfxMessageBox(L"TileTexture Create Failed");
		return E_FAIL;
	}

	return S_OK;
}

int CTerrain_Act3::Update()
{
	return 0;
}

void CTerrain_Act3::Late_Update()
{
}

void CTerrain_Act3::Render()
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	TCHAR		szBuf[MIN_STR] = L"";
	int			iIndex = 0;

	RECT	rc{};

	// GetClientRect : ���� Ŭ���̾�Ʈ ������ rect ������ ����
	GetClientRect(m_pMainView->m_hWnd, &rc);

	float	fX = WINCX / float(rc.right - rc.left);
	float	fY = WINCY / float(rc.bottom - rc.top);


	for (auto iter : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			iter->vPos.x - m_pMainView->GetScrollPos(0), // 0�� ��� x ��ũ�� �� ����
			iter->vPos.y - m_pMainView->GetScrollPos(1), // 1�� ��� y ��ũ�� �� ����
			0.f);

		matWorld = matScale * matTrans;

		Set_Ratio(&matWorld, fX, fY);

		const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Act3Tile", iter->byDrawID);

		float	fX = pTexInfo->tImgInfo.Width / 2.f;
		float	fY = pTexInfo->tImgInfo.Height / 2.f;

		// �̹����� ����� �ݿ�
		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,							// ����� �̹��� ������ ���� Rect �ּ�, null�� ��� �̹����� 0, 0 �������� ���
			&D3DXVECTOR3(fX, fY, 0.f),			// ����� �̹����� �߽��࿡ ���� vector3 �ּ�, null�� ��� �̹����� 0, 0�� �߽� ��ǥ
			nullptr,							// ��ġ ��ǥ�� ���� vector3 �ּ�, null�� ��� ��ũ�� ���� 0, 0��ǥ ���
			D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� �̹����� ���� ���� ��, 0xffffffff�� �Ѱ��ָ� ���� ���� ����


		/*swprintf_s(szBuf, L"%d", iIndex);

		CDevice::Get_Instance()->Get_Font()->DrawTextW(CDevice::Get_Instance()->Get_Sprite(),
			szBuf,
			lstrlen(szBuf),
			nullptr,
			DT_CENTER,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		++iIndex;*/
	}
}

void CTerrain_Act3::Release()
{
}

void CTerrain_Act3::Set_Ratio(D3DXMATRIX * pOut, float fRatioX, float fRatioY)
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
