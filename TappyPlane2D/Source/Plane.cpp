#include "Plane.h"
#include "Background.h"
#include "Ground.h"
#include "ObjectScheduler.h"
#include "Rock.h"
#include "ScoreBoard.h"
#include "Star.h"

#include "AssertionMacro.h"
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
	collisionBound_ = Circle(center_, height_ / 2.0f);

	// 애니메이션 속성 설정
	flightAnimationTextures_ = {
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 1)),
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 2)),
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 3)),
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 2)),
		ResourceManager::Get().GetResource<Texture2D>(StringUtils::PrintF("%s%d", colorTypeMaps.at(colorType).c_str(), 1)),
	};
	flightAnimationTextureIndex_ = 0;
	flightAnimationFrameTime_ = 0.09f;

	explosionAnimationTextures_ = {
		ResourceManager::Get().GetResource<Texture2D>("explosion1"),
		ResourceManager::Get().GetResource<Texture2D>("explosion2"),
		ResourceManager::Get().GetResource<Texture2D>("explosion3"),
		ResourceManager::Get().GetResource<Texture2D>("explosion4"),
		ResourceManager::Get().GetResource<Texture2D>("explosion5"),
	};
	explosionAnimationTextureIndex_ = 0;
	explosionAnimationFrameTime_ = 0.2f;
	accumulateAnimationFrameTime_ = 0.0f;
	
	waitAccumulateTime_ = 0.0f;
	waitPosition_ = Vector2f(static_cast<float>(windowWidth) / 2.0f, static_cast<float>(windowHeight) / 2.0f);

	maxSpeed_ = 400.0f;
	currentSpeed_ = 0.0f;
	dampingSpeed_ = 20.0f;

	countOfCollisionStar_ = 0;

	tapWidth_ = 85.0f;
	tapHeight_ = 42.0f;
	tickTapSize_ = 59.0f;
	leftTapTexture_ = ResourceManager::Get().GetResource<Texture2D>("tapLeft");
	rightTapTexture_ = ResourceManager::Get().GetResource<Texture2D>("tapRight");
	tickTapTexture_ = ResourceManager::Get().GetResource<Texture2D>("tapTick");

	readyTexturePosition_ = Vector2f(static_cast<float>(windowWidth) / 2.0f, 200.0f);
	readyTexture_ = ResourceManager::Get().GetResource<Texture2D>("textGetReady");

	bIsInitialized_ = true;
}

void Plane::Update(float deltaSeconds)
{
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
	RenderManager& renderManager = RenderManager::Get();

	switch (state_)
	{
	case EState::Wait:
		renderManager.DrawTexture2D(flightAnimationTextures_[flightAnimationTextureIndex_], center_, width_, height_, rotate_, 1.0f);
		renderManager.DrawTexture2D( leftTapTexture_, Vector2f(center_.x - 100.0f,          center_.y), tapWidth_, tapHeight_, 0.0f);
		renderManager.DrawTexture2D(rightTapTexture_, Vector2f(center_.x + 100.0f,          center_.y), tapWidth_, tapHeight_, 0.0f);
		renderManager.DrawTexture2D( tickTapTexture_, Vector2f(center_.x +  20.0f, center_.y + 70.0f), tickTapSize_, tickTapSize_, 0.0f);
		renderManager.DrawTexture2D(readyTexture_, readyTexturePosition_, 400.0f, 73.0f, 0.0f);
		break;

	case EState::Flight:
		renderManager.DrawTexture2D(flightAnimationTextures_[flightAnimationTextureIndex_], center_, width_, height_, rotate_, 1.0f);
		break;

	case EState::Crash:
		if (explosionAnimationTextureIndex_ < explosionAnimationTextures_.size())
		{
			renderManager.DrawTexture2D(explosionAnimationTextures_[explosionAnimationTextureIndex_], center_, width_, height_, rotate_, 1.0f);
		}
		break;

	default:
		ASSERT(false, "undefined plane state : %d", static_cast<int32_t>(state_));
	}
}

void Plane::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");
	bIsInitialized_ = false;
}

void Plane::UpdateFlightAnimation(float deltaSeconds)
{
	accumulateAnimationFrameTime_ += deltaSeconds;

	if (accumulateAnimationFrameTime_ >= flightAnimationFrameTime_)
	{
		accumulateAnimationFrameTime_ = 0.0f;
		flightAnimationTextureIndex_ = (flightAnimationTextureIndex_ + 1) % (flightAnimationTextures_.size());
	}
}

void Plane::UpdateExplosionAnimation(float deltaSeconds)
{
	if (explosionAnimationTextureIndex_ >= explosionAnimationTextures_.size())
	{
		return;
	}

	accumulateAnimationFrameTime_ += deltaSeconds;

	if (accumulateAnimationFrameTime_ >= explosionAnimationFrameTime_)
	{
		accumulateAnimationFrameTime_ = 0.0f;
		explosionAnimationTextureIndex_++;
	}
}

void Plane::UpdateWaitState(float deltaSeconds)
{
	ASSERT(state_ == EState::Wait, "inavlid plane state : %d", static_cast<int32_t>(state_));

	UpdateFlightAnimation(deltaSeconds);

	waitAccumulateTime_ += deltaSeconds;

	center_.x = waitPosition_.x;
	center_.y = waitPosition_.y + 10.0f * MathUtils::ScalarSin(waitAccumulateTime_ * 2.0f);
	collisionBound_.SetCenter(center_);

	if (InputManager::Get().GetMouseButtonPressState(EMouseButton::BUTTON_LEFT) == EPressState::Pressed)
	{
		currentSpeed_ = maxSpeed_;
		state_ = EState::Flight;

		ObjectScheduler* scheduler = ObjectManager::Get().GetGameObject<ObjectScheduler>("Scheduler");
		scheduler->SetActive(true);

		ScoreBoard* board = ObjectManager::Get().GetGameObject<ScoreBoard>("Board");
		board->SetActive(true);
	}
}

void Plane::UpdateFlightState(float deltaSeconds)
{
	ASSERT(state_ == EState::Flight, "inavlid plane state : %d", static_cast<int32_t>(state_));

	UpdateFlightAnimation(deltaSeconds);
	
	currentSpeed_ -= dampingSpeed_;
	center_.y -= currentSpeed_ * deltaSeconds;

	if (currentSpeed_ <= 0.0f && InputManager::Get().GetMouseButtonPressState(EMouseButton::BUTTON_LEFT) == EPressState::Pressed)
	{
		currentSpeed_ = maxSpeed_;
	}
	
	collisionBound_.SetCenter(center_);

	ObjectScheduler* scheduler = ObjectManager::Get().GetGameObject<ObjectScheduler>("Scheduler");
	Star* star = scheduler->GetCollisionStar(this);
	if (star != nullptr)
	{
		countOfCollisionStar_++;
		star->SetState(Star::EState::Wait);

		ScoreBoard* board = ObjectManager::Get().GetGameObject<ScoreBoard>("Board");
		board->SetScore(countOfCollisionStar_);
	}

	Background* background = ObjectManager::Get().GetGameObject<Background>("Background");
	if (scheduler->IsCollisionRocks(this) || !background->IsInnerPlane(this))
	{
		scheduler->SetActive(false);
		state_ = EState::Crash;

		background->SetCanMove(false);

		Ground* ground = ObjectManager::Get().GetGameObject<Ground>("Ground");
		ground->SetCanMove(false);

		ScoreBoard* board = ObjectManager::Get().GetGameObject<ScoreBoard>("Board");
		board->SetActive(false);
	}
}

void Plane::UpdateCrashState(float deltaSeconds)
{
	ASSERT(state_ == EState::Crash, "inavlid plane state : %d", static_cast<int32_t>(state_));

	UpdateExplosionAnimation(deltaSeconds);
}