#pragma once

#include <cstdint>
#include <vector>

struct Signature
{
	inline std::uintptr_t Get() const
	{
		return m_nAddress;
	}

	std::uintptr_t m_nAddress;

	const char* m_szModule;
	const char* m_szSignature;
	std::uintptr_t m_nOffset;
	bool m_bRelative;

	Signature(const char* szModule, const char* szSignature, std::uintptr_t nOffset = 0, bool bRelative = false);

	inline operator std::uintptr_t() const
	{
		return m_nAddress;
	}

	inline operator bool() const
	{
		return m_nAddress != 0;
	}

	inline bool operator== (const Signature& other) const
	{
		return m_nAddress == other.m_nAddress;
	}

	inline bool operator!= (const Signature& other) const
	{
		return m_nAddress != other.m_nAddress;
	}

	inline bool operator== (std::uintptr_t nAddress) const
	{
		return m_nAddress == nAddress;
	}

	inline bool operator!= (std::uintptr_t nAddress) const
	{
		return m_nAddress != nAddress;
	}
};

class Signatures
{
	std::vector<Signature*> m_vSignatures;

public:
	inline void Add(Signature* pSignature)
	{
		m_vSignatures.push_back(pSignature);
	}

	void Init();
};

inline Signatures g_Signatures;

#define SIGNATURE(name, module, signature, ...) namespace Sigs { inline Signature name = Signature(module, signature, ##__VA_ARGS__); }