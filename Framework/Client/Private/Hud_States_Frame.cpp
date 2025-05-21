#include "Hud_States_Frame.h"
#include "GameInstance.h"

CHud_States_Frame::CHud_States_Frame(LPDIRECT3DDEVICE9 pGraphic_Device) : CUIObject(pGraphic_Device)
{
}

CHud_States_Frame::CHud_States_Frame(const CHud_States_Frame& Prototype) : CUIObject(Prototype)
{
}

HRESULT CHud_States_Frame::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CHud_States_Frame::Initialize(void* pArg)
{
	UIOBJECT_DESC Desc{};

	Desc.fSizeX = 200;
	Desc.fSizeY = 60;
	Desc.fX = 20 + Desc.fSizeX * 0.5f;
	Desc.fY = 20 + Desc.fSizeY * 0.5f;

	if (FAILED(__super::Initialize(&Desc)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	m_pTransformCom->Scaling(m_fSizeX, m_fSizeY, 1.f);
	m_pTransformCom->Set_State(STATE::POSITION, _float3(m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.f));

	return S_OK;
}

void CHud_States_Frame::Priority_Update(_float fTimeDelta)
{
}

void CHud_States_Frame::Update(_float fTimeDelta)
{
}

void CHud_States_Frame::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_UI, this);
}

HRESULT CHud_States_Frame::Render()
{
	m_pTransformCom->Bind_Matrix();
	m_pVIBufferCom->Bind_Buffers();
	m_pGraphic_Device->SetTexture(0, NULL);
	__super::Begin();
	m_pVIBufferCom->Render();
	__super::End();

	return S_OK;
}

HRESULT CHud_States_Frame::Ready_Components()
{
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_Component_VIBuffer_Rect_UI_Player_HpFream"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom))))
		return E_FAIL;

	return S_OK;
}

CHud_States_Frame* CHud_States_Frame::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CHud_States_Frame* pInstance = new CHud_States_Frame(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CHud_States_Frame"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CUIObject* CHud_States_Frame::Clone(void* pArg)
{
	CHud_States_Frame* pInstance = new CHud_States_Frame(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Clone : CHud_States_Frame"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CHud_States_Frame::Free()
{
	__super::Free();
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
