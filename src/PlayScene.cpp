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

	v = AngleLengthToVector(launchAngle, launchSpeed);
	endPoint = startPos + (AngleLengthToVector(launchAngle, launchSpeed) * glm::vec2(10, 10));
	
	//Draw velocity vector
	SDL_RenderDrawLineF(Renderer::Instance().GetRenderer(), startPos.x, startPos.y, endPoint.x, endPoint.y);

	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 210, 85, 45, 255);
}

void PlayScene::ShootProjectile()
{
	//if (bShot)
	//{
	//	glm::vec2 lastPosition = m_pBullet->GetTransform()->position;
	//	m_pBullet->GetTransform()->position = lastPosition + AngleLengthToVector(launchAngle, launchSpeed);
	//	m_pBullet->GetTransform()->position.y -= g * t;
	//}
	//else
	//{
	//	m_pBullet->GetTransform()->position = glm::vec2(startPos);
	//	t = 0.0f;
	//	v.y = 20.f;
	//}
}

void PlayScene::Update()
{
	t += dt;
	physicsEngine.UpdatePhysics();
	
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
		Game::Instance().ChangeSceneState(SceneState::START);
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
	startPos = glm::vec2(x, y);
		// Set GUI Title
	m_guiTitle = "Play Scene";

	// Set Input Type
	m_pCurrentInputType = static_cast<int>(InputType::KEYBOARD_MOUSE);

	// Projectile
	m_pBullet = new Target();
	AddChild(m_pBullet);
	m_pBullet->GetTransform()->position = glm::vec2(startPos);
	physicsEngine.physicsObjects.push_back(m_pBullet);
	
	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", GameObjectType::BACK_BUTTON);
	m_pBackButton->GetTransform()->position = glm::vec2(300.0f, 550.0f);
	m_pBackButton->AddEventListener(Event::CLICK, [&]()-> void
	{
		m_pBackButton->SetActive(false);
		Game::Instance().ChangeSceneState(SceneState::START);
	});

	m_pBackButton->AddEventListener(Event::MOUSE_OVER, [&]()->void
	{
		m_pBackButton->SetAlpha(128);
	});

	m_pBackButton->AddEventListener(Event::MOUSE_OUT, [&]()->void
	{
		m_pBackButton->SetAlpha(255);
	});
	AddChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", GameObjectType::NEXT_BUTTON);
	m_pNextButton->GetTransform()->position = glm::vec2(500.0f, 550.0f);
	m_pNextButton->AddEventListener(Event::CLICK, [&]()-> void
	{
		m_pNextButton->SetActive(false);
		Game::Instance().ChangeSceneState(SceneState::END);
	});

	m_pNextButton->AddEventListener(Event::MOUSE_OVER, [&]()->void
	{
		m_pNextButton->SetAlpha(128);
	});

	m_pNextButton->AddEventListener(Event::MOUSE_OUT, [&]()->void
	{
		m_pNextButton->SetAlpha(255);
	});

	AddChild(m_pNextButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->GetTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	AddChild(m_pInstructionsLabel);

	/* DO NOT REMOVE */
	ImGuiWindowFrame::Instance().SetGuiFunction([this] { GUI_Function(); });
}
void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("GAME2005_Lab3_HendersonPhilip", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::Separator();

	ImGui::SliderFloat("Launch Angle", &launchAngle, 0.0f, 90.0f, "%.3f");
	ImGui::SliderFloat("Launch Speed", &launchSpeed, 0.0f, 15.0f, "%.3f");
	ImGui::SliderFloat("Starting Y", &startPos.y, 200.0f, 500.0f, "%.3f");	
	ImGui::SliderFloat("Gravity", &g, -9.81f, 0.0f, "%.3f");

	glm::vec2 velocity = AngleLengthToVector(launchAngle, launchSpeed);
	ImGui::LabelText("Velocity Vector", "x:%f, y:%f", velocity.x, -velocity.y);

	ImGui::Separator();

	ImGui::End();
}
