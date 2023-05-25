#pragma once

#include "UnitTool.h"
#include "MapTool.h"
#include "afxcmn.h"
#include "UnitTool_Tab1.h"
#include "MapTool_Tab2.h"

// CMyForm �� ���Դϴ�.

class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

private:
	CFont		m_Font;
	CUnitTool	m_UnitTool;
	CMapTool	m_MapTool;

	CUnitTool_Tab1*	m_pUnitTool_Tab1;
	CMapTool_Tab2*	m_pMapTool_Tab2;

public:
	virtual void OnInitialUpdate();
	CTabCtrl m_tab;
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);


	afx_msg void OnDestroy();


	afx_msg void OnSize(UINT nType, int cx, int cy);
};


