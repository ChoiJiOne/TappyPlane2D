#pragma once

#include "IShape.h"
#include "Vector2.h"


/**
 * @brief ��(Circle) �����Դϴ�.
 */
class Circle : public IShape
{
public:
	/**
	 * @brief Circle�� ����Ʈ �������Դϴ�.
	 */
	Circle() = default;


	/**
	 * @brief ���� �������Դϴ�.
	 * 
	 * @param center ���� �߽� ��ǥ�Դϴ�.
	 * @param radius ���� ������ �����Դϴ�.
	 */
	Circle(const Vector2f& center, const float& radius)
		: center_(center)
		, radius_(radius) {}


	/**
	 * @brief ���� ���� �������Դϴ�.
	 * 
	 * @param instance ������ �� �ν��Ͻ��Դϴ�.
	 */
	Circle(Circle&& instance) noexcept
		: center_(instance.center_)
		, radius_(instance.radius_) {}


	/**
	 * @brief ���� ���� �������Դϴ�.
	 *
	 * @param instance ������ �� �ν��Ͻ��Դϴ�.
	 */
	Circle(const Circle& instance) noexcept
		: center_(instance.center_)
		, radius_(instance.radius_) {}


	/**
	 * @brief ���� ���� �������Դϴ�.
	 *
	 * @param instance ������ �� �ν��Ͻ��Դϴ�.
	 * 
	 * @return ������ �� �ν��Ͻ��� �����ڸ� ��ȯ�մϴ�.
	 */
	Circle& operator=(Circle&& instance) noexcept
	{
		if (this == &instance) return *this;

		center_ = instance.center_;
		radius_ = instance.radius_;

		return *this;
	}


	/**
	 * @brief ���� ���� �������Դϴ�.
	 *
	 * @param instance ������ �� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ �� �ν��Ͻ��� �����ڸ� ��ȯ�մϴ�.
	 */
	Circle& operator=(const Circle& instance) noexcept
	{
		if (this == &instance) return *this;

		center_ = instance.center_;
		radius_ = instance.radius_;

		return *this;
	}


	/**
	 * @brief ���� �߽� ��ǥ�� �����մϴ�.
	 * 
	 * @param center ������ ���� �߽���ǥ�Դϴ�.
	 */
	void SetCenter(const Vector2f& center) { center_ = center; }


	/**
	 * @brief ���� ������ ���̸� �����մϴ�.
	 * 
	 * @param radius ������ ���� ������ �����Դϴ�.
	 */
	void SetRadius(const float& radius) { radius_ = radius; }


	/**
	 * @brief ���� ������Ƽ�� �����մϴ�.
	 * 
	 * @param center ������ ���� �߽���ǥ�Դϴ�.
	 * @param radius ������ ���� ������ �����Դϴ�.
	 */
	void SetProperty(const Vector2f& center, const float& radius)
	{
		center_ = center;
		radius_ = radius;
	}


	/**
	 * @brief �� Ÿ���� ����ϴ�.
	 *
	 * @return �� Ÿ���� ��ȯ�մϴ�.
	 */
	virtual EType GetType() const override { return IShape::EType::Circle; }


	/**
	 * @brief ���� �ٸ� ���� ������Ʈ���� �浹 ���θ� �˻��մϴ�.
	 *
	 * @param shape �浹 �˻縦 ������ ������Ʈ�Դϴ�.
	 * 
	 * @return �ٸ� ������Ʈ�� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	virtual bool IsCollision(const IShape* shape) const override;


	/**
	 * @brief ���� �߽� ��ǥ�� ����ϴ�.
	 * 
	 * @return ���� �߽� ��ǥ�� ��ȯ�մϴ�.
	 */
	Vector2f GetCenter() const { return center_; }

	
	/**
	 * @brief ���� ������ ���̸� ����ϴ�.
	 * 
	 * @return ���� ������ ���̸� ��ȯ�մϴ�.
	 */
	float GetRadius() const { return radius_; }


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
	 * @brief LineSegment ������Ʈ���� �浹 ���θ� �˻��մϴ�.
	 *
	 * @param shape �浹 ���θ� �˻��� LineSegment ������Ʈ�Դϴ�.
	 *
	 * @return �ٸ� LineSegment ������Ʈ�� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 * 
	 * @see https://mathworld.wolfram.com/Circle-LineIntersection.html
	 */
	bool IsCollisionLineSegment(const IShape* shape) const;


	/**
	 * @brief ���� ���� ���ԵǴ��� Ȯ���մϴ�.
	 * 
	 * @param point ���� ���ԵǴ��� Ȯ���� ���Դϴ�. 
	 */
	bool CheckCircleSegment(const Vector2f& point) const;


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
	 * @brief ���� �߽��Դϴ�.
	 */
	Vector2f center_;


	/**
	 * @brief ���� ������ �����Դϴ�.
	 */
	float radius_ = 0.0f;
};