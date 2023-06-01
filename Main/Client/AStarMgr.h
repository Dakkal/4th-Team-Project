#pragma once

#include "Include.h"

class CObj;
class CAStarMgr
{
	DECLARE_SINGLETON(CAStarMgr)

public:
	CAStarMgr();
	~CAStarMgr();

public:
	list<TILE*>&	Get_BestList() { return m_BestList; }

public:
	void	Start_AStar(const VECTOR& vStart, const VECTOR& vGaol);

	bool	Make_Route(int iStartIdx, int iGoalIdx);
	void	Make_BestRoute(int iStartIdx, int iGoalIdx);

public:
	bool		Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex);
	int			Get_TileIndex(const D3DXVECTOR3& vPos);
	void		Release();

private:
	bool		Check_Close(int iIndex);
	bool		Check_Open(int iIndex);

private:
	list<int>		m_OpenList;
	list<int>		m_CloseList;
	list<TILE*>		m_BestList;

	int				m_iStartIdx = 0;

	CObj*					m_pTerrian = nullptr;
	vector<TILE*>			m_vecTile;
	vector<list<TILE*>>		m_vecAdj;

};

