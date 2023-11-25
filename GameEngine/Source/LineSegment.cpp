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

	Vector2f p0 = points_[0];
	Vector2f q0 = points_[1];
	Vector2f p1 = lineSegment->points_[0];
	Vector2f q1 = lineSegment->points_[1];

	EOrientation orient0 = GetOrientation(p0, q0, p1);
	EOrientation orient1 = GetOrientation(p0, q0, q1);
	EOrientation orient2 = GetOrientation(p1, q1, p0);
	EOrientation orient3 = GetOrientation(p1, q1, q0);
	
	if (orient0 != orient1 && orient2 != orient3)
	{
		return true;
	}

	if (orient0 == EOrientation::Collinear && CheckSegment(p0, p1, q0))
	{
		return true;
	}

	if (orient1 == EOrientation::Collinear && CheckSegment(p0, q1, q0))
	{
		return true;
	}

	if (orient2 == EOrientation::Collinear && CheckSegment(p1, p0, q1))
	{
		return true;
	}

	if (orient3 == EOrientation::Collinear && CheckSegment(p1, q0, q1))
	{
		return true;
	}

	return false;
}

LineSegment::EOrientation LineSegment::GetOrientation(const Vector2f& p0, const Vector2f& p1, const Vector2f& p2) const
{
	float cross = (p1.y - p0.y) * (p2.x - p1.x) - (p1.x - p0.x) * (p2.y - p1.y);

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
