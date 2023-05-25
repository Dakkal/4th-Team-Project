#pragma once


// CUnitTool_Tab1 dialog

class CUnitTool_Tab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CUnitTool_Tab1)

public:
	CUnitTool_Tab1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUnitTool_Tab1();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
