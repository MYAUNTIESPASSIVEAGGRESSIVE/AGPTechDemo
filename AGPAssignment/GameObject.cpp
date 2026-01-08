#include "GameObject.h"

GameObject::GameObject(std::string objectName, Mesh* objectMesh, Material* material)
	: name(objectName), mesh(objectMesh), material(material)
{
	parent = nullptr;
}

void GameObject::SetParent(GameObject* GOparent)
{
	transform.position = DirectX::XMVectorSubtract(transform.position, GOparent->transform.position);

	parent = GOparent;
}
