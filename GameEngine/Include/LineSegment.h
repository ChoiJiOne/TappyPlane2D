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
	 * @brief �� ���� ������ ��Ÿ���� �������Դϴ�.
	 */
	enum class EOrientation : int32_t
	{
		Collinear = 0x00, // �� ���� �� ���� ���� ����
		Clockwise = 0x01, // �� ���� �ð� ����
		Counterclockwise = 0x02 // �� ���� �� �ð� ����
	};


private:
	/**
	 * @brief ���� ������Ʈ���� �浹 ���θ� �˻��մϴ�.
	 * 
	 * @param shape �浹 ���θ� �˻��� ���� ������Ʈ�Դϴ�.
	 *
	 * @return �ٸ� ���� ������Ʈ�� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsCollisionLineSegment(const IShape* shape) const;


	/**
	 * @brief �� ���� ������ ����ϴ�.
	 *
	 * @param p0 �� �� �� ù ��° ���Դϴ�.
	 * @param p1 �� �� �� �� ��° ���Դϴ�.
	 * @param p2 �� �� �� �� ��° ���Դϴ�.
	 */
	EOrientation GetOrientation(const Vector2f& p0, const Vector2f& p1, const Vector2f& p2) const;


	/**
	 * @brief �� ���� �� ���� ��� ������ ���ԵǴ��� Ȯ���մϴ�.
	 *
	 * @param boundPoint0 ��� ������ �� �� ���Դϴ�.
	 * @param boundPoint1 ��� ������ �� �ٸ� �� ���Դϴ�.
	 * @param point ��� ������ ���ԵǴ��� Ȯ���� ���Դϴ�.
	 */
	bool CheckSegment(const Vector2f& boundPoint0, const Vector2f& boundPoint1, const Vector2f& point) const;


private:
	/**
	 * @brief ������ �� �����Դϴ�.
	 */
	std::array<Vector2f, 2> points_;
};