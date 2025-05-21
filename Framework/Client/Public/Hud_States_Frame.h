#pragma once
#include "Client_Defines.h"
#include "UIObject.h"
BEGIN(Engine)
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)
class CHud_States_Frame final : public CUIObject
{
private:
								CHud_States_Frame(LPDIRECT3DDEVICE9 pGraphic_Device);
								CHud_States_Frame(const CHud_States_Frame& Prototype);
	virtual						~CHud_States_Frame() = default;
public:
	virtual HRESULT				Initialize_Prototype(LEVEL eLevel);
	virtual HRESULT				Initialize(void* pArg) override;
	virtual void				Priority_Update(_float fTimeDelta) override;
	virtual void				Update(_float fTimeDelta) override;
	virtual void				Late_Update(_float fTimeDelta) override;
	virtual HRESULT				Render() override;

private:
	CVIBuffer_Rect*				m_pVIBufferCom = { nullptr };
	LEVEL						m_eLevel = {};

private:
	virtual HRESULT				Ready_Prototype(LEVEL eLevel);
	virtual HRESULT				Ready_Components() override;
	virtual HRESULT				Ready_Children() override;

public:
	static CHud_States_Frame*	Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eLevel);
	virtual CUIObject*			Clone(void* pArg) override;
	virtual void				Free() override;
};
END