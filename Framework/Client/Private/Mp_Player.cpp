#include "Mp_Player.h"
#include "GameInstance.h"

CMp_Player::CMp_Player(LPDIRECT3DDEVICE9 pGraphic_Device) : CUIObject(pGraphic_Device)
{
}

CMp_Player::CMp_Player(const CMp_Player& Prototype) : CUIObject(Prototype)
{
}

HRESULT CMp_Player::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CMp_Player::Initialize(void* pArg)
{
	m_iMaxMp = 100;
	m_iCulMp = m_iMaxMp;
	m_iPreMp = m_iCulMp;

	UIOBJECT_DESC Desc{};

	Desc.fSizeX = 180;
	Desc.fSizeY = 20;
	Desc.fX = 0;
	Desc.fY = 10;

	if (FAILED(__super::Initialize(&Desc)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	m_pTransformCom->Scaling(m_fSizeX, m_fSizeY, 1.f);
	__super::Update_Position(g_iWinSizeX, g_iWinSizeY);

	return S_OK;
}

void CMp_Player::Priority_Update(_float fTimeDelta)
{
	if (GetKeyState('C') < 0)
	{
		m_iCulMp -= 1;
	}
	if (GetKeyState('V') < 0)
	{
		m_iCulMp += 1;
	}
}

void CMp_Player::Update(_float fTimeDelta)
{
}

void CMp_Player::Late_Update(_float fTimeDelta)
{
	Update_Mp();
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_UI, this);
}

HRESULT CMp_Player::Render()
{
	m_pTransformCom->Bind_Matrix();
	m_pVIBufferCom->Bind_Buffers();
	__super::Begin();
	m_pVIBufferCom->Render();
	__super::End();

	return S_OK;
}


HRESULT CMp_Player::Ready_Components()
{
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_Component_VIBuffer_Rect_UI_Player_Mp"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom))))
		return E_FAIL;

	return S_OK;
}

void CMp_Player::Update_Mp()
{
	if (m_iCulMp != m_iPreMp)
	{
		if (m_iCulMp >= m_iMaxMp)
		{
			m_iCulMp = m_iMaxMp;
			m_pTransformCom->Scaling(m_fSizeX, m_fSizeY, 1.f);
		}
		else if (m_iCulMp <= 0)
		{
			m_iCulMp = 0;
			float fSizeX = m_fSizeX * (0.1f / (float)m_iMaxMp);
			m_pTransformCom->Scaling(fSizeX, m_fSizeY, 1.f);
		}
		else
		{
			float fSizeX = m_fSizeX * (float(m_iCulMp) / (float)m_iMaxMp);
			m_pTransformCom->Scaling(fSizeX, m_fSizeY, 1.f);
		}
		m_iPreMp = m_iCulMp;
	}
}

CMp_Player* CMp_Player::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CMp_Player* pInstance = new CMp_Player(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CMp_Player"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CUIObject* CMp_Player::Clone(void* pArg)
{
	CMp_Player* pInstance = new CMp_Player(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Clone : CMp_Player"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMp_Player::Free()
{
	__super::Free();
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
