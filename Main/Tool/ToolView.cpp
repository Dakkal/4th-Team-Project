
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"
#include "Device.h"
#include "TextureMgr.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND		g_hWnd;

// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView() : m_pTerrain(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToolView::~CToolView()
{
}

void CToolView::OnInitialUpdate()
{
	g_hWnd = m_hWnd;

	CScrollView::OnInitialUpdate();

	//// SetScrollSizes : 스크롤 바의 사이즈를 지정하는 함수
	//// MM_TEXT : 픽셀 단위로 조정하겠다는 옵션
	//// 스크롤 가로 사이즈, 스크롤 세로 사이즈

	SetScrollSizes(MM_TEXT, CSize(WINCX, WINCY));


	//// AfxGetMainWnd : 현재의 메인 창의 주소를 반환하는 함수
	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWnd{};

	// GetWindowRect : 현재 창의 렉트 정보를 얻어오는 함수
	pMainFrm->GetWindowRect(&rcWnd);

	// SetRect : 매개 변수대로 렉트의 정보를 지정하는 함수
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT	rcMainView{};

	// GetClientRect : 현재 view창의 RECT 정보를 얻어오는 함수
	GetClientRect(&rcMainView);

	float		fRowFrm = float(rcWnd.right - rcMainView.right);
	float		fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	//SetWindowPos : 매개 변수대로 새롭게 윈도우 위치와 크기를 조정하는 함수
	 // (배치할 윈도우의 Z순서에 대한 포인터, X좌표, Y좌표, 가로 크기, 세로 크기, 배치할 윈도우의 크기및 위치 지정 옵션)
	pMainFrm->SetWindowPos(nullptr,  // 순서 변경을 안하기 때문에 NULL
							0, 
							0, 
							int(WINCX + fRowFrm),
							int(WINCY + fColFrm), 
							SWP_NOZORDER);	// 현재 순서를 유지하겠다는 옵션

	//// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (FAILED(CDevice::Get_Instance()->Initialize()))
	{
		AfxMessageBox(L"Device Create Failed");
		return;
	}


	// 이걸로 사이즈 조절했는데 맞는 걸까?

	/*GetParentSplitter(this, FALSE)->SetColumnInfo(0, 400, 10);
	GetParentSplitter(this, FALSE)->RecalcLayout();*/


	m_eCurTopTab = TOP_TAB_TYPE::UNIT;
	m_eCurMidTab = MID_TAB_TYPE::PLAYER;

	//if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Cube.png", TEX_SINGLE, L"Cube")))
	//{
	//	AfxMessageBox(L"CubeTexture Create Failed");
	//	return;
	//}

	//m_pTerrain = new CTerrain;

	//if (FAILED(m_pTerrain->Initialize()))
	//{
	//	AfxMessageBox(L"Terrain Init Failed");
	//	return;
	//}

	//m_pTerrain->Set_MainView(this);

}

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	RECT	rc{};
	GetClientRect(&rc);
	int CX = rc.right - rc.left;
	int CY = rc.bottom - rc.top;

	CDevice::Get_Instance()->Render_Begin();

	switch (m_eCurTopTab)
	{
		case TOP_TAB_TYPE::UNIT:
		{
			// Draw Line
			{
				IDirect3DDevice9* g_pd3dDevice = CDevice::Get_Instance()->Get_Device();
				ID3DXLine* g_pLine;

				D3DXCreateLine(g_pd3dDevice, &g_pLine); // 라인 생성
				g_pLine->SetWidth(2); // 굵기 설정
				g_pLine->Begin();

				D3DXVECTOR2 vList1[] =
				{
					D3DXVECTOR2(CX * 0.5f, 0),
					D3DXVECTOR2(CX * 0.5f, WINCY),
				};
				g_pLine->Draw(vList1, 2, D3DCOLOR_XRGB(255, 0, 0));

				D3DXVECTOR2 vList2[] =
				{
					D3DXVECTOR2(0, CY * 0.5f),
					D3DXVECTOR2(CX, CY * 0.5f),
				};
				g_pLine->Draw(vList2, 2, D3DCOLOR_XRGB(255, 0, 0));
				g_pLine->End();
			}
			switch (m_eCurMidTab)
			{
			case MID_TAB_TYPE::PLAYER:
			{

			}
			break;
			case MID_TAB_TYPE::MONSTER:
			{
				if (nullptr == m_pCopyUnit) break;
				D3DXVECTOR3 vCenter{ CX * 0.5f, CY * 0.5f, 0.f };
				m_pCopyUnit->Tool_Render(vCenter);
			}
			break;
			case MID_TAB_TYPE::ITEM:
			{

			}
			break;
			default:
				break;
			}
			break;
		case TOP_TAB_TYPE::TILE:
		{
			// HEEJUNE
		}
		break;
		case TOP_TAB_TYPE::MAP:
		{

		}
		break;
		default:
			break;
		}
	}

	CDevice::Get_Instance()->Render_End();
}
void CToolView::OnDestroy()
{

	CScrollView::OnDestroy();




	/* HEEJUNE */

	/* CHAN */
	if (nullptr != m_pCopyUnit)
		Safe_Delete(m_pCopyUnit);


	CTextureMgr::Get_Instance()->Destroy_Instance();
	CDevice::Get_Instance()->Destroy_Instance();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
#pragma region 안봐
BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기


// CToolView 그리기
#pragma endregion 안봐

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonDown(nFlags, point);

	switch (m_eCurTopTab)
	{
	case TOP_TAB_TYPE::UNIT:
		switch (m_eCurMidTab)
		{
		case MID_TAB_TYPE::PLAYER:
		{

		}
		break;
		case MID_TAB_TYPE::MONSTER:
		{

		}
		break;
		case MID_TAB_TYPE::ITEM:
		{

		}
		break;
		default:
			break;
		}
		break;
	case TOP_TAB_TYPE::TILE:
	{
		// HEEJUNE
	}
	break;
	case TOP_TAB_TYPE::MAP:
	{

	}
	break;
	default:
		break;
	}



	return;







	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	// point : 마우스 좌표를 갖고 있음.

	m_pTerrain->Tile_Change({ float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f }, 0);

	// Invalidate : 호출 시 윈도우에 WM_PAINT와 WM_ERASEBKGND 메세지를 발생 시킴, 이때 OnDraw함수를 다시 한번 호출
	// 인자가 FALSE : WM_PAINT만 발생
	// 인자가 TRUE : WM_PAINT와 WM_ERASEBKGND 메세지를 발생
	
	Invalidate(FALSE);


	// AfxGetMainWnd : 현재 쓰레드로부터 WND를 반환하는 함수
	//CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());

	// AfxGetApp : 메인 쓰레드를 갖고 있는 현재 메인 APP을 반환
	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());

	// GetParentFrame : 현재 VIEW를 둘러싸고 있는 상위 FrameWnd를 반환
	//CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(GetParentFrame());

	CMiniView*		pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));
	pMiniView->Invalidate(FALSE);
}

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	CScrollView::OnMouseMove(nFlags, point);
	switch (m_eCurTopTab)
	{
	case TOP_TAB_TYPE::UNIT:
		switch (m_eCurMidTab)
		{
		case MID_TAB_TYPE::PLAYER:
		{

		}
		break;
		case MID_TAB_TYPE::MONSTER:
		{

		}
		break;
		case MID_TAB_TYPE::ITEM:
		{

		}
		break;
		default:
			break;
		}
		break;
	case TOP_TAB_TYPE::TILE:
	{
		// HEEJUNE
	}
	break;
	case TOP_TAB_TYPE::MAP:
	{

	}
	break;
	default:
		break;
	}



	return;
	
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		m_pTerrain->Tile_Change({ float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f }, 0);
		Invalidate(FALSE);
		CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		CMiniView*		pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));
		pMiniView->Invalidate(FALSE);
	}

}

HRESULT CToolView::Change_Tab(const TOP_TAB_TYPE & _eTopTab, const MID_TAB_TYPE & _eMidTab)
{
	if(TOP_TAB_TYPE::TYPEEND == _eTopTab || MID_TAB_TYPE::TYPEEND == _eMidTab)
		return E_FAIL;

	Invalidate(FALSE);

	m_eCurTopTab = _eTopTab;
	m_eCurMidTab = _eMidTab;

	// 매개변수로 넘어온 탭으로 변경하기전 현재 상황에서 처리해야할 일들을 구현한다.
	switch (m_eCurTopTab)
	{
	case TOP_TAB_TYPE::UNIT:
	{
		switch (m_eCurMidTab)
		{
		case MID_TAB_TYPE::PLAYER:
		{

		}
		break;
		case MID_TAB_TYPE::MONSTER:
		{
			if (nullptr != m_pCopyUnit) break;

			m_pCopyUnit = new CUnit();
			m_pCopyUnit->Initialize();
			// Texture\01.Object\00.Player\00.Amazon\stand_8         0.png
			if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/01.Object/00.Player/00.Amazon/stand_8/%d.png", TEX_MULTI, L"Player", L"Stand", 1)))
			{
				AfxMessageBox(L"TileTexture Create Failed");
				return E_FAIL;
			}

		}
		break;
		case MID_TAB_TYPE::ITEM:
		{

		}
		break;
		default:
			break;
		}
	}
		break;
	case TOP_TAB_TYPE::TILE:
	{
		// HEEJUNE
	}
	break;
	case TOP_TAB_TYPE::MAP:
	{

	}
	break;
	default:
		break;
	}

	return S_OK;
}
