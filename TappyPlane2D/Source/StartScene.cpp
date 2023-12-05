#include "StartScene.h"

#include "AssertionMacro.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "MathUtils.h"

#include "Background.h"
#include "ClickTrigger.h"
#include "MainTitle.h"

StartScene::~StartScene()
{
}

void StartScene::EnterScene()
{
	bIsEnterScene_ = true;
	currentSceneState_ = ESceneState::Enter;
	enterAccumulateTime_ = 0.0f;
	exitAccumulateTime_ = 0.0f;

	Background* background = ObjectManager::Get().GetGameObject<Background>("Background");
	if (!background)
	{
		background = ObjectManager::Get().CreateGameObject<Background>("Background");
		background->Initialize();
	}

	MainTitle* mainTitle = ObjectManager::Get().GetGameObject<MainTitle>("MainTitle");
	if (!mainTitle)
	{
		mainTitle = ObjectManager::Get().CreateGameObject<MainTitle>("MainTitle");
		mainTitle->Initialize();
	}

	ClickTrigger* clickTrigger = ObjectManager::Get().GetGameObject<ClickTrigger>("StartTrigger");
	if (!clickTrigger)
	{
		clickTrigger = ObjectManager::Get().CreateGameObject<ClickTrigger>("StartTrigger");
		clickTrigger->Initialize(
			L"PRESS MOUSE BUTTON", 
			Vector2f(500.0f, 400.0f), 
			Vector4f(1.0f, 0.0f, 0.0f, 1.0f),
			[&]() { currentSceneState_ = ESceneState::Exit; }
		);
	}

	objects_ = {
		background, 
		mainTitle,
		clickTrigger,
	};
}

void StartScene::ExitScene()
{
	currentSceneState_ = ESceneState::Wait;
	bIsEnterScene_ = false;
}

void StartScene::TickScene(float deltaSeconds)
{
	switch (currentSceneState_)
	{
	case ESceneState::Enter:
		enterAccumulateTime_ += deltaSeconds;
		if (enterAccumulateTime_ >= 1.0f)
		{
			currentSceneState_ = ESceneState::Play;
		}
		break;

	case ESceneState::Exit:
		exitAccumulateTime_ += deltaSeconds;
		if (exitAccumulateTime_ >= 1.0f)
		{
			currentSceneState_ = ESceneState::Wait;
			SceneManager::Get().SwitchNextScene();
		}
		break;
	}

	RenderManager& renderManager = RenderManager::Get();
	renderManager.SetViewport(0, 0, 1000, 800);
	renderManager.BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	for (auto& object : objects_)
	{
		object->Update(deltaSeconds);
		object->Render();
	}

	float bias = 0.0f;
	switch (currentSceneState_)
	{
	case ESceneState::Enter:
		bias = MathUtils::Clamp<float>(enterAccumulateTime_, 0.0f, 1.0f);
		renderManager.PostEffectFadeEffect(bias);
		break;

	case ESceneState::Exit:
		bias = 1.0f - MathUtils::Clamp<float>(exitAccumulateTime_, 0.0f, 1.0f);
		renderManager.PostEffectFadeEffect(bias);
		break;

	case ESceneState::Wait:
		bias = 0.0f;
		renderManager.PostEffectFadeEffect(bias);
		break;
	}
	
	renderManager.EndFrame();
}

void StartScene::SetNextScene(IScene* scene)
{
	nextScene_ = scene;
}

IScene* StartScene::GetNextScene()
{
	return nextScene_;
}