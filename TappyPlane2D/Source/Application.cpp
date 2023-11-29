#include "EngineManager.h"

#include "Background.h"
#include "Ground.h"
#include "ObjectScheduler.h"
#include "Plane.h"
#include "Rock.h"
#include "ScoreBoard.h"
#include "Star.h"

int main(int argc, char* argv[])
{
	EngineManager::Get().Startup();

	RenderManager::Get().SetAlphaBlend(true);
	RenderManager::Get().SetDepthMode(false);

	GameTimer globalTimer;
	globalTimer.Reset();

	Background* background = ObjectManager::Get().CreateGameObject<Background>("Background");
	background->Initialize();

	Ground* ground = ObjectManager::Get().CreateGameObject<Ground>("Ground");
	ground->Initialize(Ground::EType::Grass);

	ObjectScheduler* scheduler = ObjectManager::Get().CreateGameObject<ObjectScheduler>("Scheduler");
	scheduler->Initialize(Rock::EType::Plain, 1100.0f);

	Plane* plane = ObjectManager::Get().CreateGameObject<Plane>("Plane");
	plane->Initialize(Plane::EColor::Yellow);

	ScoreBoard* board = ObjectManager::Get().CreateGameObject<ScoreBoard>("Board");
	board->Initialize(Vector2f(500.0f, 100.0f), 53.0f, 78.0f, 10.0f);

	while (!InputManager::Get().ShouldCloseWindow())
	{
		globalTimer.Tick();
		InputManager::Get().Tick();
		
		background->Update(globalTimer.GetDeltaSeconds());
		ground->Update(globalTimer.GetDeltaSeconds());
		scheduler->Update(globalTimer.GetDeltaSeconds());
		plane->Update(globalTimer.GetDeltaSeconds());
		board->Update(globalTimer.GetDeltaSeconds());

		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		
		background->Render();
		ground->Render();
		scheduler->Render();
		plane->Render();
		board->Render();

		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}