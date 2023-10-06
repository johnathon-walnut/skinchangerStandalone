#pragma once

#include "TF2/cdll_int.h"
#include "TF2/client_class.h"

class Netvars
{
public:
	std::uintptr_t GetOffset(RecvTable* pTable, const char* szPropName);
	std::uintptr_t GetNetvar(const char* szTableName, const char* szPropName);
};

inline Netvars g_Netvars;