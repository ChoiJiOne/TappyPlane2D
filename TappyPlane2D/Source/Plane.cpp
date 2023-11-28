#include "Plane.h"
#include "Background.h"
#include "Rock.h"

#include "AssertionMacro.h"
#include "CommandLineArg.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
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
	ASSERT(!bIsInitialized_, "already initialize plane game object...");

	int32_t windowWidth = 0;
	int32_t windowHeight = 0;
	RenderManager::Get().GetRenderWindowSize(windowWidth, windowHeight);

	// 기본 속성 설정
	colorType_ = colorType;
	center_ = Vector2f(static_cast<float>(windowWidth) / 2.0f, static_cast<float>(windowHeight) / 2.0f);
	width_ = 88.0f;
	height_ = 73.0f;
	rotate_ = 0.0f;
	state_ = EState::Wait;
	collisionBound_ = AABB(center_, width_, height_);

	// 애니메이션 속성 설정
	animationTextures_ = {
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 1)),
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 2)),
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 3)),
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 2)),
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 1)),
	};
	accumulateAnimationFrameTime_ = 0;
	animationFrameTime_ = 0.09f;
	accumulateAnimationFrameTime_ = 0.0f;

	waitAccumulateTime_ = 0.0f;
	waitPosition_ = Vector2f(static_cast<float>(windowWidth) / 2.0f, static_cast<float>(windowHeight) / 2.0f);

	maxSpeed_ = 400.0f;
	currentSpeed_ = 0.0f;
	dampingSpeed_ = 10.0f;

	bIsInitialized_ = true;
}

void Plane::Update(float deltaSeconds)
{
	UpdateAnimation(deltaSeconds);

	switch (state_)
	{
	case EState::Wait:
		UpdateWaitState(deltaSeconds);
		break;

	case EState::Flight:
		UpdateFlightState(deltaSeconds);
		break;

	case EState::Crash:
		UpdateCrashState(deltaSeconds);
		break;

	default:
		ASSERT(false, "undefined plane state : %d", static_cast<int32_t>(state_));
	}
}

void Plane::Render()
{
	RenderManager::Get().DrawTexture2D(animationTextures_[animationTextureIndex_], center_, width_, height_, rotate_, 1.0f);

	Rock* rock = ObjectManager::Get().GetGameObject<Rock>("Rock");
	if (rock->IsCollisionPlane(this))
	{
		RenderManager::Get().DrawWireframeRectangle2D(center_, width_, height_, 0.0f, Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		RenderManager::Get().DrawWireframeRectangle2D(center_, width_, height_, 0.0f, Vector4f(0.0f, 0.0f, 1.0f, 1.0f));
	}
}

void Plane::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");
	bIsInitialized_ = false;
}

void Plane::UpdateAnimation(float deltaSeconds)
{
	accumulateAnimationFrameTime_ += deltaSeconds;

	if (accumulateAnimationFrameTime_ >= animationFrameTime_)
	{
		accumulateAnimationFrameTime_ = 0.0f;
		animationTextureIndex_ = (animationTextureIndex_ + 1) % (animationTextures_.size());
	}
}

void Plane::UpdateWaitState(float deltaSeconds)
{
	ASSERT(state_ == EState::Wait, "inavlid plane state : %d", static_cast<int32_t>(state_));

	waitAccumulateTime_ += deltaSeconds;

	center_.x = waitPosition_.x;
	center_.y = waitPosition_.y + 10.0f * MathUtils::ScalarSin(waitAccumulateTime_ * 2.0f);
	collisionBound_.SetProperty(center_, width_, height_);

	if (InputManager::Get().GetKeyPressState(EKeyCode::KEY_SPACE) == EPressState::Pressed)
	{
		currentSpeed_ = maxSpeed_;
		state_ = EState::Flight;
	}
}

void Plane::UpdateFlightState(float deltaSeconds)
{
	ASSERT(state_ == EState::Flight, "inavlid plane state : %d", static_cast<int32_t>(state_));
	
	currentSpeed_ -= dampingSpeed_;
	center_.y -= currentSpeed_ * deltaSeconds;

	if (currentSpeed_ <= 0.0f && InputManager::Get().GetKeyPressState(EKeyCode::KEY_SPACE) == EPressState::Pressed)
	{
		currentSpeed_ = maxSpeed_;
	}
	
	collisionBound_.SetProperty(center_, width_, height_);
}

void Plane::UpdateCrashState(float deltaSeconds)
{
	ASSERT(state_ == EState::Crash, "inavlid plane state : %d", static_cast<int32_t>(state_));
}