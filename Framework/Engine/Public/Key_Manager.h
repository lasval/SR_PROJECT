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
	void Update(float fDeltaTime);                    // �� ������ ȣ��

public:
	bool IsKeyDown(int key) const;   // �̹� �����ӿ� ����
	bool IsKeyUp(int key) const;     // �̹� �����ӿ� ����
	bool IsKeyHold(int key) const;   // ��� ����
	float GetKeyHoldTime(int key) const; // ���� �ð� (���û���)


private:
	std::unordered_map<int, bool> m_mPrevState;
	std::unordered_map<int, bool> m_mCurrState;
	std::unordered_map<int, float> m_mKeyHoldTime;


public:
	static CKey_Manager* Create();
	virtual void Free() override;

};

END