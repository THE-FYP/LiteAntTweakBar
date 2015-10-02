#include "main.h"

void TW_CALL TwErrorHandlerCallback(const char* errorMessage)
{
	SF->Log("AntTweakBar Error: %s", errorMessage);
}

void TwUpdateWindowSize(void)
{
	if (sfRender == nullptr)
		return;

	D3DPRESENT_PARAMETERS* presentParams = sfRender->getPresentationParameters();
	TwWindowSize(presentParams->BackBufferWidth, presentParams->BackBufferHeight);
}

bool TwInitAll(void)
{
	if (sfRender == nullptr)
		return false;

	if (sfRender->getD3DDevice() == nullptr)
		return false;

	TwHandleErrors(TwErrorHandlerCallback);
	TwUpdateWindowSize();
	bool result = TwInit(TwGraphAPI::TW_DIRECT3D9, SF->getRender()->getD3DDevice());
	if (result)
	{
		// set some options by default
		TwDefine("TW_HELP visible=false");
		TwDefine("GLOBAL iconpos=bottomright iconalign=vertical");
	}
	return result;
}

int TW_CALL TwLoaded(void)
{
	return g_initialized;
}
