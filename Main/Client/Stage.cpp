#include "stdafx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "MyTerrain.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{

	CObj*	pTerrian = new CMyTerrain;

	if (nullptr == pTerrian)
		return E_FAIL;

	static_cast<CMyTerrain*>(pTerrian)->Set_Act(TERRIAN_TYPE::ACT1);
	
	CObjMgr::Get_Instance()->Add_Object(CObjMgr::TERRAIN, pTerrian);
	
	return S_OK;
}

void CStage::Update_Scene()
{
	CObjMgr::Get_Instance()->Update();
}

void CStage::Late_Update_Scene()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render_Scene()
{
	CObjMgr::Get_Instance()->Render();
}

void CStage::Release_Scene()
{
	//CObjMgr::Get_Instance()->Release();
}
