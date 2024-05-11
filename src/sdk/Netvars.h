#pragma once

#include "TF2/cdll_int.h"
#include "TF2/client_class.h"

class Netvars
{
public:
	std::size_t GetOffset(RecvTable* pTable, const char* szPropName);
	std::size_t GetNetvar(const char* szTableName, const char* szPropName);

	void DumpTables();
};

inline Netvars g_Netvars;