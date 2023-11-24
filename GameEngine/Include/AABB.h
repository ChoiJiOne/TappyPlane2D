#pragma once

#include "IShape.h"
#include "Vector2.h"


/**
 * @brief 축 정렬 경계 상자(AABB) 형태입니다.
 */
class AABB : public IShape
{
public:
	/**
	 * @brief AABB의 생성자입니다.
	 * 
	 * @param minPosition 축 정렬 경계 상자의 최소 좌표입니다.
	 * @param maxPosition 축 정렬 경계 상자의 최대 좌표입니다.
	 */
	AABB(const Vector2f& minPosition, const Vector2f& maxPosition);


	/**
	 * @brief AABB의 생성자입니다.
	 * 
	 * @param center 축 정렬 경계 상자의 중심 좌표입니다.
	 * @param width 축 정렬 경계 상자의 가로 크기입니다.
	 * @param height 축 정렬 경계 상자의 세로 크기입니다.
	 */
	AABB(const Vector2f& center, const float& width, const float& height);


	/**
	 * @brief AABB의 복사 생성자입니다.
	 * 
	 * @param instance 복사할 AABB 인스턴스입니다.
	 */
	AABB(AABB&& instance) noexcept
		: minPosition_(instance.minPosition_)
		, maxPosition_(instance.maxPosition_) {}


	/**
	 * @brief AABB의 복사 생성자입니다.
	 * 
	 * @param instance 복사할 AABB 인스턴스입니다.
	 */
	AABB(const AABB& instance) noexcept
		: minPosition_(instance.minPosition_)
		, maxPosition_(instance.maxPosition_) {}


	/**
	 * @brief AABB의 대입 연산자입니다.
	 * 
	 * @param instance 복사할 AABB 인스턴스입니다.
	 * 
	 * @return 대입한 AABB의 참조자를 반환합니다.
	 */
	AABB& operator=(AABB&& instance) noexcept
	{
		if (this == &instance) return *this;

		minPosition_ = instance.minPosition_;
		maxPosition_ = instance.maxPosition_;

		return *this;
	}
	

	/**
	 * @brief AABB의 대입 연산자입니다.
	 *
	 * @param instance 복사할 AABB 인스턴스입니다.
	 *
	 * @return 대입한 AABB의 참조자를 반환합니다.
	 */
	AABB& operator=(const AABB& instance) noexcept
	{
		if (this == &instance) return *this;

		minPosition_ = instance.minPosition_;
		maxPosition_ = instance.maxPosition_;

		return *this;
	}


	/**
	 * @brief AABB의 프로퍼티를 설정합니다.
	 * 
	 * @param minPosition 축 정렬 경계 상자의 최소 좌표입니다.
	 * @param maxPosition 축 정렬 경계 상자의 최대 좌표입니다.
	 */
	void SetProperty(const Vector2f& minPosition, const Vector2f& maxPosition);


	/**
	 * @brief AABB의 생성자입니다.
	 *
	 * @param center 축 정렬 경계 상자의 중심 좌표입니다.
	 * @param width 축 정렬 경계 상자의 가로 크기입니다.
	 * @param height 축 정렬 경계 상자의 세로 크기입니다.
	 */
	void SetProperty(const Vector2f& center, const float& width, const float& height);


	/**
	 * @brief AABB의 타입을 반환합니다.
	 * 
	 * @return AABB의 타입을 반환합니다.
	 */
	virtual EType GetType() const override { return IShape::EType::AABB; }


	/**
	 * @brief AABB와 다른 오브젝트와의 충돌 여부를 검사합니다.
	 * 
	 * @param shape 충돌 검사를 수행할 오브젝트입니다.
	 * 
	 * @return 다른 오브젝트와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	virtual bool IsCollision(const IShape* shape) const override;


private:
	/**
	 * @brief AABB 오브젝트와의 충돌 여부를 검사합니다.
	 * 
	 * @param shape 충돌 여부를 검사할 AABB 오브젝트입니다.
	 * 
	 * @return 다른 AABB 오브젝트와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsCollisionAABB(const IShape* shape) const;


private:
	/**
	 * @brief 상자 영역의 최소값입니다.
	 */
	Vector2f minPosition_;


	/**
	 * @brief 상자 영역의 최대값입니다.
	 */
	Vector2f maxPosition_;
};