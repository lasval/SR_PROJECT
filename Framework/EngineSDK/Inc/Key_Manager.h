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
	void Update(float fDeltaTime);                    // �� ������ ȣ��

public:
	bool IsKeyDown(int iKey);                           // ���� ������ �ִ°�
	bool IsKeyUp(int iKey);                             // �̹� �����ӿ� �����°�
	bool IsKeyPressedOnce(int iKey);                    // ���� ������ ���� (ª��)
	bool IsKeyHeld(int iKey, float fHoldThresholdSec);   // Ư�� �ð� �̻� ���ȴ°�


private:
	map<int, bool> m_mPrevState;
	map<int, bool> m_mCurrState;
	map<int, bool> m_mProcessed;     // PressedOnce���� ���
	map<int, float> m_mKeyHoldTime;  // Ű ���� �ð� ���� (��)


public:
	static CKey_Manager* Create();
	virtual void Free() override;

};

END