#include "Window.h"
#include "WindowsInclude.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd)
{
	// Set up window
	D3dSb::Window window(1280, 720, L"Direct3D SandBox");

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

	return 0;
}