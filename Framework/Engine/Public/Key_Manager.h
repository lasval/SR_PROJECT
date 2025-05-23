#pragma once

#include "GameInstance.h"

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
	bool IsKeyDown(int key) const;   // 이번 프레임에 눌림
	bool IsKeyUp(int key) const;     // 이번 프레임에 떼짐
	bool IsKeyHold(int key) const;   // 계속 눌림
	float GetKeyHoldTime(int key) const; // 눌린 시간 (선택사항)


private:
	std::unordered_map<int, bool> m_mPrevState;
	std::unordered_map<int, bool> m_mCurrState;
	std::unordered_map<int, float> m_mKeyHoldTime;


public:
	static CKey_Manager* Create();
	virtual void Free() override;

};

END