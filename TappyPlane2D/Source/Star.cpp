#include "Star.h"
#include "Plane.h"

#include "AssertionMacro.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "MathUtils.h"

Star::~Star()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Star::Initialize(const Vector2f& center)
{
	ASSERT(!bIsInitialized_, "already initialize star game object...");

	SetupProperties(center);

	bIsInitialized_ = true;
}

void Star::Update(float deltaSeconds)
{
	if (state_ == EState::Wait || state_ == EState::Stop)
	{
		return;
	}

	center_.x -= speed_ * deltaSeconds;
	collisionBound_.SetProperty(center_, width_, height_);
}

void Star::Render()
{
	if (state_ == EState::Wait)
	{
		return;
	}

	RenderManager::Get().DrawTexture2D(texture_, center_, width_, height_, 0.0f);
}

void Star::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");
	bIsInitialized_ = false;
}

bool Star::IsCollisionPlane(const Plane* plane) const
{
	if (state_ == EState::Wait)
	{
		return false;
	}

	const Circle& circle = plane->GetCollisionBound();

	return collisionBound_.IsCollision(&circle);
}

void Star::SetupProperties(const Vector2f& center)
{
	state_ = EState::Wait;

	center_ = center;
	width_ = 39.0f;
	height_ = 38.0f;
	speed_ = 200.0f;

	texture_ = ResourceManager::Get().GetResource<Texture2D>("starGold");

	collisionBound_.SetProperty(center_, width_, height_);
}