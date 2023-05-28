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
	virtual						BOOL OnInitDialog();

public:
	// User
	void						Init_Dlg(const CUnit* _pUnit = nullptr); // ��� ��Ʈ�� �ʱ�ȭ

	void						Set_Editability(const bool& _bAlility); // ���� ��Ʈ�� ���� ���� ����
	HRESULT						Load_DB(); // ���Ͽ� ����Ǿ��ִ� ���ֵ��� ������ ���Ϳ� ����Ʈ �ڽ��� Ǫ���Ѵ�.

	CToolView*					m_pToolView = nullptr;
	CUnit*						m_pOriginUnit = nullptr;
	CUnit*						m_pCopyUnit = nullptr;


	// Unit List
	vector<CUnit*>				m_vecUnit;		// ���� ����Ʈ�� �ö��ִ� ���� ����Ʈ
	CListBox					m_UnitListBox;
	int							m_iCurUnitListIndex = 0; // ���� ���� ����Ʈ �ε���

	// Texture List
	map<CString, CImage*>		m_mapPngImg;	// �ؽ�ó �̹����� �����Ѵ�
	CString						m_FilePath = L""; // ���ϸ��� ���� ���� ��� ���
	CListBox					m_TextureListBox;
	CStatic						m_Picture;


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

	CComboBox					m_ComboUnitType;

	// Control Method
	DECLARE_MESSAGE_MAP()


	// Btn5
	afx_msg void				OnBnClickedButtonMonsterNew();		// New
	afx_msg void				OnBnClickedButtonMonsterInit();		// Init
	afx_msg void				OnBnClickedButtonMonsterDelete();	// Delete
	afx_msg void				OnBnClickedButtonMonsterEdit();		// Edit
	afx_msg void				OnBnClickedButtonMonsterSave();		// Save			������ ����� ������ �����Ѵ�.
	afx_msg void				OnBnClickedButtonMonsterSaveDb();	// Save DB		DB�� ���� �����Ѵ�.
	afx_msg void				OnBnClickedButtonMonsterTexLoad();	// Texture Load �ؽ�ó�� �ε��� ������ Ž����� ����.

	// Edit
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

	// Scroll
	afx_msg void				OnNMCustomdrawSliderMonsterHp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnNMCustomdrawSliderMonsterAd(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnNMCustomdrawSliderMonsterSpeed(NMHDR *pNMHDR, LRESULT *pResult);

	// List 
	afx_msg void				OnLbnSelchangeListMonster();		// ���� ����Ʈ �׸� ����
	afx_msg void				OnLbnSelchangeListMonsterTexture(); // �ؽ�ó ����Ʈ �׸� ����
	
	// Combo Box
	afx_msg void				OnCbnSelchangeComboMonsterType();
	
	afx_msg void				OnDropFiles(HDROP hDropInfo);
};
