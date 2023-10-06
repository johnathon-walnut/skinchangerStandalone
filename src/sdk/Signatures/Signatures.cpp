#include "Signatures.h"

#include "../Memory/Memory.h"

void Signatures::Init()
{
	for (auto& sig : m_vSignatures)
	{
		sig->m_nAddress = g_Memory.FindSignature(sig->m_szModule, sig->m_szSignature);
		if (sig->m_nAddress == 0)
		{
			printf("Failed to find signature %s in module %s\n", sig->m_szSignature, sig->m_szModule);
			exit(EXIT_FAILURE);
		}

		if (sig->m_nOffset != 0)
		{
			sig->m_nAddress += sig->m_nOffset;
		}

		if (sig->m_bRelative)
		{
			std::uintptr_t nAddress = sig->m_nAddress + 1;
			std::uintptr_t nOffset = *reinterpret_cast<std::uintptr_t*>(nAddress);
			sig->m_nAddress = nAddress + nOffset + 4;
		}

		if (sig->m_nAddress == 0)
		{
			printf("Failed to find signature %s in module %s\n", sig->m_szSignature, sig->m_szModule);
			exit(EXIT_FAILURE);
		}
	}
}

Signature::Signature(const char* szModule, const char* szSignature, std::uintptr_t nOffset, bool bRelative)
{
	m_nAddress = 0x0;

	m_szModule = szModule;
	m_szSignature = szSignature;
	m_nOffset = nOffset;
	m_bRelative = bRelative;

	g_Signatures.Add(this);
}
