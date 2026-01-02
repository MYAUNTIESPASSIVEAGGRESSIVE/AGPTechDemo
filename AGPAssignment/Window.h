#pragma once
#include "Windows.h"

class Window
{
private:
	HWND handle = NULL;
	HINSTANCE instance = NULL;
	int height = 32, width = 32;

private:

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:

	bool DoesExist() { return handle != NULL; }
	HWND GetHandle() { return handle; }
	int GetHeight() { return height; }
	int GetWidth() { return width; }


	Window(int width, int height, HINSTANCE instance, int nCmdShow);
};

