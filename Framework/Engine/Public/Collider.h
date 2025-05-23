#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CCollider abstract : public CComponent
{
protected:
	CCollider(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCollider(const CCollider& Prototype);
	virtual ~CCollider() = default;

public:
	HRESULT Initialize_Prototype();
	HRESULT Initialize(void* pArg);

public:
	virtual void Update_Collider(const _float4x4* pWorldMatrix) = 0;
	virtual COLLIDER_TYPE Get_ColliderType() { return m_eType; }
	virtual COLLIDER_OBJ_TYPE Get_ColliderObjType() { return m_eObjType; }

protected:
	COLLIDER_OBJ_TYPE m_eObjType = {};
	COLLIDER_TYPE m_eType = {};
public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END