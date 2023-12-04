#include "StartScene.h"

#include "AssertionMacro.h"
#include "ObjectManager.h"
#include "RenderManager.h"

#include "Background.h"
#include "MainTitle.h"

StartScene::~StartScene()
{
}

void StartScene::EnterScene()
{
	bIsEnterScene_ = true;

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

	objects_ = {
		background, 
		mainTitle,
	};
}

void StartScene::ExitScene()
{
	bIsEnterScene_ = false;
}

void StartScene::TickScene(float deltaSeconds)
{
	RenderManager& renderManager = RenderManager::Get();
	renderManager.SetViewport(0, 0, 1000, 800);
	renderManager.BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	for (auto& object : objects_)
	{
		object->Update(deltaSeconds);
		object->Render();
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