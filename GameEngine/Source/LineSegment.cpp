#include "LineSegment.h"

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

	case IShape::EType::LineSegment:
		bIsCollision = IsCollisionLineSegment(shape);
		break;

	default:
		ASSERT(false, "undefined object shape type : %d", static_cast<int32_t>(type));
	}

	return bIsCollision;
}

bool LineSegment::IsCollisionLineSegment(const IShape* shape) const
{
	ASSERT(shape->GetType() == EType::LineSegment, "must be of the LineSegment shape type...");

	const LineSegment* lineSegment = reinterpret_cast<const LineSegment*>(shape);

	float x1 = points_[0].x;
	float y1 = points_[0].y;

	float x2 = points_[1].x;
	float y2 = points_[1].y;

	float x3 = lineSegment->points_[0].x;
	float y3 = lineSegment->points_[0].y;

	float x4 = lineSegment->points_[1].x;
	float y4 = lineSegment->points_[1].y;

	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) 
	{
		return true;
	}

	return false;
}

LineSegment::EOrientation LineSegment::GetOrientation(const Vector2f& p0, const Vector2f& p1, const Vector2f& p2) const
{
	Vector2f p12 = p2 - p1;
	Vector2f p01 = p1 - p0;
	float cross = MathUtils::CrossProduct<float>(p12, p01);

	if (MathUtils::NearZero(cross))
	{
		return EOrientation::Collinear;
	}
	else
	{
		return (cross > 0.0f) ? EOrientation::Clockwise : EOrientation::Counterclockwise;
	}
}

bool LineSegment::CheckSegment(const Vector2f& boundPoint0, const Vector2f& boundPoint1, const Vector2f& point) const
{
	Vector2f minPoint = Vector2f(
		MathUtils::Min<float>(boundPoint0.x, boundPoint1.x),
		MathUtils::Min<float>(boundPoint0.y, boundPoint1.y)
	);

	Vector2f maxPoint = Vector2f(
		MathUtils::Max<float>(boundPoint0.x, boundPoint1.x),
		MathUtils::Max<float>(boundPoint0.y, boundPoint1.y)
	);

	return (point.x >= minPoint.x && point.x <= maxPoint.x && point.y >= minPoint.y && point.y <= maxPoint.y);
}