#include "Background.h"
#include "Plane.h"
#include "Rock.h"
#include "Star.h"

#include "AssertionMacro.h"
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

	texture_ = ResourceManager::Get().GetResource<Texture2D>("background");

	int32_t windowWidth = 0;
	int32_t windowHeight = 0;
	RenderManager::Get().GetRenderWindowSize(windowWidth, windowHeight);

	width_ = static_cast<float>(windowWidth);
	height_ = static_cast<float>(windowHeight);

	scrollSpeed_ = 50.0f;
	scrollPosition_ = 0.0f;
	maxScrollPosition_ = width_;

	outlines_ = {
		LineSegment(Vector2f(  0.0f,    0.0f), Vector2f(  0.0f, height_)),
		LineSegment(Vector2f(  0.0f, height_), Vector2f(width_, height_)),
		LineSegment(Vector2f(width_, height_), Vector2f(width_,    0.0f)),
		LineSegment(Vector2f(width_,    0.0f), Vector2f(  0.0f,    0.0f)),
	};
	
	bIsInitialized_ = true;
}

void Background::Update(float deltaSeconds)
{
	scrollPosition_ += scrollSpeed_ * deltaSeconds;

	if (scrollPosition_ >= maxScrollPosition_)
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
	bIsInitialized_ = false;
}

bool Background::IsInnerPlane(const Plane* plane) const
{
	const AABB& aabb = plane->GetCollisionBound();

	for (const auto& outline : outlines_)
	{
		if (aabb.IsCollision(&outline))
		{
			return false;
		}
	}

	return true;
}

bool Background::IsOuterRock(const Rock* rock) const
{
	const std::array<LineSegment, 4>& outlines = rock->GetOutlines();

	for (const auto& outline : outlines)
	{
		const std::array<Vector2f, 2>& points = outline.GetPoints();
		for (const auto& point : points)
		{
			if (point.x >= 0 && point.x <= width_)
			{
				return false;
			}
		}
	}

	return true;
}

bool Background::IsOuterStar(const Star* star) const
{
	const AABB& aabb = star->GetCollisionBound();

	for (const auto& outline : outlines_)
	{
		if (aabb.IsCollision(&outline))
		{
			return false;
		}
	}

	return true;
}