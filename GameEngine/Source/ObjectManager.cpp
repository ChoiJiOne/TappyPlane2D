#include "ObjectManager.h"

#include "AssertionMacro.h"

void ObjectManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup resource manager...");

	gameObjects_ = std::unordered_map<std::string, std::unique_ptr<IGameObject>>();

	bIsStartup_ = true;
}

void ObjectManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	for (auto& gameObject : gameObjects_)
	{
		gameObject.second->Release();
		gameObject.second.reset();
	}

	bIsStartup_ = false;
}

void ObjectManager::DestroyResource(const std::string& signature)
{
	if (VerifyResource(signature))
	{
		IGameObject* gameObject = gameObjects_.at(signature).get();
		if (gameObject && gameObject->IsInitialized())
		{
			gameObject->Release();
		}

		gameObjects_.erase(signature);
	}
}

bool ObjectManager::VerifyResource(const std::string& signature)
{
	return gameObjects_.find(signature) != gameObjects_.end();
}