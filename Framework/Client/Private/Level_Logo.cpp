#include "Level_Logo.h"
#include "GameInstance.h"
#include "Level_Loading.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

CLevel_Logo::CLevel_Logo(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CLevel { pGraphic_Device }
{
}

HRESULT CLevel_Logo::Initialize()
{
	g_hCursor = LoadCursorFromFile(L"Resources/Sephiria/UI/Cursor/Cursor_Combat.cur");

	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;

	return S_OK;
}

void CLevel_Logo::Update(_float fTimeDelta)
{
	if (GetKeyState(VK_RETURN) & 0x8000)
	{
		if(FAILED(m_pGameInstance->Open_Level(ENUM_CLASS(LEVEL::LEVEL_LOADING), CLevel_Loading::Create(m_pGraphic_Device, LEVEL::LEVEL_GAMEPLAY))))
			return;
	}

	if (m_pGameInstance->IsKeyPressedOnce('P'))
	{
		TEST* a = m_pGameInstance->Ping();
		string c = a->title;
		string d = a->desc;
		int b = 1;
	}

	if (m_pGameInstance->IsKeyPressedOnce('U'))
	{
		list<USER*> a = m_pGameInstance->Get_AllUsers();
		for (auto& user : a)
		{
			int id = user->iId;
			string name = user->sName;
			string nickname = user->sNickname;
			string password = user->sPassword;
		}
		int b = 1;
	}

		

	return;
}



HRESULT CLevel_Logo::Render()
{
	SetWindowText(g_hWnd, TEXT("로고레벨입니다."));

	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_BackGround(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::LEVEL_LOGO), strLayerTag,
		ENUM_CLASS(LEVEL::LEVEL_LOGO), TEXT("Prototype_GameObject_BackGround"))))
		return E_FAIL;

	return S_OK;
}

CLevel_Logo* CLevel_Logo::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLevel_Logo* pInstance = new CLevel_Logo(pGraphic_Device);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed to Created : CLevel_Logo"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Logo::Free()
{
	__super::Free();

}
