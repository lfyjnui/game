#include "stdafx.h"
#include "MainWnd.h"

MainWnd g_MainWnd;


MainWnd* GetMainWnd()
{
	return &g_MainWnd;
}

bool MainWnd::Init()
{
	Create(L"game", 1024, 768, true, false);
	ShowWindow();
	return true;
}

void MainWnd::Destroy()
{
}

LRESULT MainWnd::HandleMessage(UINT message, WPARAM wParam, LPARAM lParm)
{
	switch (message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;
}
