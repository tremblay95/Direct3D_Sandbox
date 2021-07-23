#include "Window.h"

D3dSb::Window::Window(int width, int height, const WCHAR* windowTitle)
	: width(width), height(height)
{
	hInst = GetModuleHandle(nullptr);

	WNDCLASS wndClass = {};
	wndClass.style = CS_OWNDC | CS_DBLCLKS;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInst;
	wndClass.hIcon = nullptr;
	wndClass.hCursor = nullptr;
	wndClass.hbrBackground = nullptr;
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = windowClassName;

	if (!RegisterClass(&wndClass))
	{
		DWORD dwError = GetLastError();
		if (dwError != ERROR_CLASS_ALREADY_EXISTS)
		{
			return;
		}
	}

	DWORD windowStyles = WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION;

	RECT windowRect;
	windowRect.left = 100;
	windowRect.right = width + windowRect.left;
	windowRect.top = 100;
	windowRect.bottom = height + windowRect.top;

	if (AdjustWindowRect(&windowRect, windowStyles, FALSE) == 0)
	{
		DWORD dwError = GetLastError(); return;
	}

	// Create window
	hWnd = CreateWindow(
		windowClassName, windowTitle, windowStyles,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, nullptr, hInst, nullptr
	);

	if (hWnd == NULL)
	{
		DWORD dwError = GetLastError(); return;
	}

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

D3dSb::Window::~Window()
{
	UnregisterClass(windowClassName, hInst);
}

std::optional<int> D3dSb::Window::ProcessMessages()
{
	// Message pump

	MSG msg;

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		// Check for quit
		if (msg.message == WM_QUIT)
		{
			return (int)msg.wParam;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Return empty optional when not quitting
	return {};
}

LRESULT D3dSb::Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
