#include "Background.h"

#include "AssertionMacro.h"
#include "CommandLineArg.h"
#include "RenderManager.h"
#include "ResourceManager.h"

Background::~Background()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Background::Initialize()
{
	ASSERT(!bIsInitialized_, "already initialize background game object...");

	std::string resourcePath;
	CommandLineArg::GetStringValue("resource", resourcePath);

	ResourceManager& manager = ResourceManager::Get();
	if (!manager.GetResource<Texture2D>("Background"))
	{
		texture_ = manager.CreateResource<Texture2D>("Background");
		texture_->Initialize(resourcePath + "Texture\\background.png");
	}

	bIsInitialized_ = true;
}

void Background::Update(float deltaSeconds)
{
}

void Background::Render()
{
	RenderManager::Get().DrawTexture2D(texture_);
}

void Background::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	ResourceManager::Get().DestroyResource("Background");

	bIsInitialized_ = false;
}