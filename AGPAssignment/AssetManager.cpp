#include "AssetManager.h"
#include "Debugger.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Texture.h"

AssetManager::AssetManager(Renderer& inRenderer)
	: renderer(inRenderer)
{
	
}

void AssetManager::Load(std::string filePath, std::string ID, bool isDoubleSided,
	bool isTransparent)
{
	
			fileExe = FileExtension::UNKNOWN;
	// extract final .fileext
	// if/switch texture then contruct texture or if/switch obj then constuct mesh
	std::string subs;
	auto npos = filePath.find('.');
	if (npos != std::string::npos)
		subs = filePath.substr(npos + 1);

	if (!subs.empty() && fileExe == FileExtension::UNKNOWN)
		CheckType(subs);

	switch (fileExe)
	{
		case(FileExtension::OBJ):
		{
			if (isDoubleSided)
			{
				Mesh mesh{ renderer, filePath, true };
				MeshMap.insert({ ID, mesh });
				LOG("Mesh added to map");
			}
			else
			{
				Mesh mesh{ renderer, filePath };
				MeshMap.insert({ ID, mesh });
				LOG("Mesh added to map");
			}


			fileExe = FileExtension::UNKNOWN;
			break;
		}
		case(FileExtension::BMP):
		{
			if (isTransparent)
			{
				Texture texture{ renderer, filePath, true };
				TextureMap.insert({ ID, texture });
				LOG("Texture added to map");
			}
			else
			{
				Texture texture{ renderer, filePath };
				TextureMap.insert({ ID, texture });
				LOG("Texture added to map");
			}


			fileExe = FileExtension::UNKNOWN;
			break;
		}
		case(FileExtension::PNG):
		{
			if (isTransparent)
			{
				Texture texture{ renderer, filePath, true };
				TextureMap.insert({ ID, texture });
				LOG("Texture added to map");
			}
			else
			{
				Texture texture{ renderer, filePath };
				TextureMap.insert({ ID, texture });
				LOG("Texture added to map");
			}


			fileExe = FileExtension::UNKNOWN;
			break;
		}
		case(FileExtension::JPG):
		{
			if (isTransparent)
			{
				Texture texture{ renderer, filePath, true };
				TextureMap.insert({ ID, texture });
				LOG("Texture added to map");
			}
			else
			{
				Texture texture{ renderer, filePath };
				LOG("added" + filePath + "to texturemap");
				TextureMap.insert({ ID, texture });
			}

			fileExe = FileExtension::UNKNOWN;
			break;
		}
		case(FileExtension::JPEG):
		{
			if (isTransparent)
			{
				Texture texture{ renderer, filePath, true };
				TextureMap.insert({ ID, texture });
				LOG("Texture added to map");
			}
			else
			{
				Texture texture{ renderer, filePath };
				TextureMap.insert({ ID, texture });
				LOG("Texture added to map");
			}


			fileExe = FileExtension::UNKNOWN;
			break;
		}
		case(FileExtension::NONE):
		{
			LOG("Cannot find File Extension!");

			fileExe = FileExtension::UNKNOWN;
			return;
		}
	}
}

AssetManager::FileExtension AssetManager::CheckType(std::string type)
{
	if (type == obj) return fileExe = FileExtension::OBJ;
	if (type == png) return fileExe = FileExtension::PNG;
	if (type == jpg) return fileExe = FileExtension::JPG;
	if (type == jpeg) return fileExe = FileExtension::JPEG;
	if (type == bmp) return fileExe = FileExtension::BMP;
	else { return fileExe = FileExtension::NONE; };
}