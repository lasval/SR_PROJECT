#include "Hud_Exp_Frame.h"
#include "GameInstance.h"

CHud_Exp_Frame::CHud_Exp_Frame(LPDIRECT3DDEVICE9 pGraphic_Device) : CUIObject(pGraphic_Device)
{
}

CHud_Exp_Frame::CHud_Exp_Frame(const CHud_Exp_Frame& Prototype) : CUIObject(Prototype)
{
}

HRESULT CHud_Exp_Frame::Initialize_Prototype(LEVEL eLevel)
{
	m_eLevel = eLevel;

	if (FAILED(Ready_Prototype(eLevel)))
		return E_FAIL;

	return S_OK;
}

HRESULT CHud_Exp_Frame::Initialize(void* pArg)
{
	UIOBJECT_DESC Desc{};

	Desc.fSizeX = g_iWinSizeX;
	Desc.fSizeY = 15;
	Desc.fX = Desc.fSizeX * 0.5f;
	Desc.fY = g_iWinSizeY - Desc.fSizeY * 0.5f;
	Desc.fZ = 0.f;
	Desc.iWinSizeX = g_iWinSizeX;
	Desc.iWinSizeY = g_iWinSizeY;

	m_fSizeY2 = Desc.fSizeY * 0.5;
	if (FAILED(__super::Initialize(&Desc)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	m_pTransformCom->Scaling(m_fSizeX, m_fSizeY, 1.f);
	__super::Update_Position();

	if (FAILED(Ready_Children()))
		return E_FAIL;

	return S_OK;
}

void CHud_Exp_Frame::Priority_Update(_float fTimeDelta)
{
	__super::Priority_Update(fTimeDelta);
}

void CHud_Exp_Frame::Update(_float fTimeDelta)
{
	__super::Update(fTimeDelta);
}

void CHud_Exp_Frame::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_UI, this);
	

	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_UI, this);
	

	__super::Late_Update(fTimeDelta);
}

HRESULT CHud_Exp_Frame::Render()
{
	Render_Buffer1();
	Render_Buffer2();

	return S_OK;
}

HRESULT CHud_Exp_Frame::Ready_Components()
{
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_Component_VIBuffer_Rect_UI_Hud_Exp_Fream_1"),
		TEXT("Com_VIBuffer1"), reinterpret_cast<CComponent**>(&m_pVIBufferCom1))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_Component_VIBuffer_Rect_UI_Hud_Exp_Fream_2"),
		TEXT("Com_VIBuffer2"), reinterpret_cast<CComponent**>(&m_pVIBufferCom2))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CHud_Exp_Frame::Ready_Prototype(LEVEL eLevel)
{
	return S_OK;
}

HRESULT CHud_Exp_Frame::Ready_Children()
{
	return S_OK;
}

void CHud_Exp_Frame::Render_Buffer1()
{
	m_pGraphic_Device->SetTexture(0, NULL);

	m_pTransformCom->Bind_Matrix();
	m_pVIBufferCom1->Bind_Buffers();

	__super::Begin();
	m_pVIBufferCom1->Render();
	__super::End();
}

void CHud_Exp_Frame::Render_Buffer2()
{
	m_pTransformCom->Scaling(m_fSizeX, m_fSizeY2, 1.f);
	
	_float3 vOriginPos = m_pTransformCom->Get_State(STATE::POSITION);

	m_pTransformCom->Set_State(STATE::POSITION, _float3{ vOriginPos.x , vOriginPos.y - (m_fSizeY2 * 0.5f), vOriginPos.z });

	m_pTransformCom->Bind_Matrix();
	m_pVIBufferCom2->Bind_Buffers();

	__super::Begin();
	m_pVIBufferCom2->Render();
	__super::End();

	m_pTransformCom->Scaling(m_fSizeX, m_fSizeY, 1.f);
	m_pTransformCom->Set_State(STATE::POSITION, _float3{ vOriginPos.x , vOriginPos.y, vOriginPos.z });
}


CHud_Exp_Frame* CHud_Exp_Frame::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eLevel)
{
	CHud_Exp_Frame* pInstance = new CHud_Exp_Frame(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype(eLevel)))
	{
		MSG_BOX(TEXT("Failed to Create : CHud_Exp_Frame"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CUIObject* CHud_Exp_Frame::Clone(void* pArg)
{
	CHud_Exp_Frame* pInstance = new CHud_Exp_Frame(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Clone : CHud_Exp_Frame"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CHud_Exp_Frame::Free()
{
	__super::Free();
	Safe_Release(m_pVIBufferCom1);
	Safe_Release(m_pVIBufferCom2);
}
