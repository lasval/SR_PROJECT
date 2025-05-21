#include "Key_Manager.h"

#include "GameInstance.h"

CKey_Manager::CKey_Manager()
{
}

HRESULT CKey_Manager::Initialize()
{

	return S_OK;
}

void CKey_Manager::Update(float fDeltaTime)
{
    for (auto& pair : m_mCurrState)
    {
        int vk = pair.first;

        bool bPrev = m_mCurrState[vk];
        bool bCurr = (GetAsyncKeyState(vk) & 0x8000) != 0;

        m_mPrevState[vk] = bPrev;
        m_mCurrState[vk] = bCurr;

        if (bCurr)
        {
            m_mKeyHoldTime[vk] += fDeltaTime;
        }
        else
        {
            m_mKeyHoldTime[vk] = 0.f;
            m_mProcessed[vk] = false;
        }
    }
}

bool CKey_Manager::IsKeyDown(int iKey)
{
    m_mCurrState[iKey] = (GetAsyncKeyState(iKey) & 0x8000) != 0;
    return m_mCurrState[iKey];
}

bool CKey_Manager::IsKeyUp(int iKey)
{
    return (m_mPrevState[iKey] == true && m_mCurrState[iKey] == false);
}

bool CKey_Manager::IsKeyPressedOnce(int iKey)
{
    bool bNow = (GetAsyncKeyState(iKey) & 0x8000) != 0;
    bool bPrev = m_mPrevState[iKey];

    if (bNow && !bPrev && !m_mProcessed[iKey])
    {
        m_mProcessed[iKey] = true;
        m_mCurrState[iKey] = bNow;
        return true;
    }

    m_mCurrState[iKey] = bNow;
    return false;
}

bool CKey_Manager::IsKeyHeld(int iKey, float fHoldThresholdSec)
{
    return m_mKeyHoldTime[iKey] >= fHoldThresholdSec;
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
