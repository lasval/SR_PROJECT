#pragma once

#include "Prototype_Manager.h"

BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance)
private:
	CGameInstance();
	virtual ~CGameInstance() = default;

#pragma region ENGINE
public:
	HRESULT Initialize_Engine(const ENGINE_DESC& EngineDesc, LPDIRECT3DDEVICE9* ppOut);
	void Update_Engine(_float fTimeDelta);
	HRESULT Clear_Resources(_uint iClearLevelID);

public:
	void Render_Begin(D3DXCOLOR Color);
	HRESULT Draw();
	void Render_End(HWND hWnd = 0);

public:
	_float Compute_Random_Normal();
	_float Compute_Random(_float fMin, _float fMax);
#pragma endregion

#pragma region LEVEL_MANAGER
public:
	HRESULT Open_Level(_uint iLevelID, class CLevel* pNewLevel);
#pragma endregion

#pragma region PROTOTYPE_MANAGER
public:
	HRESULT Add_Prototype(_uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, class CBase* pPrototype);
	class CBase* Clone_Prototype(PROTOTYPE ePrototype, _uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, void* pArg = nullptr);
#pragma endregion

#pragma region OBJECT_MANAGER
public:
	HRESULT Add_GameObject_ToLayer(_uint iLayerLevelIndex, const _wstring& strLayerTag, _uint iPrototypeLevelIndex, const _wstring strPrototypeTag, void* pArg = nullptr);
	CComponent* Get_Component(_uint iLayerLevelIndex, const _wstring& strLayerTag, const _wstring& strComponentTag, _uint iIndex = 0);
	class CGameObject* Get_GameObject(_uint iLayerLevelIndex, const _wstring& strLayerTag, _uint iIndex = 0);
#pragma endregion

#pragma region RENDERER
public:
	HRESULT Add_RenderGroup(RENDERGROUP eRenderGroup, class CGameObject* pRenderObject);
#pragma endregion

#pragma region TIMER_MANAGER
public:
	_float	Get_TimeDelta(const _wstring& strTimerTag);		// 마지막 Compute 호출로부터 경과한 시간을 반환 (초 단위)
	HRESULT	Add_Timer(const _wstring& strTimerTag);			// 타이머 새로 추가
	void	Compute_TimeDelta(const _wstring& strTimerTag);	// 타이머 갱신
#pragma endregion

#pragma region KEY_MANAGER
	bool IsKeyDown(int key) const;   // 이번 프레임에 눌림
	bool IsKeyUp(int key) const;     // 이번 프레임에 떼짐
	bool IsKeyHold(int key) const;   // 계속 눌림
	float GetKeyHoldTime(int key) const; // 눌린 시간 (선택사항)
#pragma endregion

#pragma region NETWORK_MANAGER
	TEST* Ping();
	list<USER*> Get_AllUsers();
#pragma endregion
	void Transform_Picking_ToLocalSpace(const _float4x4& WorldMatrixInverse);
	_bool Picking_InWorld(_float3& vPickedPos, const _float3& vPointA, const _float3& vPointB, const _float3& vPointC);
	_bool Picking_InLocal(_float3& vPickedPos, const _float3& vPointA, const _float3& vPointB, const _float3& vPointC);
#pragma region PICKING


#pragma endregion

private:
	class CGraphic_Device*		m_pGraphic_Device = { nullptr };
	class CLevel_Manager*		m_pLevel_Manager = { nullptr };
	class CObject_Manager*		m_pObject_Manager = { nullptr };
	class CPrototype_Manager*	m_pPrototype_Manager = { nullptr };
	class CRenderer*			m_pRenderer = { nullptr };
	class CTimer_Manager*		m_pTimer_Manager = { nullptr };
	class CKey_Manager*			m_pKey_Manager = { nullptr };
	class CNetwork_Manager*		m_pNetwork_Manager = { nullptr };
	class CPicking*				m_pPicking = { nullptr };

public:
	void Release_Engine();
	virtual void Free() override;
};

END

