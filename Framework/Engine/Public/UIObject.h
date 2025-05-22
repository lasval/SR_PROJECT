#pragma once

#include "GameObject.h"
BEGIN(Engine)

class ENGINE_DLL CUIObject abstract : public CGameObject
{
public:
	typedef struct tagUIObjectDesc
	{
		_float		fX, fY, fZ, fSizeX, fSizeY;
	}UIOBJECT_DESC;
protected:
	CUIObject(LPDIRECT3DDEVICE9 pGraphic_Device);
	CUIObject(const CUIObject& Prototype);
	virtual ~CUIObject() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Priority_Update(_float fTimeDelta);
	virtual void Update(_float fTimeDelta);
	virtual void Late_Update(_float fTimeDelta);
	virtual HRESULT Render();

protected:
	_float					m_fX = {};
	_float					m_fY = {};
	_float					m_fZ = {};
	_float					m_fSizeX = {};
	_float					m_fSizeY = {};
	_float3					m_fWorldPos = {};

	_float4x4				m_ViewMatrix = {};
	_float4x4				m_ProjMatrix = {};

	_float4x4				m_OldViewMatrix = {};
	_float4x4				m_OldProjMatrix = {};

	CUIObject*				m_pParent = { nullptr };
	vector<CUIObject*>		m_vecChildren = {};

	class CTransform*		m_pTransformCom = { nullptr };
protected:
	void					Begin();
	void					End();
	_bool					isPick(HWND hWnd);

	void					Update_Position(const _uint iWinX, const _uint iWinY);
	void					Add_Child(CUIObject* pChildUI, const _uint iWinX, const _uint iWinY );
	
	virtual HRESULT			Ready_Components();
	virtual HRESULT			Ready_Children();
public:
	virtual CGameObject*	Clone(void* pArg) = 0;
	virtual void			Free();
};

END