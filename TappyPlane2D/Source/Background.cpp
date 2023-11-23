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

	int32_t windowWidth = 0;
	int32_t windowHeight = 0;
	RenderManager::Get().GetRenderWindowSize(windowWidth, windowHeight);

	scrollSpeed_ = 100.0f;
	scrollPosition_ = 0.0f;
	maxScrollPosition_ = static_cast<float>(windowWidth);
	
	bIsInitialized_ = true;
}

void Background::Update(float deltaSeconds)
{
	scrollPosition_ += scrollSpeed_ * deltaSeconds;

	if (scrollSpeed_ >= maxScrollPosition_)
	{
		scrollPosition_ -= maxScrollPosition_;
	}
}

void Background::Render()
{
	float rate = scrollPosition_ / maxScrollPosition_;
	RenderManager::Get().DrawHorizonScrollTexture2D(texture_, rate);
}

void Background::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	ResourceManager::Get().DestroyResource("Background");

	bIsInitialized_ = false;
}