#pragma once

#include "Include.h"
#include "afxwin.h"
// CMapTool_Tab2 dialog
class CToolView;
class CTerrain_Act;
class CTerrain_Act;
class CTerrain_Act;
class CMapTool_Tab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CMapTool_Tab2)

public:
	CMapTool_Tab2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMapTool_Tab2();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();

#pragma region Jun
public:
	afx_msg void OnList_Tile();
	afx_msg void OnCombo_ChangeAct();
	afx_msg void OnButton_ReloadTile();
	afx_msg void OnButton_CreateMap();
private:
	void	Load_TileList();
	void	Sort_TileList(TERRIAN_TYPE _eType);

public:
	CListBox	m_ListTile;
	CStatic		m_Texture_Tile;
	CComboBox	m_ComboTile;
	CComboBox	m_Combo_SelecMap;

public:
	CToolView* m_pMainView = nullptr;
	CTerrain_Act* m_pTerrain_Act1 = nullptr;
	CTerrain_Act* m_pTerrain_Act2 = nullptr;
	CTerrain_Act* m_pTerrain_Act3 = nullptr;

	UINT		m_iTileX;
	UINT		m_iTileY;
	
	vector<TILE*>	m_vecTile;
	TILE*			m_tSelectTile = nullptr;
	UINT			m_iTileDrawID;
	CString			m_strTileType;
	float			m_fTileDmg;
	
	map<CString, CImage*>	m_TilePngImg;

#pragma endregion

#pragma region Chan

#pragma endregion




	
	
	
	
	
	

	
	
	
	
	afx_msg void OnButton_SaveMap();
	afx_msg void OnButton_LoadMap();
	afx_msg void OnCombo_ChangeActMap();
	afx_msg void OnList_TileReset();
};
