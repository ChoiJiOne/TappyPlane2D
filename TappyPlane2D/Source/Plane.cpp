#include "Plane.h"

#include "AssertionMacro.h"
#include "CommandLineArg.h"
#include "InputManager.h"
#include "MathUtils.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "StringUtils.h"
#include "Texture2D.h"

#include <map>

std::map<Plane::EColor, std::string> colorTypeMaps = {
	{ Plane::EColor::Blue,   "planeBlue"   },
	{ Plane::EColor::Green,  "planeGreen"  },
	{ Plane::EColor::Red,    "planeRed"    },
	{ Plane::EColor::Yellow, "planeYellow" },
};

Plane::~Plane()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Plane::Initialize(const EColor& colorType)
{
	ASSERT(!bIsInitialized_, "already initialize ground game object...");

	animationFrameTime_ = 0.09f;

	animationTextures_ = {
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 1)),
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 2)),
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 3)),
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 2)),
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 1)),
	};

	width_ = 88.0f;
	height_ = 73.0f;
	rotate_ = 0.0f;

	int32_t windowWidth = 0;
	int32_t windowHeight = 0;
	RenderManager::Get().GetRenderWindowSize(windowWidth, windowHeight);

	center_ = Vector2f(static_cast<float>(windowWidth) / 2.0f, static_cast<float>(windowHeight) / 2.0f);

	collisionBound_ = Circle(center_, height_ / 2.0f);

	bIsInitialized_ = true;
}

void Plane::Update(float deltaSeconds)
{
	accumulateAnimationFrameTime_ += deltaSeconds;

	if (accumulateAnimationFrameTime_ >= animationFrameTime_)
	{
		accumulateAnimationFrameTime_ = 0.0f;
		animationTextureIndex_ = (animationTextureIndex_ + 1) % (animationTextures_.size());
	}
}

void Plane::Render()
{
	RenderManager::Get().DrawTexture2D(animationTextures_[animationTextureIndex_], center_, width_, height_, rotate_, 1.0f);

	// 충돌 처리 확인용! => 나중에 삭제해야 함
	RenderManager::Get().DrawWireframeCircle2D(collisionBound_.GetCenter(), collisionBound_.GetRadius(), Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
}

void Plane::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");
	bIsInitialized_ = false;
}