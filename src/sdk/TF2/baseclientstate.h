#pragma once

#include "interface.h"

class CClockDriftMgr
{
public:
	float clock_offsets[16];
	int current_offset = 0;
	int server_tick = 0;
	int client_tick = 0;
};

SIGNATURE(CClientState_ForceFullUpdate, "engine.dll", "56 8B F1 83 BE ? ? ? ? ? 74 1D");

class CBaseClientState
{
private:
	char pad_0000[8]; //0x0000
public:
	void* thisptr = nullptr; //0x0008
private:
	char pad_000C[4]; //0x000C
public:
	void* m_NetChannel = nullptr; //0x0010
private:
	char pad_0014[320]; //0x0014
public:
	CClockDriftMgr m_ClockDriftMgr = { }; //0x0154
	int m_nDeltaTick = 0; //0x01A0
private:
	char pad_01A4[16]; //0x01A4
public:
	char m_szLevelFileName[128]; //0x01B4
	char m_szLevelBaseName[128]; //0x0234
	int m_nMaxClients = 0; //0x02B4
private:
	char pad_02B8[18528]; //0x02B8
public:
	int	oldtickcount = 0;		//0x4B18
	float m_tickRemainder = 0.f;	//0x4B1C
	float m_frameTime = 0.f; //0x4B20
	int lastoutgoingcommand = 0; //0x4B24
	int chokedcommands = 0; //0x4B28
	int last_command_ack = 0; //0x4B2C

public:
	void ForceFullUpdate()
	{
		reinterpret_cast<void(__thiscall*)(CBaseClientState*)>(Sigs::CClientState_ForceFullUpdate.Get())(this);
	}
};

SIGNATURE_INTERFACE(ClientState, CBaseClientState*, "engine.dll", "68 ? ? ? ? E8 ? ? ? ? 83 C4 08 5F 5E 5B 5D C3", 1, 1);