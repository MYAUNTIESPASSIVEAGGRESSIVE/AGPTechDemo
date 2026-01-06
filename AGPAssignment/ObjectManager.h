#pragma once
#include <vector>

class Renderer;
class GameObject;

class ObjectManager
{
public:

	Renderer& renderer;

	ObjectManager(Renderer& inRenderer);

	~ObjectManager();

	std::vector<GameObject*> gameObjects;

	void InitObjects();

private:


};

