#include "../SkinChanger/SkinChanger.h"

SIGNATURE(CL_CallPostDataUpdates, "engine.dll", "55 8B EC 8B 45 ? 53 33 DB");

HOOK(CL_CallPostDataUpdates, Sigs::CL_CallPostDataUpdates, void, __cdecl, void* u)
{
	g_SkinChanger.ApplySkins();

	CALL_ORIGINAL(u);
}