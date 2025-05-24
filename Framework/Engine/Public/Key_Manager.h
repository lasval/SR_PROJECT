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
	void AddTrackingKey(int iKey);                         // �߰���
	bool IsKeyDown(int iKey) const;   // �̹� �����ӿ� ����
	bool IsKeyUp(int iKey) const;     // �̹� �����ӿ� ����
	bool IsKeyHold(int iKey) const;   // ��� ����
	float GetKeyHoldTime(int iKey) const; // ���� �ð� (���û���)


private:
	unordered_map<int, bool> m_mPrevState;
	unordered_map<int, bool> m_mCurrState;
	unordered_map<int, float> m_mKeyHoldTime;
	vector<int> m_vTrackingKeys;

public:
	static CKey_Manager* Create();
	virtual void Free() override;

};

END