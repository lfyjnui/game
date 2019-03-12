#pragma once

class GameLoop
{
public:
	bool Init(int fps);
	void Destroy();
	void Tick();
	void Update(float dt);
	void Render(float dt);

	float GetLogicFps()
	{
		return m_fLogicFps;
	}

	float GetRenderFps()
	{
		return m_fRenderFps;
	}
private:
	float m_logicStep;
	float m_fLogicFps;
	float m_fRenderFps;
};

GameLoop* GetGameLoop();