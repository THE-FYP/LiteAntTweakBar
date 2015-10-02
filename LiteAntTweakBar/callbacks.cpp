#include "main.h"

bool g_initialized = false;


bool CALLBACK ResetHook(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	TwUpdateWindowSize();
	return true;
}

bool CALLBACK PresentHook(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	if (!sfRender->CanDraw())
		return true;
	TwDraw();
	return true;
}

void CALLBACK OnUnInit(void)
{
	TwWindowSize(0, 0);
	TwTerminate();
}

bool CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (TwEventWin(hwnd, uMsg, wParam, lParam))
		return false;
	return true;
}

void CALLBACK mainLoop(void)
{
	static bool die = false;
	if (!g_initialized && !die)
	{
		// this shouldn't happen but let's check it anyway
		if (sfRender == nullptr)
		{
			die = true;
			return;
		}

		if (sfRender->getD3DDevice() == nullptr)
			return;

		// init AntTweakBar
		if (!TwInitAll())
		{
			die = true;
			return;
		}

		// setup callbacks
		sfRender->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_PRESENT, PresentHook);
		sfRender->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_RESET, ResetHook);
		SF->getGame()->registerGameDestructorCallback(OnUnInit);
		SF->getGame()->registerWndProcCallback(SFGame::WndProcCallbackPriority::MEDIUM_CB_PRIORITY, WndProc);

		SF->Log("---\nLite AntTweakBar\nBased on AntTweakBar v1.16 Copyright © 2005-2013 Philippe Decaudin\nMade by FYP\nSuccessfully loaded.\n\nBlastHack.Net\n---");
		g_initialized = true;
	}
}