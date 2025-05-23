#include "Animator.h"
#include "GameInstance.h" // �̷��� �ǳ�


// �ִϸ����͸� �� ĳ���Ϳ� ������ ����� ���ɼ��� ����
// �׷��� Ÿ�̸Ӹ� �ѵ��� �����ϸ� �ȵ� �� ����
// ���� Ÿ�̸� �±׸� ���� �ȵ��ٵ�..
// 
// �׷� �ִϸ����� ������ Ÿ�̸� �±׷� ����� ���ڿ��� ���ڷ� �޾ƿ;��ϳ�


CAnimator::CAnimator(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent{ pGraphic_Device }
{
}

CAnimator::CAnimator(const CAnimator& Prototype)
	: CComponent{ Prototype }
{
}

HRESULT CAnimator::Initialize_Prototype()
{
	std::cout << "[CAnimator::Initialize_Prototype] Prototype Initialized!" << std::endl;

	return S_OK;
}

HRESULT CAnimator::Initialize(void* pArg)
{
	if (nullptr == pArg)
	{
		std::cout << "[CAnimator::Initialize] Initialized Failed. Argument was nullptr." << std::endl;
		return E_FAIL;
	}


	ANIMSTATE_DESC* pDesc = static_cast<ANIMSTATE_DESC*>(pArg);
	Add_State(pDesc->strFirstStateTag, pDesc->tFirstAnimState);
	m_strTimerTag = pDesc->strTimerTag;

	m_pCurState = &pDesc->tFirstAnimState;
	m_strCurStateTag = pDesc->strFirstStateTag;
		
	// Ÿ�̸� ����
	m_pGameInstance->Add_Timer(m_strTimerTag);


	std::cout << "[CAnimator::Initialize] Initialized!" << std::endl;

	return S_OK;
}

HRESULT CAnimator::Add_State(const _wstring strStateTag, ANIMSTATE _state)
{
	if (nullptr != Find_State(strStateTag))
	{
		std::cout << "[CAnimator::Add_State] Adding State Failed." << std::endl;
		return E_FAIL;
	}

	m_pStates.emplace(strStateTag, _state);
	std::wcout << "[CAnimator::Add_State] \"" << strStateTag << "\" State Added." << std::endl;

	return S_OK;
}

void CAnimator::Change_State(const _wstring strStateTag)
{
	ANIMSTATE* pTmpState = Find_State(strStateTag);

	// ��� ���̰� ������ State�� ��� ����,
	// ��� ���̰� �Ұ����� State�� ��� ���������� ��ȯ�� �� ����� �ð��� ���� ��쿡�� ����

	if (nullptr == pTmpState)
	{
		std::wcout << "[CAnimator::Change_State] Failed to Change State. Can't find State : \"" << strStateTag << "\"." << std::endl;
		return;
	}
	else if (m_pGameInstance->Get_TimeDelta(m_strTimerTag) <= m_pCurState->fAnimLength &&
		!m_pCurState->isExitable)
	{
		// �ð� ������� ��� ���̰� �Ұ����� State �ε� �ð��� ����� ������ ���� ���
		float fElapsedTime = m_pGameInstance->Get_TimeDelta(m_strTimerTag);
		std::wcout << "[CAnimator::Change_State] Failed to Change State. \"" << m_strCurStateTag << "\" State Time Elapsed : " << fElapsedTime << "s / " << m_pCurState->fAnimLength  << "s." << std::endl;
		return;
	}

	m_pCurState = pTmpState;
	m_strCurStateTag = strStateTag;
	std::wcout << "[CAnimator::Change_State] State Changed to \""<< strStateTag << "\"." << std::endl;
	m_pGameInstance->Compute_TimeDelta(m_strTimerTag);
}

CAnimator::ANIMSTATE* CAnimator::Find_State(const _wstring& strStateTag)
{
	auto iter = m_pStates.find(strStateTag);

	if (iter == m_pStates.end())
		return nullptr;

	return &(iter->second);
}


CAnimator* CAnimator::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CAnimator* pInstance = new CAnimator(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CAnimator"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CAnimator::Clone(void* pArg)
{
	CAnimator* pInstance = new CAnimator(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to cloned : CAnimator"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CAnimator::Free()
{
	__super::Free();
}
