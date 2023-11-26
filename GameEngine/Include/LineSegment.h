#pragma once

#include <array>

#include "IShape.h"
#include "Vector2.h"


/**
 * @brief ���� �����Դϴ�.
 */
class LineSegment : public IShape
{
public:
	/**
	 * @brief ������ �������Դϴ�.
	 * 
	 * @param point0 ������ �� �����Դϴ�.
	 * @param point1 ������ �ٸ� �� �����Դϴ�.
	 */
	LineSegment(const Vector2f& point0, const Vector2f& point1)
		: points_(std::array<Vector2f, 2>{ point0, point1 }) {}

	
	/**
	 * @brief ������ �������Դϴ�.
	 * 
	 * @param points ������ �� �����Դϴ�.
	 */
	LineSegment(const std::array<Vector2f, 2>& points)
		: points_(points) {}


	/**
	 * @brief ������ ���� �������Դϴ�.
	 * 
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	LineSegment(LineSegment&& instance) noexcept
		: points_(instance.points_) {}


	/**
	 * @brief ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	LineSegment(const LineSegment& instance) noexcept
		: points_(instance.points_) {}


	/**
	 * @brief ������ ���� �������Դϴ�.
	 * 
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 * 
	 * @return ������ ���� �ν��Ͻ��� �����ڸ� ��ȯ�մϴ�.
	 */
	LineSegment& operator=(LineSegment&& instance) noexcept
	{
		if (this == &instance) return *this;
		
		points_ = instance.points_;

		return *this;
	}


	/**
	 * @brief ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ���� �ν��Ͻ��� �����ڸ� ��ȯ�մϴ�.
	 */
	LineSegment& operator=(const LineSegment& instance) noexcept
	{
		if (this == &instance) return *this;

		points_ = instance.points_;

		return *this;
	}


	/**
	 * @brief ������ Ÿ���� ��ȯ�մϴ�.
	 *
	 * @return ������ Ÿ���� ��ȯ�մϴ�.
	 */
	virtual EType GetType() const override { return IShape::EType::LineSegment; }


	/**
	 * @brief ���а� �ٸ� ������Ʈ���� �浹 ���θ� �˻��մϴ�.
	 *
	 * @param shape �浹 �˻縦 ������ ������Ʈ�Դϴ�.
	 *
	 * @return �ٸ� ������Ʈ�� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	virtual bool IsCollision(const IShape* shape) const override;


	/**
	 * @brief ������ �� ������ �����մϴ�.
	 * 
	 * @param points ������ ������ �� �����Դϴ�.
	 */
	void SetPoints(const std::array<Vector2f, 2>& points) { points_ = points; }


	/**
	 * @brief ������ �� ������ ����ϴ�.
	 *
	 * @return ������ �� ������ ��ȯ�մϴ�.
	 */
	std::array<Vector2f, 2>& GetPoints() { return points_; }


	/**
	 * @brief ������ �� ������ ����ϴ�.
	 * 
	 * @return ������ �� ������ ��ȯ�մϴ�.
	 */
	const std::array<Vector2f, 2>& GetPoints() const { return points_; }


private:
	/**
	 * @brief AABB ������Ʈ���� �浹 ���θ� �˻��մϴ�.
	 *
	 * @param shape �浹 ���θ� �˻��� AABB ������Ʈ�Դϴ�.
	 *
	 * @return �ٸ� AABB ������Ʈ�� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsCollisionAABB(const IShape* shape) const;


	/**
	 * @brief Circle ������Ʈ���� �浹 ���θ� �˻��մϴ�.
	 *
	 * @param shape �浹 ���θ� �˻��� AABB ������Ʈ�Դϴ�.
	 *
	 * @return �ٸ� Circle ������Ʈ�� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsCollisionCircle(const IShape* shape) const;


	/**
	 * @brief ���� ������Ʈ���� �浹 ���θ� �˻��մϴ�.
	 * 
	 * @param shape �浹 ���θ� �˻��� ���� ������Ʈ�Դϴ�.
	 *
	 * @return �ٸ� ���� ������Ʈ�� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsCollisionLineSegment(const IShape* shape) const;


	/**
	 * @brief Ư�� ���� �� ���� ������ ���ԵǴ��� Ȯ���մϴ�.
	 * 
	 * @param boundMinPoint ������ �ּ� ��ǥ�Դϴ�.
	 * @param boundMaxPoint ������ �ִ� ��ǥ�Դϴ�.
	 * @param point Ȯ���� ���Դϴ�.
	 */
	bool CheckSegment(const Vector2f& boundMinPoint, const Vector2f& boundMaxPoint, const Vector2f& point) const;

	
private:
	/**
	 * @brief ������ �� �����Դϴ�.
	 */
	std::array<Vector2f, 2> points_;
};