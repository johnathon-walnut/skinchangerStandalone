#include "Hooks.h"

#include "../../utils/MinHook/include/MinHook.h"

Hook::Hook(const char* szName, void* pInitFunc)
{
	m_pOriginal = nullptr;
	m_pInitFunc = pInitFunc;
	m_szName = szName;

	g_Hooks.Add(this);
}

void Hook::CreateHook(std::uintptr_t pTarget, void* pDetour)
{
	MH_STATUS status = MH_CreateHook(reinterpret_cast<void*>(pTarget), pDetour, &m_pOriginal);
	if (status != MH_OK)
	{
		printf("Failed to create hook for %s! MH_STATUS: %d\n", m_szName, status);
		exit(EXIT_FAILURE);
	}
}

void Hooks::Init()
{
	MH_STATUS initStatus = MH_Initialize();
	if (initStatus != MH_OK)
	{
		printf("Failed to initialize MinHook! MH_STATUS: %d\n", initStatus);
		exit(EXIT_FAILURE);
	}

	for (Hook* pHook : m_vHooks)
	{
		reinterpret_cast<void(__cdecl*)()>(pHook->m_pInitFunc)();
	}

	MH_STATUS enableStatus = MH_EnableHook(MH_ALL_HOOKS);
	if (enableStatus != MH_OK)
	{
		printf("Failed to enable hooks! MH_STATUS: %d\n", enableStatus);
		exit(EXIT_FAILURE);
	}
}

void Hooks::Stop()
{
	MH_STATUS disableStatus = MH_Uninitialize();
	if (disableStatus != MH_OK)
	{
		printf("Failed to disable hooks! MH_STATUS: %d\n", disableStatus);
		exit(EXIT_FAILURE);
	}
}
