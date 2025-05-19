#include "UI_Test.h"
#include "GameInstance.h"

CUI_Test::CUI_Test(LPDIRECT3DDEVICE9 pGraphic_Device) : CGameObject(pGraphic_Device)
{
}

CUI_Test::CUI_Test(const CUI_Test& Prototype) : CGameObject(Prototype)
{
}

HRESULT CUI_Test::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CUI_Test::Initialize(void* pArg)
{
	if (FAILED(Ready_Components()))
		return E_FAIL;
	return S_OK;
}

void CUI_Test::Priority_Update(_float fTimeDelta)
{
}

void CUI_Test::Update(_float fTimeDelta)
{

}

void CUI_Test::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_UI, this);
}

HRESULT CUI_Test::Render()
{
	m_pTransformCom->Bind_Matrix();

	if (FAILED(m_pTextureCom->Bind_Texture(0)))
		return E_FAIL;

	m_pVIBufferCom->Bind_Buffers();
	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CUI_Test::Ready_Components()
{
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Rect"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_GAMEPLAY), TEXT("Prototype_Component_Texture_UI_Test"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	CTransform::TRANSFORM_DESC TransformDesc{};
	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.f);

	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom), &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

CUI_Test* CUI_Test::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CUI_Test* pInstance = new CUI_Test(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CUI_Test"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CUI_Test::Clone(void* pArg)
{
	CUI_Test* pInstance = new CUI_Test(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Clone : CUI_Test"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CUI_Test::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCom);
}
