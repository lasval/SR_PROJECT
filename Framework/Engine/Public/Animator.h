#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CAnimator final : public CComponent
{
public:
	// 각 State가 가질 정보
	typedef struct tagAnimState
	{
		_float fAnimLength;
		_bool isExitable;
	} ANIMSTATE;

	// Animator 최초 생성 시 필요로 하는 정보 (pArg)
	typedef struct tagStartStateDesc
	{
		_wstring strTimerTag; // 애니메이터 다중 사용을 고려하여 타이머 태그를 다르게 구성
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
	//void Update(_float fTimeDelta); // 필요하면 구현?

public:
	HRESULT Add_State(const _wstring strStateTag, ANIMSTATE _state);
	ANIMSTATE* Get_CurState()	{ return m_pCurState; };
	_wstring Get_CurStateTag()	{ return m_strCurStateTag; };

	void Change_State(const _wstring strStatetag);

private:
	ANIMSTATE* Find_State(const _wstring& strStateTag);

private:
	// ANIMSTATE m_tPrevState = {}; // 필요하면 사용?
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