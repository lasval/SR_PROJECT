#pragma once
#include "Client_Defines.h"
#include "UIObject.h"
BEGIN(Engine)
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)
class CMp_Player final : public CUIObject
{
private:
							CMp_Player(LPDIRECT3DDEVICE9 pGraphic_Device);
							CMp_Player(const CMp_Player& Prototype);
	virtual					~CMp_Player() = default;
public:
	virtual HRESULT			Initialize_Prototype() override;
	virtual HRESULT			Initialize(void* pArg) override;
	virtual void			Priority_Update(_float fTimeDelta) override;
	virtual void			Update(_float fTimeDelta) override;
	virtual void			Late_Update(_float fTimeDelta) override;
	virtual HRESULT			Render() override;

private:
	CVIBuffer_Rect*			m_pVIBufferCom = { nullptr };
	
	int						m_iMaxMp = {};
	int						m_iPreMp = {};
	int						m_iCulMp = {};

private:
	HRESULT					Ready_Components();
	void					Update_Mp();

public:
	static CMp_Player*		Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CUIObject*		Clone(void* pArg) override;
	virtual void			Free() override;
};
END
