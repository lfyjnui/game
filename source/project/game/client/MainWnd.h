#pragma once
#include "WndBase.h"

class MainWnd:public WndBase
{
public:
	bool Init();
	void Destroy();

protected:

	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParm) override;

};

MainWnd* GetMainWnd();