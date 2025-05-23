#pragma once
#include "UIObject.h"

BEGIN(Engine)
class ENGINE_DLL CProgressBar abstract : public CUIObject
{
protected:
								CProgressBar(LPDIRECT3DDEVICE9 pGraphic_Device);
								CProgressBar(const CProgressBar& Prototype);
	virtual						~CProgressBar() = default;

public:
	virtual HRESULT				Initialize_Prototype() = 0;
	virtual HRESULT				Initialize(void* pArg) = 0;
	virtual void				Priority_Update(_float fTimeDelta) = 0;
	virtual void				Update(_float fTimeDelta) = 0;
	virtual void				Late_Update(_float fTimeDelta) = 0;
	virtual HRESULT				Render() = 0;
	
public:
	void						Progress_UpdateX();

protected:
	_int						m_iCulMaxValue = {};
	_int						m_iPreMaxValue = {};
	_int						m_iCulValue = {};
	_int						m_iPreValue = {};


public:
	virtual CGameObject*		Clone(void* pArg) = 0;
	virtual void				Free();
};
END
