#include "Ground.h"

#include "AssertionMacro.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "MathUtils.h"

#include <map>

std::map<Ground::EType, std::string> groundTypeMaps = {
	{ Ground::EType::Dirt,  "groundDirt" },
	{ Ground::EType::Grass, "groundGrass" },
	{ Ground::EType::Ice,   "groundIce" },
	{ Ground::EType::Rock,  "groundRock" },
	{ Ground::EType::Snow,  "groundSnow" },
};

Ground::~Ground()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Ground::Initialize(const EType& type)
{
	bCanMove_ = true;
	
	int32_t windowWidth = 0;
	int32_t windowHeight = 0;
	RenderManager::Get().GetRenderWindowSize(windowWidth, windowHeight);

	width_ = static_cast<float>(windowWidth);
	height_ = static_cast<float>(windowHeight) / 10.0f;
	texture_ = ResourceManager::Get().GetResource<Texture2D>(groundTypeMaps.at(type));
	topCenter_ = Vector2f(width_ / 2.0f, height_ / 2.0f);
	bottomCenter_ = Vector2f(width_ / 2.0f, static_cast<float>(windowHeight) - height_ / 2.0f);
	
	scrollSpeed_ = 200.0f;
	scrollPosition_ = 0.0f;

	bIsInitialized_ = true;
}

void Ground::Update(float deltaSeconds)
{
	if (bCanMove_)
	{
		scrollPosition_ += scrollSpeed_ * deltaSeconds;

		if (scrollPosition_ >= width_)
		{
			scrollPosition_ -= width_;
		}
	}
}

void Ground::Render()
{
	float rate = scrollPosition_ / width_;

	RenderManager::Get().DrawHorizonScrollTexture2D(texture_, bottomCenter_, width_, height_, 0.0f, rate);
	RenderManager::Get().DrawHorizonScrollTexture2D(texture_, topCenter_, width_, height_, MathUtils::Pi, 1.0f - rate);
}

void Ground::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");
	bIsInitialized_ = false;
}