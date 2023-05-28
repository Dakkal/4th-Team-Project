#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual HRESULT		Initialize()							PURE;
	virtual int			Update()								PURE;
	virtual void		Late_Update()							PURE;
	virtual void		Render()								PURE;
	virtual	void		Tool_Render(const D3DXVECTOR3& _vWorld)							PURE;
	virtual void		Release()								PURE;

public:

	// ���� ��������� public���� �δ� ���� ���� ���� ������ �׼��� �޼���� ������� �ʵ��� �Ѵ�.
	// Ŭ���̾�Ʈ���� ����� ���� ����� ���ܵд�.

	/*CString				Get_ObjKey() const		{ return m_strObjKey; }
	CString				Get_StateKey() const	{ return m_strStateKey; }
	INFO				Get_Info(void) const	{ return m_tInfo; }
	STAT				Get_Stat() const		{ return m_tStat; }
	FRAME				Get_Frame() const		{ return m_tFrame; }
	OBJ_TYPE			Get_Type() const		{ return m_eType; }
	OBJ_STATE			Get_State() const		{ return m_eState; }*/

protected:
	void				Move_Frame(void); // �ִϸ��̼� ����

public:
	INFO				m_tInfo; 
	STAT				m_tStat;
	FRAME				m_tFrame;
	OBJ_TYPE			m_eType = OBJ_TYPE::TYPEEND;
	OBJ_STATE			m_eState = OBJ_STATE::TYPEEND;


	/* ���� �̷��� ����ϴ� �������� �ƴ����� ���ݸ� �̷��� ����ϵ��� �Ѵ�. */

	CString				m_strPath			= L""; // ���� ���
	CString				m_strObjKey			= L""; // ����Ž���⿡�� ������Ʈ ������ (������ �ؽ�Ʈ �Ŵ��� ������Ʈ Ű������ ���)
	CString				m_strStateKey		= L""; // ����Ž���Կ��� ������Ʈ ���� ��, ������Ʈ ������ (������ �ؽ�Ʈ �Ŵ��� ������Ʈ ������Ʈ Ű������ ���)

};

