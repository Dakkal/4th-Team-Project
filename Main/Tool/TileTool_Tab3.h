#pragma once


// CTileTool_Tab3 dialog

class CTileTool_Tab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CTileTool_Tab3)

public:
	CTileTool_Tab3(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTileTool_Tab3();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TILETOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
