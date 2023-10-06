#include "App.h"

#include "WebInterface/WebInterface.h"

void App::Init()
{
#ifdef _DEBUG
	AllocConsole();
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
#endif

	g_Signatures.Init();
	g_Interfaces.Init();
	g_Hooks.Init();
	g_WebInterface.Init();
}

void App::Stop()
{
#ifdef _DEBUG
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
	FreeConsole();
#endif

	g_WebInterface.Stop();
	g_Hooks.Stop();
}
