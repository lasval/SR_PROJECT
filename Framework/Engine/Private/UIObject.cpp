#include "UIObject.h"
#include "GameInstance.h"
CUIObject::CUIObject(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject{ pGraphic_Device }
{
}

CUIObject::CUIObject(const CUIObject& Prototype)
	: CGameObject{ Prototype }
{
}

HRESULT CUIObject::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CUIObject::Initialize(void* pArg)
{
    D3DXMatrixIdentity(&m_ViewMatrix);

    
    D3DVIEWPORT9    ViewportDesc{};
    //���� ����̽��� ����Ʈ�� ������
    m_pGraphic_Device->GetViewport(&ViewportDesc);
    
    //���� ���� ��� ���� (������ ���, �ʺ�, ����, �Ͼ�, ��)
    D3DXMatrixOrthoLH(&m_ProjMatrix, ViewportDesc.Width, ViewportDesc.Height, 0.f, 1.f);
    
    UIOBJECT_DESC* pDesc = static_cast<UIOBJECT_DESC*>(pArg);

    m_fX = pDesc->fX;
    m_fY = pDesc->fY;
    m_fZ = pDesc->fZ;
    m_fSizeX = pDesc->fSizeX;
    m_fSizeY = pDesc->fSizeY;

    return S_OK;
}

void CUIObject::Priority_Update(_float fTimeDelta)
{
    for (auto child : m_vecChildren)
        child->Priority_Update(fTimeDelta);
}

void CUIObject::Update(_float fTimeDelta)
{
    for (auto child : m_vecChildren)
        child->Update(fTimeDelta);
}

void CUIObject::Late_Update(_float fTimeDelta)
{
    for (auto child : m_vecChildren)
        child->Late_Update(fTimeDelta);
}

HRESULT CUIObject::Render()
{
	return S_OK;
}
void CUIObject::Begin()
{
    //���� ��, ���� ��� ����
    m_pGraphic_Device->GetTransform(D3DTS_VIEW, &m_OldViewMatrix);
    m_pGraphic_Device->GetTransform(D3DTS_PROJECTION, &m_OldProjMatrix);

    //UI ��� ����
    m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_ViewMatrix);
    m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);
}

void CUIObject::End()
{
    //���� ��ķ� �ǵ�����
    m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_OldViewMatrix);
    m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_OldProjMatrix);
}

_bool CUIObject::isPick(HWND hWnd)
{
	POINT			ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(hWnd, &ptMouse);

	RECT			rcUI = { m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f, m_fX + m_fSizeX * 0.5f, m_fY + m_fSizeY * 0.5f };

	return PtInRect(&rcUI, ptMouse);
}

void CUIObject::Update_Position(const _uint iWinX, const _uint iWinY)
{
    if (m_pParent)
    {
        m_vWorldPos.x = m_pParent->m_fX + m_fX; 
        m_vWorldPos.y = m_pParent->m_fY + m_fY;
        m_vWorldPos.z = m_pParent->m_fZ;
    }
    else
    {
        m_vWorldPos.x = m_fX;
        m_vWorldPos.y= m_fY;
        m_vWorldPos.z = m_fZ;
    }
    
    m_pTransformCom->Set_State(STATE::POSITION, _float3{ m_vWorldPos.x - iWinX * 0.5f, -m_vWorldPos.y + iWinY * 0.5f, m_vWorldPos.z });
    for (auto child : m_vecChildren)
        child->Update_Position(iWinX, iWinY);
}

void CUIObject::Add_Child(CUIObject* pChildUI, const _uint iWinX, const _uint iWinY)
{
    pChildUI->m_pParent = this; 
    m_vecChildren.push_back(pChildUI); 
    
    pChildUI->Update_Position(iWinX, iWinY);
   
}

HRESULT CUIObject::Ready_Components()
{
    return S_OK;
}

HRESULT CUIObject::Ready_Children()
{
    return S_OK;
}



void CUIObject::Free()
{
    for (auto& pChildren : m_vecChildren)
        Safe_Release(pChildren);
    m_vecChildren.clear();

    m_pParent = nullptr;

    __super::Free();
   
    
}
