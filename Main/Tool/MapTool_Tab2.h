#pragma once


// CMapTool_Tab2 dialog

class CMapTool_Tab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CMapTool_Tab2)

public:
	CMapTool_Tab2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMapTool_Tab2();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
