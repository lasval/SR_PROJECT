#pragma once

#include "Base.h"
BEGIN(Engine)

class CCollisionManager final : public CBase
{
private:
	CCollisionManager() = default;
	virtual ~CCollisionManager() = default;

public:
	HRESULT Add_Collider(class CCollider* pCollider);
	void Clear_Colliders();
	void Check_AllCollisions();

private:
	bool Check_OBBtoOBB(class CCollider_OBB* pA, class CCollider_OBB* pB);

private:
	vector<CCollider*> m_Colliders[ENUM_CLASS(COLLIDER_OBJ_TYPE::COL_END)];

public:
	static CCollisionManager* Create();
	virtual void Free() override;
};

END
