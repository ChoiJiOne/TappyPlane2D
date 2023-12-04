#include "SceneManager.h"

#include "AssertionMacro.h"

void SceneManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup scene manager...");

	scenes_ = std::unordered_map<std::string, std::unique_ptr<IScene>>();

	bIsStartup_ = true;
}

void SceneManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	for (auto& scene : scenes_)
	{
		scene.second.reset();
	}

	bIsStartup_ = false;
}

void SceneManager::DestroyScene(const std::string& signature)
{
	if (VerifyScene(signature))
	{
		scenes_.erase(signature);
	}
}

IScene* SceneManager::SetCurrentScene(const std::string& signature)
{
	currentScene_ = GetScene<IScene>(signature);
	return currentScene_;
}

void SceneManager::SwitchNextScene()
{
	currentScene_->ExitScene();
	currentScene_ = currentScene_->GetNextScene();
	currentScene_->EnterScene();
}

bool SceneManager::VerifyScene(const std::string& signature)
{
	return scenes_.find(signature) != scenes_.end();
}