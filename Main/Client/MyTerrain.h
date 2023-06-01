#pragma once
#include "Obj.h"
class CMyTerrain :	public CObj
{
public:
	CMyTerrain();
	virtual ~CMyTerrain();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

	HRESULT			Set_Act(TERRIAN_TYPE _eType);

	vector<TILE*>&			Get_VecTile() { return m_vecTile; }
	vector<list<TILE*>>&	Get_VecAdj() { return m_vecAdj; }

	UINT			Get_TerrianRow() { return m_iRow; }
	UINT			Get_TerrianCol() { return m_iCol; }

private:
	HRESULT			LoadTile(const TCHAR* pTilePath);
	HRESULT			Ready_Adj();

private:
	vector<list<TILE*>> m_vecAdj;

	vector<TILE*>		m_vecTile;

	UINT				m_iRow;
	UINT				m_iCol;
};

