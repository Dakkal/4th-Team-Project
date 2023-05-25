// UnitTool_Monster.cpp : implementation file
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool_Monster.h"
#include "afxdialogex.h"


// UnitTool_Monster dialog

IMPLEMENT_DYNAMIC(UnitTool_Monster, CDialogEx)

UnitTool_Monster::UnitTool_Monster(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_UNIT_MONSTER, pParent)
{

}

UnitTool_Monster::~UnitTool_Monster()
{
}

void UnitTool_Monster::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(UnitTool_Monster, CDialogEx)
END_MESSAGE_MAP()


// UnitTool_Monster message handlers
