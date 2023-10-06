#pragma once

#include "../sdk/SDK.h"

class App
{
	HMODULE m_hModule = nullptr;

public:
	void Init();
	void Stop();

	inline void SetHandle(HMODULE hModule)
	{
		m_hModule = hModule;
	}

	inline HMODULE GetHandle()
	{
		return m_hModule;
	}

	inline bool ShouldStop()
	{
//#ifdef _DEBUG
//		if (GetAsyncKeyState(VK_END) & 1)
//			m_bShouldStop = true;
//#endif
		return m_bShouldStop;
	}

private:
	bool m_bShouldStop = false;
};

inline App g_App;