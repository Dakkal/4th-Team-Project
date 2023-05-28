#pragma once


// UnitTool_Monster dialog
#include "Include.h"
#include "ToolView.h"
#include "Unit.h"
#include "afxcmn.h"
#include <atlimage.h>
#include "afxwin.h"

class UnitTool_Monster : public CDialogEx
{
	DECLARE_DYNAMIC(UnitTool_Monster)

public:
	UnitTool_Monster(CWnd* pParent = NULL);   // standard constructor
	virtual ~UnitTool_Monster();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNIT_MONSTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


public:
	virtual			BOOL OnInitDialog();


public:
	// User
	void						Init_Dlg(); // 모든 컨트롤 초기화
	void						Set_Editability(const bool& _bAlility); // 에딧 컨트롤 편집 가능 여부

	CToolView*					m_pToolView = nullptr;
	CUnit*						m_pOriginUnit = nullptr;
	CUnit*						m_pCopyUnit = nullptr;

	map<CString, CImage*>		m_mapPngImg; // 텍스처 이미지를 저장한다

	CString						m_FilePath = L""; // 파일명을 지운 순수 상대 경로


	// Control Field
	CString						EDIT_NAME;

	float						EDIT_TRANSFORM_POS_X;
	float						EDIT_TRANSFORM_POS_Y;
	float						EDIT_TRANSFORM_POS_Z;
	float						EDIT_TRANSFORM_ROT_X;
	float						EDIT_TRANSFORM_ROT_Y;
	float						EDIT_TRANSFORM_ROT_Z;
	float						EDIT_TRANSFORM_SCL_X;
	float						EDIT_TRANSFORM_SCL_Y;
	float						EDIT_TRANSFORM_SCL_Z;
	float						EDIT_STAT_HP;
	float						EDIT_STAT_AD;
	float						EDIT_STAT_SPEED;

	CSliderCtrl					SLIDE_CTRL_HP;
	CSliderCtrl					SLIDE_CTRL_AD;
	CSliderCtrl					SLIDE_CTRL_SPEED;

	CListBox					m_ListBox;
	CStatic						m_Picture;
	CStatic						m_StaticText;

	// Control Method
	DECLARE_MESSAGE_MAP()

	afx_msg void				OnEnChangeEditMonsterName();

	afx_msg void				OnEnChangeEditMonsterPosX();
	afx_msg void				OnEnChangeEditMonsterPosY();
	afx_msg void				OnEnChangeEditMonsterPosZ();
	afx_msg void				OnEnChangeEditMonsterRotX();
	afx_msg void				OnEnChangeEditMonsterRotY();
	afx_msg void				OnEnChangeEditMonsterRotZ();
	afx_msg void				OnEnChangeEditMonsterSclX();
	afx_msg void				OnEnChangeEditMonsterSclY();
	afx_msg void				OnEnChangeEditMonsterSclZ();

	afx_msg void				OnEnChangeEditMonsterStatHpValue();
	afx_msg void				OnEnChangeEditMonsterStatAdValue();
	afx_msg void				OnEnChangeEditMonsterStatSpeedValue();

	afx_msg void				OnNMCustomdrawSliderMonsterHp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnNMCustomdrawSliderMonsterAd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnNMCustomdrawSliderMonsterSpeed(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void				OnBnClickedButtonMonsterNew();
	afx_msg void				OnBnClickedButtonMonsterInit();
	afx_msg void				OnBnClickedButtonMonsterDelete();
	afx_msg void				OnBnClickedButtonMonsterEdit();
	afx_msg void				OnBnClickedButtonMonsterSave();

	afx_msg HBRUSH				OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void				OnDropFiles(HDROP hDropInfo);
	afx_msg void				OnLbnSelchangeListMonsterTexture();
};
