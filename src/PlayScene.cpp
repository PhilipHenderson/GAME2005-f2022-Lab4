#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "InputType.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::Start();
}
PlayScene::~PlayScene()
= default;
glm::vec2 AngleLengthToVector(float angle, float length)
{
	return glm::vec2(cos(-angle * Util::Deg2Rad) * length, 
					 sin(-angle * Util::Deg2Rad) * length);
}
// 360 DEGREES = 2 pie
// 180 DEGREES = 1 pie 
// 90 DEGREES = 1/2 pie 
// 0 DEGREES = 0 
void PlayScene::Draw()
{
	DrawDisplayList();

	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 0, 0, 0, 255);

	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 255);

	v1 = AngleLengthToVector(launchAngle, launchSpeed);
	endPoint1 = startPos1 + (AngleLengthToVector(launchAngle, launchSpeed) * glm::vec2(10, 10));
	
	//Draw velocity vector
	SDL_RenderDrawLineF(Renderer::Instance().GetRenderer(), startPos1.x, startPos1.y, endPoint1.x, endPoint1.y);

	v2 = AngleLengthToVector(launchAngle, launchSpeed);
	endPoint2 = startPos2 + (AngleLengthToVector(launchAngle, launchSpeed) * glm::vec2(10, 10));

	//Draw velocity vector
	SDL_RenderDrawLineF(Renderer::Instance().GetRenderer(), startPos2.x, startPos2.y, endPoint2.x, endPoint2.y);

	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 210, 85, 45, 255);
}

void PlayScene::ShootProjectile()
{
	if (bShot)
	{
		glm::vec2 lastPosition = m_pBullet1->GetTransform()->position;
		m_pBullet1->GetTransform()->position = lastPosition + AngleLengthToVector(launchAngle, launchSpeed);
	}
	else
	{	
		m_pBullet1->GetTransform()->position = glm::vec2(startPos1);
		t = 0.0f;
		v1.y = 20.f;
	}
}

void PlayScene::ResetObjects()
{
	if (bShot)
	{
	glm::vec2 lastPosition1 = m_pBullet1->GetTransform()->position;
	glm::vec2 lastPosition2 = m_pBullet2->GetTransform()->position;

	m_pBullet1->GetTransform()->position = lastPosition1 + AngleLengthToVector(launchAngle, launchSpeed);
	m_pBullet2->GetTransform()->position = lastPosition2 + AngleLengthToVector(launchAngle, launchSpeed);
	}
	else
	{
		m_pBullet1->GetTransform()->position = glm::vec2(startPos1);
		m_pBullet2->GetTransform()->position = glm::vec2(startPos2);

		m_pBullet1->GetRigidBody()->velocity = glm::vec2(0.0f,0.0f);
		m_pBullet2->GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		
		t = 0.0f;
	}
}

//void PlayScene::ResetObjects2()
//{
//	if (bShot)
//	{
//		for (int i = 0; i < physicsEngine.physicsObjects.size(); i++)
//		{
//			glm::vec2 lastPosition = physicsEngine.physicsObjects[i]->GetTransform()->position;
//			physicsEngine.physicsObjects[i]->GetTransform()->position = lastPosition + AngleLengthToVector(launchAngle, launchSpeed);
//		}
//	}
//	else
//	{
//		for (int i = 0; i < physicsEngine.physicsObjects.size(); i++)
//		{
//			physicsEngine.physicsObjects[i]->GetTransform()->position = glm::vec2(rand()*1);
//			physicsEngine.physicsObjects[i]->GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
//		}
//	}
//}

void PlayScene::Update()
{
	t += dt;
	std::cout << t;
	std::cout << "\n";
	physicsEngine.UpdatePhysics();
	
	ResetObjects();
	ShootProjectile();
	UpdateDisplayList();
}

void PlayScene::Clean()
{
	RemoveAllChildren();
}
void PlayScene::HandleEvents()
{
	EventManager::Instance().Update();

	GetKeyboardInput();
}

void PlayScene::GetKeyboardInput()
{
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_1))
	{
		Game::Instance().ChangeSceneState(SceneState::PLAY);
	}
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_2))
	{
		Game::Instance().ChangeSceneState(SceneState::END);
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_SPACE))
	{
 		if (!bShot)
		{
			bShot = true;
			SDL_Delay(300);
		}
		else
		{
			bShot = false;
			SDL_Delay(300);
		}
	}
}

void PlayScene::Start()

{
	startPos1 = glm::vec2(x, y);
	startPos2 = glm::vec2(400, 400);
		// Set GUI Title
	m_guiTitle = "Play Scene";

	// Set Input Type
	m_pCurrentInputType = static_cast<int>(InputType::KEYBOARD_MOUSE);

	// Projectile
	m_pBullet1 = new PhysicsObject();
	AddChild(m_pBullet1);
	m_pBullet1->GetTransform()->position = glm::vec2(startPos1);
	physicsEngine.physicsObjects.push_back(m_pBullet1);

	// Projectile
	m_pBullet2 = new PhysicsObject();
	AddChild(m_pBullet2);
	m_pBullet2->GetTransform()->position = glm::vec2(startPos2);
	physicsEngine.physicsObjects.push_back(m_pBullet2);



	/* DO NOT REMOVE */
	ImGuiWindowFrame::Instance().SetGuiFunction([this] { GUI_Function(); });
}
void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("GAME2005_Lab4_HendersonPhilip", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::Separator();

	ImGui::SliderFloat("Time", &t, 0.0f, 100.0f);
	ImGui::SliderFloat("Gravity", &gravity, -9.81f, 0.0f);
	//ImGui::SliderFloat("Launch Angle", &launchAngle, 0.0f, 90.0f);
	//ImGui::SliderFloat("Launch Speed", &launchSpeed, 0.0f, 15.0);

	//glm::vec2 velocity = AngleLengthToVector(launchAngle, launchSpeed);
	//ImGui::LabelText("Velocity Vector", "x:%f, y:%f", velocity.x, -velocity.y);

	ImGui::Separator();

	ImGui::End();
}
