#include "Stdafx.h"
#include "WndBase.h"
#include "Resource.h"

static const wchar_t* szWndClass = L"WndBase";

WndBase::WndBase()
{
	m_bMaximized = false;
}

bool WndBase::Create(wchar_t* strTitle, UINT width, UINT height, bool frame, bool bMaximized)
{
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
	wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = szWndClass;

	::RegisterClassExW(&wcex);

	DWORD dwStyle = 0;
	if (frame)
	{
		dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE;
	}
	else
	{
		dwStyle = WS_POPUP | WS_SYSMENU | WS_VISIBLE | WS_CLIPCHILDREN;
	}
	DWORD	dwExStyle = WS_EX_LEFT | WS_EX_ACCEPTFILES;

	RECT	rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = width;
	rt.bottom = height;
	if (AdjustWindowRectEx(&rt, dwStyle, FALSE, dwExStyle) == FALSE)
	{
		return false;
	}

	width = rt.right - rt.left;
	height = rt.bottom - rt.top;
	m_hWnd = ::CreateWindowExW(dwExStyle, szWndClass, strTitle, dwStyle,
		0, 0, width, height, NULL, NULL, hInstance, this);

	if (m_hWnd == NULL)
		return FALSE;
	::ShowWindow(m_hWnd, SW_HIDE);
	m_bMaximized = bMaximized;
	return true;
}

void WndBase::CenterWindow()
{
	HWND hwndParent = ::GetParent(m_hWnd);
	RECT rectWindow, rectParent;

	// make the window relative to its parent
	if (hwndParent == NULL)
	{
		hwndParent = ::GetDesktopWindow();
	}
	{
		GetWindowRect(m_hWnd, &rectWindow);
		GetWindowRect(hwndParent, &rectParent);

		int nWidth = rectWindow.right - rectWindow.left;
		int nHeight = rectWindow.bottom - rectWindow.top;

		int nX = ((rectParent.right - rectParent.left) - nWidth) / 2 + rectParent.left;
		int nY = ((rectParent.bottom - rectParent.top) - nHeight) / 2 + rectParent.top;

		int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		// make sure that the dialog box never moves outside of the screen
		if (nX < 0) nX = 0;
		if (nY < 0) nY = 0;
		if (nX + nWidth > nScreenWidth) nX = nScreenWidth - nWidth;
		if (nY + nHeight > nScreenHeight) nY = nScreenHeight - nHeight;

		MoveWindow(m_hWnd, nX, nY, nWidth, nHeight, TRUE);
	}
}

void WndBase::ShowWindow()
{
	::ShowWindow(m_hWnd, m_bMaximized ? SW_SHOWMAXIMIZED : SW_SHOWDEFAULT);

	if (!m_bMaximized)
	{
		CenterWindow();
	}
	::UpdateWindow(m_hWnd);
	::SetActiveWindow(m_hWnd);
}


LRESULT CALLBACK WndBase::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WndBase *pThis = NULL;
	if (message == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		pThis = (WndBase*)pCreate->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

		pThis->m_hWnd = hWnd;
	}
	else
	{
		pThis = (WndBase*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}

	if (pThis)
	{
		if (!pThis->HandleMessage(message, wParam, lParam))
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	else
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
