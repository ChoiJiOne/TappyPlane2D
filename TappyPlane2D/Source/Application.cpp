#include "EngineManager.h"

#include "Background.h"
#include "Ground.h"
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

	Plane* plane = ObjectManager::Get().CreateGameObject<Plane>("Plane");
	plane->Initialize(Plane::EColor::Yellow);

	Rock* rock = ObjectManager::Get().CreateGameObject<Rock>("Rock");
	rock->Initialize(Rock::EType::Ice, 1100.0f);

	Star* star = ObjectManager::Get().CreateGameObject<Star>("Star");
	star->Initialize(rock->GetEmptyMiddlePoint());

	while (!InputManager::Get().ShouldCloseWindow())
	{
		globalTimer.Tick();
		InputManager::Get().Tick();

		background->Update(globalTimer.GetDeltaSeconds());
		ground->Update(globalTimer.GetDeltaSeconds());
		rock->Update(globalTimer.GetDeltaSeconds());
		star->Update(globalTimer.GetDeltaSeconds());
		plane->Update(globalTimer.GetDeltaSeconds());

		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		
		background->Render();
		ground->Render();
		rock->Render();
		star->Render();
		plane->Render();
		
		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}