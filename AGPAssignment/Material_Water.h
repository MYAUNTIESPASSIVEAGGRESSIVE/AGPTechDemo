#pragma once
#include "Material.h"
class Material_Water :
    public Material
{
public:

    Material_Water(std::string name, Renderer& renderer,
        std::string vShaderFilename, std::string pShaderFilename,
        Texture* texture);

    void Bind() override;

    void UpdateMaterial(GameObject* GO) override;
};

