#include "EngineManager.h"

#include "Background.h"
#include "Ground.h"
#include "ObjectScheduler.h"
#include "Plane.h"
#include "Rock.h"
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

	while (!InputManager::Get().ShouldCloseWindow())
	{
		globalTimer.Tick();
		InputManager::Get().Tick();

		background->Update(globalTimer.GetDeltaSeconds());
		ground->Update(globalTimer.GetDeltaSeconds());
		scheduler->Update(globalTimer.GetDeltaSeconds());
		plane->Update(globalTimer.GetDeltaSeconds());

		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		
		background->Render();
		ground->Render();
		scheduler->Render();
		plane->Render();
		
		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}