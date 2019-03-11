#pragma once
#include <windows.h>

struct IApp
{
	virtual void Run() = 0;
};

struct Win32App:public IApp
{
	virtual void Tick() = 0;
	virtual void Run() override
	{
		bool isQuit = false;
		while (!isQuit)
		{
			MSG msg;
			// 主消息循环:
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					isQuit = true;
				// translate keystroke messages into the right format
				TranslateMessage(&msg);

				// send the message to the WindowProc function
				DispatchMessage(&msg);
			}
			Tick();
		}
	}
};

struct GameApp :public Win32App
{
	virtual void Tick() override
	{

	}
};