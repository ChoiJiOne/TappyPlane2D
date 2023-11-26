#include "Circle.h"

#include "AABB.h"
#include "AssertionMacro.h"
#include "LineSegment.h"
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

	case IShape::EType::LineSegment:
		bIsCollision = IsCollisionLineSegment(shape);
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

bool Circle::IsCollisionLineSegment(const IShape* shape) const
{
	ASSERT(shape->GetType() == EType::LineSegment, "must be of the LineSegment shape type...");

	const LineSegment* lineSegment = reinterpret_cast<const LineSegment*>(shape);
	const std::array<Vector2f, 2> points = lineSegment->GetPoints();
	
	if (CheckCircleSegment(points[0]) || CheckCircleSegment(points[1]))
	{
		return true;
	}

	Vector2f ab = points[1] - points[0];
	Vector2f ac = center_ - points[0];

	float dot = MathUtils::DotProduct(ab, ac) / MathUtils::LengthSquare(ab);
	Vector2f closet(points[0].x + dot * (points[1].x - points[0].x), points[0].y + dot * (points[1].y - points[0].y));

	if (!CheckSegment(points[0], points[1], closet))
	{
		return false;
	}

	Vector2f diff = closet - center_;
	float distanceSquare = MathUtils::LengthSquare(diff);
	float radiusSquare = radius_ * radius_;

	if (distanceSquare <= radiusSquare)
	{
		return true;
	}

	return false;
}

bool Circle::CheckCircleSegment(const Vector2f& point) const
{
	Vector2f diff = point - center_;
	float distanceSquare = MathUtils::LengthSquare(diff);
	float radiusSquare = radius_ * radius_;
	
	return distanceSquare <= radiusSquare;
}

bool Circle::CheckSegment(const Vector2f& boundMinPoint, const Vector2f& boundMaxPoint, const Vector2f& point) const
{
	float minX = MathUtils::Min<float>(boundMinPoint.x, boundMaxPoint.x);
	float minY = MathUtils::Min<float>(boundMinPoint.y, boundMaxPoint.y);
	float maxX = MathUtils::Max<float>(boundMinPoint.x, boundMaxPoint.x);
	float maxY = MathUtils::Max<float>(boundMinPoint.y, boundMaxPoint.y);

	return (minX <= point.x && point.x <= maxX) && (minY <= point.y && point.y <= maxY);
}