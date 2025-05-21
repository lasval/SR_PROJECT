#pragma once
#include "Client_Defines.h"
#include "UIObject.h"
BEGIN(Engine)
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)
class CHp_Player final : public CUIObject
{
private:
							CHp_Player(LPDIRECT3DDEVICE9 pGraphic_Device);
							CHp_Player(const CHp_Player& Prototype);
	virtual					~CHp_Player() = default;
public:
	virtual HRESULT			Initialize_Prototype() override;
	virtual HRESULT			Initialize(void* pArg) override;
	virtual void			Priority_Update(_float fTimeDelta) override;
	virtual void			Update(_float fTimeDelta) override;
	virtual void			Late_Update(_float fTimeDelta) override;
	virtual HRESULT			Render() override;

private:					
	CTransform*				m_pTransformCom = { nullptr };
	CVIBuffer_Rect*			m_pVIBufferCom = { nullptr };
private:
	int						m_iMaxHp = {};
	int						m_iPreHp = {};
	int						m_iCulHp = {};
	
private:
	HRESULT					Ready_Components();

	void					Update_Hp();
public:
	static CHp_Player*		Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CUIObject*		Clone(void* pArg) override;
	virtual void			Free() override;
};
END
