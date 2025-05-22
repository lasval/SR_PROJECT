#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer(const CVIBuffer& Prototype);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Bind_Buffers();
	virtual HRESULT Render();

public:
	_float3 Compute_PickedPosition(const _float4x4* pWorldMatrixInverse);

protected:
	LPDIRECT3DVERTEXBUFFER9			m_pVB = { nullptr };
	LPDIRECT3DINDEXBUFFER9			m_pIB = { nullptr };

	_uint							m_iNumVertices = { };
	_uint							m_iVertexStride = { };
	_uint							m_iFVF = { };
	D3DPRIMITIVETYPE				m_ePrimitiveType = { };
	_uint							m_iNumPrimitive = { };

	_uint							m_iIndexStride = { };
	_uint							m_iNumIndices = {};
	D3DFORMAT						m_eIndexFormat = {};

	_float3*						m_pVertexPositions = { nullptr };
	void*							m_pIndices = {};

public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END