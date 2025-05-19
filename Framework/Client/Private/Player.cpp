#include "Player.h"

#include "GameInstance.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject{ pGraphic_Device }
{
}

CPlayer::CPlayer(const CPlayer& Prototype)
	:	CGameObject { Prototype }
{
}

HRESULT CPlayer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlayer::Initialize(void* pArg)
{
	if (FAILED(Ready_Components()))
		return E_FAIL;

	return S_OK;
}

void CPlayer::Priority_Update(_float fTimeDelta)
{
}

void CPlayer::Update(_float fTimeDelta)
{
    if (GetKeyState(VK_UP) < 0)
    {
        m_pTransformCom->Go_Straight(fTimeDelta);
    }

    if (GetKeyState(VK_DOWN) < 0)
    {
        m_pTransformCom->Go_Backward(fTimeDelta);
    }

    if (GetKeyState(VK_LEFT) < 0)
    {
        m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta * -1.f);
    }

    if (GetKeyState(VK_RIGHT) < 0)
    {
        m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta);
    }
}

void CPlayer::Late_Update(_float fTimeDelta)
{
    m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_PRIORITY, this);
}

HRESULT CPlayer::Render()
{

    m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    m_pTransformCom->Bind_Matrix();

    if (FAILED(m_pTextureCom->Bind_Texture(0)))
        return E_FAIL;

    m_pVIBufferCom->Bind_Buffers();

    m_pVIBufferCom->Render();

    return S_OK;
	return S_OK;
}

HRESULT CPlayer::Ready_Components()
{
    if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Rect"),
        TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
        return E_FAIL;

    /* For.Com_Texture */
    if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Texture_Player"),
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

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
    CPlayer* pInstance = new CPlayer(pGraphic_Device);

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX(TEXT("Failde to Created : CPlayer"));
        Safe_Release(pInstance);
    }

    return pInstance;
}

CGameObject* CPlayer::Clone(void* pArg)
{
    CPlayer* pInstance = new CPlayer(*this);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX(TEXT("Failde to Cloned : CPlayer"));
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CPlayer::Free()
{
    __super::Free();

    Safe_Release(m_pVIBufferCom);
    Safe_Release(m_pTransformCom);
    Safe_Release(m_pTextureCom);
}
