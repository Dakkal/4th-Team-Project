
// ToolView.h : CToolView Ŭ������ �������̽�
//

#pragma once


/* Together */
#include "Include.h"
#include "Terrain.h"
class CToolDoc;


/* HEEJUNE */



/* CHAN */
#include "Unit.h"


class CToolView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

// Ư���Դϴ�.
public:
	CToolDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();

public:
	CTerrain*			m_pTerrain;

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

/*-----------------------------------------------------------------------------------------------*/


public: 

/* Together */

	// ���� �ٲ� �� ȣ��Ǵ� �Լ� (�߰����� ����Ʈ �Ű������̹Ƿ�, �߰����� ������� ��� �Ǹ� �Ű������� ������).
	HRESULT	Change_Tab(const TOP_TAB_TYPE& _eTopTab, const MID_TAB_TYPE& _eMidTab = MID_TAB_TYPE::NONE); 

	TOP_TAB_TYPE m_eCurTopTab;
	MID_TAB_TYPE m_eCurMidTab;


/* HEEJUNE */
#pragma region TileTool

	


#pragma endregion


/* CHAN */

#pragma region UnitTool

	CUnit* m_pRenderUnit = nullptr;  


#pragma endregion



};

#ifndef _DEBUG  // ToolView.cpp�� ����� ����
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

// �Ϻΰ� �ƴ� ��ü �� Ÿ���� �̴ϸʿ� ����ؿ���