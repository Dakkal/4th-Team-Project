#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CTileTool_Tab3 dialog
class CTerrain_Act1;
class CTerrain_Act2;
class CTerrain_Act3;
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
public:

	virtual BOOL OnInitDialog();

	afx_msg void OnPush_Tile();
	afx_msg void OnClear_Tile();
	afx_msg void OnSaveDB_Tile();
	afx_msg void OnDestroy();
	afx_msg void OnSet_TileDamage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnActTileChange();

public:

	CComboBox		m_Combo_Tile;
	CListBox		m_List_Tile;
	CButton			m_Check_Tile[3];
	CSpinButtonCtrl m_Spin_Tile;

public:
	
	int m_iTileDamage;
	int m_iDrawId_First;
	int m_iDrawId_Last;
	
	int	m_iDrawID = 0;

private:
	void		Sort_File();
	
};
