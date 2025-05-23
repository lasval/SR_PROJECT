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

	m_pCurState = Find_State(pDesc->strFirstStateTag);
	m_strCurStateTag = pDesc->strFirstStateTag;
		
	// Ÿ�̸� ����
	m_pGameInstance->Add_Timer(m_strTimerTag);

	std::cout << "[CAnimator::Initialize] Initialized!" << std::endl;

	return S_OK;
}

void CAnimator::Update_State()
{
 	CTexture* pCurTextureCom = m_pCurState->pTextureCom;
	
	if (m_pCurState == nullptr)
		return;

	_uint iImageMaxIndex = pCurTextureCom->Get_NumTextures();
	_uint iImageCurIndex = m_iStackedFrames / m_pCurState->iFramePerImage;
	iImageCurIndex %= iImageMaxIndex;

	std::cout << "[CAnimator::Update_State] " << iImageCurIndex << "/" << iImageMaxIndex << std::endl;

	pCurTextureCom->Bind_Texture(iImageCurIndex);
	m_iStackedFrames++;
}

HRESULT CAnimator::Add_State(const _wstring strStateTag, ANIMSTATE _state)
{
	// State�� �̹� �����Ѵٸ�
	if (nullptr != Find_State(strStateTag))
	{
		std::wcout << "[CAnimator::Add_State] Adding State Failed. \"" << strStateTag << "\" state already exist." << std::endl;
		return E_FAIL;
	}
	
	if (_state.pTextureCom == nullptr)
	{
		std::wcout << "[CAnimator::Add_State] Adding State Failed. Texture Component was nullptr." << std::endl;
		return E_FAIL;
	}

	m_pStates.emplace(strStateTag, _state);
	std::wcout << "[CAnimator::Add_State] \"" << strStateTag << "\" State Added." << std::endl;

	return S_OK;
}

void CAnimator::Change_State(const _wstring strStateTag, _bool isChangeCurFrame)
{
	ANIMSTATE* pTmpState = Find_State(strStateTag);

	// ��� ���̰� ������ State�� ��� ����,
	// ��� ���̰� �Ұ����� State�� ��� ���������� ��ȯ�� �� ����� �ð��� ���� ��쿡�� ����

	if (nullptr == pTmpState)
	{
		std::wcout << "[CAnimator::Change_State] Failed to Change State. Can't find State : \"" << strStateTag << "\"." << std::endl;
		return;
	}

	_uint iTextureMaxFrame = m_pCurState->pTextureCom->Get_NumTextures();

	// ksta : �� �Ǵ��� Ȯ���ؾ���
	if (m_iStackedFrames / m_pCurState->iFramePerImage > iTextureMaxFrame &&
		!m_pCurState->isExitable)
	{
		// �ð� ������� ��� ���̰� �Ұ����� State �ε� �������� ������ ���� ���
		std::wcout << "[CAnimator::Change_State] Failed to Change State. \"" << m_strCurStateTag << "\" State Frame Elapsed : " << m_iStackedFrames << " / " << m_pCurState->pTextureCom->Get_NumTextures() << "." << std::endl;
		return;
	}

	m_pCurState = pTmpState;
	m_strCurStateTag = strStateTag;
	std::wcout << "[CAnimator::Change_State] State Changed to \""<< strStateTag << "\"." << std::endl;
	
	// ������ ���� ���� ���ʿ�ÿ��� ����
	if (isChangeCurFrame)
		m_iStackedFrames = 0;
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
