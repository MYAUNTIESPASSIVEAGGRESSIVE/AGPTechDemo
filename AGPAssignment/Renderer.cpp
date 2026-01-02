#include "Renderer.h"
#include "Debugger.h"
#include "d3d11.h"
#include "Window.h"
//#include <DirectXColors.h>
//#include <DirectXMath.h>
//using namespace DirectX;

Renderer::Renderer(Window& inWindow)
	: window(inWindow)
{
	if (InitD3D() != S_OK)
	{
		LOG("Failed to initalise D3D renderer");
		return;
	}

	InitGraphics();
}

long Renderer::InitD3D()
{
	// struct to hold info about swap chain
	DXGI_SWAP_CHAIN_DESC scd = {};

	// fill the swap chain description struct
	scd.BufferCount = 1; // 1 back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32-bit color
	scd.BufferDesc.Width = window.GetWidth(); // set the back buffer width
	scd.BufferDesc.Height = window.GetHeight(); // set the back buffer height
	scd.BufferDesc.RefreshRate.Numerator = 60; // 60fps
	scd.BufferDesc.RefreshRate.Denominator = 1; // 60/1 = 60 fps
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // intended swapchain use
	scd.OutputWindow = window.GetHandle(); // window to use
	scd.SampleDesc.Count = 1; // number of smaples for AA
	scd.Windowed = TRUE; // windowed/full-screen mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // allow full-screen switching

	HRESULT hr;

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon);

	// get the address of the back buffer
	ID3D11Texture2D* backBufferTexture = nullptr;

	// get the back buffer from the swap chain
	hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
	if (FAILED(hr))
	{
		LOG("failed to create backbuffer texture.");
		return hr;
	}

	hr = dev->CreateRenderTargetView(backBufferTexture, NULL, &backBuffer);

	backBufferTexture->Release();
	if (FAILED(hr))
	{
		LOG("failed to create backbuffer view.");
		return hr;
	}

	//// init the depth buffer
	//hr = InitDepthBuffer();
	//if (FAILED(hr))
	//{
	//	LOG("Failed to create depth buffer");
	//	return hr;
	//}

	// set the backbuffer as the current render target
	devcon->OMSetRenderTargets(1, &backBuffer, NULL);

	// define and set viewport struct
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)window.GetWidth();
	viewport.Height = (float)window.GetHeight();
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	devcon->RSSetViewports(1, &viewport);

	if (FAILED(hr))
	{
		LOG("failed to create a renderer");
		return hr; // ABORT SHIP!! YARRRRR
	}

	return S_OK;
}

void Renderer::InitGraphics()
{
	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(D3D11_RASTERIZER_DESC));
	rsDesc.CullMode = D3D11_CULL_NONE;
	rsDesc.FillMode = D3D11_FILL_SOLID;
	//rsDesc.FillMode = D3D11_FILL_WIREFRAME;

	// create no culling rasteriser
	dev->CreateRasterizerState(&rsDesc, &rasterizerCullNone);

	// create backface culling rasteriser
	rsDesc.CullMode = D3D11_CULL_BACK;
	dev->CreateRasterizerState(&rsDesc, &rasterizerCullBack);

	// create front rasteriser
	rsDesc.CullMode = D3D11_CULL_FRONT;
	dev->CreateRasterizerState(&rsDesc, &rasterizerCullFront);

	D3D11_BLEND_DESC bdDesc = { 0 };
	bdDesc.IndependentBlendEnable = FALSE;
	bdDesc.AlphaToCoverageEnable = FALSE;
	bdDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bdDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bdDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bdDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bdDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bdDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bdDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// transparent blend state
	bdDesc.RenderTarget[0].BlendEnable = TRUE;
	dev->CreateBlendState(&bdDesc, &blendTransparent);

	// opaque blend state
	bdDesc.RenderTarget[0].BlendEnable = TRUE;
	dev->CreateBlendState(&bdDesc, &blendOpaque);


	D3D11_DEPTH_STENCIL_DESC dsDesc = { 0 };
	//depth test params
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	dev->CreateDepthStencilState(&dsDesc, &depthWriteOff);
}

long Renderer::InitDepthBuffer()
{
	HRESULT hr;
	DXGI_SWAP_CHAIN_DESC scd = {};
	swapchain->GetDesc(&scd);

	D3D11_TEXTURE2D_DESC tex2dDesc = { 0 };
	tex2dDesc.Width = window.GetWidth();
	tex2dDesc.Height = window.GetHeight();
	tex2dDesc.ArraySize = 1;
	tex2dDesc.MipLevels = 1;
	tex2dDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex2dDesc.SampleDesc.Count = scd.SampleDesc.Count; // same sample count as the swap chain
	tex2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex2dDesc.Usage = D3D11_USAGE_DEFAULT;

	ID3D11Texture2D* zBufferTexture;
	hr = dev->CreateTexture2D(&tex2dDesc, NULL, &zBufferTexture);
	if (FAILED(hr))
	{
		LOG("Failed to create Z-Buffer Texture");
		return E_FAIL;
	}

	// create the depth buffer view
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvDesc.Format = tex2dDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	hr = dev->CreateDepthStencilView(zBufferTexture, &dsvDesc, &depthBuffer);
	if (FAILED(hr))
	{
		LOG("Failed to create depth stencil view");
		return E_FAIL;
	}

	zBufferTexture->Release();

	return S_OK;
}

void Renderer::DrawSkyBox()
{

}

void Renderer::RenderFrame()
{
	// clear back buffer with colour
	FLOAT bg[4] = { 0.2f, 0.3f,0.2f,1.0f };
	devcon->ClearRenderTargetView(backBuffer, bg);
	//devcon->ClearDepthStencilView(depthBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// flip the back and front buffers
	swapchain->Present(0, 0);
}

void Renderer::Release()
{
	if (backBuffer) backBuffer->Release();
	if (swapchain) swapchain->Release();
	if (dev) dev->Release();
	if (devcon) devcon->Release();
	//if (cBuffer_PerObject) cBuffer_PerObject->Release();
	if (depthBuffer) depthBuffer->Release();
}

