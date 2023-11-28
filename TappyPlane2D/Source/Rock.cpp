#include "Rock.h"

#include "AssertionMacro.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "MathUtils.h"

#include <map>

std::map<Rock::EType, std::string> topRockMaps = {
	{ Rock::EType::Plain, "rockDown" },
	{ Rock::EType::Grass, "rockGrassDown" },
	{ Rock::EType::Ice,   "rockIceDown" },
	{ Rock::EType::Snow,  "rockSnowDown" },
};

std::map<Rock::EType, std::string> bottomRockMaps = {
	{ Rock::EType::Plain, "rock" },
	{ Rock::EType::Grass, "rockGrass" },
	{ Rock::EType::Ice,   "rockIce" },
	{ Rock::EType::Snow,  "rockSnow" },
};

Rock::~Rock()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Rock::Initialize(const EType& type)
{
	ASSERT(!bIsInitialized_, "already initialize rock game object...");

	int32_t windowWidth = 0;
	int32_t windowHeight = 0;
	RenderManager::Get().GetRenderWindowSize(windowWidth, windowHeight);

	topTexture_ = ResourceManager::Get().GetResource<Texture2D>(topRockMaps.at(type));
	bottomTexture_ = ResourceManager::Get().GetResource<Texture2D>(bottomRockMaps.at(type));
	width_ = 108.0f;
	height_ = 239.0f;
	speed_ = 200.0f;
	
	startXPosition_ = static_cast<float>(windowWidth) + width_ / 2.0f;

	topCenter_ = Vector2f(startXPosition_, height_ / 2.0f);
	bottomCenter_ = Vector2f(startXPosition_, static_cast<float>(windowHeight) - height_ / 2.0f);
	
	bIsInitialized_ = true;
}

void Rock::Update(float deltaSeconds)
{
	topCenter_.x -= speed_ * deltaSeconds;
	bottomCenter_.x -= speed_ * deltaSeconds;
}

void Rock::Render()
{
	RenderManager::Get().DrawTexture2D(topTexture_, topCenter_, width_, height_, 0.0f);
	RenderManager::Get().DrawTexture2D(bottomTexture_, bottomCenter_, width_, height_, 0.0f);
}

void Rock::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");
	bIsInitialized_ = false;
}