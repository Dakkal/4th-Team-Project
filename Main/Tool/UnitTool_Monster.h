#pragma once


// UnitTool_Monster dialog

class UnitTool_Monster : public CDialogEx
{
	DECLARE_DYNAMIC(UnitTool_Monster)

public:
	UnitTool_Monster(CWnd* pParent = NULL);   // standard constructor
	virtual ~UnitTool_Monster();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNIT_MONSTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
