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

	// 툴은 멤버변수를 public으로 두는 것을 권장 따라서 별도의 액세스 메서드는 사용하지 않도록 한다.
	// 클라이언트에서 사용할 것을 대비해 남겨둔다.

	/*CString				Get_ObjKey() const		{ return m_strObjKey; }
	CString				Get_StateKey() const	{ return m_strStateKey; }
	INFO				Get_Info(void) const	{ return m_tInfo; }
	STAT				Get_Stat() const		{ return m_tStat; }
	FRAME				Get_Frame() const		{ return m_tFrame; }
	OBJ_TYPE			Get_Type() const		{ return m_eType; }
	OBJ_STATE			Get_State() const		{ return m_eState; }*/

protected:
	void				Move_Frame(void); // 애니메이션 관련

public:
	INFO				m_tInfo; 
	STAT				m_tStat;
	FRAME				m_tFrame;
	OBJ_TYPE			m_eType = OBJ_TYPE::TYPEEND;
	OBJ_STATE			m_eState = OBJ_STATE::TYPEEND;
	CString				m_strObjKey = L""; // 파일탐색기에서 오브젝트 폴더명
	CString				m_strStateKey = L""; // 파일탐색게에서 오브젝트 폴더 안, 스테이트 폴더명

};

