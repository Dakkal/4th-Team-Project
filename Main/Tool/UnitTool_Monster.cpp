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

	// 테스트 이미지 불러오기
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


#pragma region 트랜스폼, 스탯 컨트롤 함수


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

void UnitTool_Monster::OnBnClickedButtonMonsterInit() // 다이얼로그에서 초기화 버튼을 눌렀을 때
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

	// 새로운 객체 생성
	m_pOriginUnit = new CUnit();
	m_pOriginUnit->Initialize();

	// 편집용으로 사용할 객체 복사 생성
	m_pCopyUnit = new CUnit(*m_pOriginUnit);
	m_pCopyUnit->Initialize();

	// 툴뷰에 유닛 세팅
	m_pToolView->m_pRenderUnit = m_pCopyUnit;


	// 다이얼로그 초기화
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


	// 파일명을 지운 순수 상대 경로 추출 (테스트 중)
	{
		DragQueryFile(hDropInfo, 0, szFilePath, MAX_PATH);

		CString strRelative = CFileInfo::ConvertRelativePath(szFilePath); // 상대경로로 만들어준다.
		CString	strFileName = PathFindFileName(strRelative); // 파일 이름만 추출하는 함수

		TCHAR	szFilePath[MAX_PATH] = L"";
		TCHAR	szFileName[MIN_STR] = L"";

		lstrcpy(szFilePath, strRelative.GetString());
		PathRemoveFileSpec(szFilePath);

		m_FilePath = szFilePath; // 파일명을 지운 순수 상대 경로 추출
	}



	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);

		CString strRelative = CFileInfo::ConvertRelativePath(szFilePath); // 상대경로로 만들어준다.
		CString	strFileName = PathFindFileName(strRelative); // 파일 이름만 추출하는 함수

		lstrcpy(szFileName, strFileName.GetString());
		PathRemoveExtension(szFileName); // 파일 이름에서 확장자를 지우는 함수

		strFileName = szFileName; // 대입함으로써 문자열에서 스트링으로 변환

								  // 해당 이미지의 파일명(확장자 제외)을 키로, 이미지를 밸류로 맵에 추가한다

		auto	iter = m_mapPngImg.find(strFileName);

		if (iter == m_mapPngImg.end())
		{
			CImage*	pPngImg = new CImage;
			pPngImg->Load(strRelative);

			m_mapPngImg.insert({ strFileName, pPngImg });
			m_ListBox.AddString(szFileName); // 리스트에 추가
		}

	}

	/*
	// 맨 위를 선택하고 바로 그려주기
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

	// 리스트 컨트롤 내에서 현재 선택된 항목의 이름에서 정수 값만 가져온다.
	int	iSelect = m_ListBox.GetCurSel();

	if (LB_ERR == iSelect)
		return;

	m_ListBox.GetText(iSelect, strSelectName); // 선택된 항목의 이름을 가져온다.

	auto iter = m_mapPngImg.find(strSelectName);

	if (iter == m_mapPngImg.end())
		return;

	//m_Picture.SetBitmap(*(iter->second));



	// 선택한 파일로 유닛의 렌더를 시작한다.
	{
		// 1. 텍스처 매니저에 저장
		CString strFinalPath = m_FilePath + L"\\" +  strSelectName + L".png";

		CString strObjKey = L"Test" + strSelectName;
		CString strStateKey = L"Test" + strSelectName;

		if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(strFinalPath, TEX_MULTI, strObjKey, strStateKey, m_mapPngImg.size())))
		{
			AfxMessageBox(L"TileTexture Create Failed");
			return;
		}

		// 2. 유닛의 m_strObjKey	, m_strStateKey로 세팅
		if (nullptr != m_pCopyUnit)
		{
			m_pCopyUnit->m_strObjKey = strObjKey;
			m_pCopyUnit->m_strStateKey = strStateKey;

		}

		m_pToolView->Invalidate(FALSE);

	}

	UpdateData(FALSE);
}
