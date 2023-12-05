#include "PlayScene.h"

#include "AssertionMacro.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "RenderManager.h"

#include "Background.h"
#include "ClickTrigger.h"
#include "Ground.h"
#include "ObjectScheduler.h"
#include "Plane.h"
#include "Rock.h"
#include "ScoreBoard.h"
#include "Star.h"

PlayScene::~PlayScene()
{
}

void PlayScene::EnterScene()
{
	bIsEnterScene_ = true;
	currentSceneState_ = ESceneState::Enter;
	enterAccumulateTime_ = 0.0f;

	std::function<void()> pauseTrigger = [&]() 
	{ 
		if (currentSceneState_ == ESceneState::Play && plane_->GetState() == Plane::EState::Flight)
		{
			currentSceneState_ = ESceneState::Pause;
		}
	};
	InputManager::Get().BindWindowEventAction("Minimize", EWindowEvent::EnterMinimize, pauseTrigger);
	InputManager::Get().BindWindowEventAction("LostFocus", EWindowEvent::LostFocus, pauseTrigger);
	InputManager::Get().BindWindowEventAction("Move", EWindowEvent::Move, pauseTrigger);
	
    background_ = ObjectManager::Get().GetGameObject<Background>("Background");

	std::array<Ground::EType, 5> groundTypes = {
		Ground::EType::Dirt,
		Ground::EType::Grass,
		Ground::EType::Ice,
		Ground::EType::Rock,
		Ground::EType::Snow,
	};
	ground_ = ObjectManager::Get().GetGameObject<Ground>("Ground");
	if (!ground_)
	{
		ground_ = ObjectManager::Get().CreateGameObject<Ground>("Ground");
	}
	ground_->Initialize(groundTypes.at(MathUtils::GenerateRandomInt(0, static_cast<int32_t>(groundTypes.size()) - 1)));

	std::array<Rock::EType, 4> rockTypes = {
		Rock::EType::Plain,
		Rock::EType::Grass,
		Rock::EType::Ice,
		Rock::EType::Snow,
	};
	scheduler_ = ObjectManager::Get().GetGameObject<ObjectScheduler>("Scheduler");
	if (!scheduler_)
	{
		scheduler_ = ObjectManager::Get().CreateGameObject<ObjectScheduler>("Scheduler");
	}
	scheduler_->Initialize(rockTypes.at(MathUtils::GenerateRandomInt(0, static_cast<int32_t>(rockTypes.size()) - 1)), 1100.0f);
	
	std::array<Plane::EColor, 4> planeColors = {
		Plane::EColor::Blue,
		Plane::EColor::Green,
		Plane::EColor::Red,
		Plane::EColor::Yellow,
	};
	plane_ = ObjectManager::Get().GetGameObject<Plane>("Plane");
	if (!plane_)
	{
		plane_ = ObjectManager::Get().CreateGameObject<Plane>("Plane");
	}
	plane_->Initialize(planeColors.at(MathUtils::GenerateRandomInt(0, static_cast<int32_t>(planeColors.size()) - 1)));
	
	board_ = ObjectManager::Get().GetGameObject<ScoreBoard>("Board");
	if (!board_)
	{
		board_ = ObjectManager::Get().CreateGameObject<ScoreBoard>("Board");
	}
	board_->Initialize(Vector2f(500.0f, 100.0f), Vector4f(0.3f, 0.3f, 0.3f, 1.0f));

	continueTrigger_ = ObjectManager::Get().GetGameObject<ClickTrigger>("ContinueTrigger");
	if (!continueTrigger_)
	{
		continueTrigger_ = ObjectManager::Get().CreateGameObject<ClickTrigger>("ContinueTrigger");
	}
	continueTrigger_->Initialize(
		L"PRESS MOUSE BUTTON",
		Vector2f(500.0f, 400.0f),
		Vector4f(1.0f, 0.0f, 0.0f, 1.0f),
		[&]() 
		{ 
			if (currentSceneState_ == ESceneState::Pause)
			{
				currentSceneState_ = ESceneState::Play;
			}
		}
	);
}

void PlayScene::ExitScene()
{
	bIsEnterScene_ = false;
	currentSceneState_ = ESceneState::Wait;
}

void PlayScene::TickScene(float deltaSeconds)
{
	if (currentSceneState_ == ESceneState::Enter)
	{
		enterAccumulateTime_ += deltaSeconds;
		if (enterAccumulateTime_ >= 1.0f)
		{
			currentSceneState_ = ESceneState::Play;
		}
	}

	RenderManager& renderManager = RenderManager::Get();
	renderManager.SetViewport(0, 0, 1000, 800);
	renderManager.BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	//for (auto& object : objects_)
	//{
	//	object->Update(deltaSeconds);
	//	object->Render();
	//}

	if (currentSceneState_ == ESceneState::Enter)
	{
		float bias = MathUtils::Clamp<float>(enterAccumulateTime_, 0.0f, 1.0f);
		renderManager.PostEffectFadeEffect(bias);
	}

	renderManager.EndFrame();
}

void PlayScene::SetNextScene(IScene* scene)
{
	nextScene_ = scene;
}

IScene* PlayScene::GetNextScene()
{
	return nextScene_;
}