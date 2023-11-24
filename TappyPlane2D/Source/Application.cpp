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

	Ground* bottomGround = ObjectManager::Get().CreateGameObject<Ground>("BottomGround");
	bottomGround->Initialize(Ground::EType::Bottom);

	Ground* topGround = ObjectManager::Get().CreateGameObject<Ground>("TopGround");
	topGround->Initialize(Ground::EType::Top);

	while (!InputManager::Get().ShouldCloseWindow())
	{
		globalTimer.Tick();
		InputManager::Get().Tick();

		background->Update(globalTimer.GetDeltaSeconds());
		bottomGround->Update(globalTimer.GetDeltaSeconds());
		topGround->Update(globalTimer.GetDeltaSeconds());
		
		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		
		background->Render();
		bottomGround->Render();
		topGround->Render();

		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}