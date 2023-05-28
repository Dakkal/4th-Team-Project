// UnitTool_Monster.cpp : implementation file
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool_Monster.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "TextureMgr.h"
#include "FileInfo.h"

CString OBJ_TYPE_STRING[(UINT)OBJ_TYPE::TYPEEND]{ L"PLAYER", L"MONSTER", L"NPC", L"ITEM", L"TERRAIN", L"UI" };

CString OBJ_DIR_STRING[(UINT)OBJ_DIR::TYPEEND]{ L"UP", L"RIGHT_UP", L"RIGHT", L"RIGHT_DOWN", L"DOWN", L"LEFT_DONN", L"LEFT", L"LEFT_UP" };

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

	// �ؽ�ó ���� �޸� ����
	for_each(m_mapPngImg.begin(), m_mapPngImg.end(),
		[](auto& MyPair)
	{
		MyPair.second->Destroy();
		Safe_Delete(MyPair.second);
	});

	m_mapPngImg.clear();

	// ���� ���� �޸� ����
	if (nullptr != m_pOriginUnit)
		Safe_Delete(m_pOriginUnit);

	for_each(m_vecUnit.begin(), m_vecUnit.end(), CDeleteObj());

	m_vecUnit.clear();
	m_vecUnit.shrink_to_fit();
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
	DDX_Control(pDX, IDC_LIST4, m_TextureListBox);
	DDX_Control(pDX, IDC_STATIC_MONSTER_TEXTURE, m_Picture);
	DDX_Control(pDX, IDC_LIST_MONSTER, m_UnitListBox);
	DDX_Control(pDX, IDC_COMBO_MONSTER_TYPE, m_ComboUnitType);
}

BOOL UnitTool_Monster::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���̾�α� ��Ʈ�ѵ��� �����Ѵ�.

	SLIDE_CTRL_HP.SetRange(0, (int)UNIT_MAX_HP);
	SLIDE_CTRL_AD.SetRange(0, (int)UNIT_MAX_AD);
	SLIDE_CTRL_SPEED.SetRange(0, (int)UNIT_MAX_SPEED);

	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	m_pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 0));



	// ����� DB�� �ҷ��´�
	Load_DB();
	if (FAILED(Load_DB()))
	{
		AfxMessageBox(L"Load Unit DB Failed");
		return E_FAIL;
	}


	DragAcceptFiles(TRUE);
	UpdateData(FALSE);


	for (int i = 0; i < (UINT)OBJ_TYPE::TYPEEND; ++i)
		m_ComboUnitType.AddString(OBJ_TYPE_STRING[i]);
	return TRUE;  
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
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_TEX_LOAD, &UnitTool_Monster::OnBnClickedButtonMonsterTexLoad)
	ON_BN_CLICKED(IDC_BUTTON_MONSTER_SAVE_DB, &UnitTool_Monster::OnBnClickedButtonMonsterSaveDb)

	ON_WM_CTLCOLOR()
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST_MONSTER_TEXTURE, &UnitTool_Monster::OnLbnSelchangeListMonsterTexture)
	ON_LBN_SELCHANGE(IDC_LIST_MONSTER, &UnitTool_Monster::OnLbnSelchangeListMonster)

	ON_CBN_SELCHANGE(IDC_COMBO_MONSTER_TYPE, &UnitTool_Monster::OnCbnSelchangeComboMonsterType)
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

	m_UnitListBox.DeleteString(m_iCurUnitListIndex);
	m_UnitListBox.InsertString(m_iCurUnitListIndex, m_pCopyUnit->m_tStat.strName);



}

#pragma endregion


void UnitTool_Monster::Init_Dlg(const CUnit* _pUnit)
{
	// Edit ����
	EDIT_NAME = _pUnit->m_tStat.strName;

	EDIT_TRANSFORM_POS_X = _pUnit->m_tInfo.vPos.x;
	EDIT_TRANSFORM_POS_Y = _pUnit->m_tInfo.vPos.y;
	EDIT_TRANSFORM_POS_Z = _pUnit->m_tInfo.vPos.z;
	EDIT_TRANSFORM_ROT_X = _pUnit->m_tInfo.vRot.x;
	EDIT_TRANSFORM_ROT_Y = _pUnit->m_tInfo.vRot.y;
	EDIT_TRANSFORM_ROT_Z = _pUnit->m_tInfo.vRot.z;
	EDIT_TRANSFORM_SCL_X = _pUnit->m_tInfo.vSize.x;
	EDIT_TRANSFORM_SCL_Y = _pUnit->m_tInfo.vSize.y;
	EDIT_TRANSFORM_SCL_Z = _pUnit->m_tInfo.vSize.z;

	// �����̵� ����
	SLIDE_CTRL_HP.SetPos(_pUnit->m_tStat.iHP);
	SLIDE_CTRL_AD.SetPos(_pUnit->m_tStat.iAD);
	SLIDE_CTRL_SPEED.SetPos(_pUnit->m_tStat.iSpeed);

	if (_pUnit->m_eType == OBJ_TYPE::TYPEEND)
		m_ComboUnitType.SetCurSel(-1);
	else
		m_ComboUnitType.SetCurSel((UINT)_pUnit->m_eType);

	// �ؽ�ó ����
	for_each(m_mapPngImg.begin(), m_mapPngImg.end(),
		[](auto& MyPair)
	{
		MyPair.second->Destroy();
		Safe_Delete(MyPair.second);
	});

	m_mapPngImg.clear();

	// �ؽ�ó ����Ʈ �ڽ� �����
	m_TextureListBox.ResetContent();

	UpdateData(FALSE);
}

void UnitTool_Monster::Set_Editability(const bool & _bAlility)
{
	
}


void UnitTool_Monster::OnBnClickedButtonMonsterInit() // ���̾�α׿��� �ʱ�ȭ ��ư�� ������ ��
{
	if (nullptr == m_pCopyUnit)
	{
		AfxMessageBox(L"Not Create Unit");
		return;
	}


	m_pCopyUnit->Initialize();
	Init_Dlg(m_pCopyUnit);
	m_UnitListBox.DeleteString(m_iCurUnitListIndex);
	m_UnitListBox.InsertString(m_iCurUnitListIndex, m_pCopyUnit->m_tStat.strName);

	m_pToolView->Invalidate(FALSE);
}

void UnitTool_Monster::OnBnClickedButtonMonsterNew()
{
	// ���ο� ��ü ����
	if (nullptr != m_pOriginUnit)
		Safe_Delete(m_pOriginUnit);

	m_pOriginUnit = new CUnit();
	m_pOriginUnit->Initialize();

	// ���������� ����� ��ü ���� ����
	m_pCopyUnit = new CUnit(*m_pOriginUnit);
	m_pCopyUnit->Initialize();

	// ���信 ���� ����'
	m_pToolView->m_pRenderUnit = m_pCopyUnit;

	// ����Ʈ �� ���� �߰�
	m_UnitListBox.AddString(m_pCopyUnit->m_tStat.strName);
	m_vecUnit.push_back(m_pCopyUnit);

	// ���̾�α� �ʱ�ȭ
	Init_Dlg(m_pCopyUnit);

	UpdateData(FALSE);

	m_pToolView->Invalidate();
}


void UnitTool_Monster::OnBnClickedButtonMonsterDelete()
{
	for (vector<CUnit*>::iterator iter = m_vecUnit.begin(); iter != m_vecUnit.end(); ++iter)
	{
		if (*iter == m_pCopyUnit)
		{
			m_vecUnit.erase(iter);
			m_UnitListBox.DeleteString(m_iCurUnitListIndex);

			Safe_Delete(m_pOriginUnit);
			m_pOriginUnit = nullptr;

			Safe_Delete(m_pCopyUnit);
			m_pCopyUnit = nullptr;
			
			m_pToolView->m_pRenderUnit = nullptr;

			m_pToolView->Invalidate(FALSE);
			return;
		}
	}
}


void UnitTool_Monster::OnBnClickedButtonMonsterEdit()
{
	if (nullptr == m_pCopyUnit)
	{
		AfxMessageBox(L"Not Create Unit");
		return;
	}
}


void UnitTool_Monster::OnBnClickedButtonMonsterSave()
{
	//C:\Users\ChanYoon\Desktop\Programming\Tasks\Team\Jusin_TeamAssignment_D2D_2\ProjectFIle\Main\Data\01.Object

	// ���� ���ֿ� ������ ������ �����Ѵ�.

	if (nullptr == m_pCopyUnit)
	{
		AfxMessageBox(L"Not Create Unit");
		return;
	}

	m_pOriginUnit = m_pCopyUnit;
}




void UnitTool_Monster::OnDropFiles(HDROP hDropInfo)
{
	UpdateData(TRUE);


	CDialogEx::OnDropFiles(hDropInfo);

	TCHAR		szFilePath[MAX_PATH] = L"";
	TCHAR		szFileName[MIN_STR] = L"";

	int iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0); 


	// ���ϸ��� ���� ���� ��� ��� ���� -> ���ֿ��� ����
	{
		DragQueryFile(hDropInfo, 0, szFilePath, MAX_PATH);

		CString strRelative = CFileInfo::ConvertRelativePath(szFilePath); // ����η� ������ش�.
		CString	strFileName = PathFindFileName(strRelative); // ���� �̸��� �����ϴ� �Լ�

		TCHAR	szFilePath[MAX_PATH] = L"";
		TCHAR	szFileName[MIN_STR] = L"";

		lstrcpy(szFilePath, strRelative.GetString());
		PathRemoveFileSpec(szFilePath);

		m_FilePath = szFilePath; // ���ϸ��� ���� ���� ��� ��� ����

		m_pCopyUnit->m_strRelativePath = m_FilePath;
	}


	// �ؽ�ó ����Ʈ�� �߰� 
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
			m_TextureListBox.AddString(szFileName); // ����Ʈ�� �߰�
		}

	}

	UpdateData(FALSE);
}


void UnitTool_Monster::OnLbnSelchangeListMonsterTexture()
{
	UpdateData(TRUE);

	CString			strSelectName;

	int	iSelect = m_TextureListBox.GetCurSel(); // ����Ʈ ��Ʈ�� ������ ���� ���õ� �׸��� �̸����� ���� ���� �����´�.

	if (LB_ERR == iSelect)
		return;

	m_TextureListBox.GetText(iSelect, strSelectName); // ���õ� �׸��� �̸��� �����´�.

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
			m_pCopyUnit->m_strRelativePath;
			m_pCopyUnit->m_strObjKey = strObjKey;
			m_pCopyUnit->m_strStateKey = strStateKey;

		}


	}
	m_pToolView->Invalidate(FALSE);

	UpdateData(FALSE);
}


void UnitTool_Monster::OnBnClickedButtonMonsterTexLoad()
{
	CFileDialog		Dlg(FALSE,	// TRUE(����), FALSE(�ٸ� �̸����� ����) ��� ����	
		L"png", // defaule ���� Ȯ���ڸ�
		L"*.png", // ��ȭ ���ڿ� ǥ�õ� ���� ���ϸ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(�б����� üũ�ڽ� ����), OFN_OVERWRITEPROMPT(�ߺ����� ���� �� ���޼��� ����)
		L"Data Files(*.png) | *.png||",  // ��ȭ ���ڿ� ǥ�õ� ���� ���� '�޺� �ڽ��� ��µ� ���ڿ� | ���� ����� ���͸� ���ڿ� ||'
		this); // �θ� ������ �ּ�

	TCHAR	szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Texture\\Object");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		CString		strTemp = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = strTemp.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		CloseHandle(hFile);
	}
}


void UnitTool_Monster::OnLbnSelchangeListMonster()
{
	m_iCurUnitListIndex = m_UnitListBox.GetCurSel();

	if (0 > m_iCurUnitListIndex)
	{
		AfxMessageBox(L"Index Range Error");
		return;
	}

	CUnit* pSelectedUnit = m_vecUnit[m_iCurUnitListIndex];

	m_pCopyUnit = pSelectedUnit;

	if (nullptr == pSelectedUnit)
	{
		AfxMessageBox(L"None Selected Unit In Unit List");
		return;
	}

	Init_Dlg(m_pCopyUnit); // ���õ� �׸��� �������� ���̾�α׸� �����Ѵ�.
}


HRESULT UnitTool_Monster::Load_DB()
{
	return S_OK;

	HANDLE	hFile = CreateFile(L"\\Data\\01.Object", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD	dwByte = 0;
	CUnit*	pUnit = nullptr;

	while (true)
	{
		pUnit = new CUnit;
		
		ReadFile(hFile, &(m_pCopyUnit->m_tInfo)				, sizeof(INFO)		, &dwByte, nullptr);
		ReadFile(hFile, &(m_pCopyUnit->m_tStat)				, sizeof(STAT)		, &dwByte, nullptr);
		ReadFile(hFile, &(m_pCopyUnit->m_tFrame)			, sizeof(FRAME)		, &dwByte, nullptr);
		ReadFile(hFile, &(m_pCopyUnit->m_eType)				, sizeof(OBJ_TYPE)	, &dwByte, nullptr);
		ReadFile(hFile, &(m_pCopyUnit->m_tStat)				, sizeof(OBJ_STATE)	, &dwByte, nullptr);
		ReadFile(hFile, &(m_pCopyUnit->m_strRelativePath)	, sizeof(CString)	, &dwByte, nullptr);
		ReadFile(hFile, &(m_pCopyUnit->m_strObjKey)			, sizeof(CString)	, &dwByte, nullptr);
		ReadFile(hFile, &(m_pCopyUnit->m_strStateKey)		, sizeof(CString)	, &dwByte, nullptr);

		if (0 == dwByte)
		{
			Safe_Delete(pUnit);
			break;
		}

		m_vecUnit.push_back(pUnit);
		m_UnitListBox.AddString(pUnit->m_tStat.strName);
	}

	CloseHandle(hFile);
	
	

	return S_OK;
}


void UnitTool_Monster::OnBnClickedButtonMonsterSaveDb()
{
	// ���̾�α� ����
	CFileDialog		Dlg(FALSE,	// TRUE(����), FALSE(�ٸ� �̸����� ����) ��� ����	
		L"dat", // defaule ���� Ȯ���ڸ�
		L"*.dat", // ��ȭ ���ڿ� ǥ�õ� ���� ���ϸ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(�б����� üũ�ڽ� ����), OFN_OVERWRITEPROMPT(�ߺ����� ���� �� ���޼��� ����)
		L"Data Files(*.dat) | *.dat||",  // ��ȭ ���ڿ� ǥ�õ� ���� ���� '�޺� �ڽ��� ��µ� ���ڿ� | ���� ����� ���͸� ���ڿ� ||'
		this); // �θ� ������ �ּ�

	TCHAR	szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data\\01.Object");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		CString		strTemp = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = strTemp.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD dwByte = 0;

		WriteFile(hFile, &(m_pCopyUnit->m_tInfo), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &(m_pCopyUnit->m_tStat), sizeof(STAT), &dwByte, nullptr);
		WriteFile(hFile, &(m_pCopyUnit->m_tFrame), sizeof(FRAME), &dwByte, nullptr);
		WriteFile(hFile, &(m_pCopyUnit->m_eType), sizeof(OBJ_TYPE), &dwByte, nullptr);
		WriteFile(hFile, &(m_pCopyUnit->m_tStat), sizeof(OBJ_STATE), &dwByte, nullptr);
		WriteFile(hFile, &(m_pCopyUnit->m_strRelativePath), sizeof(CString), &dwByte, nullptr);
		WriteFile(hFile, &(m_pCopyUnit->m_strObjKey), sizeof(CString), &dwByte, nullptr);
		WriteFile(hFile, &(m_pCopyUnit->m_strStateKey), sizeof(CString), &dwByte, nullptr);

		CloseHandle(hFile);
	}
}


void UnitTool_Monster::OnCbnSelchangeComboMonsterType()
{
	m_pCopyUnit->m_eType = (OBJ_TYPE)m_ComboUnitType.GetCurSel();
}
