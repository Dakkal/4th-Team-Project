#pragma once
#include "Obj.h"

class CToolView;
class CTerrain_Act2 :
	public CObj
{
public:
	CTerrain_Act2();
	virtual ~CTerrain_Act2();

	// Inherited via CObj
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void		Set_MainView(CToolView* pMainView) { m_pMainView = pMainView; }
	void		Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);

public:
	vector<TILE*>&		Get_vecTile() { return m_vecTile; }

private:
	vector<TILE*>		m_vecTile;
	CToolView*			m_pMainView = nullptr;
};

