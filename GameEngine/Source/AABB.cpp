#include "AABB.h"

#include "AssertionMacro.h"
#include "MathUtils.h"

AABB::AABB(const Vector2f& minPosition, const Vector2f& maxPosition)
{
	minPosition_ = Vector2f(
		MathUtils::Min<float>(minPosition.x, maxPosition_.x),
		MathUtils::Min<float>(minPosition.y, maxPosition_.y)
	);

	maxPosition_ = Vector2f(
		MathUtils::Max<float>(minPosition.x, maxPosition_.x),
		MathUtils::Max<float>(minPosition.y, maxPosition_.y)
	);
}

AABB::AABB(const Vector2f& center, const float& width, const float& height)
{
	minPosition_ = center - Vector2f(width / 2.0f, height / 2.0f);
	maxPosition_ = center + Vector2f(width / 2.0f, height / 2.0f);
}

void AABB::SetProperty(const Vector2f& minPosition, const Vector2f& maxPosition)
{
	minPosition_ = Vector2f(
		MathUtils::Min<float>(minPosition.x, maxPosition_.x),
		MathUtils::Min<float>(minPosition.y, maxPosition_.y)
	);

	maxPosition_ = Vector2f(
		MathUtils::Max<float>(minPosition.x, maxPosition_.x),
		MathUtils::Max<float>(minPosition.y, maxPosition_.y)
	);
}

void AABB::SetProperty(const Vector2f& center, const float& width, const float& height)
{
	minPosition_ = center - Vector2f(width / 2.0f, height / 2.0f);
	maxPosition_ = center + Vector2f(width / 2.0f, height / 2.0f);
}

bool AABB::IsCollision(const IShape* shape) const
{
	EType type = shape->GetType();
	bool bIsCollision = false;

	switch (type)
	{
	case IShape::EType::None:
		bIsCollision = false;
		break;

	case IShape::EType::AABB:
		bIsCollision = IsCollisionAABB(shape);
		break;

	default:
		ASSERT(false, "undefined object shape type : %d", static_cast<int32_t>(type));
	}
	
	return bIsCollision;
}

bool AABB::IsCollisionAABB(const IShape* shape) const
{
	ASSERT(shape->GetType() == EType::AABB, "must be of the AABB shape type...");

	const AABB* aabb = reinterpret_cast<const AABB*>(shape);
	
	if (minPosition_.x > aabb->maxPosition_.x || maxPosition_.x < aabb->minPosition_.x)
	{
		return false;
	}

	if (minPosition_.y > aabb->maxPosition_.y || maxPosition_.y < aabb->minPosition_.y)
	{
		return false;
	}
	
	return true;
}