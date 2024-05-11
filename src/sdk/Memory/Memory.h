#pragma once

#include <cstdint>
#include <string_view>

class Memory
{
public:
	std::uintptr_t FindSignature(const std::string_view moduleName, const std::string_view pattern);
	void* FindInterface(const char* szModule, const char* szVersion);
};

inline Memory g_Memory;