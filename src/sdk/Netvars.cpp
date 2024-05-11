#include "Netvars.h"

std::size_t Netvars::GetOffset(RecvTable* pTable, const char* szPropName)
{
	for (int i = 0; i < pTable->m_nProps; i++)
	{
		const auto& prop = pTable->m_pProps[i];

		if (strcmp(prop.m_pVarName, szPropName) == 0)
			return prop.GetOffset();

		if (RecvTable* pChild = prop.GetDataTable())
			if (std::size_t offset = GetOffset(pChild, szPropName))
				return offset;
	}

	return 0;
}

std::size_t Netvars::GetNetvar(const char* szTableName, const char* szPropName)
{
	ClientClass* pClasses = I::BaseClientDLL->GetAllClasses();
	if (!pClasses)
		return 0;

	for (ClientClass* pClass = pClasses; pClass; pClass = pClass->m_pNext)
		if (std::strcmp(pClass->m_pNetworkName, szTableName) == 0)
			return GetOffset(pClass->m_pRecvTable, szPropName);

	return 0;
}

#include <fstream>

static std::ofstream File;
static void DumpNetvars(RecvTable* pTable, int depth)
{
	if (!pTable)
		return;

	for (int i = 0; i < pTable->m_nProps; ++i)
	{
		RecvProp* pProp = &pTable->m_pProps[i];
		if (!pProp || !pProp->m_pVarName)
			continue;

		if (strcmp(pProp->m_pVarName, "baseclass") != 0)
			File << std::string(depth * 4, ' ') << pProp->m_pVarName << " (offset: " << pProp->GetOffset() << ")\n";

		// If the property is a datatable, recursively dump its netvars
		if (pProp->GetDataTable())
			DumpNetvars(pProp->GetDataTable(), depth + 1);
	}
}

static void DumpTabless(ClientClass* pClass, int depth = 0)
{
	if (!pClass)
		return;

	// Dump class name
	File << std::string(depth * 4, ' ') << pClass->GetName() << ":\n";

	// Dump netvars
	DumpNetvars(pClass->m_pRecvTable, depth + 1);

	// Recurse for next class
	DumpTabless(pClass->m_pNext, depth);
}

void Netvars::DumpTables()
{
	File.open("NETVAR_DUMP_NEW.h");

	DumpTabless(I::BaseClientDLL->GetAllClasses());

	File.close();
}