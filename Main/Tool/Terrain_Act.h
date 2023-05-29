#pragma once
#include "Obj.h"

class CToolView;
class CTerrain_Act :
	public CObj
{
public:
	CTerrain_Act();
	virtual ~CTerrain_Act();

	// Inherited via CObj
	virtual HRESULT Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render() override;
	virtual void	Release() override;
	virtual	void	Tool_Render(const D3DXVECTOR3& _vWorld)	override;

public:
	void		Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);
	void		Create_Terrian(int _TileX, int _TileY);

public:
	int		Get_TileIndex(const D3DXVECTOR3& vPos);
	void	Tile_Change(const D3DXVECTOR3& vPos, TILE* _Tile);
	bool	Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex);


public:
	vector<TILE*>		m_vecActTile;
	CToolView*			m_pMainView = nullptr;

	UINT				m_ActTileX;
	UINT				m_ActTileY;

};

