#include "EngineManager.h"

#include "Background.h"
#include "Ground.h"

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
	ground->Initialize();
	
	while (!InputManager::Get().ShouldCloseWindow())
	{
		globalTimer.Tick();
		InputManager::Get().Tick();

		background->Update(globalTimer.GetDeltaSeconds());
		ground->Update(globalTimer.GetDeltaSeconds());

		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

		background->Render();
		ground->Render();

		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}