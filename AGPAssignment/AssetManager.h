#pragma once
#include <string>
#include <map>

class Renderer;

class Mesh;

class Texture;

class AssetManager
{
private:

	Renderer& renderer;

	static std::string obj;
	static std::string png;
	static std::string jpg;
	static std::string jpeg;
	static std::string bmp;

public:

	enum class FileExtension
	{
		OBJ, PNG, JPG, JPEG, BMP
	};

	static std::map<std::string, Mesh> MeshMap;

	static std::map<std::string, Texture> TextureMap;

private:

	static FileExtension fileExe;

public:

	static void Load(Renderer& inRenderer, std::string filePath, std::string ID, bool isDoubleSided = false,
		bool isTransparent = false);

	static FileExtension CheckType(std::string type);

	Texture& GetTexture(std::string ID) { return TextureMap[ID]; }

	Mesh& GetMesh(std::string ID) { return MeshMap[ID]; }
};

