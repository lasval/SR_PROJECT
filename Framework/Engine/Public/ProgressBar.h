#pragma once
#include "Component.h"

BEGIN(Engine)
class ENGINE_DLL CProgressBar final : public CComponent
{
public:
	typedef struct tagProgressDesc
	{
		class CTransform*			pTransformCom = { nullptr };
		_uint						iMaxValue = {};
		_uint						iCulValue = {};
	}PROGRESSBAR_DESC;
private:
								CProgressBar(LPDIRECT3DDEVICE9 pGraphic_Device);
								CProgressBar(const CProgressBar& Prototype);
	virtual						~CProgressBar() = default;

public:
	virtual HRESULT				Initialize_Prototype();
	virtual HRESULT				Initialize(void* pArg);
	
public:
	void						Progress_UpdateX(_uint iCulValue, const _float3 vOriginPos, const _float3 vOriginSize);
	void						MaxValue_UpdateX(_uint iMaxValue, const _float3 vOriginPos, const _float3 vOriginSize);

private:
	class CTransform*			m_pTransformCom = { nullptr };
	_uint						m_iMaxValue = {};
	_uint						m_iCulValue = {};
	_uint						m_iPreValue = {};


public:
	static CProgressBar*		Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent*			Clone(void* pArg);
	virtual void				Free();
};
END
