#include <iostream>
#include "Debugger.h"
#include "Renderer.h"
#include "Window.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	Window _window{ 800,600, hInstance, nCmdShow };
	Renderer _renderer{ _window };

	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			_renderer.RenderFrame();
		}

	}

	_renderer.Release();

	return 0;
}