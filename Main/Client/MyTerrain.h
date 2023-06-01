#pragma once
#include "Obj.h"
class CMyTerrain :	public CObj
{
public:
	CMyTerrain();
	virtual ~CMyTerrain();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

	HRESULT			Set_Act(TERRIAN_TYPE _eType);

private:
	HRESULT			LoadTile(const TCHAR* pTilePath);
	

private:
	vector<TILE*>		m_vecTile;

	UINT				m_iRow;
	UINT				m_iCol;
};

