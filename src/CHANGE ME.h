#pragma once
#include <vector>

class PlayScene;
class GameObject;
class PhysicsEngine
{
public:
	std::vector<GameObject*> physicsObjects;
	std::vector<PlayScene*> playScene;
	void UpdatePhysics();
};