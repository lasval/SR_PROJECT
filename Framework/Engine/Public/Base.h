#pragma once

#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected:
	CBase();
	virtual ~CBase() = default;

public:
	unsigned int AddRef();
	unsigned int Release();

private:
	unsigned int m_iRefCnt = {};

public:
	virtual void Free();
};

END
