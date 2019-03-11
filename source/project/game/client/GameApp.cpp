#include "stdafx.h"
#include "GameApp.h"
#include "MainWnd.h"

GameApp::GameApp()
{
	GetMainWnd()->Init();
}

GameApp::~GameApp()
{
	GetMainWnd()->Destroy();
}

void GameApp::Tick()
{

}
