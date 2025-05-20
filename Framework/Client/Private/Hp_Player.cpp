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

	m_iMaxHp = 100;
	m_iCulHp = m_iMaxHp;
	m_iPreHp = m_iCulHp;

	UIOBJECT_DESC Desc{};

	Desc.fSizeX = 180;
	Desc.fSizeY = 20;
	Desc.fX = 30 + Desc.fSizeX * 0.5f;
	Desc.fY = 25 + Desc.fSizeY * 0.5f;
	
	if (FAILED(__super::Initialize(&Desc)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	m_pTransformCom->Scaling(m_fSizeX, m_fSizeY, 1.f);
	m_pTransformCom->Set_State(STATE::POSITION, _float3(m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.f));

	return S_OK;
}

void CHp_Player::Priority_Update(_float fTimeDelta)
{
	if (GetKeyState('Z') < 0)
	{
		m_iCulHp -= 1;
	}
	if (GetKeyState('X') < 0)
	{
		m_iCulHp += 1;
	}
}

void CHp_Player::Update(_float fTimeDelta)
{
	Update_Hp();
}

void CHp_Player::Late_Update(_float fTimeDelta)
{
	Update_Hp();
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_UI, this);
}

HRESULT CHp_Player::Render()
{
	m_pTransformCom->Bind_Matrix();
	m_pVIBufferCom->Bind_Buffers();
	m_pGraphic_Device->SetTexture(0, NULL);
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

	return S_OK;
}

void CHp_Player::Update_Hp()
{
	if (m_iCulHp != m_iPreHp)
	{
		if (m_iCulHp >= m_iMaxHp)
		{
			m_iCulHp = m_iMaxHp;
			m_pTransformCom->Scaling(m_fSizeX, m_fSizeY, 1.f);
			m_pTransformCom->Set_State(STATE::POSITION, _float3(m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.f));
		}
		else if(m_iCulHp <= 0)
		{
			m_iCulHp = 0;
			m_pTransformCom->Scaling(0.f, m_fSizeY, 1.f);
			m_pTransformCom->Set_State(STATE::POSITION, _float3(m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.f));
		}
		else
		{
			float fSizeX = m_fSizeX * (float(m_iCulHp) / (float)m_iMaxHp);
			m_pTransformCom->Scaling(fSizeX, m_fSizeY, 1.f);
			m_pTransformCom->Set_State(STATE::POSITION, _float3(m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.f));
		}
		m_iPreHp = m_iCulHp;
	}
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
