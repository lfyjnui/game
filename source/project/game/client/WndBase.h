#pragma once
#include <windows.h>

enum class WindowShowType
{
	Hide,
	Normal,
	Mini,
	Max,
	Restore,
};

class WndBase
{
public:
	WndBase();
	bool Create(wchar_t* strTitle, UINT width, UINT height, bool frame, bool bMaximized);

	void ShowWindow();
	void CenterWindow();

	HWND GetHWnd()
	{
		return m_hWnd;
	}
protected:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParm) { return TRUE; }
private:

	bool m_bMaximized;
	HWND m_hWnd;
};