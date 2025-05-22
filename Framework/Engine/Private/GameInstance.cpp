#include "Network_Manager.h"
#include "GameInstance.h"

#include "Graphic_Device.h"
#include "Level_Manager.h"
#include "Prototype_Manager.h"
#include "Object_Manager.h"
#include "Renderer.h"
#include "Timer_Manager.h"
#include "Key_Manager.h"
#include "Picking.h"

IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
{

}

#pragma region ENGINE
HRESULT CGameInstance::Initialize_Engine(const ENGINE_DESC& EngineDesc, LPDIRECT3DDEVICE9* ppOut)
{
    m_pGraphic_Device = CGraphic_Device::Create(EngineDesc.hWnd, EngineDesc.eWinMode, EngineDesc.iWinSizeX, EngineDesc.iWinSizeY, ppOut);
    if (nullptr == m_pGraphic_Device)
        return E_FAIL;

    m_pLevel_Manager = CLevel_Manager::Create();
    if (nullptr == m_pLevel_Manager)
        return E_FAIL;

    m_pPrototype_Manager = CPrototype_Manager::Create(EngineDesc.iNumLevels);
    if (nullptr == m_pPrototype_Manager)
        return E_FAIL;

    m_pObject_Manager = CObject_Manager::Create(EngineDesc.iNumLevels);
    if (nullptr == m_pObject_Manager)
        return E_FAIL;

    m_pRenderer = CRenderer::Create(*ppOut);
    if (nullptr == m_pRenderer)
        return E_FAIL;

    m_pTimer_Manager = CTimer_Manager::Create();
    if (nullptr == m_pTimer_Manager)
        return E_FAIL;

    m_pKey_Manager = CKey_Manager::Create();
    if (nullptr == m_pKey_Manager)
        return E_FAIL;

    m_pNetwork_Manager = CNetwork_Manager::Create();
    if (nullptr == m_pNetwork_Manager)
        return E_FAIL;

    m_pPicking = CPicking::Create(*ppOut, EngineDesc.hWnd, EngineDesc.iWinSizeX, EngineDesc.iWinSizeY);
    if (nullptr == m_pPicking)
        return E_FAIL;

    return S_OK;
}

void CGameInstance::Update_Engine(_float fTimeDelta)
{
    m_pObject_Manager->Priority_Update(fTimeDelta);
    
    m_pPicking->Update();

    m_pObject_Manager->Update(fTimeDelta);
    m_pObject_Manager->Late_Update(fTimeDelta);

    m_pLevel_Manager->Update(fTimeDelta);

    m_pKey_Manager->Update(fTimeDelta);
}

HRESULT CGameInstance::Clear_Resources(_uint iClearLevelID)
{
    m_pPrototype_Manager->Clear(iClearLevelID);

    m_pObject_Manager->Clear(iClearLevelID);

    return S_OK;
}

void CGameInstance::Render_Begin(D3DXCOLOR Color)
{
    if (nullptr != m_pGraphic_Device)
        m_pGraphic_Device->Render_Begin(Color);
}

HRESULT CGameInstance::Draw()
{
    if (nullptr == m_pLevel_Manager)
        return E_FAIL;

    if (FAILED(m_pRenderer->Draw()))
        return E_FAIL;

    if (FAILED(m_pLevel_Manager->Render()))
        return E_FAIL;

    return S_OK;
}

void CGameInstance::Render_End(HWND hWnd)
{
    if (nullptr != m_pGraphic_Device)
        m_pGraphic_Device->Render_End();
}
_float CGameInstance::Compute_Random_Normal()
{
    return rand() / static_cast<_float>(RAND_MAX);
}
_float CGameInstance::Compute_Random(_float fMin, _float fMax)
{
    return fMin + (fMax - fMin) * Compute_Random_Normal();
}
#pragma endregion

#pragma region LEVEL_MANAGER
HRESULT CGameInstance::Open_Level(_uint iLevelID, CLevel* pNewLevel)
{
    if (nullptr == m_pLevel_Manager)
        return E_FAIL;

    return m_pLevel_Manager->Open_Level(iLevelID, pNewLevel);
}
#pragma endregion

#pragma region PROTOTYPE_MANAGER
HRESULT CGameInstance::Add_Prototype(_uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, CBase* pPrototype)
{
    if (nullptr == m_pPrototype_Manager)
        return E_FAIL;

    return m_pPrototype_Manager->Add_Prototype(iPrototypeLevelIndex, strPrototypeTag, pPrototype);
}

CBase* CGameInstance::Clone_Prototype(PROTOTYPE ePrototype, _uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, void* pArg)
{
    if (nullptr == m_pPrototype_Manager)
        return nullptr;

    return m_pPrototype_Manager->Clone_Prototype(ePrototype, iPrototypeLevelIndex, strPrototypeTag, pArg);
}
#pragma endregion

#pragma region OBJECT_MANAGER
HRESULT CGameInstance::Add_GameObject_ToLayer(_uint iLayerLevelIndex, const _wstring& strLayerTag, _uint iPrototypeLevelIndex, const _wstring strPrototypeTag, void* pArg)
{
    if (nullptr == m_pObject_Manager)
        return E_FAIL;

    return m_pObject_Manager->Add_GameObject_ToLayer(iLayerLevelIndex, strLayerTag, iPrototypeLevelIndex, strPrototypeTag, pArg);
}
CComponent* CGameInstance::Get_Component(_uint iLayerLevelIndex, const _wstring& strLayerTag, const _wstring& strComponentTag, _uint iIndex)
{
    return m_pObject_Manager->Get_Component(iLayerLevelIndex, strLayerTag, strComponentTag, iIndex);
}
#pragma endregion

#pragma region RENDERER
HRESULT CGameInstance::Add_RenderGroup(RENDERGROUP eRenderGroup, CGameObject* pRenderObject)
{
    if (nullptr == m_pRenderer)
        return E_FAIL;

    return m_pRenderer->Add_RenderGroup(eRenderGroup, pRenderObject);
}
#pragma endregion

#pragma region TIMER_MANAGER
_float CGameInstance::Get_TimeDelta(const _wstring& strTimerTag)
{
    return m_pTimer_Manager->Get_TimeDelta(strTimerTag);
}

HRESULT CGameInstance::Add_Timer(const _wstring& strTimerTag)
{
    return m_pTimer_Manager->Add_Timer(strTimerTag);
}

void CGameInstance::Compute_TimeDelta(const _wstring& strTimerTag)
{
    m_pTimer_Manager->Compute_TimeDelta(strTimerTag);
}
#pragma endregion 

#pragma region KEY_MANAGER
bool CGameInstance::IsKeyDown(int iKey)
{
    return m_pKey_Manager->IsKeyDown(iKey);
}
bool CGameInstance::IsKeyUp(int iKey)
{
    return m_pKey_Manager->IsKeyUp(iKey);
}
bool CGameInstance::IsKeyPressedOnce(int iKey)
{
    return m_pKey_Manager->IsKeyPressedOnce(iKey);
}
bool CGameInstance::IsKeyHeld(int iKey, float fHoldThresholdSec)
{
    return m_pKey_Manager->IsKeyHeld(iKey, fHoldThresholdSec);
}
#pragma endregion

#pragma region NETWORK_MANAGER
TEST* CGameInstance::Ping()
{
    return m_pNetwork_Manager->Ping();
}
list<USER*> CGameInstance::Get_AllUsers()
{
    return m_pNetwork_Manager->Get_AllUsers();
}
#pragma endregion

#pragma region PICKING
void CGameInstance::Transform_Picking_ToLocalSpace(const _float4x4& WorldMatrixInverse)
{
    m_pPicking->Transform_ToLocalSpace(WorldMatrixInverse);
}
_bool CGameInstance::Picking_InWorld(_float3& vPickedPos, const _float3& vPointA, const _float3& vPointB, const _float3& vPointC)
{
    return m_pPicking->Picking_InWorld(vPickedPos, vPointA, vPointB, vPointC);
}
_bool CGameInstance::Picking_InLocal(_float3& vPickedPos, const _float3& vPointA, const _float3& vPointB, const _float3& vPointC)
{
    return m_pPicking->Picking_InLocal(vPickedPos, vPointA, vPointB, vPointC);
}
#pragma endregion

void CGameInstance::Release_Engine()
{
    Release();
    
    Safe_Release(m_pTimer_Manager);
    Safe_Release(m_pLevel_Manager);
    Safe_Release(m_pGraphic_Device);
    Safe_Release(m_pPrototype_Manager);
    Safe_Release(m_pObject_Manager);
    Safe_Release(m_pRenderer);
    Safe_Release(m_pTimer_Manager);
    Safe_Release(m_pKey_Manager);
    Safe_Release(m_pNetwork_Manager);
    Safe_Release(m_pPicking);
}

void CGameInstance::Free()
{
    __super::Free();
}
