#include "Window.h"
#include "Debugger.h"

const wchar_t* windowName = L"AGP Tech Demo";

Window::Window(int width, int height, HINSTANCE instance, int nCmdShow)
    : instance(instance), width(width), height(height)
{
	WNDCLASSEX wc = {}; 
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc; 
	wc.hInstance = instance; 
	wc.lpszClassName = L"WindowClass1"; 
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; 

	if (!RegisterClassEx(&wc))
	{
		LOG("failed to register class!");
	}

	RECT wr = { 0,0, width, height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	handle = CreateWindowEx(NULL,
		L"WindowClass1", 
		windowName,
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, 
		100, 
		100, 
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		instance,
		NULL);

	if (handle != NULL)
	{
		ShowWindow(handle, nCmdShow);
	}
	else
	{
		LOG("failed to create window!");
		DWORD var = GetLastError();
	}
}

LRESULT Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd); // destorying window is not closing app
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

