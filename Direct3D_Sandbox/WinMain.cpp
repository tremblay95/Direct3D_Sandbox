#include <Windows.h>

#define SIMPLE_ERROR_EXIT() DWORD dwError = GetLastError(); return NULL;

const WCHAR *className = L"D3D_SB_Window";

LRESULT CALLBACK D3DSB_WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

HWND D3DSB_CreateWindow(HINSTANCE hInstance, int width, int height, const WCHAR* windowTitle)
{
	WNDCLASS wndClass = {};
	wndClass.style = CS_OWNDC | CS_DBLCLKS;
	wndClass.lpfnWndProc = D3DSB_WindowProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = nullptr;
	wndClass.hCursor = nullptr;
	wndClass.hbrBackground = nullptr;
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = className;

	if (!RegisterClass(&wndClass))
	{
		DWORD dwError = GetLastError();
		if (dwError != ERROR_CLASS_ALREADY_EXISTS)
		{
			return NULL;
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
		SIMPLE_ERROR_EXIT();
	}

	// Create window
	HWND hWnd = CreateWindow(
		className, windowTitle, windowStyles,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, nullptr, hInstance, nullptr
	);

	if (hWnd == NULL)
	{
		SIMPLE_ERROR_EXIT();
	}

	ShowWindow(hWnd, SW_SHOWDEFAULT);

	return hWnd;
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd)
{
	

	// Set up window parameters
	int width = 1280;
	int height = 720;
	const WCHAR *windowTitle = L"Direct3D SandBox";

	HWND hWnd = D3DSB_CreateWindow(hInstance, width, height, windowTitle);

	// Message pump
	bool hasMsg = false;
	MSG msg;
	msg.message = WM_NULL;
	PeekMessage(&msg, nullptr, 0u, 0u, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		hasMsg = (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE) != 0);

		if (hasMsg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//update

			//render
			
			//present
		}
	}

	UnregisterClass(className, hInstance);

	return 0;
}