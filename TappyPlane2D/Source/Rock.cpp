#include "Rock.h"
#include "Plane.h"

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

void Rock::Initialize(const EType& type, const float& startXPosition)
{
	ASSERT(!bIsInitialized_, "already initialize rock game object...");

	int32_t windowWidth = 0;
	int32_t windowHeight = 0;
	RenderManager::Get().GetRenderWindowSize(windowWidth, windowHeight);
	
	topTexture_ = ResourceManager::Get().GetResource<Texture2D>(topRockMaps.at(type));
	bottomTexture_ = ResourceManager::Get().GetResource<Texture2D>(bottomRockMaps.at(type));
	startXPosition_ = startXPosition;
	speed_ = 200.0f;

	float minHeight = 200.0f;
	float diffHeight = 200.0f;

	topWidth_ = 108.0f;
	topHeight_ = MathUtils::GenerateRandomFloat(minHeight, static_cast<float>(windowHeight) - diffHeight - minHeight);
	topCenter_ = Vector2f(startXPosition_, topHeight_ / 2.0f);

	bottomWidth_ = 108.0f;
	bottomHeight_ = static_cast<float>(windowHeight) - diffHeight - topHeight_;
	bottomCenter_ = Vector2f(startXPosition_, static_cast<float>(windowHeight) - bottomHeight_ / 2.0f);

	outlines_ = {
		LineSegment(Vector2f(startXPosition_ - topWidth_ * 0.5f, 0.0f), Vector2f(startXPosition_ + topWidth_ * 0.1f, topHeight_)),
		LineSegment(Vector2f(startXPosition_ + topWidth_ * 0.5f, 0.0f), Vector2f(startXPosition_ + topWidth_ * 0.1f, topHeight_)),
		LineSegment(Vector2f(startXPosition_ - topWidth_ * 0.5f, static_cast<float>(windowHeight)), Vector2f(startXPosition_ + topWidth_ * 0.1f, static_cast<float>(windowHeight) - bottomHeight_)),
		LineSegment(Vector2f(startXPosition_ + topWidth_ * 0.5f, static_cast<float>(windowHeight)), Vector2f(startXPosition_ + topWidth_ * 0.1f, static_cast<float>(windowHeight) - bottomHeight_)),
	};

	bIsInitialized_ = true;
}

void Rock::Update(float deltaSeconds)
{
	std::array<Vector2f, 2> points;
	for (auto& outline : outlines_)
	{
		points = outline.GetPoints();
		points[0].x -= speed_ * deltaSeconds;
		points[1].x -= speed_ * deltaSeconds;
		outline.SetPoints(points);
	}

	topCenter_.x -= speed_ * deltaSeconds;
	bottomCenter_.x -= speed_ * deltaSeconds;
}

void Rock::Render()
{
	RenderManager::Get().DrawTexture2D(topTexture_, topCenter_, topWidth_, topHeight_, 0.0f);
	RenderManager::Get().DrawTexture2D(bottomTexture_, bottomCenter_, bottomWidth_, bottomHeight_, 0.0f);

	std::array<Vector2f, 2> points;
	for (auto& outline : outlines_)
	{
		points = outline.GetPoints();
		RenderManager::Get().DrawLine2D(points[0], points[1], Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
	}
}

void Rock::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");
	bIsInitialized_ = false;
}

bool Rock::IsCollision(const Plane* plane)
{
	const AABB& aabb = plane->GetCollisionBound();

	for (const auto& outline : outlines_)
	{
		if (aabb.IsCollision(&outline))
		{
			return true;
		}
	}

	return false;
}