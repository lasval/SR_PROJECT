#pragma once

#include "Collider.h"

BEGIN(Engine)

class ENGINE_DLL CCollider_OBB final : public CCollider
{
public:
	typedef struct tagOBB_Desc {
		_float3		vLocalCenter;
		_float3		vLocalExtents;
	}OBB_DESC;

private:
	CCollider_OBB(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCollider_OBB(const CCollider_OBB& Prototype);
	virtual ~CCollider_OBB() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	virtual void Update_Collider(const _float4x4* pWorldMatrix) override;

public:
	void Get_MatrixData(_float3& vCenter, _float3& vExtent, _float3* vAxis)
	{
		vCenter = m_vWorldCenter;
		vExtent = m_vWorldExtents;
		memcpy(vAxis, m_vAxis, sizeof(_float3) * 3);
	}

private:
	_float3		m_vLocalCenter = { 0.f, 0.f, 0.f };
	_float3		m_vLocalExtents = { 0.5f, 0.5f, 0.5f };
	_float3		m_vWorldCenter = {};
	_float3		m_vAxis[3] = {};
	_float3		m_vWorldExtents = {};

public:
	static CCollider_OBB* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END
