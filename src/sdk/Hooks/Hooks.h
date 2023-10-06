#pragma once

#include <cstdint>
#include <vector>

struct Signature;

class Hook
{
public:
	void* m_pOriginal;
	void* m_pInitFunc;
	const char* m_szName;

	void CreateHook(std::uintptr_t pTarget, void* pDetour);

	template <typename FN>
	inline FN Original() const
	{
		return reinterpret_cast<FN>(m_pOriginal);
	}

public:
	Hook(const char* szName, void* pInitFunc);
};

class Hooks
{
	std::vector<Hook*> m_vHooks;

public:
	inline void Add(Hook* pHook)
	{
		m_vHooks.push_back(pHook);
	}

	void Init();
	void Stop();
};

inline Hooks g_Hooks;

#define HOOK(name, address, returnType, callingConvention, ...) namespace H { \
namespace name { \
void Init(); \
inline Hook hook(#name, Init); \
using FN = returnType(callingConvention*)(__VA_ARGS__); \
returnType callingConvention Func(__VA_ARGS__); \
} \
} \
void H::name::Init() { \
hook.CreateHook(address, &Func); \
} \
returnType callingConvention H::name::Func(__VA_ARGS__)

#define CALL_ORIGINAL hook.Original<FN>()
#define CALL_OTHER(name) H::name::hook.Original<H::name::FN>()