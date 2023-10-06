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

class SkinChanger
{


public:
	void ApplySkins();

	int m_nCurrentWeaponIndex = -1;
private:
	struct SkinInfo
	{
		struct Attribute
		{
			uint16_t attributeIndex;
			float attributeValue;
		};
		std::vector<Attribute> m_Attributes;
	};

	std::unordered_map<int, SkinInfo> m_Skins;

	struct SetAttributeCommand
	{
		int index;
		uint16_t attributeIndex;
		float value;
	};

	std::vector<SetAttributeCommand> m_Commands;
	bool m_bForceFullUpdate = false;

public:
	inline void WebSetAttribute(int index, std::string attributeStr, float value)
	{
		if (index == -1)
			return;

		uint16_t attributeIndex = attributes::StringToAttribute(attributeStr);

		m_Commands.push_back({ index, attributeIndex, value });

#ifdef _DEBUG
		// lets log the entire map
		for (auto& skin : m_Skins)
		{
			std::cout << "Weapon index: " << skin.first << std::endl;
			for (auto& attribute : skin.second.m_Attributes)
			{
				std::cout << "Attribute index: " << attribute.attributeIndex << " value: " << attribute.attributeValue << std::endl;
			}
		}
#endif
	}

	inline void WebRemoveAttribute(int index, std::string attributeStr)
	{
		if (m_Skins.find(index) == m_Skins.end())
			return;

		auto& attributes = m_Skins[index].m_Attributes;

		uint16_t attributeIndex = attributes::StringToAttribute(attributeStr);
#ifdef _DEBUG
		std::cout << "Removing attribute: " << attributeIndex << " (" << attributeStr << ")" << std::endl; // "Removing attribute: 834 (paintkit_proto_def_index)
#endif
		// Find attribute
		for (auto it = attributes.begin(); it != attributes.end(); ++it)
		{
			if (it->attributeIndex == attributeIndex)
			{
				attributes.erase(it);
				m_bForceFullUpdate = true;

				return;
			}
		}
	}

	inline void ConsumeCommands()
	{
		for (auto& cmd : m_Commands)
			SetAttribute(cmd);

		if (m_Commands.size() || m_bForceFullUpdate)
		{
			I::ClientState->ForceFullUpdate();
			m_bForceFullUpdate = false;
		}

		m_Commands.clear();
	}

	inline void SetAttribute(SetAttributeCommand cmd)
	{
		if (cmd.attributeIndex == attributes::paintkit_proto_def_index)
		{
			cmd.value = IntToStupidFloat(static_cast<int>(cmd.value));
		}

		if (m_Skins.find(cmd.index) == m_Skins.end())
			m_Skins[cmd.index] = SkinInfo();

		// Check if attribute already exists, if so, update it
		for (auto& attribute : m_Skins[cmd.index].m_Attributes)
		{
			if (attribute.attributeIndex == cmd.attributeIndex)
			{
				attribute.attributeValue = cmd.value;
				return;
			}
		}

		// Attribute doesn't exist, add it
		m_Skins[cmd.index].m_Attributes.push_back({ cmd.attributeIndex, cmd.value });
	}

	const SkinInfo& GetSkinInfo(int index)
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

private:
	bool m_bInitialSkinLoad = false;
};

inline SkinChanger g_SkinChanger;