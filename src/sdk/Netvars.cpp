#include "Netvars.h"

std::uintptr_t Netvars::GetOffset(RecvTable* pTable, const char* szPropName)
{
	for (int i = 0; i < pTable->m_nProps; i++)
	{
		const auto& prop = pTable->m_pProps[i];

		if (strcmp(prop.m_pVarName, szPropName) == 0)
			return prop.GetOffset();

		if (RecvTable* pChild = prop.GetDataTable())
			if (std::uintptr_t offset = GetOffset(pChild, szPropName))
				return offset;
	}

	return 0;
}

std::uintptr_t Netvars::GetNetvar(const char* szTableName, const char* szPropName)
{
	ClientClass* pClasses = I::BaseClientDLL->GetAllClasses();
	if (!pClasses)
		return 0;

	for (ClientClass* pClass = pClasses; pClass; pClass = pClass->m_pNext)
		if (std::strcmp(pClass->m_pNetworkName, szTableName) == 0)
			return GetOffset(pClass->m_pRecvTable, szPropName);

	return 0;
}
