// CCollider_OBB.cpp
#include "Collider_OBB.h"
#include "GameInstance.h"

USING(Engine)

CCollider_OBB::CCollider_OBB(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCollider(pGraphic_Device)
{
}

CCollider_OBB::CCollider_OBB(const CCollider_OBB& Prototype)
	: CCollider(Prototype)
	, m_vLocalCenter(Prototype.m_vLocalCenter)
	, m_vLocalExtents(Prototype.m_vLocalExtents)
{
}

HRESULT CCollider_OBB::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCollider_OBB::Initialize(void* pArg)
{
	OBB_DESC* desc = static_cast<OBB_DESC*>(pArg);
	if (desc != nullptr)
	{
		m_vLocalCenter = desc->vLocalCenter;
		m_vLocalExtents = desc->vLocalExtents;
	}
	return S_OK;
}

void CCollider_OBB::Update_Collider(const _float4x4* pWorldMatrix)
{
	D3DXVec3TransformCoord(&m_vWorldCenter, &m_vLocalCenter, pWorldMatrix);

	_float3 vRight = _float3(1.f, 0.f, 0.f);
	_float3 vUp = _float3(0.f, 1.f, 0.f);
	_float3 vLook = _float3(0.f, 0.f, 1.f);

	D3DXVec3TransformNormal(&m_vAxis[0], &vRight, pWorldMatrix);
	D3DXVec3TransformNormal(&m_vAxis[1], &vUp, pWorldMatrix);
	D3DXVec3TransformNormal(&m_vAxis[2], &vLook, pWorldMatrix);

	for (int i = 0; i < 3; ++i)
		D3DXVec3Normalize(&m_vAxis[i], &m_vAxis[i]);

	m_vWorldExtents = m_vLocalExtents;
}

CCollider_OBB* CCollider_OBB::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CCollider_OBB* pInstance = new CCollider_OBB(pGraphic_Device);
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("CCollider_OBB Create Failed"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent* CCollider_OBB::Clone(void* pArg)
{
	CCollider_OBB* pInstance = new CCollider_OBB(*this);
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("CCollider_OBB Clone Failed"));
		Safe_Release(pInstance);
	}
	pInstance->m_isCloned = true;
	return pInstance;
}

void CCollider_OBB::Free()
{
	__super::Free();
}
