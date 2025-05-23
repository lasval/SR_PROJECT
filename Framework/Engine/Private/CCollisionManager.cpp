// CollisionManager.cpp
#include "CollisionManager.h"
#include "Collider.h"
#include "Collider_OBB.h"
#include "GameObject.h"

USING(Engine)

HRESULT CCollisionManager::Add_Collider(CCollider* pCollider)
{
	if (pCollider == nullptr)
		return E_FAIL;

	COLLIDER_OBJ_TYPE eColliderType = pCollider->Get_ColliderObjType();
	m_Colliders[ENUM_CLASS(eColliderType)].push_back(pCollider);
	return S_OK;
}

void CCollisionManager::Clear_Colliders()
{
	for (size_t i = 0; i < ENUM_CLASS(COLLIDER_OBJ_TYPE::COL_END); ++i)
		m_Colliders[i].clear();
}

void CCollisionManager::Check_AllCollisions()
{
	
}

bool CCollisionManager::Check_OBBtoOBB(CCollider_OBB* pColliderA, CCollider_OBB* pColliderB)
{
	const _float fEpsilon = 1e-5f;

	_float3 vCenterA, vExtentA, vAxisA[3];
	_float3 vCenterB, vExtentB, vAxisB[3];

	pColliderA->Get_MatrixData(vCenterA, vExtentA, vAxisA);
	pColliderB->Get_MatrixData(vCenterB, vExtentB, vAxisB);

	_float3 vDeltaCenter = vCenterB - vCenterA;

	_float fRot[3][3];
	_float fAbsRot[3][3];

	for (int i = 0; i < 3; ++i)
	{
		const _float3& axisA = vAxisA[i];
		for (int j = 0; j < 3; ++j)
		{
			fRot[i][j] = D3DXVec3Dot(&axisA, &vAxisB[j]);
			fAbsRot[i][j] = fabsf(fRot[i][j]) + fEpsilon;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		_float fProjCenter = fabsf(D3DXVec3Dot(&vDeltaCenter, &vAxisA[i]));
		_float fProjA = vExtentA[i];
		_float fProjB =
			vExtentB.x * fAbsRot[i][0] +
			vExtentB.y * fAbsRot[i][1] +
			vExtentB.z * fAbsRot[i][2];

		if (fProjCenter > fProjA + fProjB)
			return false;
	}

	for (int i = 0; i < 3; ++i)
	{
		_float fProjCenter = fabsf(D3DXVec3Dot(&vDeltaCenter, &vAxisB[i]));
		_float fProjA =
			vExtentA.x * fAbsRot[0][i] +
			vExtentA.y * fAbsRot[1][i] +
			vExtentA.z * fAbsRot[2][i];
		_float fProjB = vExtentB[i];

		if (fProjCenter > fProjA + fProjB)
			return false;
	}

	return true;
}

CCollisionManager* CCollisionManager::Create()
{
	return new CCollisionManager();
}

void CCollisionManager::Free()
{
	Clear_Colliders();
}
