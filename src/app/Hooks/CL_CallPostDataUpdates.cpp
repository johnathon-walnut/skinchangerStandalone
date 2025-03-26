#include "../SkinChanger/SkinChanger.h"

#ifndef _WIN64
SIGNATURE(CL_CallPostDataUpdates, "engine.dll", "55 8B EC 8B 45 ? 53 33 DB");

HOOK(CL_CallPostDataUpdates, Sigs::CL_CallPostDataUpdates, void, __cdecl, void* u)
{
	g_SkinChanger.ApplySkins();

	CALL_ORIGINAL(u);
}
#else
// On x64, CL_CallPostDataUpdates is inlined into CL_ProcessPacketEntities - whereas, ClientDLL_FrameStageNotify is not - we can call this in the same place just before FRAME_NET_UPDATE_POSTDATAUPDATE_END - hoping this doesn't get hooked by anything else like CL_CallPostDataUpdates doesn't

/*
* engine/cl_ents_parse.cpp - line 664
* 
	ClientDLL_FrameStageNotify( FRAME_NET_UPDATE_POSTDATAUPDATE_START );

	// call PostDataUpdate() for each entity
	CL_CallPostDataUpdates( u );

	ClientDLL_FrameStageNotify( FRAME_NET_UPDATE_POSTDATAUPDATE_END );
*
*
*/

SIGNATURE(ClientDLL_FrameStageNotify, "engine.dll", "4C 8B DC 56 48 83 EC");
SIGNATURE(CL_ProcessPacketEntitites_FSN_Call, "engine.dll", "E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B 01 FF 50 ? 44 8B F0", 5); // Return address of FSN(3) call

#include <intrin.h>

HOOK(ClientDLL_FrameStageNotify, Sigs::ClientDLL_FrameStageNotify, void, __fastcall, int stage)
{
	/*static bool done = false;
	if (I::EngineClient->IsInGame() && !done)
	{
		g_Netvars.DumpTables();
		done = true;
	}*/

	if (std::uintptr_t(_ReturnAddress()) == Sigs::CL_ProcessPacketEntitites_FSN_Call.Get())
		g_SkinChanger.ApplySkins();

	CALL_ORIGINAL(stage);
}
#endif