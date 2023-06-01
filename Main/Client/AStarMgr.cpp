#include "stdafx.h"
#include "AStarMgr.h"
#include "ObjMgr.h"
#include "MyTerrain.h"

IMPLEMENT_SINGLETON(CAStarMgr)

CAStarMgr::CAStarMgr()
{
}


CAStarMgr::~CAStarMgr()
{
	Release();
}

void CAStarMgr::Start_AStar(const VECTOR & vStart, const VECTOR & vGaol)
{
	Release();

	m_pTerrian = CObjMgr::Get_Instance()->Get_Terrain();
	m_vecTile = static_cast<CMyTerrain*>(m_pTerrian)->Get_VecTile();
	m_vecAdj = static_cast<CMyTerrain*>(m_pTerrian)->Get_VecAdj();

	if (m_vecTile.empty())
		return;

	m_iStartIdx = Get_TileIndex(vStart);

	int iGoalIdx = Get_TileIndex(vGaol);

	if (0 > m_iStartIdx || 0 > iGoalIdx || (UINT)m_iStartIdx >= m_vecTile.size())
		return;

	if (m_iStartIdx == iGoalIdx)
		return;

	if (NONETILE == m_vecTile[iGoalIdx]->byOption)
		return;

	if (Make_Route(m_iStartIdx, iGoalIdx))
		Make_BestRoute(m_iStartIdx, iGoalIdx);
}

bool CAStarMgr::Make_Route(int iStartIdx, int iGoalIdx)
{
	if (m_vecTile.empty() || m_vecAdj.empty())
		return false;

	if (!m_OpenList.empty())
		m_OpenList.pop_front();

	m_CloseList.push_back(iStartIdx);

	for (auto& iter : m_vecAdj[iStartIdx])
	{




	}


}

void CAStarMgr::Make_BestRoute(int iStartIdx, int iGoalIdx)
{
}

bool CAStarMgr::Picking_Dot(const D3DXVECTOR3 & vPos, const int & iIndex)
{
	if (m_vecTile.empty())
		return false;

	D3DXVECTOR3		vPoint[4]{

		{ m_vecTile[iIndex]->vPos.x,m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x + (TILECX / 2.f),m_vecTile[iIndex]->vPos.y, 0.f },
		{ m_vecTile[iIndex]->vPos.x,m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x - (TILECX / 2.f),m_vecTile[iIndex]->vPos.y , 0.f }
	};

	D3DXVECTOR3			vDir[4]{

		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3],
	};

	D3DXVECTOR3			vNormal[4]{
		{ -vDir[0].y, vDir[0].x, 0.f },
		{ -vDir[1].y, vDir[1].x, 0.f },
		{ -vDir[2].y, vDir[2].x, 0.f },
		{ -vDir[3].y, vDir[3].x, 0.f },
	};

	D3DXVECTOR3			vMouseDir[4]{

		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);
	}

	for (int i = 0; i < 4; ++i)
	{
		if (0.f < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;
	}

	return true;
}

int CAStarMgr::Get_TileIndex(const D3DXVECTOR3 & vPos)
{
	if (m_vecTile.empty())
		return -1;

	for (size_t index = 0; index < m_vecTile.size(); ++index)
	{
		if (Picking_Dot(vPos, index))
		{
			return index;
		}
	}

	return -1;
}

void CAStarMgr::Release()
{
	m_CloseList.clear();
	m_OpenList.clear();
	m_BestList.clear();
}

bool CAStarMgr::Check_Close(int iIndex)
{
	for (int& iCloseIdx : m_CloseList)
	{
		if (iIndex == iCloseIdx)
			return true;
	}

	return false;
}

bool CAStarMgr::Check_Open(int iIndex)
{
	for (int& iOpenIdx : m_OpenList)
	{
		if (iIndex == iOpenIdx)
			return true;
	}



	return false;
}
