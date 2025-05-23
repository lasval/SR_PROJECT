#include "Collider.h"

CCollider::CCollider(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent { pGraphic_Device }
{
}

CCollider::CCollider(const CCollider& Prototype)
	: CComponent { Prototype }
	, m_eObjType { Prototype.m_eObjType }
	, m_eType { Prototype.m_eType }
{
}

HRESULT CCollider::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCollider::Initialize(void* pArg)
{
	return S_OK;
}

void CCollider::Free()
{
	__super::Free();
}
