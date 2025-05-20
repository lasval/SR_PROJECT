#pragma once

#include "GameInstance.h"
#include "nlohmann/json.hpp"

BEGIN(Engine)


class CNetwork_Manager final : public CBase
{
private:
	CNetwork_Manager();
	virtual ~CNetwork_Manager() = default;

public:
	HRESULT Initialize();

public:
	_bool	Get();


private:
	_json SendHttpGetJson(const string& host, const string& port, const string& target);

public:
	static CNetwork_Manager* Create();
	virtual void Free() override;

};

END