#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
BEGIN(Engine)
class CTexture;
class CTransform;
class CVIBuffer_Rect;
END
BEGIN(Client)
class CUI_Test final : public CGameObject
{
private:
	CUI_Test(LPDIRECT3DDEVICE9 pGraphic_Device);
	CUI_Test(const CUI_Test& Prototype);
	virtual ~CUI_Test() = default;

public:
	virtual HRESULT				Initialize_Prototype() override;
	virtual HRESULT				Initialize(void* pArg) override;
	virtual void				Priority_Update(_float fTimeDelta) override;
	virtual void				Update(_float fTimeDelta) override;
	virtual void				Late_Update(_float fTimeDelta) override;
	virtual HRESULT				Render() override;

private:
	CVIBuffer_Rect*				m_pVIBufferCom = { nullptr };
	CTexture*					m_pTextureCom = { nullptr };
	CTransform*					m_pTransformCom = { nullptr };

private:
	HRESULT						Ready_Components();

public:
	static CUI_Test*			Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject*		Clone(void* pArg) override;
	virtual void				Free() override;
};
END
