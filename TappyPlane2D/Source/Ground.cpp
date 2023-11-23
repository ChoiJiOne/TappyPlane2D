#include "Ground.h"

#include "AssertionMacro.h"
#include "CommandLineArg.h"
#include "RenderManager.h"
#include "ResourceManager.h"

Ground::~Ground()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Ground::Initialize()
{
	ASSERT(!bIsInitialized_, "already initialize ground game object...");

	std::string resourcePath;
	CommandLineArg::GetStringValue("resource", resourcePath);

	ResourceManager& manager = ResourceManager::Get();
	if (!manager.GetResource<Texture2D>("Ground"))
	{
		texture_ = manager.CreateResource<Texture2D>("Ground");
		texture_->Initialize(resourcePath + "Texture\\groundGrass.png");
	}

	int32_t windowWidth = 0;
	int32_t windowHeight = 0;
	RenderManager::Get().GetRenderWindowSize(windowWidth, windowHeight);

	width_ = static_cast<float>(windowWidth);
	height_ = static_cast<float>(windowHeight) / 10.0f;
	center_ = Vector2f(width_ / 2.0f, static_cast<float>(windowHeight) - height_ / 2.0f);
	
	bIsInitialized_ = true;
}

void Ground::Update(float deltaSeconds)
{
}

void Ground::Render()
{
	RenderManager::Get().DrawTexture2D(texture_, center_, width_, height_, 0.0f);
}

void Ground::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	ResourceManager::Get().DestroyResource("Ground");

	bIsInitialized_ = false;
}