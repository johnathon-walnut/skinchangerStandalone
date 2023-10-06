#pragma once

#include <cstdint>

class Memory
{
public:
	std::uintptr_t FindSignature(const char* szModule, const char* szSignature);
	void* FindInterface(const char* szModule, const char* szVersion);
};

inline Memory g_Memory;