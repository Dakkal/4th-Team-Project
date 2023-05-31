#pragma once

#include "Include.h"
#include "afxwin.h"
#include "afxcmn.h"

// CMapTool_Tab2 dialog

class CToolView;
class CTerrain_Act;
class CTerrain_Act;
class CTerrain_Act;
class CObj;

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

#pragma region 공용

	MAPTOOL_MODE			m_eToolMode; // 현재 컨트롤하고 있는 것이 Map인지, Tile인지 Obj인지

#pragma endregion

#pragma region Jun
public:
	afx_msg void			OnCombo_ChangeActMap();
	afx_msg void			OnButton_SaveMap();
	afx_msg void			OnButton_LoadMap();
	afx_msg void			OnButton_CreateMap();

	afx_msg void			OnList_Tile();
	afx_msg void			OnButton_ReloadTile();
	afx_msg void			OnCombo_ChangeAct();
	afx_msg void			OnList_TileReset();

private:
	void					Load_TileList();
	void					Sort_TileList(TERRIAN_TYPE _eType);

public:
	CListBox				m_ListTile;
	CStatic					m_Texture_Tile;
	CComboBox				m_ComboTile;
	CComboBox				m_Combo_SelecMap;

public:
	CToolView*				m_pMainView		= nullptr;
	CTerrain_Act*			m_pTerrain_Act1 = nullptr;
	CTerrain_Act*			m_pTerrain_Act2 = nullptr;
	CTerrain_Act*			m_pTerrain_Act3 = nullptr;

	UINT					m_iTileX;
	UINT					m_iTileY;
	
	vector<TILE*>			m_vecTile;
	TILE*					m_tSelectTile	= nullptr;
	UINT					m_iTileDrawID;
	CString					m_strTileType;
	float					m_fTileDmg;
	
	map<CString, CImage*>	m_TilePngImg;

#pragma endregion

#pragma region Chan

public:						
	// Field - Control
	CComboBox				m_cComboBox_Obj;
	CListCtrl				m_cListCtrl_Obj;
	CImageList				m_cImgList_Obj[(UINT)OBJ_TYPE::TYPEEND];

	// Field - General
	vector<CObj*>			m_vecObj[(UINT)OBJ_TYPE::TYPEEND];
	CObj*					m_pCurObj;

public:						
	// Methods - Control
	afx_msg void			OnCbnSelchangeMapObjComboType();					// 오브젝트 타입 콤보 박스 선택 항목 변경시

	// Methods - General
	HRESULT					Load_UnitData	(const CString& _strPath);			// 데이터 파일에 저장되어 있는 유닛 프리팹 로드
	const UINT				Get_IconID		(const CObj* const _pUnit) const;	// 리스트 컨트롤에 사용할 아이콘 ID 고유 번호를 생성하여 반환
	HRESULT					Set_ListCtrl	(const OBJ_TYPE& _eType);			// 매개변수로 받은 오브젝트 타입에 맞게 리스트 컨트롤을 업데이트 한다.

#pragma endregion

};
