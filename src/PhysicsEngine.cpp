#include "PhysicsEngine.h"
#include "GameObject.h"
#include "PlayScene.h"

class PlayScene;
void PhysicsEngine::UpdatePhysics()
{
	GameObject* physicsObject;
	PlayScene* playScene{};

	for (int i = 0; i < physicsObjects.size(); i++)
	{
		physicsObject = physicsObjects[i];


		//apply gravity to velocity
		physicsObject->GetTransform()->position.y -= playScene->g * playScene->dt;
	
	
		//apply friction to velocity
		physicsObject->GetRigidBody()->velocity *= playScene->friction;

		//apply velocity to position
		physicsObject->GetTransform()->position += physicsObject->GetRigidBody()->velocity * playScene->dt;

	}
}
