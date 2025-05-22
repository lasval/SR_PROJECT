#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CPlayerStats final : public CComponent
{
public:
	typedef struct tagPlayerStatsDesc
	{
		_wstring	strName;
		_int		iLevel;
		_int		iExp;

		_float		fHp;
		_float		fMp;
		_float		fDash;
		_float		fAtkSpeed;
		_float		fMoveSpeed;

		_float		fHpRegen;
		_float		fMpRegen;
		_float		fDashRegen;

		_float		fEvade;
		_float		fDef;

		_float		fExpMultiply;
		_float		fGoldMultiply;
	}PLAYERSTAT_DESC;

private:
	CPlayerStats(LPDIRECT3DDEVICE9 pGraphic_Device);
	CPlayerStats(const CPlayerStats& Prototype);
	virtual ~CPlayerStats() = default;

public:
	PLAYERSTAT_DESC Get_Stats() const{
		return tPlayerStats;
	}

	void Set_Stats(PLAYERSTAT_DESC _stats) {
		tPlayerStats = _stats;
	}

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

private:
	PLAYERSTAT_DESC tPlayerStats = {};

public:
	static CPlayerStats* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};


END
