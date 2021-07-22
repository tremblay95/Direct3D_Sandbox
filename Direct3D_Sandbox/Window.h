#pragma once
#include "WindowsInclude.h"

namespace D3dSb {

	class Window
	{
	public:
		Window(int width, int height, const WCHAR* windowTitle);
		~Window();

		//delete copy constructor and assignment operator
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		int width;
		int height;
		HWND hWnd;
		HINSTANCE hInst;

		static constexpr const WCHAR* windowClassName = L"D3dSb_Window";
	};

}