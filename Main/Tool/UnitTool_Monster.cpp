// UnitTool_Monster.cpp : implementation file
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool_Monster.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "TextureMgr.h"
#include "FileInfo.h"

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
	, EDIT_NAME(_T(""))
{

}

UnitTool_Monster::~UnitTool_Monster()
{
	if (nullptr != m_pOriginUnit)
		Safe_Delete(m_pOriginUnit);

	if (nullptr != m_pCopyUnit)
		Safe_Delete(m_pCopyUnit);

	for_each(m_mapPngImg.begin(), m_mapPngImg.end(),
		[](auto& MyPair)
	{
		MyPair.second->Destroy();
		Safe_Delete(MyPair.second);
	});

	m_mapPngImg.clear();
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
	DDX_Control(pDX, IDC_SLIDER_MONSTER_HP, SLIDE_CTRL_HP);
	DDX_Control(pDX, IDC_SLIDER_MONSTER_AD, SLIDE_CTRL_AD);
	DDX_Control(pDX, IDC_SLIDER_MONSTER_SPEED, SLIDE_CTRL_SPEED);
	DDX_Text(pDX, IDC_EDIT_MONSTER_NAME, EDIT_NAME);
	DDX_Control(pDX, IDC_LIST4, m_ListBox);
	DDX_Control(pDX, IDC_STATIC_MONSTER_TEXTURE, m_Picture);
	DDX_Control(pDX, IDC_STATIC_MOSTER_LIST_DRAG, m_StaticText);
}

BOOL UnitTool_Monster::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Control Setting

	SLIDE_CTRL_HP.SetRange(0, (int)UNIT_MAX_HP);
	SLIDE_CTRL_AD.SetRange(0, (int)UNIT_MAX_AD);
	SLIDE_CTRL_SPEED.SetRange(0, (int)UNIT_MAX_SPEED);

	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	m_pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 0));

	// �׽�Ʈ �̹��� �ҷ�����
	/*if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Object/Player/Amazon/stand_8/%d.png", TEX_MULTI, L"Player", L"Stand", 1)))
	{
		AfxMessageBox(L"TileTexture Create Failed");
		return E_FAIL;
	}*/

	m_StaticText.ShowWindow(SW_HIDE);

	DragAcceptFiles(TRUE);
	UpdateData(FALSE);

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
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MONSTER_HP, &UnitTool_Monster::OnNMCustomdrawSliderMonsterHp)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MONSTER_AD, &UnitTool_Monster::OnNMCustomdrawSliderMonsterAd)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MONSTER_SPEED, &UnitTool_Monster::OnNMCustomdrawSliderMonsterSpeed)
	ON_EN_CHANGE(IDC_EDIT_MONSTER_NAME, &UnitTool_Monster::OnEnChangeEditMonsterName)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_INIT, &UnitTool_Monster::OnBnClickedButtonMonsterInit)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_NEW, &UnitTool_Monster::OnBnClickedButtonMonsterNew)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_DELETE, &UnitTool_Monster::OnBnClickedButtonMonsterDelete)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_EDIT, &UnitTool_Monster::OnBnClickedButtonMonsterEdit)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_SAVE, &UnitTool_Monster::OnBnClickedButtonMonsterSave)
	ON_WM_CTLCOLOR()
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST_MONSTER_TEXTURE, &UnitTool_Monster::OnLbnSelchangeListMonsterTexture)
END_MESSAGE_MAP()


#pragma region Ʈ������, ���� ��Ʈ�� �Լ�


void UnitTool_Monster::OnEnChangeEditMonsterPosX()
{
	if (nullptr == m_pCopyUnit) return;


	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vPos.x = EDIT_TRANSFORM_POS_X;


	m_pToolView->Invalidate(FALSE);
}


void UnitTool_Monster::OnEnChangeEditMonsterPosY()
{
	if (nullptr == m_pCopyUnit) return;

	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vPos.y = EDIT_TRANSFORM_POS_Y;


	m_pToolView->Invalidate(FALSE);

}


void UnitTool_Monster::OnEnChangeEditMonsterPosZ()
{
	if (nullptr == m_pCopyUnit) return;


	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vPos.z = EDIT_TRANSFORM_POS_Z;


	m_pToolView->Invalidate(FALSE);

}


void UnitTool_Monster::OnEnChangeEditMonsterRotX()
{
	if (nullptr == m_pCopyUnit) return;


	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vRot.x = EDIT_TRANSFORM_ROT_X;


	m_pToolView->Invalidate(FALSE);

}


void UnitTool_Monster::OnEnChangeEditMonsterRotY()
{
	if (nullptr == m_pCopyUnit) return;


	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vRot.y = EDIT_TRANSFORM_ROT_Y;


	m_pToolView->Invalidate(FALSE);

}


void UnitTool_Monster::OnEnChangeEditMonsterRotZ()
{
	if (nullptr == m_pCopyUnit) return;


	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vRot.z = D3DXToRadian(EDIT_TRANSFORM_ROT_Z);


	m_pToolView->Invalidate(FALSE);
}


void UnitTool_Monster::OnEnChangeEditMonsterSclX()
{
	if (nullptr == m_pCopyUnit) return;



	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vSize.x = EDIT_TRANSFORM_SCL_X;


	m_pToolView->Invalidate(FALSE);


}


void UnitTool_Monster::OnEnChangeEditMonsterSclY()
{
	if (nullptr == m_pCopyUnit) return;


	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vSize.y = EDIT_TRANSFORM_SCL_Y;


	m_pToolView->Invalidate(FALSE);
}


void UnitTool_Monster::OnEnChangeEditMonsterSclZ()
{
	if (nullptr == m_pCopyUnit) return;


	UpdateData(TRUE);

	m_pCopyUnit->m_tInfo.vSize.z = EDIT_TRANSFORM_SCL_Z;


	m_pToolView->Invalidate(FALSE);
}


void UnitTool_Monster::OnEnChangeEditMonsterStatHpValue()
{
	if (nullptr == m_pCopyUnit) return;

	UpdateData(TRUE);

	m_pCopyUnit->m_tStat.iHP = (int)EDIT_STAT_HP;

	SLIDE_CTRL_HP.SetPos((int)EDIT_STAT_HP);
	
	m_pToolView->Invalidate(FALSE);
}


void UnitTool_Monster::OnEnChangeEditMonsterStatAdValue()
{
	if (nullptr == m_pCopyUnit) return;


	UpdateData(TRUE);

	m_pCopyUnit->m_tStat.iAD = (int)EDIT_STAT_AD;
	
	SLIDE_CTRL_AD.SetPos(int(EDIT_STAT_AD));

	m_pToolView->Invalidate(FALSE);

}


void UnitTool_Monster::OnEnChangeEditMonsterStatSpeedValue()
{
	if (nullptr == m_pCopyUnit) return;


	UpdateData(TRUE);

	m_pCopyUnit->m_tStat.iSpeed = (int)EDIT_STAT_SPEED;

	SLIDE_CTRL_SPEED.SetPos(int(EDIT_STAT_SPEED));

	m_pToolView->Invalidate(FALSE);
}


void UnitTool_Monster::OnNMCustomdrawSliderMonsterHp(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (nullptr == m_pCopyUnit) return;


	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	int iScroll = SLIDE_CTRL_HP.GetPos();
	
	EDIT_STAT_HP = (float)iScroll;

	m_pCopyUnit->m_tStat.iHP = (int)EDIT_STAT_HP;

	UpdateData(FALSE);

	*pResult = 0;
}


void UnitTool_Monster::OnNMCustomdrawSliderMonsterAd(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (nullptr == m_pCopyUnit) return;


	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	int iScroll = SLIDE_CTRL_AD.GetPos();
	
	EDIT_STAT_AD = (float)iScroll;

	m_pCopyUnit->m_tStat.iAD = (int)EDIT_STAT_AD;

	UpdateData(FALSE);

	*pResult = 0;
}


void UnitTool_Monster::OnNMCustomdrawSliderMonsterSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (nullptr == m_pCopyUnit) return;


	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	int iScroll = SLIDE_CTRL_SPEED.GetPos();

	EDIT_STAT_SPEED = (float)iScroll;

	m_pCopyUnit->m_tStat.iSpeed = (int)EDIT_STAT_SPEED;

	UpdateData(FALSE);

	*pResult = 0;
}


void UnitTool_Monster::OnEnChangeEditMonsterName()
{
	if (nullptr == m_pCopyUnit) return;


	UpdateData(TRUE);

	m_pCopyUnit->m_tStat.strName = EDIT_NAME;
}

#pragma endregion


void UnitTool_Monster::Init_Dlg()
{
	EDIT_NAME = L"Enter Name";

	EDIT_TRANSFORM_POS_X = 0.f;
	EDIT_TRANSFORM_POS_Y = 0.f;
	EDIT_TRANSFORM_POS_Z = 0.f;
	EDIT_TRANSFORM_ROT_X = 0.f;
	EDIT_TRANSFORM_ROT_Y = 0.f;
	EDIT_TRANSFORM_ROT_Z = 0.f;
	EDIT_TRANSFORM_SCL_X = 1.f;
	EDIT_TRANSFORM_SCL_Y = 1.f;
	EDIT_TRANSFORM_SCL_Z = 1.f;

	SLIDE_CTRL_HP.SetPos(int(UNIT_MAX_HP * 0.5f));
	SLIDE_CTRL_AD.SetPos(int(UNIT_MAX_AD * 0.5f));
	SLIDE_CTRL_SPEED.SetPos(int(UNIT_MAX_SPEED * 0.5f));

	m_StaticText.ShowWindow(SW_SHOW);

	UpdateData(FALSE);
}

void UnitTool_Monster::Set_Editability(const bool & _bAlility)
{
	
}

void UnitTool_Monster::OnBnClickedButtonMonsterInit() // ���̾�α׿��� �ʱ�ȭ ��ư�� ������ ��
{
	if (nullptr != m_pCopyUnit) Safe_Delete(m_pCopyUnit);

	m_pCopyUnit = new CUnit(*m_pOriginUnit);
	m_pCopyUnit->Initialize();

	m_pToolView->m_pRenderUnit = m_pCopyUnit;
	Init_Dlg();

	m_pToolView->Invalidate(FALSE);
}

void UnitTool_Monster::OnBnClickedButtonMonsterNew()
{
	if (nullptr != m_pOriginUnit) Safe_Delete(m_pOriginUnit);
	if (nullptr != m_pCopyUnit) Safe_Delete(m_pCopyUnit);

	// ���ο� ��ü ����
	m_pOriginUnit = new CUnit();
	m_pOriginUnit->Initialize();

	// ���������� ����� ��ü ���� ����
	m_pCopyUnit = new CUnit(*m_pOriginUnit);
	m_pCopyUnit->Initialize();

	// ���信 ���� ����
	m_pToolView->m_pRenderUnit = m_pCopyUnit;


	// ���̾�α� �ʱ�ȭ
	Init_Dlg();

	m_pToolView->Invalidate();

	m_StaticText.ShowWindow(SW_SHOW);
}


void UnitTool_Monster::OnBnClickedButtonMonsterDelete()
{
	// TODO: Add your control notification handler code here
}


void UnitTool_Monster::OnBnClickedButtonMonsterEdit()
{
	// TODO: Add your control notification handler code here
}


void UnitTool_Monster::OnBnClickedButtonMonsterSave()
{
	m_pOriginUnit = m_pCopyUnit;
}


HBRUSH UnitTool_Monster::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

		//https://lock.tistory.com/20
	/*int nRet = pWnd->GetD
	pDC->SetBkMode(TRANSPARENT);*/

	return hbr;
}


void UnitTool_Monster::OnDropFiles(HDROP hDropInfo)
{
	UpdateData(TRUE);

	m_StaticText.ShowWindow(SW_HIDE);

	CDialogEx::OnDropFiles(hDropInfo);

	TCHAR		szFilePath[MAX_PATH] = L"";
	TCHAR		szFileName[MIN_STR] = L"";

	int iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0); 


	// ���ϸ��� ���� ���� ��� ��� ���� (�׽�Ʈ ��)
	{
		DragQueryFile(hDropInfo, 0, szFilePath, MAX_PATH);

		CString strRelative = CFileInfo::ConvertRelativePath(szFilePath); // ����η� ������ش�.
		CString	strFileName = PathFindFileName(strRelative); // ���� �̸��� �����ϴ� �Լ�

		TCHAR	szFilePath[MAX_PATH] = L"";
		TCHAR	szFileName[MIN_STR] = L"";

		lstrcpy(szFilePath, strRelative.GetString());
		PathRemoveFileSpec(szFilePath);

		m_FilePath = szFilePath; // ���ϸ��� ���� ���� ��� ��� ����
	}



	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);

		CString strRelative = CFileInfo::ConvertRelativePath(szFilePath); // ����η� ������ش�.
		CString	strFileName = PathFindFileName(strRelative); // ���� �̸��� �����ϴ� �Լ�

		lstrcpy(szFileName, strFileName.GetString());
		PathRemoveExtension(szFileName); // ���� �̸����� Ȯ���ڸ� ����� �Լ�

		strFileName = szFileName; // ���������ν� ���ڿ����� ��Ʈ������ ��ȯ

								  // �ش� �̹����� ���ϸ�(Ȯ���� ����)�� Ű��, �̹����� ����� �ʿ� �߰��Ѵ�

		auto	iter = m_mapPngImg.find(strFileName);

		if (iter == m_mapPngImg.end())
		{
			CImage*	pPngImg = new CImage;
			pPngImg->Load(strRelative);

			m_mapPngImg.insert({ strFileName, pPngImg });
			m_ListBox.AddString(szFileName); // ����Ʈ�� �߰�
		}

	}

	/*
	// �� ���� �����ϰ� �ٷ� �׷��ֱ�
	CString			strSelectName;
	int	iSelect = m_ListBox.GetCurSel();

	if (LB_ERR == iSelect)
		return;

	m_ListBox.GetText(iSelect, strSelectName);

	auto iter = m_mapPngImg.find(strSelectName);

	if (iter == m_mapPngImg.end())
		return;

	m_Picture.SetBitmap(*(iter->second));
	*/

	UpdateData(FALSE);
}


void UnitTool_Monster::OnLbnSelchangeListMonsterTexture()
{
	UpdateData(TRUE);

	CString			strSelectName;

	// ����Ʈ ��Ʈ�� ������ ���� ���õ� �׸��� �̸����� ���� ���� �����´�.
	int	iSelect = m_ListBox.GetCurSel();

	if (LB_ERR == iSelect)
		return;

	m_ListBox.GetText(iSelect, strSelectName); // ���õ� �׸��� �̸��� �����´�.

	auto iter = m_mapPngImg.find(strSelectName);

	if (iter == m_mapPngImg.end())
		return;

	//m_Picture.SetBitmap(*(iter->second));



	// ������ ���Ϸ� ������ ������ �����Ѵ�.
	{
		// 1. �ؽ�ó �Ŵ����� ����
		CString strFinalPath = m_FilePath + L"\\" +  strSelectName + L".png";

		CString strObjKey = L"Test" + strSelectName;
		CString strStateKey = L"Test" + strSelectName;

		if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(strFinalPath, TEX_MULTI, strObjKey, strStateKey, m_mapPngImg.size())))
		{
			AfxMessageBox(L"TileTexture Create Failed");
			return;
		}

		// 2. ������ m_strObjKey	, m_strStateKey�� ����
		if (nullptr != m_pCopyUnit)
		{
			m_pCopyUnit->m_strObjKey = strObjKey;
			m_pCopyUnit->m_strStateKey = strStateKey;

		}

		m_pToolView->Invalidate(FALSE);

	}

	UpdateData(FALSE);
}
