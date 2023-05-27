#pragma once
#include "Obj.h"

class CToolView;
class CTerrain_Act3 :
	public CObj
{
public:
	CTerrain_Act3();
	virtual ~CTerrain_Act3();

	// Inherited via CObj
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void		Set_MainView(CToolView* pMainView) { m_pMainView = pMainView; }
	void		Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);

private:
	vector<TILE*>		m_vecTile;
	CToolView*			m_pMainView = nullptr;
};

