#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
{
}


CObj::~CObj()
{
}

void CObj::Move_Frame(void)
{
	//m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;
}
