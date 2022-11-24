#pragma once
#include <vector>

class GameObject;
class PhysicsEngine
{
public:
	std::vector<GameObject*> physicsObjects;
	void UpdatePhysics();
};