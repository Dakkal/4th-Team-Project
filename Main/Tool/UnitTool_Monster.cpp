// UnitTool_Monster.cpp : implementation file
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool_Monster.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// UnitTool_Monster dialog

IMPLEMENT_DYNAMIC(UnitTool_Monster, CDialogEx)

UnitTool_Monster::UnitTool_Monster(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_UNIT_MONSTER, pParent)
	, EDIT_TRANSFORM_POS_X(0)
	, EDIT_TRANSFORM_POS_Y(0)
	, EDIT_TRANSFORM_POS_Z(0)
	, EDIT_TRANSFORM_ROT_X(0)
	, EDIT_TRANSFORM_ROT_Y(0)
	, EDIT_TRANSFORM_ROT_Z(0)
	, EDIT_TRANSFORM_SCL_X(0)
	, EDIT_TRANSFORM_SCL_Y(0)
	, EDIT_TRANSFORM_SCL_Z(0)
	, EDIT_STAT_HP(0)
	, EDIT_STAT_AD(0)
	, EDIT_STAT_SPEED(0)
{

}

UnitTool_Monster::~UnitTool_Monster()
{
}

void UnitTool_Monster::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MONSTER_POS_X, EDIT_TRANSFORM_POS_X);
	DDX_Text(pDX, IDC_EDIT_MONSTER_POS_Y, EDIT_TRANSFORM_POS_Y);
	DDX_Text(pDX, IDC_EDIT_MONSTER_POS_Z, EDIT_TRANSFORM_POS_Z);
	DDX_Text(pDX, IDC_EDIT_MONSTER_ROT_X, EDIT_TRANSFORM_ROT_X);
	DDX_Text(pDX, IDC_EDIT_MONSTER_ROT_Y, EDIT_TRANSFORM_ROT_Y);
	DDX_Text(pDX, IDC_EDIT_MONSTER_ROT_Z, EDIT_TRANSFORM_ROT_Z);
	DDX_Text(pDX, IDC_EDIT_MONSTER_SCL_X, EDIT_TRANSFORM_SCL_X);
	DDX_Text(pDX, IDC_EDIT_MONSTER_SCL_Y, EDIT_TRANSFORM_SCL_Y);
	DDX_Text(pDX, IDC_EDIT_MONSTER_SCL_Z, EDIT_TRANSFORM_SCL_Z);
	DDX_Text(pDX, IDC_EDIT_MONSTER_STAT_HP_VALUE, EDIT_STAT_HP);
	DDX_Text(pDX, IDC_EDIT_MONSTER_STAT_AD_VALUE, EDIT_STAT_AD);
	DDX_Text(pDX, IDC_EDIT_MONSTER_STAT_SPEED_VALUE, EDIT_STAT_SPEED);
}

BOOL UnitTool_Monster::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	
	m_pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 0));
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
BEGIN_MESSAGE_MAP(UnitTool_Monster, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_MONSTER_POS_X, &UnitTool_Monster::OnEnChangeEditMonsterPosX)
	ON_EN_CHANGE(IDC_EDIT_MONSTER_POS_Y, &UnitTool_Monster::OnEnChangeEditMonsterPosY)
	ON_EN_CHANGE(IDC_EDIT_MONSTER_POS_Z, &UnitTool_Monster::OnEnChangeEditMonsterPosZ)
	ON_EN_CHANGE(IDC_EDIT_MONSTER_ROT_X, &UnitTool_Monster::OnEnChangeEditMonsterRotX)
	ON_EN_CHANGE(IDC_EDIT_MONSTER_ROT_Y, &UnitTool_Monster::OnEnChangeEditMonsterRotY)
	ON_EN_CHANGE(IDC_EDIT_MONSTER_ROT_Z, &UnitTool_Monster::OnEnChangeEditMonsterRotZ)
	ON_EN_CHANGE(IDC_EDIT_MONSTER_SCL_X, &UnitTool_Monster::OnEnChangeEditMonsterSclX)
	ON_EN_CHANGE(IDC_EDIT_MONSTER_SCL_Y, &UnitTool_Monster::OnEnChangeEditMonsterSclY)
	ON_EN_CHANGE(IDC_EDIT_MONSTER_SCL_Z, &UnitTool_Monster::OnEnChangeEditMonsterSclZ)
	ON_EN_CHANGE(IDC_EDIT_MONSTER_STAT_HP_VALUE, &UnitTool_Monster::OnEnChangeEditMonsterStatHpValue)
	ON_EN_CHANGE(IDC_EDIT_MONSTER_STAT_AD_VALUE, &UnitTool_Monster::OnEnChangeEditMonsterStatAdValue)
	ON_EN_CHANGE(IDC_EDIT_MONSTER_STAT_SPEED_VALUE, &UnitTool_Monster::OnEnChangeEditMonsterStatSpeedValue)
END_MESSAGE_MAP()


void UnitTool_Monster::OnEnChangeEditMonsterPosX()
{
	if (nullptr == m_pCopyUnit)
		m_pCopyUnit = m_pToolView->m_pCopyUnit;

	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vPos.x = EDIT_TRANSFORM_POS_X;

	UpdateData(FALSE);

	m_pToolView->Invalidate(FALSE);
}


void UnitTool_Monster::OnEnChangeEditMonsterPosY()
{
	if (nullptr == m_pCopyUnit)
		m_pCopyUnit = m_pToolView->m_pCopyUnit;

	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vPos.y = EDIT_TRANSFORM_POS_Y;

	UpdateData(FALSE);

	m_pToolView->Invalidate(FALSE);

}


void UnitTool_Monster::OnEnChangeEditMonsterPosZ()
{
	if (nullptr == m_pCopyUnit)
		m_pCopyUnit = m_pToolView->m_pCopyUnit;

	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vPos.z = EDIT_TRANSFORM_POS_Z;

	UpdateData(FALSE);

	m_pToolView->Invalidate(FALSE);

}


void UnitTool_Monster::OnEnChangeEditMonsterRotX()
{
	if (nullptr == m_pCopyUnit)
		m_pCopyUnit = m_pToolView->m_pCopyUnit;

	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vRot.x = EDIT_TRANSFORM_ROT_X;

	UpdateData(FALSE);

	m_pToolView->Invalidate(FALSE);

}


void UnitTool_Monster::OnEnChangeEditMonsterRotY()
{
	if (nullptr == m_pCopyUnit)
		m_pCopyUnit = m_pToolView->m_pCopyUnit;

	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vRot.y = EDIT_TRANSFORM_ROT_Y;

	UpdateData(FALSE);

	m_pToolView->Invalidate(FALSE);

}


void UnitTool_Monster::OnEnChangeEditMonsterRotZ()
{
	if (nullptr == m_pCopyUnit)
		m_pCopyUnit = m_pToolView->m_pCopyUnit;

	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vRot.z = EDIT_TRANSFORM_ROT_Z;

	UpdateData(FALSE);

	m_pToolView->Invalidate(FALSE);
}


void UnitTool_Monster::OnEnChangeEditMonsterSclX()
{
	if (nullptr == m_pCopyUnit)
		m_pCopyUnit = m_pToolView->m_pCopyUnit;



	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vSize.x = EDIT_TRANSFORM_SCL_X + 1;

	UpdateData(FALSE);

	m_pToolView->Invalidate(FALSE);


}


void UnitTool_Monster::OnEnChangeEditMonsterSclY()
{
	if (nullptr == m_pCopyUnit)
		m_pCopyUnit = m_pToolView->m_pCopyUnit;

	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vSize.y = EDIT_TRANSFORM_SCL_Y + 1;

	UpdateData(FALSE);

	m_pToolView->Invalidate(FALSE);
}


void UnitTool_Monster::OnEnChangeEditMonsterSclZ()
{
	if (nullptr == m_pCopyUnit)
		m_pCopyUnit = m_pToolView->m_pCopyUnit;

	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vSize.z = EDIT_TRANSFORM_SCL_Z + 1;

	UpdateData(FALSE);

	m_pToolView->Invalidate(FALSE);
}


void UnitTool_Monster::OnEnChangeEditMonsterStatHpValue()
{
	if (nullptr == m_pCopyUnit)
		m_pCopyUnit = m_pToolView->m_pCopyUnit;

	UpdateData(TRUE);

	m_pCopyUnit->m_tStat.iHP = EDIT_STAT_HP;

	UpdateData(FALSE);
}


void UnitTool_Monster::OnEnChangeEditMonsterStatAdValue()
{
	if (nullptr == m_pCopyUnit)
		m_pCopyUnit = m_pToolView->m_pCopyUnit;

	UpdateData(TRUE);

	m_pCopyUnit->m_tStat.iAD = EDIT_STAT_AD;

	UpdateData(FALSE);
}


void UnitTool_Monster::OnEnChangeEditMonsterStatSpeedValue()
{
	if (nullptr == m_pCopyUnit)
		m_pCopyUnit = m_pToolView->m_pCopyUnit;

	UpdateData(TRUE);

	m_pCopyUnit->m_tStat.iSpeed = EDIT_STAT_SPEED;

	UpdateData(FALSE);
}
