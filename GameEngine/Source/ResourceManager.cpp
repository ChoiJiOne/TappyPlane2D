#include "ResourceManager.h"

#include "AssertionMacro.h"

void ResourceManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup resource manager...");

	resources_ = std::unordered_map<std::string, std::unique_ptr<IResource>>();
	
	bIsStartup_ = true;
}

void ResourceManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	for (auto& resource : resources_)
	{
		resource.second->Release();
		resource.second.reset();
	}

	bIsStartup_ = false;
}

void ResourceManager::DestroyResource(const std::string& signature)
{
	if (VerifyResource(signature))
	{
		IResource* resource = resources_.at(signature).get();
		if (resource && resource->IsInitialized())
		{
			resource->Release();
		}

		resources_.erase(signature);
	}
}

bool ResourceManager::VerifyResource(const std::string& signature)
{
	return resources_.find(signature) != resources_.end();
}