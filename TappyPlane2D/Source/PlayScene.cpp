#include "PlayScene.h"

#include "AssertionMacro.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "SceneManager.h"

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

	restartTrigger_ = ObjectManager::Get().GetGameObject<ClickTrigger>("ResetTrigger");
	if (!restartTrigger_)
	{
		restartTrigger_ = ObjectManager::Get().CreateGameObject<ClickTrigger>("ResetTrigger");
	}
	restartTrigger_->Initialize(
		L"PRESS MOUSE BUTTON FOR RESET",
		Vector2f(500.0f, 400.0f),
		Vector4f(1.0f, 0.0f, 0.0f, 1.0f),
		[&]()
		{
			SceneManager::Get().SwitchNextScene();
		}
	);
}

void PlayScene::ExitScene()
{
	bIsEnterScene_ = false;
	currentSceneState_ = ESceneState::Wait;

	InputManager::Get().UnbindWindowEventAction("Minimize");
	InputManager::Get().UnbindWindowEventAction("LostFocus");
	InputManager::Get().UnbindWindowEventAction("Move");

	scheduler_->Release();
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

	switch (currentSceneState_)
	{
	case ESceneState::Enter:
		background_->Update(deltaSeconds);
		ground_->Update(deltaSeconds);
		scheduler_->Update(deltaSeconds);
		plane_->Update(deltaSeconds);
		board_->Update(deltaSeconds);
		break;

	case ESceneState::Play:
		background_->Update(deltaSeconds);
		ground_->Update(deltaSeconds);
		scheduler_->Update(deltaSeconds);
		plane_->Update(deltaSeconds);
		board_->Update(deltaSeconds);

		if (plane_->GetState() == Plane::EState::Crash && plane_->IsDoneExplosionAnimation())
		{
			currentSceneState_ = ESceneState::Crash;
		}
		break;

	case ESceneState::Pause:
		continueTrigger_->Update(deltaSeconds);
		break;

	case ESceneState::Crash:
		background_->Update(deltaSeconds);
		ground_->Update(deltaSeconds);
		scheduler_->Update(deltaSeconds);
		plane_->Update(deltaSeconds);
		board_->Update(deltaSeconds);
		restartTrigger_->Update(deltaSeconds);
		break;

	case ESceneState::Exit:
		break;

	default:
		break;
	}
	
	RenderManager& renderManager = RenderManager::Get();
	renderManager.SetViewport(0, 0, 1000, 800);
	renderManager.BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	switch (currentSceneState_)
	{
	case ESceneState::Enter:
		background_->Render();
		ground_->Render();
		scheduler_->Render();
		plane_->Render();
		board_->Render();

		if (currentSceneState_ == ESceneState::Enter)
		{
			float bias = MathUtils::Clamp<float>(enterAccumulateTime_, 0.0f, 1.0f);
			renderManager.PostEffectFadeEffect(bias);
		}
		break;

	case ESceneState::Play:
		background_->Render();
		ground_->Render();
		scheduler_->Render();
		plane_->Render();
		board_->Render();
		break;

	case ESceneState::Pause:
		background_->Render();
		ground_->Render();
		scheduler_->Render();
		plane_->Render();
		board_->Render();
		continueTrigger_->Render();
		break;

	case ESceneState::Crash:
		background_->Render();
		ground_->Render();
		scheduler_->Render();
		plane_->Render();
		board_->Render();
		restartTrigger_->Render();
		break;
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