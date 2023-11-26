#include "LineSegment.h"

#include "AABB.h"
#include "AssertionMacro.h"
#include "MathUtils.h"

bool LineSegment::IsCollision(const IShape* shape) const
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

	case IShape::EType::LineSegment:
		bIsCollision = IsCollisionLineSegment(shape);
		break;

	default:
		ASSERT(false, "undefined object shape type : %d", static_cast<int32_t>(type));
	}

	return bIsCollision;
}

bool LineSegment::IsCollisionAABB(const IShape* shape) const
{
	ASSERT(shape->GetType() == EType::AABB, "must be of the AABB shape type...");

	const AABB* aabb = reinterpret_cast<const AABB*>(shape);

	return aabb->IsCollision(this);
}

bool LineSegment::IsCollisionLineSegment(const IShape* shape) const
{
	ASSERT(shape->GetType() == EType::LineSegment, "must be of the LineSegment shape type...");

	const LineSegment* lineSegment = reinterpret_cast<const LineSegment*>(shape);

	Vector2f p1 = points_[0];
	Vector2f p2 = points_[1];
	Vector2f p3 = lineSegment->points_[0];
	Vector2f p4 = lineSegment->points_[1];

	Vector2f p12 = p2 - p1;
	Vector2f p34 = p4 - p3;
	Vector2f p31 = p1 - p3;

	float cross = MathUtils::CrossProduct<float>(p12, p34);
	if (MathUtils::NearZero(cross)) // 두 벡터가 평행하거나 같은 방향
	{
		return CheckSegment(p1, p2, p3) || CheckSegment(p1, p2, p4) || CheckSegment(p3, p4, p1) || CheckSegment(p3, p4, p2);
	}
	else
	{
		float uA = MathUtils::CrossProduct<float>(p34, p31) / cross;
		float uB = MathUtils::CrossProduct<float>(p12, p31) / cross;

		if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
		{
			return true;
		}
	}

	return false;
}

bool LineSegment::CheckSegment(const Vector2f& boundMinPoint, const Vector2f& boundMaxPoint, const Vector2f& point) const
{
	float minX = MathUtils::Min<float>(boundMinPoint.x, boundMaxPoint.x);
	float minY = MathUtils::Min<float>(boundMinPoint.y, boundMaxPoint.y);
	float maxX = MathUtils::Max<float>(boundMinPoint.x, boundMaxPoint.x);
	float maxY = MathUtils::Max<float>(boundMinPoint.y, boundMaxPoint.y);
	
	return (minX <= point.x && point.x <= maxX) && (minY <= point.y && point.y <= maxY);
}