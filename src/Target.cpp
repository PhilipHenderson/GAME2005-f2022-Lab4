#include "Target.h"
#include "TextureManager.h"
#include "PlayScene.h"


Target::Target()
{
	TextureManager::Instance().Load("../Assets/textures/bullet.png","circle");

	const auto size = TextureManager::Instance().GetTextureSize("circle");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	GetRigidBody()->velocity = glm::vec2(0, 0);
	GetRigidBody()->isColliding = false;

	SetType(GameObjectType::TARGET);
}

Target::~Target()
= default;

void Target::Draw()
{
	// draw the target
	TextureManager::Instance().Draw("circle", GetTransform()->position, 0, 255, true);
}

void Target::Update()
{
	CheckBounds();
}

void Target::Clean()
{
}

void Target::CheckBounds()
{
}

void Target::Reset()
{
}
