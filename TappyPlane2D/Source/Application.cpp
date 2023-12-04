#include "EngineManager.h"

#include "PlayScene.h"
#include "StartScene.h"

int main(int argc, char* argv[])
{
	EngineManager::Get().Startup();

	RenderManager::Get().SetAlphaBlend(true);
	RenderManager::Get().SetDepthMode(false);

	GameTimer globalTimer;
	globalTimer.Reset();

	StartScene* startScene = SceneManager::Get().CreateScene<StartScene>("StartScene");
	startScene->EnterScene();

	PlayScene* playScene = SceneManager::Get().CreateScene<PlayScene>("PlayScene");
	//playScene->EnterScene();

	while (!InputManager::Get().ShouldCloseWindow())
	{
		globalTimer.Tick();
		InputManager::Get().Tick();

		startScene->TickScene(globalTimer.GetDeltaSeconds());
	}

	EngineManager::Get().Shutdown();
	return 0;
}