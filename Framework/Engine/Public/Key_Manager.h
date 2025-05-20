#pragma once

#include "VIBuffer_Rect.h"
#include "VIBuffer_Terrain.h"
#include "Transform.h"
#include "Texture.h"

BEGIN(Engine)

class CKey_Manager final : public CBase
{
private:
	CKey_Manager();
	virtual ~CKey_Manager() = default;

public:
	HRESULT Initialize();
	void Update(float fDeltaTime);                    // 매 프레임 호출

public:
	bool IsKeyDown(int iKey);                           // 지금 눌리고 있는가
	bool IsKeyUp(int iKey);                             // 이번 프레임에 떼졌는가
	bool IsKeyPressedOnce(int iKey);                    // 눌린 순간만 감지 (짧게)
	bool IsKeyHeld(int iKey, float fHoldThresholdSec);   // 특정 시간 이상 눌렸는가


private:
	map<int, bool> m_mPrevState;
	map<int, bool> m_mCurrState;
	map<int, bool> m_mProcessed;     // PressedOnce에서 사용
	map<int, float> m_mKeyHoldTime;  // 키 누른 시간 누적 (초)


public:
	static CKey_Manager* Create();
	virtual void Free() override;

};

END