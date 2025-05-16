#include "GameInstance.h"

#include "Graphic_Device.h"
#include "Level_Manager.h"
#include "Prototype_Manager.h"
#include "Object_Manager.h"
#include "Renderer.h"

IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
{

}

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

    return S_OK;
}

void CGameInstance::Update_Engine(_float fTimeDelta)
{
    m_pObject_Manager->Priority_Update(fTimeDelta);
    m_pObject_Manager->Update(fTimeDelta);
    m_pObject_Manager->Late_Update(fTimeDelta);

    m_pLevel_Manager->Update(fTimeDelta);
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

HRESULT CGameInstance::Open_Level(_uint iLevelID, CLevel* pNewLevel)
{
    if (nullptr == m_pLevel_Manager)
        return E_FAIL;

    return m_pLevel_Manager->Open_Level(iLevelID, pNewLevel);
}

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

HRESULT CGameInstance::Add_GameObject_ToLayer(_uint iLayerLevelIndex, const _wstring& strLayerTag, _uint iPrototypeLevelIndex, const _wstring strPrototypeTag, void* pArg)
{
    if (nullptr == m_pObject_Manager)
        return E_FAIL;

    return m_pObject_Manager->Add_GameObject_ToLayer(iLayerLevelIndex, strLayerTag, iPrototypeLevelIndex, strPrototypeTag, pArg);
}

HRESULT CGameInstance::Add_RenderGroup(RENDERGROUP eRenderGroup, CGameObject* pRenderObject)
{
    if (nullptr == m_pRenderer)
        return E_FAIL;

    return m_pRenderer->Add_RenderGroup(eRenderGroup, pRenderObject);
}

void CGameInstance::Release_Engine()
{
    Release();
    Safe_Release(m_pLevel_Manager);
    Safe_Release(m_pGraphic_Device);
    Safe_Release(m_pPrototype_Manager);
    Safe_Release(m_pObject_Manager);
    Safe_Release(m_pRenderer);
}

void CGameInstance::Free()
{
    __super::Free();
}
