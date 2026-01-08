#pragma once
#include <vector>
#include "Transform.h"
#include "Camera.h"
#include "Lighting.h"

#define MAX_POINT_LIGHTS 8

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

class GameObject;

class Renderer
{
public:

	Camera camera;

	GameObject* SkyBoxGO;
	std::vector<GameObject*> gameObjects;

	DirectX::XMVECTOR ambientLightColour{ 0.1f, 0.1f, 0.1f };
	DirectionalLight directionalLight{ {0.9f, 1.0f, 1.0f}, {0.098039225f, 0.098039225f, 0.439215720f} };
	PointLight pointLights[MAX_POINT_LIGHTS];

	void RegisterGameObject(GameObject* go);
	void RemoveGameObject(GameObject* go);

	Renderer(Window& inWindow);
	void Release();
	void RenderFrame();
	ID3D11Device* GetDevice() { return dev; }
	ID3D11DeviceContext* GetDeviceContext() { return devcon; }

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

	// const buffers
	ID3D11Buffer* cBuffer_PerObject = nullptr; 
	ID3D11Buffer* cBuffer_PerFrame = nullptr;

	long InitD3D();
	void InitGraphics();
	long InitDepthBuffer();
	void DrawSkyBox();

};

