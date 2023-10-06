#include "Memory.h"

#include <Windows.h>

#define INRANGE(x, a, b) (x >= a && x <= b) 
#define GetBits(x) (INRANGE((x & (~0x20)),'A','F') ? ((x & (~0x20)) - 'A' + 0xA) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GetBytes(x) (GetBits(x[0]) << 4 | GetBits(x[1]))

DWORD FindSignatureInternal(const DWORD& dwAddress, const DWORD& dwLength, const char* szPattern)
{
	auto szPat = szPattern;
	DWORD dwFirstMatch = 0x0;

	for (auto dwCurrent = dwAddress; dwCurrent < dwLength; dwCurrent++)
	{
		if (!*szPat)
		{
			return dwFirstMatch;
		}

		const auto pCurrentByte = *(BYTE*)dwCurrent;
		const auto pBytePattern = *(BYTE*)szPat;

		if (pBytePattern == '\?' || pCurrentByte == GetBytes(szPat))
		{
			if (!dwFirstMatch)
				dwFirstMatch = dwCurrent;

			if (!szPat[2])
				return dwFirstMatch;

			szPat += (pBytePattern == '\?\?' || pBytePattern != '\?') ? 3 : 2;
		}
		else
		{
			szPat = szPattern;
			dwFirstMatch = 0x0;
		}
	}

	return 0x0;
}

std::uintptr_t Memory::FindSignature(const char* szModule, const char* szSignature)
{
	const auto dwModuleHandle = reinterpret_cast<DWORD>(GetModuleHandleA(szModule));
	if (!dwModuleHandle)
		return 0x0;

	const auto pNtHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(dwModuleHandle + reinterpret_cast<PIMAGE_DOS_HEADER>(dwModuleHandle)->e_lfanew);
	if (!pNtHeaders)
		return 0x0;

	return FindSignatureInternal(dwModuleHandle + pNtHeaders->OptionalHeader.BaseOfCode, dwModuleHandle + pNtHeaders->OptionalHeader.SizeOfCode, szSignature);
}

using InstantiateInterfaceFn = void* (__cdecl*)();

struct InterfaceReg
{
	InstantiateInterfaceFn m_pInterface = nullptr;
	const char* m_pszInterfaceName = nullptr;
	InterfaceReg* m_pNextInterface = nullptr;
};

void* Memory::FindInterface(const char* szModule, const char* szVersion)
{
	const auto moduleHandle = GetModuleHandleA(szModule);
	if (!moduleHandle)
		return 0x0;

	auto dwCreateInterface = reinterpret_cast<DWORD>(GetProcAddress(moduleHandle, "CreateInterface"));
	if (!dwCreateInterface)
		return 0x0;

	auto pList = **reinterpret_cast<InterfaceReg***>((dwCreateInterface + 0x5 + *reinterpret_cast<DWORD*>(dwCreateInterface + 0x5)) + 0x4 + 0x6);
	if (!pList)
		return 0x0;

	while (pList != nullptr)
	{
		if (strstr(pList->m_pszInterfaceName, szVersion) &&
			(strlen(pList->m_pszInterfaceName) - strlen(szVersion)) < 5)
		{
			return pList->m_pInterface();
		}

		pList = pList->m_pNextInterface;
	}

	return 0x0;
}