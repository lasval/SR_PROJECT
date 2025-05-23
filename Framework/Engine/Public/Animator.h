#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CAnimator final : public CComponent
{
public:
	// �� State�� ���� ����
	typedef struct tagAnimState
	{
		_float fAnimLength;
		_bool isExitable;
	} ANIMSTATE;

	// Animator ���� ���� �� �ʿ�� �ϴ� ���� (pArg)
	typedef struct tagStartStateDesc
	{
		_wstring strTimerTag; // �ִϸ����� ���� ����� ����Ͽ� Ÿ�̸� �±׸� �ٸ��� ����
		_wstring strFirstStateTag;
		ANIMSTATE tFirstAnimState;
	} ANIMSTATE_DESC;
	
private:
	CAnimator(LPDIRECT3DDEVICE9 pGraphic_Device);
	CAnimator(const CAnimator& Prototype);
	virtual ~CAnimator() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	//void Update(_float fTimeDelta); // �ʿ��ϸ� ����?

public:
	HRESULT Add_State(const _wstring strStateTag, ANIMSTATE _state);
	ANIMSTATE* Get_CurState()	{ return m_pCurState; };
	_wstring Get_CurStateTag()	{ return m_strCurStateTag; };

	void Change_State(const _wstring strStatetag);

private:
	ANIMSTATE* Find_State(const _wstring& strStateTag);

private:
	// ANIMSTATE m_tPrevState = {}; // �ʿ��ϸ� ���?
	ANIMSTATE* m_pCurState = { nullptr };
	_wstring m_strCurStateTag = {};
	_wstring m_strTimerTag = {};

	std::map<const _wstring, ANIMSTATE> m_pStates = {};

	

public:
	static CAnimator* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END