#pragma once

#include "IShape.h"
#include "Vector2.h"


/**
 * @brief 원(Circle) 형태입니다.
 */
class Circle : public IShape
{
public:
	/**
	 * @brief Circle의 디폴트 생성자입니다.
	 */
	Circle() = default;


	/**
	 * @brief 원의 생성자입니다.
	 * 
	 * @param center 원의 중심 좌표입니다.
	 * @param radius 원의 반지름 길이입니다.
	 */
	Circle(const Vector2f& center, const float& radius)
		: center_(center)
		, radius_(radius) {}


	/**
	 * @brief 원의 복사 생성자입니다.
	 * 
	 * @param instance 복사할 원 인스턴스입니다.
	 */
	Circle(Circle&& instance) noexcept
		: center_(instance.center_)
		, radius_(instance.radius_) {}


	/**
	 * @brief 원의 복사 생성자입니다.
	 *
	 * @param instance 복사할 원 인스턴스입니다.
	 */
	Circle(const Circle& instance) noexcept
		: center_(instance.center_)
		, radius_(instance.radius_) {}


	/**
	 * @brief 원의 대입 연산자입니다.
	 *
	 * @param instance 복사할 원 인스턴스입니다.
	 * 
	 * @return 대입한 원 인스턴스의 참조자를 반환합니다.
	 */
	Circle& operator=(Circle&& instance) noexcept
	{
		if (this == &instance) return *this;

		center_ = instance.center_;
		radius_ = instance.radius_;

		return *this;
	}


	/**
	 * @brief 원의 대입 연산자입니다.
	 *
	 * @param instance 복사할 원 인스턴스입니다.
	 *
	 * @return 대입한 원 인스턴스의 참조자를 반환합니다.
	 */
	Circle& operator=(const Circle& instance) noexcept
	{
		if (this == &instance) return *this;

		center_ = instance.center_;
		radius_ = instance.radius_;

		return *this;
	}


	/**
	 * @brief 원의 중심 좌표를 설정합니다.
	 * 
	 * @param center 설정할 원의 중심좌표입니다.
	 */
	void SetCenter(const Vector2f& center) { center_ = center; }


	/**
	 * @brief 원의 반지름 길이를 설정합니다.
	 * 
	 * @param radius 설정할 원의 반지름 길이입니다.
	 */
	void SetRadius(const float& radius) { radius_ = radius; }


	/**
	 * @brief 원의 프로퍼티를 설정합니다.
	 * 
	 * @param center 설정할 원의 중심좌표입니다.
	 * @param radius 설정할 원의 반지름 길이입니다.
	 */
	void SetProperty(const Vector2f& center, const float& radius)
	{
		center_ = center;
		radius_ = radius;
	}


	/**
	 * @brief 원 타입을 얻습니다.
	 *
	 * @return 원 타입을 반환합니다.
	 */
	virtual EType GetType() const override { return IShape::EType::Circle; }


	/**
	 * @brief 원과 다른 게임 오브젝트와의 충돌 여부를 검사합니다.
	 *
	 * @param shape 충돌 검사를 수행할 오브젝트입니다.
	 * 
	 * @return 다른 오브젝트와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	virtual bool IsCollision(const IShape* shape) const override;


	/**
	 * @brief 원의 중심 좌표를 얻습니다.
	 * 
	 * @return 원의 중심 좌표를 반환합니다.
	 */
	Vector2f GetCenter() const { return center_; }

	
	/**
	 * @brief 원의 반지름 길이를 얻습니다.
	 * 
	 * @return 원의 반지름 길이를 반환합니다.
	 */
	float GetRadius() const { return radius_; }


private:
	/**
	 * @brief AABB 오브젝트와의 충돌 여부를 검사합니다.
	 *
	 * @param shape 충돌 여부를 검사할 AABB 오브젝트입니다.
	 *
	 * @return 다른 AABB 오브젝트와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsCollisionAABB(const IShape* shape) const;


	/**
	 * @brief Circle 오브젝트와의 충돌 여부를 검사합니다.
	 * 
	 * @param shape 충돌 여부를 검사할 AABB 오브젝트입니다.
	 *
	 * @return 다른 Circle 오브젝트와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsCollisionCircle(const IShape* shape) const;


	/**
	 * @brief LineSegment 오브젝트와의 충돌 여부를 검사합니다.
	 *
	 * @param shape 충돌 여부를 검사할 LineSegment 오브젝트입니다.
	 *
	 * @return 다른 LineSegment 오브젝트와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 * 
	 * @see https://mathworld.wolfram.com/Circle-LineIntersection.html
	 */
	bool IsCollisionLineSegment(const IShape* shape) const;


	/**
	 * @brief 점이 원에 포함되는지 확인합니다.
	 * 
	 * @param point 원에 포함되는지 확인할 점입니다. 
	 */
	bool CheckCircleSegment(const Vector2f& point) const;


	/**
	 * @brief 특정 점이 두 점의 영역에 포함되는지 확인합니다.
	 *
	 * @param boundMinPoint 영역의 최소 좌표입니다.
	 * @param boundMaxPoint 영역의 최대 좌표입니다.
	 * @param point 확인할 점입니다.
	 */
	bool CheckSegment(const Vector2f& boundMinPoint, const Vector2f& boundMaxPoint, const Vector2f& point) const;


private:
	/**
	 * @brief 원의 중심입니다.
	 */
	Vector2f center_;


	/**
	 * @brief 원의 반지름 길이입니다.
	 */
	float radius_ = 0.0f;
};