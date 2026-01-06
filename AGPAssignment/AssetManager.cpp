#include "AssetManager.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Texture.h"

void AssetManager::Load(Renderer& inRenderer, std::string filePath, std::string ID, bool isDoubleSided = false,
	bool isTransparent = false)
{
	// extract final .fileext
	// if/switch texture then contruct texture or if/switch obj then constuct mesh
	std::string subs;
	auto npos = filePath.find('.');
	if (npos != std::string::npos)
		subs = filePath.substr(npos + 1);

	if (!subs.empty())
		CheckType(subs);

	switch (fileExe)
	{
		case(FileExtension::OBJ):
		{
			if (isTransparent)
			{
				Texture texture{ inRenderer, filePath, true };
				TextureMap.insert({ ID, texture });
			}
			else
			{
				Texture texture{ inRenderer, filePath };
				TextureMap.insert({ ID, texture });
			}
			break;
		}
		case(FileExtension::BMP):
		{
			if (isDoubleSided)
			{
				Mesh mesh{ inRenderer, filePath, true };
				MeshMap.insert({ ID, mesh });
			}
			else
			{
				Mesh mesh{ inRenderer, filePath };
				MeshMap.insert({ ID, mesh });
			}
			break;
		}
		case(FileExtension::PNG):
		{
			if (isDoubleSided)
			{
				Mesh mesh{ inRenderer, filePath, true };
				MeshMap.insert({ ID, mesh });
			}
			else
			{
				Mesh mesh{ inRenderer, filePath };
				MeshMap.insert({ ID, mesh });
			}
			break;
		}
		case(FileExtension::JPG):
		{
			if (isDoubleSided)
			{
				Mesh mesh{ inRenderer, filePath, true };
				MeshMap.insert({ ID, mesh });
			}
			else
			{
				Mesh mesh{ inRenderer, filePath };
				MeshMap.insert({ ID, mesh });
			}
			break;
		}
		case(FileExtension::JPEG):
		{
			if (isDoubleSided)
			{
				Mesh mesh{ inRenderer, filePath, true };
				MeshMap.insert({ ID, mesh });
			}
			else
			{
				Mesh mesh{ inRenderer, filePath };
				MeshMap.insert({ ID, mesh });
			}
			break;
		}
	}
}

AssetManager::FileExtension AssetManager::CheckType(std::string type)
{
	if (type.find(obj)) return FileExtension::OBJ;
	if (type.find(png)) return FileExtension::PNG;
	if (type.find(jpg)) return FileExtension::JPG;
	if (type.find(jpeg)) return FileExtension::JPEG;
	if (type.find(bmp)) return FileExtension::BMP;
}