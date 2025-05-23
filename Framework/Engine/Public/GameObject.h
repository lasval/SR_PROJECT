#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device);
	CGameObject(const CGameObject& Prototype);
	virtual ~CGameObject() = default;

public:
	class CComponent* Find_Component(const _wstring& strComponentTag);

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Priority_Update(_float fTimeDelta);
	virtual void Update(_float fTimeDelta);
	virtual void Late_Update(_float fTimeDelta);
	virtual HRESULT Render();


public:
	BOOL Get_IsCollision() { return m_bCollision; }
	COLLISION_EVENT Get_CollosionEvent() { return m_eCollisionEvent; }
	BOOL Get_IsDead() { return m_bDead; }

public:
	void Set_IsCollision(BOOL bCollision) { m_bCollision = bCollision; }
	void Set_CollisionEvent(COLLISION_EVENT eCollisionEvent) { m_eCollisionEvent = eCollisionEvent; }
	void Set_IsDead(BOOL bDead) { m_bDead = bDead; }

protected:
	LPDIRECT3DDEVICE9			m_pGraphic_Device = { nullptr };
	class CGameInstance*		m_pGameInstance = { nullptr };

	map<const _wstring, class CComponent*>		m_Components;

	BOOL						m_bCollision = {};
	COLLISION_EVENT				m_eCollisionEvent = {};
	BOOL						m_bDead = {};

protected:
	HRESULT Add_Component(_uint iPrototypeLevelIndex, const _wstring& strPrototypeTag,
		const _wstring& strComponentTag, CComponent** ppOut, void* pArg = nullptr);

public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;

};

END