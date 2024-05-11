#include "Interfaces.h"

Interface::Interface(const char* szName, void** pInterfacePtr, const char* szModule)
{
	this->m_szName = szName;
	this->m_pInterfacePtr = pInterfacePtr;
	this->m_szModule = szModule;

	g_Interfaces.Add(this);
}

SignatureInterface::SignatureInterface(const char* szName, void** pInterfacePtr, const char* szModule, 
									   const char* szSignature, size_t nDereferenceCount, size_t nOffset, bool bRelative) : Interface(szName, pInterfacePtr, szModule)
{
	this->m_szSignature = szSignature;
	this->m_nDereferenceCount = nDereferenceCount;
	this->m_nOffset = nOffset;
	this->m_bRelative = bRelative;
}

VersionInterface::VersionInterface(const char* szName, void** pInterfacePtr, const char* szModule, const char* szVersion) : Interface(szName, pInterfacePtr, szModule)
{
	this->m_szVersion = szVersion;
}

#include "../Memory/Memory.h"

void Interfaces::Init()
{
	for (size_t i = 0; i < m_vInterfaces.size(); i++)
	{
		Interface* pInterface = m_vInterfaces.at(i);
		if (!pInterface)
			continue;

		if (!pInterface->m_pInterfacePtr)
			continue;

		if (!pInterface->m_szModule)
			continue;

		if (!pInterface->m_szName)
			continue;

		if (auto signatureInterface = dynamic_cast<SignatureInterface*>(pInterface))
		{
			auto pAddress = g_Memory.FindSignature(pInterface->m_szModule, signatureInterface->m_szSignature);
			if (!pAddress)
			{
				printf("Failed to find %s in %s\n", signatureInterface->m_szName, signatureInterface->m_szModule);
				exit(EXIT_FAILURE);
			}

			if (signatureInterface->m_bRelative)
				pAddress = pAddress + 7u + *reinterpret_cast<std::int32_t*>(pAddress + 3u);

			*pInterface->m_pInterfacePtr = reinterpret_cast<void*>(pAddress + signatureInterface->m_nOffset);

			for (size_t dereference = 0; dereference < signatureInterface->m_nDereferenceCount; dereference++)
				*pInterface->m_pInterfacePtr = *reinterpret_cast<void**>(*pInterface->m_pInterfacePtr);

			continue;
		}

		if (auto versionInterface = dynamic_cast<VersionInterface*>(pInterface))
		{
			*pInterface->m_pInterfacePtr = g_Memory.FindInterface(pInterface->m_szModule, versionInterface->m_szVersion);
			if (!*pInterface->m_pInterfacePtr)
			{
				printf("Failed to find %s in %s\n", versionInterface->m_szName, versionInterface->m_szModule);
				exit(EXIT_FAILURE);
			}
		}
	}
}
