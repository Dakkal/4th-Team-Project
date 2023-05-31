#pragma once

#include "MapTool_SubDlg.h"
#include "Include.h"
#include "afxwin.h"
#include "afxcmn.h"

// CMapTool_Tab2 dialog
class CMyForm;
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
	//맵
	afx_msg void			OnCombo_ChangeActMap(); // 콤보 : 맵 Act변경 함수시 Terrian 객체 변경
	afx_msg void			OnButton_SaveMap(); // 버튼 : 현재 액트에 해당하는 맵 세이브
	afx_msg void			OnButton_LoadMap(); // 버튼 : 현재 엑트에 해당하는 맵세이브 파일 로드
	afx_msg void			OnButton_CreateMap(); // 버튼 : Row, Col에 따라 타일맵 생성:
	afx_msg void			OnRadio_MiniView_Hide(); // 라디오 : 미니뷰 끄기
	afx_msg void			OnRadio_MiniView_Show(); // 라디오 : 미니뷰 켜기

	//타일
	afx_msg void			OnList_Tile(); // 리스트박스 : 리스트 클릭시 해당 리스트의 타일정보를 m_tSelectTile에 저장
	afx_msg void			OnButton_ReloadTile(); // 버튼 : 리스트박스에 저장된 타일DB들을 다시 불러옴
	afx_msg void			OnCombo_ChangeAct(); // 콤보 : 액트 변경시 해당 액트 타일로 변경
	afx_msg void			OnList_TileReset(); // 리스트박스 : 더블클릭시 현재 선택된 타일 해제

private:
	void					Load_TileList(); // 저장된 타일DB 함수
	void					Sort_TileList(TERRIAN_TYPE _eType); // 타일리스트의 목록을 Sort하는 함수

public:
	CListBox				m_ListTile;
	CStatic					m_Texture_Tile;
	CComboBox				m_ComboTile;
	CComboBox				m_Combo_SelecMap;
	CButton					m_Radio_Mini[2];
	CSliderCtrl				m_Slide_Row;
	CSliderCtrl				m_Slide_Col;

public:
	CMapTool_SubDlg	m_pMapTool_SubMap; // 서브다이얼로그 객체

	CToolView* m_pMainView = nullptr;
	CMyForm*   m_pFormView = nullptr;

	CTerrain_Act* m_pTerrain_Act1 = nullptr;
	CTerrain_Act* m_pTerrain_Act2 = nullptr;
	CTerrain_Act* m_pTerrain_Act3 = nullptr;

	UINT					m_iTileX; // 맵 Row
	UINT					m_iTileY; // 맵 Col
	
	vector<TILE*>			m_vecTile; // 타일DB 저장용 벡터
	TILE*					m_tSelectTile	= nullptr; // 현재 선택된 타일
	UINT					m_iTileDrawID; // DrawID용 에딧박스
	CString					m_strTileType; // 타일 타입용 에딧박스
	float					m_fTileDmg;	   // 타일 데미지용 에딧박스
	
	map<CString, CImage*>	m_TilePngImg; // 타일이미지 저장용 맵

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

	
	

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEdit_ChangeRow();
	afx_msg void OnEdit_ChangeCol();
};
