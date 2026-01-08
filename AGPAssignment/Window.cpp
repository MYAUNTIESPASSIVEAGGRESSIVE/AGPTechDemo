#include "Window.h"
#include "Debugger.h"
#include "Camera.h"

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

	mouse.SetWindow(handle);
	mouse.SetMode(DirectX::Mouse::MODE_RELATIVE);
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

	case WM_ACTIVATE:
	case WM_ACTIVATEAPP:
	case WM_INPUT:
		DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
		DirectX::Mouse::ProcessMessage(message, wParam, lParam);
		break;
	case WM_SYSKEYDOWN:
		if (wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000)
		{
			// implement hotkeys for window
		}
		DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd); // destorying window is not closing app
			break;
		}
	case WM_KEYUP:
		// keyup events
	case WM_SYSKEYUP:
		DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
		break;

	case WM_MOUSEACTIVATE:
		// ignore mouse clicks that regain focus on the window
		// good practice to prevent player misinputs when they click  into window
		return MA_ACTIVATEANDEAT;

	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		DirectX::Mouse::ProcessMessage(message, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

