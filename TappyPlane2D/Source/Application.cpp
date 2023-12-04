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

	SceneManager::Get().CreateScene<StartScene>("StartScene");
	SceneManager::Get().CreateScene<PlayScene>("PlayScene");

	IScene* scene = SceneManager::Get().SetCurrentScene("StartScene");
	scene->EnterScene();

	while (!InputManager::Get().ShouldCloseWindow())
	{
		globalTimer.Tick();
		InputManager::Get().Tick();

		scene->TickScene(globalTimer.GetDeltaSeconds());
	}

	EngineManager::Get().Shutdown();
	return 0;
}