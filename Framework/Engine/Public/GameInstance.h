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
#pragma endregion

#pragma region RENDERER
public:
	HRESULT Add_RenderGroup(RENDERGROUP eRenderGroup, class CGameObject* pRenderObject);
#pragma endregion

#pragma region TIMER_MANAGER
public:
	_float	Get_TimeDelta(const _wstring& strTimerTag);		// ������ Compute ȣ��κ��� ����� �ð��� ��ȯ (�� ����)
	HRESULT	Add_Timer(const _wstring& strTimerTag);			// Ÿ�̸� ���� �߰�
	void	Compute_TimeDelta(const _wstring& strTimerTag);	// Ÿ�̸� ����
#pragma endregion

#pragma region KEY_MANAGER
	void AddTrackingKey(int iKey);
	bool IsKeyDown(int iKey) const;   // �̹� �����ӿ� ����
	bool IsKeyUp(int iKey) const;     // �̹� �����ӿ� ����
	bool IsKeyHold(int iKey) const;   // ��� ����
	float GetKeyHoldTime(int iKey) const; // ���� �ð� (���û���)
#pragma endregion

#pragma region NETWORK_MANAGER
	TEST* Ping();
	list<USER*> Get_AllUsers();
#pragma endregion

#pragma region PICKING
	void Transform_Picking_ToLocalSpace(const _float4x4& WorldMatrixInverse);
	_bool Picking_InWorld(_float3& vPickedPos, const _float3& vPointA, const _float3& vPointB, const _float3& vPointC);
	_bool Picking_InLocal(_float3& vPickedPos, const _float3& vPointA, const _float3& vPointB, const _float3& vPointC);
#pragma endregion

#pragma region COLLISION_MANAGER
	// �ش� ���� ���� ���� �߰� ����
	HRESULT Add_Collider(class CCollider* pCollider);
#pragma endregion

#pragma region ROOM_MANAGER
	HRESULT Add_Room(class CRoom* pRoom);
	HRESULT Enter_Room(_int iRoomID);
	class CRoom* Get_CurrentRoom();
	class CRoom* Get_RoomByID(_int iRoomID);
#pragma endregion

#pragma region FONT_MANAGER
	HRESULT Add_Font_FromFile(
		const _wstring& strTag,
		const _wstring& strFontPath,
		const _wstring& strFontName,
		int iFontSize);

	void Render_Text(const _wstring& strTag,
		const _wstring& strText,
		const RECT& rc,
		D3DCOLOR color,
		DWORD dwFormat = DT_LEFT | DT_TOP);
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
	class CCollision_Manager*	m_pCollision_Manager = { nullptr };
	class CRoom_Manager*		m_pRoom_Manager = { nullptr };
	class CFont_Manager*		m_pFont_Manager = { nullptr };

public:
	void Release_Engine();
	virtual void Free() override;
};

END

