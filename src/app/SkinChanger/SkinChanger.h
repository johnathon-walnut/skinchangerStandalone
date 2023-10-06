#pragma once

#include "../App.h"
#include "../../utils/fnv1a.h"

namespace attributes
{
	constexpr uint16_t paintkit_proto_def_index = 834;
	constexpr uint16_t custom_paintkit_seed_lo = 866;
	constexpr uint16_t custom_paintkit_seed_hi = 867;
	constexpr uint16_t has_team_color_paintkit = 745;
	constexpr uint16_t set_item_texture_wear = 725;
	constexpr uint16_t weapon_allow_inspect = 731;
	constexpr uint16_t set_attached_particle_static = 370;
	constexpr uint16_t set_attached_particle = 134;
	constexpr uint16_t is_festivized = 2053;
	constexpr uint16_t is_australium_item = 2027;
	constexpr uint16_t loot_rarity = 2022;
	constexpr uint16_t item_style_override = 542;
	constexpr uint16_t set_turn_to_gold = 150;
	constexpr uint16_t killstreak_idleeffect = 2014;

#define HashCase(str) case FNV1A::HashConst(#str): return str

	inline uint16_t StringToAttribute(std::string str)
	{
		FNV1A_t hash = FNV1A::Hash(str.c_str());

		switch (hash)
		{
			HashCase(paintkit_proto_def_index);
			HashCase(custom_paintkit_seed_lo);
			HashCase(custom_paintkit_seed_hi);
			HashCase(has_team_color_paintkit);
			HashCase(set_item_texture_wear);
			HashCase(weapon_allow_inspect);
			HashCase(set_attached_particle_static);
			HashCase(set_attached_particle);
			HashCase(is_festivized);
			HashCase(is_australium_item);
			HashCase(loot_rarity);
			HashCase(item_style_override);
			HashCase(set_turn_to_gold);
			HashCase(killstreak_idleeffect);
			default:
				return 0;
		}
	}
}

namespace weapon_unusual_effects
{
	constexpr int weapon_unusual_hot = 701;
	constexpr int weapon_unusual_isotope = 702;
	constexpr int weapon_unusual_cool = 703;
	constexpr int weapon_unusual_energyorb = 704;
}

__forceinline float IntToStupidFloat(int desiredValue)
{
	return *reinterpret_cast<float*>(&desiredValue);
}

__forceinline int StupidFloatToInt(float desiredValue)
{
	return *reinterpret_cast<int*>(&desiredValue);
}

struct Attribute
{
	uint16_t attributeIndex;
	float attributeValue;
};

struct SkinInfo
{
	std::vector<Attribute> m_Attributes;
};

class SkinChanger
{
	std::unordered_map<int, SkinInfo> m_Skins;
	bool m_bForceFullUpdate = false;
	int m_nCurrentWeaponIndex = -1;
	bool m_bInitialSkinLoad = false;

public:
	void ApplySkins();

	int GetWeaponIndex() const { return m_nCurrentWeaponIndex; }

	void SetAttribute(int index, std::string attributeStr, float value);
	void RemoveAttribute(int index, std::string attributeStr);
	inline const SkinInfo& GetSkinInfo(int index) 
	{
		if (m_Skins.find(index) == m_Skins.end())
		{
			static SkinInfo empty = {};
			return empty;
		}

		return m_Skins[index];
	}

	void Save();
	void Load();
};

inline SkinChanger g_SkinChanger;