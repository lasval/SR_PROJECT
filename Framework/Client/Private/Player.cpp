#include "Player.h"

#include "GameInstance.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject{ pGraphic_Device }
{
}

CPlayer::CPlayer(const CPlayer& Prototype)
	:	CGameObject { Prototype }
{
}

HRESULT CPlayer::Initialize_Prototype()
{

	return S_OK;
}

HRESULT CPlayer::Initialize(void* pArg)
{
	if (FAILED(Ready_Components()))
		return E_FAIL;

	return S_OK;
}

void CPlayer::Priority_Update(_float fTimeDelta)
{

}

void CPlayer::Update(_float fTimeDelta)
{
    if (m_pGameInstance->IsKeyDown('W'))
        m_pTransformCom->Go_Straight(fTimeDelta);

    if (m_pGameInstance->IsKeyDown('S'))
        m_pTransformCom->Go_Backward(fTimeDelta);

    if (m_pGameInstance->IsKeyDown('A'))
        m_pTransformCom->Go_Left(fTimeDelta);

    if (m_pGameInstance->IsKeyDown('D'))
        m_pTransformCom->Go_Right(fTimeDelta);


    if (m_pGameInstance->IsKeyDown(VK_LBUTTON) < 0)
    {
        CPlayerStats::PLAYERSTAT_DESC PlayerStats = m_pPlayerStatsCom->Get_Stats();
        PlayerStats.fHp--;
        
        m_pPlayerStatsCom->Set_Stats(PlayerStats);

#ifdef _DEBUG
        std::cout << "[CPlayer::Update] Player HP : " << static_cast<int>(m_pPlayerStatsCom->Get_Stats().fHp) << std::endl;
#endif // _DEBUG
    
    }
    
    if (m_pGameInstance->IsKeyDown(VK_RBUTTON) < 0)
    {
        CPlayerStats::PLAYERSTAT_DESC PlayerStats = m_pPlayerStatsCom->Get_Stats();
        PlayerStats.fMp--;
    
        m_pPlayerStatsCom->Set_Stats(PlayerStats);

#ifdef _DEBUG
        std::cout << "[CPlayer::Update] Player MP : " << static_cast<int>(m_pPlayerStatsCom->Get_Stats().fMp) << std::endl;
#endif // _DEBUG
    
    }

    if (GetKeyState('D') < 0)
    {
        m_pTransformCom->Go_Right(fTimeDelta);
    }

    /*if (GetKeyState(VK_LBUTTON) < 0)
    {
        _float3		vTmp = m_pVIBufferCom->Compute_PickedPosition(m_pTransformCom->Get_WorldMatrix_Inverse());
        int a = 10;
    }*/


}

void CPlayer::Late_Update(_float fTimeDelta)
{
    m_pGameInstance->Add_RenderGroup(RENDERGROUP::RG_BLEND, this);
}

HRESULT CPlayer::Render()
{
	m_pTransformCom->Bind_Matrix();

	//if (FAILED(m_pTextureCom->Bind_Texture(0)))
	//	return E_FAIL;

    m_pAnimatorCom->Update_State(); // Bind_Texture 이 포함되어, 현재 State에 맞는 이미지 출력

	m_pVIBufferCom->Bind_Buffers();
	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CPlayer::Ready_Components()
{
    /* For Com_VIBuffer */
    if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_VIBuffer_Rect"),
        TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
        return E_FAIL;

    /* For.Com_Texture */
    if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Texture_Player_Roll"),
        TEXT("Com_Texture_Roll"), reinterpret_cast<CComponent**>(&m_pTextureCom_Roll))))
        return E_FAIL;
    if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Texture_Player_Idle_Lower"),
        TEXT("Com_Texture_Idle_Lower"), reinterpret_cast<CComponent**>(&m_pTextureCom_Lower))))
        return E_FAIL;


    /* For Com_Transform */
    CTransform::TRANSFORM_DESC TransformDesc{};
    TransformDesc.fSpeedPerSec = 5.f;
    TransformDesc.fRotationPerSec = D3DXToRadian(90.f);

    if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Transform"),
        TEXT("Com_Transform"), reinterpret_cast<CComponent**>(&m_pTransformCom), &TransformDesc)))
        return E_FAIL;

    /* For Com_PlayerStats */
    CPlayerStats::PLAYERSTAT_DESC PlayerStatDesc{};

    // 만약 기존 플레이 저장 정보가 존재한다면
    // 해당 정보를 불러오도록 나중에 수정
    PlayerStatDesc.strName  = L"테스트";
    PlayerStatDesc.iLevel   = 1;
    PlayerStatDesc.iExp     = 0;
    PlayerStatDesc.fHp      = 50.f;
    PlayerStatDesc.fMp      = 50.f;
    PlayerStatDesc.fDash    = 2.f;
    PlayerStatDesc.fAtkSpeed    = 1.0f;
    PlayerStatDesc.fMoveSpeed   = 1.0f;
    PlayerStatDesc.fHpRegen     = 0.f;
    PlayerStatDesc.fMpRegen     = 0.f;
    PlayerStatDesc.fDashRegen   = 0.f;
    PlayerStatDesc.fEvade   = 0.f;
    PlayerStatDesc.fDef     = 0.f;
    PlayerStatDesc.fExpMultiply     = 1.0f;
    PlayerStatDesc.fGoldMultiply    = 1.0f;

    if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_PlayerStats"),
        TEXT("Com_PlayerStats"), reinterpret_cast<CComponent**>(&m_pPlayerStatsCom), &PlayerStatDesc)))
        return E_FAIL;

    /* For Com_Animator */
    CAnimator::ANIMSTATE_DESC StartAnimStateDesc{};
    CAnimator::ANIMSTATE StartAnimState{};
    
    StartAnimState.pTextureCom = m_pTextureCom_Roll;     // 삽입할 텍스쳐 컴포넌트 주소정보
    StartAnimState.iFramePerImage = 4;  // 이미지 전환 간격 프레임
    StartAnimState.isExitable = true;   // 도중 나갈 수 있는지 여부
    
    StartAnimStateDesc.strTimerTag = L"Animator_Player_Main";   // 해당 애니메이터가 타이머에서 사용할 태그 key값
    StartAnimStateDesc.strFirstStateTag = L"Roll";              // 최초생성(시작) State의 Key값
    StartAnimStateDesc.tFirstAnimState = StartAnimState;        // 위에서 정의한 State Value 대입
    
    if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::LEVEL_STATIC), TEXT("Prototype_Component_Animator"),
        TEXT("Com_Animator"), reinterpret_cast<CComponent**>(&m_pAnimatorCom), &StartAnimStateDesc)))
        return E_FAIL;

    // m_pAnimatorCom->Add_State(L"태그명", { m_pTextureCom_상태명, 프레임단위 이미지전환간격, 도중 나갈수있는지});
    // 와 같은 꼴로 만들어서 넣어주면 됨
    m_pAnimatorCom->Add_State(L"Idle_Lower", { m_pTextureCom_Lower, 4, true });
    m_pAnimatorCom->Change_State(L"Idle_Lower");


    return S_OK;
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
    CPlayer* pInstance = new CPlayer(pGraphic_Device);

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX(TEXT("Failde to Created : CPlayer"));
        Safe_Release(pInstance);
    }

    return pInstance;
}

CGameObject* CPlayer::Clone(void* pArg)
{
    CPlayer* pInstance = new CPlayer(*this);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX(TEXT("Failde to Cloned : CPlayer"));
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CPlayer::Free()
{
    __super::Free();

    Safe_Release(m_pVIBufferCom);
    Safe_Release(m_pTransformCom);
    Safe_Release(m_pTextureCom_Roll);
    Safe_Release(m_pPlayerStatsCom);
    Safe_Release(m_pAnimatorCom);
}
