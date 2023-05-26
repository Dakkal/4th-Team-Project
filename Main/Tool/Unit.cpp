#include "stdafx.h"
#include "Unit.h"
#include "TextureMgr.h"
#include "SingleTexture.h"
#include "MultiTexture.h"
#include "Device.h"
	
CUnit::CUnit()
{
}


CUnit::~CUnit()
{
}

HRESULT CUnit::Initialize()
{

	m_tInfo.vPos = { 0.f, 0.f, 0.f };
	m_tInfo.vRot = { 0.f, 0.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 1.f };


	return E_NOTIMPL;
}

int CUnit::Update()
{
	return 0;
}

void CUnit::Late_Update()
{
}

void CUnit::Render()
{
}

void CUnit::Release()
{
}

void CUnit::Tool_Render(const D3DXVECTOR3& _vWorld)
{
	D3DXMATRIX matScale, matRotZ, matTrans;

	D3DXVECTOR3 vPos = m_tInfo.vPos + _vWorld; // 

	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, m_tInfo.vSize.z);
	D3DXMatrixRotationZ(&matRotZ, m_tInfo.vRot.z);
	D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;


	const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Player", L"Stand", 0);

	if (nullptr == pTexInfo) return;

	float	fX = pTexInfo->tImgInfo.Width / 2.f;
	float	fY = pTexInfo->tImgInfo.Height / 2.f;

	// 이미지에 행렬을 반영
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,							// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0 기준으로 출력
		&D3DXVECTOR3(fX, fY, 0.f),			// 출력할 이미지의 중심축에 대한 vector3 주소, null인 경우 이미지의 0, 0이 중심 좌표
		nullptr,							// 위치 좌표에 대한 vector3 주소, null인 경우 스크린 상의 0, 0좌표 출력
		D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 원본 색상 유지
}
