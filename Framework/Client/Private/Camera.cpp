#include "Camera.h"
#include "GameInstance.h"

CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject {pGraphic_Device}
{
}

CCamera::CCamera(const CCamera& Prototype)
	: CGameObject { Prototype }
{
}

HRESULT CCamera::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCamera::Initialize(void* pArg)
{
	if (FAILED(Ready_Components(pArg)))
		return E_FAIL;

	CAMERA_DESC* pDesc = static_cast<CAMERA_DESC*>(pArg);

	m_pTransformCom->Set_State(STATE::POSITION, pDesc->vEye);
	m_pTransformCom->Look_At(pDesc->vAt);

	m_fFovy = pDesc->fFovy;
	m_fAspect = static_cast<_float>(g_iWinSizeX) / g_iWinSizeY;
	m_fNear = pDesc->fNear;
	m_fFar = pDesc->fFar;
	m_fMouseSensor = pDesc->fMouseSensor;
	/*if(pDesc->pTargetTransform != nullptr)
		m_pTargetTransform = pDesc->pTargetTransform;*/

	m_pTargetTransformCom = dynamic_cast<CTransform*>(m_pGameInstance->Get_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Layer_Player"), TEXT("Com_Transform")));
	if (m_pTargetTransformCom == nullptr)
		return E_FAIL;

	m_OldPoint.x = g_iWinSizeX >> 1;
	m_OldPoint.y = g_iWinSizeY >> 1;

	POINT	ptMouse = m_OldPoint;
	ClientToScreen(g_hWnd, &ptMouse);

	SetCursorPos(ptMouse.x, ptMouse.y);

	m_vOffset = _float3(-10.f, 10.f, -10.f);
	m_fCurrentAngle = 0.f;

	return S_OK;
}

void CCamera::Priority_Update(_float fTimeDelta)
{
	//if (GetKeyState('W') < 0)
	//{
	//	m_pTransformCom->Go_Straight(fTimeDelta);
	//}

	//if (GetKeyState('S') < 0)
	//{
	//	m_pTransformCom->Go_Backward(fTimeDelta);
	//}

	//if (GetKeyState('A') < 0)
	//{
	//	m_pTransformCom->Go_Left(fTimeDelta);
	//}

	//if (GetKeyState('D') < 0)
	//{
	//	m_pTransformCom->Go_Right(fTimeDelta);
	//}

	//Mouse_Move(fTimeDelta);
	//m_pTargetTransform->Get_State(STATE::POSITION);

	Move_Angle(45.f);
	Follow_Target();
	

	m_pGraphic_Device->SetTransform(D3DTS_VIEW, m_pTransformCom->Get_WorldMatrix_Inverse());
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION,
		D3DXMatrixPerspectiveFovLH(
			&m_ProjMatrix, 
			m_fFovy, 
			m_fAspect, 
			m_fNear, 
			m_fFar
		)
	);


}

void CCamera::Update(_float fTimeDelta)
{
	
}

void CCamera::Late_Update(_float fTimeDelta)
{
}

HRESULT CCamera::Render()
{
	return S_OK;
}

HRESULT CCamera::Ready_Components(void* pArg)
{
	/* For,Com_Transform*/
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom), pArg)))
		return E_FAIL;


	return S_OK;
}

void CCamera::Mouse_Move(_float fTimeDelta)
{
	POINT			ptMouse{};

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	_int		iMouseMove = {};

	if (iMouseMove = ptMouse.x - m_OldPoint.x)
	{
		m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), iMouseMove * fTimeDelta * m_fMouseSensor);
	}

	if (iMouseMove = ptMouse.y - m_OldPoint.y)
	{
		m_pTransformCom->Turn(m_pTransformCom->Get_State(STATE::RIGHT), iMouseMove * fTimeDelta * m_fMouseSensor);
	}
	m_OldPoint = ptMouse;
}

void CCamera::Move_Angle(_float fAngle)
{
	if (m_pGameInstance->IsKeyPressedOnce('Q'))
	{
		m_fCurrentAngle += fAngle;
		if (m_fCurrentAngle >= 360.f)
			m_fCurrentAngle -= 360.f;
	}

	if (m_pGameInstance->IsKeyPressedOnce('E'))
	{
		m_fCurrentAngle -= fAngle;
		if (m_fCurrentAngle < 0.f)
			m_fCurrentAngle += 360.f;
	}
}

void CCamera::Follow_Target()
{
	_float3		vPlayerPosition = m_pTargetTransformCom->Get_State(STATE::POSITION);
	_float3		vPosition = m_pTransformCom->Get_State(STATE::POSITION);

	_float4x4	matRotY;
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fCurrentAngle));

	_float3 vRotatedOffset;
	D3DXVec3TransformCoord(&vRotatedOffset, &m_vOffset, &matRotY);

	_float3 vCameraPos = vPlayerPosition + vRotatedOffset;
	m_pTransformCom->Set_State(STATE::POSITION, vCameraPos);
	m_pTransformCom->Look_At(vPlayerPosition);
}

CCamera* CCamera::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CCamera* pInstance = new CCamera(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CCamera"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CCamera::Clone(void* pArg)
{
	CCamera* pInstance = new CCamera(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CCamera"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCamera::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
}
