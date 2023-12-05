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
	PlayScene* playScene = SceneManager::Get().CreateScene<PlayScene>("PlayScene");

	startScene->SetNextScene(playScene);
	playScene->SetNextScene(startScene);

	IScene* scene = SceneManager::Get().SetCurrentScene("StartScene");
	scene->EnterScene();

	while (!InputManager::Get().ShouldCloseWindow())
	{
		globalTimer.Tick();
		InputManager::Get().Tick();

		IScene* currentScene = SceneManager::Get().GetCurrentScene();
		currentScene->TickScene(globalTimer.GetDeltaSeconds());
	}

	EngineManager::Get().Shutdown();
	return 0;
}