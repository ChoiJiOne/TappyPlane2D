#include "PlayScene.h"

#include "AssertionMacro.h"
#include "ObjectManager.h"
#include "RenderManager.h"

#include "Background.h"
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

	Background* background = ObjectManager::Get().GetGameObject<Background>("Background");
	if (!background)
	{
		background = ObjectManager::Get().CreateGameObject<Background>("Background");
		background->Initialize();
	}

	Ground* ground = ObjectManager::Get().GetGameObject<Ground>("Ground");
	if (!ground)
	{
		ground = ObjectManager::Get().CreateGameObject<Ground>("Ground");
		ground->Initialize(Ground::EType::Grass);
	}

	ObjectScheduler* scheduler = ObjectManager::Get().GetGameObject<ObjectScheduler>("Scheduler");
	if (!scheduler)
	{
		scheduler = ObjectManager::Get().CreateGameObject<ObjectScheduler>("Scheduler");
		scheduler->Initialize(Rock::EType::Plain, 1100.0f);
	}

	Plane* plane = ObjectManager::Get().GetGameObject<Plane>("Plane");
	if (!plane)
	{
		plane = ObjectManager::Get().CreateGameObject<Plane>("Plane");
		plane->Initialize(Plane::EColor::Yellow);
	}

	ScoreBoard* board = ObjectManager::Get().GetGameObject<ScoreBoard>("Board");
	if(!board)
	{
		board = ObjectManager::Get().CreateGameObject<ScoreBoard>("Board");
		board->Initialize(Vector2f(500.0f, 100.0f), Vector4f(0.3f, 0.3f, 0.3f, 1.0f));
	}

	objects_ = {
		background,
		ground,
		scheduler,
		plane,
		board,
	};
}

void PlayScene::ExitScene()
{
	bIsEnterScene_ = false;
}

void PlayScene::TickScene(float deltaSeconds)
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

void PlayScene::SetNextScene(IScene* scene)
{
	nextScene_ = scene;
}

IScene* PlayScene::GetNextScene()
{
	return nextScene_;
}