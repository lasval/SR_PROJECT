#include "Key_Manager.h"

#include "GameInstance.h"

CKey_Manager::CKey_Manager()
{
}

HRESULT CKey_Manager::Initialize()
{
	m_mPrevState.clear();
	m_mCurrState.clear();
	m_mKeyHoldTime.clear();
	return S_OK;
}

void CKey_Manager::Update(float fDeltaTime)
{
    for (int vk = 0x01; vk <= 0xFE; ++vk)  // 0x01~0xFE: 가용 가능한 가상키
    {
        bool bCurr = (GetAsyncKeyState(vk) & 0x8000) != 0;

        // 이전 상태 저장
        m_mPrevState[vk] = m_mCurrState[vk];
        m_mCurrState[vk] = bCurr;

        // 누르고 있다면 누른 시간 누적
        if (bCurr)
            m_mKeyHoldTime[vk] += fDeltaTime;
        else
            m_mKeyHoldTime[vk] = 0.0f;
    }
}

bool CKey_Manager::IsKeyDown(int key) const
{
    auto itPrev = m_mPrevState.find(key);
    auto itCurr = m_mCurrState.find(key);
    return itCurr != m_mCurrState.end() && itCurr->second && (!itPrev->second);
}

bool CKey_Manager::IsKeyUp(int key) const
{
    auto itPrev = m_mPrevState.find(key);
    auto itCurr = m_mCurrState.find(key);
    return itCurr != m_mCurrState.end() && !itCurr->second && itPrev->second;
}

bool CKey_Manager::IsKeyHold(int key) const
{
    auto itCurr = m_mCurrState.find(key);
    return itCurr != m_mCurrState.end() && itCurr->second;
}

float CKey_Manager::GetKeyHoldTime(int key) const
{
    auto it = m_mKeyHoldTime.find(key);
    if (it != m_mKeyHoldTime.end())
        return it->second;
    return 0.0f;
}

CKey_Manager* CKey_Manager::Create()
{
	CKey_Manager* pInstance = new CKey_Manager();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX(TEXT("Failed to Created : CKey_Manager"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CKey_Manager::Free()
{
	__super::Free();

}
