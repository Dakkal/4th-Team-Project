#pragma once


// UnitTool_Monster dialog
#include "Include.h"
#include "ToolView.h"
#include "Unit.h"

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
	virtual BOOL OnInitDialog();

	CToolView*		m_pToolView = nullptr;
	CUnit*			m_pCopyUnit = nullptr;


	int EDIT_TRANSFORM_POS_X;
	int EDIT_TRANSFORM_POS_Y;
	int EDIT_TRANSFORM_POS_Z;
	int EDIT_TRANSFORM_ROT_X;
	int EDIT_TRANSFORM_ROT_Y;
	int EDIT_TRANSFORM_ROT_Z;
	int EDIT_TRANSFORM_SCL_X;
	int EDIT_TRANSFORM_SCL_Y;
	int EDIT_TRANSFORM_SCL_Z;
	int EDIT_STAT_HP;
	int EDIT_STAT_AD;
	int EDIT_STAT_SPEED;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChangeEditMonsterPosX();
	afx_msg void OnEnChangeEditMonsterPosY();
	afx_msg void OnEnChangeEditMonsterPosZ();
	afx_msg void OnEnChangeEditMonsterRotX();
	afx_msg void OnEnChangeEditMonsterRotY();
	afx_msg void OnEnChangeEditMonsterRotZ();
	afx_msg void OnEnChangeEditMonsterSclX();
	afx_msg void OnEnChangeEditMonsterSclY();
	afx_msg void OnEnChangeEditMonsterSclZ();
	afx_msg void OnEnChangeEditMonsterStatHpValue();
	afx_msg void OnEnChangeEditMonsterStatAdValue();
	afx_msg void OnEnChangeEditMonsterStatSpeedValue();
};
