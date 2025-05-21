#pragma once
#include "Component.h"

BEGIN(Engine)
class CProgressBar final : public CComponent
{
private:
								CProgressBar(LPDIRECT3DDEVICE9 pGraphic_Device);
								CProgressBar(const CProgressBar& Prototype);
	virtual						~CProgressBar() = default;

public:
	virtual HRESULT				Initialize_Prototype();
	virtual HRESULT				Initialize(void* pArg);

	HRESULT						Setting_Componets(class CTransform* pTransform, const _uint iCulNumber, const _uint iMaxNumber);
private:
	class CTransform*			m_pTransformCom = { nullptr };
	_uint						m_iMaxNumber = {};
	_uint						m_iCulNumber = {};
	_uint						m_iPreNumber = {};


public:
	static CProgressBar*		Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent*			Clone(void* pArg);
	virtual void				Free();
};
END
