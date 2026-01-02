#pragma once
#include <vector>

// renderer + swap chain structs
struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;

// draw buffer
struct ID3D11Buffer;

// depth buffer
struct ID3D11DepthStencilView;

struct ID3D11RasterizerState;

struct ID3D11BlendState;

struct ID3D11DepthStencilState;

class Window;

class Renderer
{

private:

	Window& window;

	// device and devcon
	ID3D11Device* dev = nullptr; 
	ID3D11DeviceContext* devcon = nullptr; 

#pragma region Rendering Variables

	// swapchain and backbuffer
	IDXGISwapChain* swapchain = nullptr; 
	ID3D11RenderTargetView* backBuffer = nullptr; 
	
	// depth, rasteriser states and blend states
	ID3D11DepthStencilView* depthBuffer = NULL; 
	ID3D11DepthStencilState* depthWriteOff = nullptr;

	ID3D11RasterizerState* rasterizerCullBack = nullptr;
	ID3D11RasterizerState* rasterizerCullFront = nullptr;
	ID3D11RasterizerState* rasterizerCullNone = nullptr;

	ID3D11BlendState* blendOpaque = nullptr;
	ID3D11BlendState* blendTransparent = nullptr;

#pragma endregion

	long InitD3D();
	void InitGraphics();
	long InitDepthBuffer();
	void DrawSkyBox();

public:
	Renderer(Window& inWindow);
	void Release();
	void RenderFrame();
	ID3D11Device* GetDevice() { return dev; }
	ID3D11DeviceContext* GetDeviceContext() { return devcon; }
};

