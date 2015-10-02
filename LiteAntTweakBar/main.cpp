#include "main.h"

SAMPFUNCS*			SF = new SAMPFUNCS();
SFRender*			sfRender = nullptr;


BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	switch (dwReasonForCall)
	{
		case DLL_PROCESS_ATTACH:
			if (SF->initPlugin(mainLoop, hModule))
			{
				sfRender = SF->getRender();
			}
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}
