#pragma once


#pragma region HEEJUNE


#pragma endregion


#pragma region CHAN

#define		UNIT_CX		100
#define		UNIT_CY		100

#define		UNIT_MAX_HP		300.f
#define		UNIT_MAX_AD		100.f
#define		UNIT_MAX_SPEED	500.f

#pragma endregion



#define		TAB_HEIGHT	30
#define		TAB_WIDTH	10


#define		TOOL_CX		1000

//#define		WINCX		1280
//#define		WINCY		720

#define		WINCX		1400
#define		WINCY		1200


#define		OBJ_NOEVENT		0
#define		OBJ_DEAD		1

#define		VK_MAX			0xff

#define		TILECX			160
#define		TILECY			80

#define		TILEX			20
#define		TILEY			30

#define		MIN_STR			64
#define		MAX_STR			256

#define		RUBY			0x01		// -> 0001
#define		DIAMOND			0x02		// -> 0010
#define		SAPPHIRE		0x04		// -> 0100

//Ÿ�Ͽɼ�
#define		NONETILE		0x00
#define		BLOCKTILE		0x01
#define		DAMAGETILE		0x02





#define ERR_MSG(message)								\
::MessageBox(nullptr, message, L"error", MB_OK)

#define NO_COPY(ClassName)								\
ClassName(const ClassName&) = delete;					\
ClassName& operator=(const ClassName&) = delete;

#define DECLARE_SINGLETON(ClassName)					\
		NO_COPY(ClassName)								\
public :												\
	static ClassName* Get_Instance();					\
	static void		  Destroy_Instance();				\
private:												\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)					\
ClassName* ClassName::m_pInstance = nullptr;			\
ClassName* ClassName::Get_Instance()					\
{														\
	if (nullptr == m_pInstance)							\
		m_pInstance = new ClassName;					\
	return m_pInstance;									\
}														\
void ClassName::Destroy_Instance()						\
{														\
	if(nullptr != m_pInstance)							\
	{													\
		delete m_pInstance;								\
		m_pInstance = nullptr;							\
	}													\
}


extern HWND		g_hWnd;

// ����� ���ÿ� �ʱ�ȭ �Ұ���, ���� ����� ���������� �ڷ���, ��������� ��ġ�ϴ� ���¿����� ��� ����