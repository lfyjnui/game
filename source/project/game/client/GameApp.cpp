#include "stdafx.h"
#include "GameApp.h"
#include "MainWnd.h"
#include "GameLoop.h"
#include <engine/renderer.h>
#include <chrono>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"rhid3d11.lib")

GameApp::GameApp()
{
	GetMainWnd()->Init();
	GetIRenderer()->Init(GetMainWnd()->GetHWnd());
	GetGameLoop()->Init(30);
}

GameApp::~GameApp()
{
	GetIRenderer()->Destroy();
	GetMainWnd()->Destroy();
	GetGameLoop()->Destroy();
}

void GameApp::Tick()
{
	GetGameLoop()->Tick();
}
