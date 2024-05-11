#pragma once

#include <cstdint>
#include <vector>

class Interface;
class Interfaces;

class Interface
{
	friend class Interfaces;

	void** m_pInterfacePtr = nullptr;
	const char* m_szModule = nullptr;
	const char* m_szName = nullptr;

public:
	Interface() = default;

	Interface(const char* szName, void** pInterfacePtr, const char* szModule);
	virtual ~Interface() = default;
};

class SignatureInterface : public Interface
{
	friend class Interfaces;

	size_t m_nOffset = 0x0;
	size_t m_nDereferenceCount = 0x0;
	const char* m_szSignature = nullptr;
	bool m_bRelative = false;

public:
	SignatureInterface(const char* szName, void** pInterfacePtr, const char* szModule, const char* szSignature, size_t nDereferenceCount = 0x0, size_t nOffset = 0x0, bool bRelative = false);
};

class VersionInterface : public Interface
{
	friend class Interfaces;

	const char* m_szVersion = nullptr;

public:
	VersionInterface(const char* szName, void** pInterfacePtr, const char* szModule, const char* szVersion);
};

class Interfaces
{
	std::vector<Interface*> m_vInterfaces;

public:
	inline void Add(Interface* pInterface)
	{
		m_vInterfaces.push_back(pInterface);
	}

	void Init();
};

inline Interfaces g_Interfaces;

#define VERSION_INTERFACE(name, type, module ,version) namespace I { \
	inline type name = nullptr; \
} \
namespace _I \
{ \
inline VersionInterface name##_Initializer(#name, (void**)&I::name, module, version); \
}

#define SIGNATURE_INTERFACE(name, type, module, signature, dereferenceCount, offset, ...) namespace I { \
	inline type name = nullptr; \
} \
namespace _I \
{ \
inline SignatureInterface name##_Initializer(#name, (void**)&I::name, module, signature, dereferenceCount, offset, __VA_ARGS__); \
}