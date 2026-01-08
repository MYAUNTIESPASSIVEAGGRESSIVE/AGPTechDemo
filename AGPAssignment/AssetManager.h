#pragma once
#include <string>
#include <map>

class Renderer;

class Mesh;

class Texture;

class AssetManager
{
public:

	enum class FileExtension
	{
		UNKNOWN, OBJ, PNG, JPG, JPEG, BMP, NONE
	};

	std::map<std::string, Mesh> MeshMap;

	std::map<std::string, Texture> TextureMap;

	AssetManager(Renderer& inRenderer);

private:

	Renderer& renderer;

	std::string obj = "obj";
	std::string png = "png";
	std::string jpg = "jpg";
	std::string jpeg =  "jpeg";
	std::string bmp = "bmp";

	FileExtension fileExe;

	Texture* texture = nullptr;

	Mesh* mesh = nullptr;

public:

	void Load(std::string filePath, std::string ID, bool isDoubleSided = false,
		bool isTransparent = false);

	FileExtension CheckType(std::string type);

	Texture& GetTexture(std::string ID) { return TextureMap.at(ID); }

	Mesh& GetMesh(std::string ID) { return MeshMap.at(ID); }
};

