#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Target.h"
#include "PhysicsEngine.h"
#include "PhysicsObject.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene() override;

	// Scene LifeCycle Functions
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	virtual void HandleEvents() override;
	virtual void Start() override;

	float t = 1.0;
	float dt = 1.0f / 60.0f;
	float gravity = -9.81;
	float airResistance = 0.9f;
	bool bShot= false;

	float launchAngle = 0.0f;
	float a = launchAngle;

	float launchSpeed = 0.0f;
	float b = launchSpeed;
	
	float startingY = 400.0f;
	float y = startingY;

	float startingX = 100.0f;
	float x = startingX;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;


	glm::vec2 v1;
	glm::vec2 v2;
	glm::vec2 startPos1;
	glm::vec2 startPos2;
	glm::vec2 endPoint1;
	glm::vec2 endPoint2;


	// Sprites
	PhysicsObject* m_pBullet1{};
	PhysicsObject* m_pBullet2{};

	// UI Items
	Button* m_pBackButton{};
	Button* m_pNextButton{};
	Label* m_pInstructionsLabel{};

	// Input Control
	int m_pCurrentInputType{};
	void GetKeyboardInput();
	void ShootProjectile();
	void ResetObjects();
	//void ResetObjects2();

	PhysicsEngine physicsEngine;
};

#endif /* defined (__PLAY_SCENE__) */