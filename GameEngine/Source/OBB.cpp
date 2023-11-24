#include "OBB.h"

#include "AssertionMacro.h"
#include "MathUtils.h"

bool OBB::IsCollision(const IShape* shape) const
{
	EType type = shape->GetType();
	bool bIsCollision = false;

	switch (type)
	{
	case IShape::EType::None:
		bIsCollision = false;
		break;

	case IShape::EType::OBB:
		bIsCollision = IsCollisionOBB(shape);
		break;

	default:
		ASSERT(false, "undefined object shape type : %d", static_cast<int32_t>(type));
	}

	return bIsCollision;
}

bool OBB::IsCollisionOBB(const IShape* shape) const
{
	return false;
}
