#pragma once

#include "IShape.h"
#include "Vector2.h"


/**
 * @brief �� ���� ��� ����(AABB) �����Դϴ�.
 */
class AABB : public IShape
{
public:
	/**
	 * @brief AABB�� �������Դϴ�.
	 * 
	 * @param minPosition �� ���� ��� ������ �ּ� ��ǥ�Դϴ�.
	 * @param maxPosition �� ���� ��� ������ �ִ� ��ǥ�Դϴ�.
	 */
	AABB(const Vector2f& minPosition, const Vector2f& maxPosition);


	/**
	 * @brief AABB�� �������Դϴ�.
	 * 
	 * @param center �� ���� ��� ������ �߽� ��ǥ�Դϴ�.
	 * @param width �� ���� ��� ������ ���� ũ���Դϴ�.
	 * @param height �� ���� ��� ������ ���� ũ���Դϴ�.
	 */
	AABB(const Vector2f& center, const float& width, const float& height);


	/**
	 * @brief AABB�� ���� �������Դϴ�.
	 * 
	 * @param instance ������ AABB �ν��Ͻ��Դϴ�.
	 */
	AABB(AABB&& instance) noexcept
		: minPosition_(instance.minPosition_)
		, maxPosition_(instance.maxPosition_) {}


	/**
	 * @brief AABB�� ���� �������Դϴ�.
	 * 
	 * @param instance ������ AABB �ν��Ͻ��Դϴ�.
	 */
	AABB(const AABB& instance) noexcept
		: minPosition_(instance.minPosition_)
		, maxPosition_(instance.maxPosition_) {}


	/**
	 * @brief AABB�� ���� �������Դϴ�.
	 * 
	 * @param instance ������ AABB �ν��Ͻ��Դϴ�.
	 * 
	 * @return ������ AABB�� �����ڸ� ��ȯ�մϴ�.
	 */
	AABB& operator=(AABB&& instance) noexcept
	{
		if (this == &instance) return *this;

		minPosition_ = instance.minPosition_;
		maxPosition_ = instance.maxPosition_;

		return *this;
	}
	

	/**
	 * @brief AABB�� ���� �������Դϴ�.
	 *
	 * @param instance ������ AABB �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ AABB�� �����ڸ� ��ȯ�մϴ�.
	 */
	AABB& operator=(const AABB& instance) noexcept
	{
		if (this == &instance) return *this;

		minPosition_ = instance.minPosition_;
		maxPosition_ = instance.maxPosition_;

		return *this;
	}


	/**
	 * @brief AABB�� ������Ƽ�� �����մϴ�.
	 * 
	 * @param minPosition �� ���� ��� ������ �ּ� ��ǥ�Դϴ�.
	 * @param maxPosition �� ���� ��� ������ �ִ� ��ǥ�Դϴ�.
	 */
	void SetProperty(const Vector2f& minPosition, const Vector2f& maxPosition);


	/**
	 * @brief AABB�� �������Դϴ�.
	 *
	 * @param center �� ���� ��� ������ �߽� ��ǥ�Դϴ�.
	 * @param width �� ���� ��� ������ ���� ũ���Դϴ�.
	 * @param height �� ���� ��� ������ ���� ũ���Դϴ�.
	 */
	void SetProperty(const Vector2f& center, const float& width, const float& height);


	/**
	 * @brief AABB�� Ÿ���� ��ȯ�մϴ�.
	 * 
	 * @return AABB�� Ÿ���� ��ȯ�մϴ�.
	 */
	virtual EType GetType() const override { return IShape::EType::AABB; }


	/**
	 * @brief AABB�� �ٸ� ������Ʈ���� �浹 ���θ� �˻��մϴ�.
	 * 
	 * @param shape �浹 �˻縦 ������ ������Ʈ�Դϴ�.
	 * 
	 * @return �ٸ� ������Ʈ�� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	virtual bool IsCollision(const IShape* shape) const override;


private:
	/**
	 * @brief AABB ������Ʈ���� �浹 ���θ� �˻��մϴ�.
	 * 
	 * @param shape �浹 ���θ� �˻��� AABB ������Ʈ�Դϴ�.
	 * 
	 * @return �ٸ� AABB ������Ʈ�� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsCollisionAABB(const IShape* shape) const;


private:
	/**
	 * @brief ���� ������ �ּҰ��Դϴ�.
	 */
	Vector2f minPosition_;


	/**
	 * @brief ���� ������ �ִ밪�Դϴ�.
	 */
	Vector2f maxPosition_;
};