#include "Window.h"
#include "WindowsInclude.h"

using namespace D3dSb;

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd)
{
	// Set up window
	Window window(1280, 720, L"Direct3D SandBox");

	// Set up GFX


	while (true)
	{
		if (const auto errorCode = Window::ProcessMessages())
		{
			return *errorCode;
		}

		//update
		
		//render
		
		//present
		
	}

	return 0;
}