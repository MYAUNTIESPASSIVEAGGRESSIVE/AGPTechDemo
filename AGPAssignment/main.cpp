#include <iostream>
#include "Debugger.h"
#include "Renderer.h"
#include "Window.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Texture.h"
#include "Material.h"
#include "Material_Lit.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	Window _window{ 800,600, hInstance, nCmdShow };
	Renderer _renderer{ _window };
	
#pragma region Meshes

	Mesh mesh_floor{ _renderer, "Assets/landscape_AW_V4_Tris.obj" };
	Mesh mesh_water{ _renderer, "Assets/Water_AW_V3_Tris.obj"};
	Mesh mesh_skybox{ _renderer, "Assets/cube.obj" };
	Mesh mesh_cube{ _renderer, "Assets/cube.obj" };
	Mesh mesh_LoafPoly{ _renderer, "Assets/LoafPoly.obj" };
	Mesh mesh_Grass{ _renderer, "Assets/grass.obj" , true};
	Mesh mesh_Cabin{ _renderer, "Assets/AW_Cabin_V2_Tris.obj" };
	Mesh mesh_Trees{ _renderer, "Assets/trees_AW_Tris.obj" };
	Mesh mesh_Well{ _renderer, "Assets/Well_AW_Tris.obj" };

#pragma endregion

#pragma region Textures

	Texture tex_floor{ _renderer, "Assets/FloorGrass.png" };
	Texture tex_water{ _renderer, "Assets/Water.png" };
	Texture tex_basemap{ _renderer, "Assets/AW_Texture_Cabin_BaseColour_Map.png" };
	Texture tex_skybox{ _renderer, "Assets/SkyBox.dds", false, Texture::TextureType::Cubemap };
	Texture tex_grass{ _renderer, "Assets/grass.png", true };

#pragma endregion

#pragma region Materials

	Material mat_unlit{ "Unlit", _renderer, "Compiled Shaders/VertexShader.cso", "Compiled Shaders/PixelShader.cso", &tex_basemap };

	Material mat_skybox{ "SkyBox", _renderer, "Compiled Shaders/SkyboxVShader.cso", "Compiled Shaders/SkyboxPShader.cso", &tex_skybox };

	Material_Lit mat_lit{ "lit", _renderer, "Compiled Shaders/ReflectiveVShader.cso", "Compiled Shaders/ReflectivePShader.cso", &tex_basemap};
	mat_lit.SetReflectionTexture(&tex_skybox);
	mat_lit.reflectiveness = -1.0f;

	Material_Lit mat_litfloor{ "litFloor", _renderer, "Compiled Shaders/ReflectiveVShader.cso", "Compiled Shaders/ReflectivePShader.cso", &tex_floor };
	mat_lit.SetReflectionTexture(&tex_skybox);
	mat_litfloor.reflectiveness = -1.0f;

	Material_Lit mat_litWater{ "litWater", _renderer, "Compiled Shaders/ReflectiveVShader.cso", "Compiled Shaders/ReflectivePShader.cso", &tex_water };
	mat_lit.SetReflectionTexture(&tex_skybox);

	Material_Lit mat_litgrass{ "litgrass", _renderer, "Compiled Shaders/ReflectiveVShader.cso", "Compiled Shaders/ReflectivePShader.cso", &tex_grass };
	mat_litgrass.SetReflectionTexture(&tex_skybox);
	mat_litgrass.reflectiveness = 0.01f;

#pragma endregion

#pragma region GameObjects


	GameObject go_grass{ "grassGO", &mesh_Grass, &mat_litgrass };

	GameObject go_cube{ "cubeGO", &mesh_cube, &mat_litWater };

	GameObject go_base{ "BaseGO", &mesh_floor, &mat_litfloor};
	go_base.transform.scale = { 0.01f,0.01f,0.01f };

	GameObject go_water{ "WaterGO", &mesh_water, &mat_litWater };
	go_water.transform.scale = { 0.01f,0.01f,0.01f };

	GameObject go_skybox{ "Skybox", &mesh_skybox, &mat_skybox };
	_renderer.SkyBoxGO = &go_skybox;

	GameObject go_cabin{ "CabinGO", &mesh_Cabin, &mat_lit };
	go_cabin.transform.scale = { 0.01f,0.01f,0.01f };

	GameObject go_trees{ "TreesGO", &mesh_Trees, &mat_lit };
	go_trees.transform.scale = { 0.01f,0.01f,0.01f };

	GameObject go_well{ "WellGO", &mesh_Well, &mat_lit };
	go_well.transform.scale = { 0.01f,0.01f,0.01f };

	GameObject go_loafpoly{ "LoafPolyGO", &mesh_LoafPoly, &mat_lit };
	go_loafpoly.transform.scale = { 0.03f,0.03f,0.03f };

	_renderer.RegisterGameObject(&go_cube);
	_renderer.RegisterGameObject(&go_water);
	_renderer.RegisterGameObject(&go_base);
	_renderer.RegisterGameObject(&go_cabin);
	_renderer.RegisterGameObject(&go_trees);
	_renderer.RegisterGameObject(&go_well);
	_renderer.RegisterGameObject(&go_loafpoly);
	_renderer.RegisterGameObject(&go_grass);

#pragma endregion

#pragma region GO Transforms

	go_base.transform.rotation = { -1.55f, 0, 0 };

	go_cabin.transform.position = DirectX::XMVectorSet(30, 0, 0, 1);

	go_well.transform.position = DirectX::XMVectorSet(20, 0, 12, 1);

	go_trees.transform.position = DirectX::XMVectorSet(0, -0.14, 0.3, 1);

	go_loafpoly.transform.position = DirectX::XMVectorSet(0 , 2, -3, 1 );

	go_grass.transform.position = DirectX::XMVectorSet(0, -0.3, -2, 1);

#pragma endregion

#pragma region Lights

	_renderer.pointLights[0] = { DirectX::XMVECTOR{-1, -1, -3}, {0.85f, 0, 0.85f}, 50, true }; // purple
	_renderer.pointLights[1] = { DirectX::XMVECTOR{1, 5, -4}, {0, 0.85f, 0.85f}, 30, true }; // blue
	_renderer.pointLights[2] = { DirectX::XMVECTOR{30, 0, 0}, {0.960784376f, 0.870588303f, 0.701960802f }, 50, true }; //yellow

#pragma endregion

	_renderer.camera.transform.position = DirectX::XMVectorSetZ(_renderer.camera.transform.position, -10);

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
			go_cube.transform.Rotate({ 0.0f, 0.00001f, 0.0f });

			auto kbState = DirectX::Keyboard::Get().GetState();

			auto msState = DirectX::Mouse::Get().GetState();
			_renderer.camera.transform.Rotate({ -(float)msState.y * 0.001f, (float)msState.x * 0.001f, 0 });

			if (kbState.W)
				_renderer.camera.transform.Translate(DirectX::XMVectorScale(_renderer.camera.transform.GetForward(), 0.01f));
			if (kbState.A) 
				_renderer.camera.transform.Translate(DirectX::XMVectorScale(_renderer.camera.transform.GetRight(), -0.01f));
			if (kbState.S)
				_renderer.camera.transform.Translate(DirectX::XMVectorScale(_renderer.camera.transform.GetForward(), -0.01f));
			if (kbState.D) 
				_renderer.camera.transform.Translate(DirectX::XMVectorScale(_renderer.camera.transform.GetRight(), 0.01f));
			if (kbState.Q) 
				_renderer.camera.transform.Translate({ 0, 0.01f, 0 });
			if (kbState.E) 
				_renderer.camera.transform.Translate({ 0, -0.01f, 0 });

			if (kbState.Escape)
			{
				PostQuitMessage(0);
			}

			if (msState.leftButton) _renderer.camera.transform.position = { 0, 0, -5 };
			if (msState.rightButton) _renderer.camera.transform.position = { 0, 0, 5 };

			_renderer.RenderFrame();
		}

	}

	_renderer.Release();

	return 0;
}