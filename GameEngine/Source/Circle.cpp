#include "Circle.h"

#include "AABB.h"
#include "AssertionMacro.h"
#include "MathUtils.h"

bool Circle::IsCollision(const IShape* shape) const
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

	case IShape::EType::Circle:
		bIsCollision = IsCollisionCircle(shape);
		break;

	default:
		ASSERT(false, "undefined object shape type : %d", static_cast<int32_t>(type));
	}

	return bIsCollision;
}

bool Circle::IsCollisionAABB(const IShape* shape) const
{
	ASSERT(shape->GetType() == EType::AABB, "must be of the AABB shape type...");

	const AABB* aabb = reinterpret_cast<const AABB*>(shape);

	return aabb->IsCollision(this);
}

bool Circle::IsCollisionCircle(const IShape* shape) const
{
	ASSERT(shape->GetType() == EType::Circle, "must be of the Circle shape type...");

	const Circle* circle = reinterpret_cast<const Circle*>(shape);

	Vector2f diff = center_ - circle->GetCenter();
	
	float sumRadiusSquare = (radius_ + circle->GetRadius()) * (radius_ + circle->GetRadius());
	float distanceSquare = MathUtils::LengthSquare(diff);

	return distanceSquare <= sumRadiusSquare;
}