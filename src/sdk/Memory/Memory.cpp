#include "Memory.h"

#include <Windows.h>
#include <vector>
#include <Psapi.h>

std::uintptr_t Memory::FindSignature(const std::string_view moduleName, const std::string_view pattern)
{
	auto patternToBytes = [](std::string_view pattern) -> std::vector<int>
		{
			std::vector<int> bytes;

			char* const start{ const_cast<char*>(pattern.data()) };
			char* const end{ start + std::strlen(pattern.data()) };

			for (char* current{ start }; current < end; ++current)
			{
				if (*current == '?')
				{
					++current;

					if (*current == '?')
					{
						++current;
					}

					bytes.push_back(-1);
				}
				else
				{
					bytes.push_back(std::strtoul(current, &current, 16));
				}
			}

			return bytes;
		};

	const auto module{ GetModuleHandleA(moduleName.data()) };

	if (!module)
	{
		return 0;
	}

	MODULEINFO moduleInfo;

	if (!K32GetModuleInformation(GetCurrentProcess(), module, &moduleInfo, sizeof(moduleInfo)))
	{
		return 0;
	}

	const auto imageSize{ moduleInfo.SizeOfImage };

	if (!imageSize)
	{
		return 0;
	}

	const auto patternBytes{ patternToBytes(pattern) };
	const byte* const scanStart{ reinterpret_cast<byte*>(module) };
	const std::size_t patternSize{ patternBytes.size() };
	const int* patternBytesData{ patternBytes.data() };

	for (std::size_t i{}; i < imageSize - patternSize; ++i)
	{
		bool found{ true };

		for (std::size_t j{}; j < patternSize; ++j)
		{
			if (scanStart[i + j] != patternBytesData[j] && patternBytesData[j] != -1)
			{
				found = false;
				break;
			}
		}

		if (found)
		{
			return reinterpret_cast<std::uintptr_t>(&scanStart[i]);
		}
	}

	return 0;
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
	const auto module{ GetModuleHandleA(szModule) };
	if (!module)
	{
		return 0;
	}

	using CreateInterfaceFn = void* (*)(const char* name, int* returnCode);

	const auto createInterface{ reinterpret_cast<CreateInterfaceFn>(GetProcAddress(module, "CreateInterface")) };
	if (!createInterface)
	{
		return 0;
	}

	for (int i = 0; i < 100; i++)
	{
		if (const auto iface{ createInterface(szVersion, nullptr) })
		{
			return iface;
		}
	}

	return 0;
}