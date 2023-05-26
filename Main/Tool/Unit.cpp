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

	// �̹����� ����� �ݿ�
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,							// ����� �̹��� ������ ���� Rect �ּ�, null�� ��� �̹����� 0, 0 �������� ���
		&D3DXVECTOR3(fX, fY, 0.f),			// ����� �̹����� �߽��࿡ ���� vector3 �ּ�, null�� ��� �̹����� 0, 0�� �߽� ��ǥ
		nullptr,							// ��ġ ��ǥ�� ���� vector3 �ּ�, null�� ��� ��ũ�� ���� 0, 0��ǥ ���
		D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� �̹����� ���� ���� ��, 0xffffffff�� �Ѱ��ָ� ���� ���� ����
}
