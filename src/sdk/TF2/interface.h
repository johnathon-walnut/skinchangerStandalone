#pragma once

#include "../Memory/Memory.h"
#include "../Signatures/Signatures.h"
#include "../Interfaces/Interfaces.h"

class IBaseInterface
{
public:
	virtual	~IBaseInterface() {}
};

typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);
typedef void* (*InstantiateInterfaceFn)();