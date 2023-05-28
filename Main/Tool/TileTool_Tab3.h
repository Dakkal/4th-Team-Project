#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "Include.h"

// CTileTool_Tab3 dialog
class CToolView;
class CTerrain_Act1;
class CTerrain_Act2;
class CTerrain_Act3;
class CTileTool_Tab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CTileTool_Tab3)

public:
	CTileTool_Tab3(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTileTool_Tab3();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TILETOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();

	afx_msg void OnPush_Tile();
	afx_msg void OnClear_Tile();
	afx_msg void OnSaveDB_Tile();
	afx_msg void OnDestroy();
	afx_msg void OnSet_TileDamage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnActTileChange();
	afx_msg void OnListTile();
	afx_msg void OnLoadDB_Tile();

public:
	void	Tool_Render(const D3DXVECTOR3& _vWorld);


public:
	CComboBox			m_Combo_Tile;
	CListBox			m_List_Tile;
	CButton				m_Check_Tile[3];
	CSpinButtonCtrl		m_Spin_Tile;
	CEdit				m_Edit_TileDmg;

public:
	int m_iTileDamage;

	int m_iDrawId_First;
	int m_iDrawId_Last;
	
	int	m_iDrawID = 0;

public:
	vector<TILE*>	m_vecTile_Act1;
	vector<TILE*>	m_vecTile_Act2;
	vector<TILE*>	m_vecTile_Act3;

	CToolView*		m_pMainView = nullptr;

private:
	// 파일명정렬 및 벡터 없으면 벡터 타일객체채우기
	void		Sort_File(TERRIAN_TYPE _eTerrainType);
	void	    Set_Ratio(D3DXMATRIX * pOut, float fRatioX, float fRatioY);
};
