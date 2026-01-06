#include <iostream>
#include "Debugger.h"
#include "Renderer.h"
#include "Window.h"
#include "ObjectManager.h"
#include "AssetManager.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	Window _window{ 800,600, hInstance, nCmdShow };
	Renderer _renderer{ _window };

	AssetManager::Load(_renderer, "Assets/SampleTexture.jpg", "Tex_Test");
	AssetManager::Load(_renderer, "Assets/TestPlane.jpg", "Mesh_Plane");

	MSG msg;

	Debugging::OpenConsole();

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
			auto kbState = DirectX::Keyboard::Get().GetState();

			if (kbState.W) _renderer.camera.transform.Translate({ 0, 0, 0.001f });
			if (kbState.A) _renderer.camera.transform.Translate({ -0.001f, 0, 0 });
			if (kbState.S) _renderer.camera.transform.Translate({ 0, 0, -0.001f });
			if (kbState.D) _renderer.camera.transform.Translate({ 0.001f, 0, 0 });
			if (kbState.Q) _renderer.camera.transform.Translate({ 0, 0.001f, 0 });
			if (kbState.E) _renderer.camera.transform.Translate({ 0, -0.001f, 0 });

			auto msState = DirectX::Mouse::Get().GetState();
			_renderer.camera.transform.Rotate({ -(float)msState.y * 0.001f, (float)msState.x * 0.001f, 0 });

			if (msState.leftButton) _renderer.camera.transform.position = { 0, 0, -5 };
			if (msState.rightButton) _renderer.camera.transform.position = { 0, 0, 5 };

			_window.HandleInput(_renderer.camera);

			_renderer.RenderFrame();
		}

	}

	_renderer.Release();

	return 0;
}