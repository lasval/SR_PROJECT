#include "Hp_Player.h"
#include "GameInstance.h"

CHp_Player::CHp_Player(LPDIRECT3DDEVICE9 pGraphic_Device) : CUIObject( pGraphic_Device )
{
}

CHp_Player::CHp_Player(const CHp_Player& Prototype) : CUIObject( Prototype )
{
}

HRESULT CHp_Player::Initialize_Prototype()
{
 	return S_OK;
}

HRESULT CHp_Player::Initialize(void* pArg)
{
	m_iCulHp = 100;
	UIOBJECT_DESC Desc{};

	Desc.fSizeX = 180;
	Desc.fSizeY = 20;
	Desc.fX = 0;
	Desc.fY = -15;
	
	if (FAILED(__super::Initialize(&Desc)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	m_pTransformCom->Scaling(m_fSizeX, m_fSizeY, 1.f);
	__super::Update_Position(g_iWinSizeX, g_iWinSizeY);
	m_vOriginPos = m_pTransformCom->Get_State(STATE::POSITION);
	m_vOriginSize = m_pTransformCom->Get_Scaled();
	return S_OK;
}

void CHp_Player::Priority_Update(_float fTimeDelta)
{
	
	if (GetKeyState('Z') < 0)
	{
		--m_iCulHp;
	}
	if (GetKeyState('X') < 0)
	{
		++m_iCulHp;
	}
}

void CHp_Player::Update(_float fTimeDelta)
{
	
}

void CHp_Player::Late_Update(_float fTimeDelta)
{
	m_pProgressCom->Progress_UpdateX(m_iCulHp, m_vOriginPos, m_vOriginSize);
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_UI, this);
}

HRESULT CHp_Player::Render()
{
	m_pTransformCom->Bind_Matrix();
	m_pVIBufferCom->Bind_Buffers();
	__super::Begin();
	m_pVIBufferCom->Render();
	__super::End();

	return S_OK;
}


HRESULT CHp_Player::Ready_Components()
{
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_Component_VIBuffer_Rect_UI_Player_Hp"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom))))
		return E_FAIL;

	CProgressBar::PROGRESSBAR_DESC ProgressDesc{};
	ProgressDesc.pTransformCom = m_pTransformCom;
	ProgressDesc.iMaxValue = 100;
	ProgressDesc.iCulValue = 100;

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_ProgressBar"),
		TEXT("Com_ProgressBar"), reinterpret_cast<CComponent**>(&m_pProgressCom), &ProgressDesc)))
		return E_FAIL;

	return S_OK;
}


CHp_Player* CHp_Player::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CHp_Player* pInstance = new CHp_Player(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CHp_Player"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CUIObject* CHp_Player::Clone(void* pArg)
{
	CHp_Player* pInstance = new CHp_Player(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Clone : CHp_Player"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CHp_Player::Free()
{
	__super::Free();
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
