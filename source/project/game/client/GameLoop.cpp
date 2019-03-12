#include "stdafx.h"
#include "GameLoop.h"
#include "MainWnd.h"
#include <engine/renderer.h>
#include <chrono>

GameLoop g_GameLoop;

GameLoop* GetGameLoop()
{
	return &g_GameLoop;
}

using namespace std::chrono;
typedef std::chrono::duration<float> dtType;

bool GameLoop::Init(int fps)
{
	m_logicStep = dtType(1.f / fps).count();
	return true;
}

void GameLoop::Destroy()
{

}

/*
|........|........|........|........|........|........|........|........|........|........|
|LRRRRRRR|LRRRRRRR|LRRRRRRR|LRRRRRRR|
*/
void GameLoop::Tick()
{
	static auto lastTick = std::chrono::steady_clock::now();
	auto now = std::chrono::steady_clock::now();
	auto dt = now - lastTick;
	lastTick = now;
	float _dt = duration_cast<dtType>(dt).count();

	while (_dt >= m_logicStep)
	{
		auto updateBegin = steady_clock::now();
		Update(m_logicStep);
		auto updateEnd = steady_clock::now();
		_dt -= m_logicStep;

		m_fLogicFps = 1.f / duration_cast<dtType>(updateEnd - updateBegin).count();
	}

	auto renderBegin = steady_clock::now();
	Render(_dt);
	auto renderEnd = steady_clock::now();
	m_fRenderFps = 1.f / duration_cast<dtType>(renderEnd - renderBegin).count();
}

//dt 在 m_duration 的左右波动
void GameLoop::Update(float _dt)
{
}

//dt 从0 涨到 m_duration
void GameLoop::Render(float _dt)
{
	GetIRenderer()->Render(nullptr);
}
