#pragma once
#include <string>
#include "Transform.h"

class Mesh;
class Material;

class GameObject
{
public:

	Transform transform;

	Mesh* mesh;

	Material* material;

private:
	std::string name = "GameObject";

	GameObject* parent;

public:
	std::string GetName() { return name; }

	GameObject(std::string objectName, Mesh* objectMesh, Material* material);

	void SetParent(GameObject* parent);

	GameObject* GetParent() { return parent; }
};

