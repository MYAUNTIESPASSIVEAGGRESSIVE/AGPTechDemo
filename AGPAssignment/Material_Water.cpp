#include "Material_Water.h"

Material_Water::Material_Water(std::string name, Renderer& renderer, 
	std::string vShaderFilename, std::string pShaderFilename, Texture* texture):
	Material(name, renderer, vShaderFilename, pShaderFilename, texture)
{
	
}

void Material_Water::Bind()
{

}

void Material_Water::UpdateMaterial(GameObject* GO)
{

}
