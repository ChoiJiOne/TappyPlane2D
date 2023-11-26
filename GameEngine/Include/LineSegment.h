#pragma once

#include <array>

#include "IShape.h"
#include "Vector2.h"


/**
 * @brief 선분 형태입니다.
 */
class LineSegment : public IShape
{
public:
	/**
	 * @brief 선분의 생성자입니다.
	 * 
	 * @param point0 선분의 한 끝점입니다.
	 * @param point1 선분의 다른 한 끝점입니다.
	 */
	LineSegment(const Vector2f& point0, const Vector2f& point1)
		: points_(std::array<Vector2f, 2>{ point0, point1 }) {}

	
	/**
	 * @brief 선분의 생성자입니다.
	 * 
	 * @param points 선분의 양 끝점입니다.
	 */
	LineSegment(const std::array<Vector2f, 2>& points)
		: points_(points) {}


	/**
	 * @brief 선분의 복사 생성자입니다.
	 * 
	 * @param instance 복사할 선분 인스턴스입니다.
	 */
	LineSegment(LineSegment&& instance) noexcept
		: points_(instance.points_) {}


	/**
	 * @brief 선분의 복사 생성자입니다.
	 *
	 * @param instance 복사할 선분 인스턴스입니다.
	 */
	LineSegment(const LineSegment& instance) noexcept
		: points_(instance.points_) {}


	/**
	 * @brief 선분의 대입 연산자입니다.
	 * 
	 * @param instance 복사할 선분 인스턴스입니다.
	 * 
	 * @return 복사한 선분 인스턴스의 참조자를 반환합니다.
	 */
	LineSegment& operator=(LineSegment&& instance) noexcept
	{
		if (this == &instance) return *this;
		
		points_ = instance.points_;

		return *this;
	}


	/**
	 * @brief 선분의 대입 연산자입니다.
	 *
	 * @param instance 복사할 선분 인스턴스입니다.
	 *
	 * @return 복사한 선분 인스턴스의 참조자를 반환합니다.
	 */
	LineSegment& operator=(const LineSegment& instance) noexcept
	{
		if (this == &instance) return *this;

		points_ = instance.points_;

		return *this;
	}


	/**
	 * @brief 선분의 타입을 반환합니다.
	 *
	 * @return 선분의 타입을 반환합니다.
	 */
	virtual EType GetType() const override { return IShape::EType::LineSegment; }


	/**
	 * @brief 선분과 다른 오브젝트와의 충돌 여부를 검사합니다.
	 *
	 * @param shape 충돌 검사를 수행할 오브젝트입니다.
	 *
	 * @return 다른 오브젝트와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	virtual bool IsCollision(const IShape* shape) const override;


	/**
	 * @brief 선분의 양 끝점을 설정합니다.
	 * 
	 * @param points 설정할 선분의 양 끝점입니다.
	 */
	void SetPoints(const std::array<Vector2f, 2>& points) { points_ = points; }


	/**
	 * @brief 선분의 양 끝점을 얻습니다.
	 *
	 * @return 선분의 양 끝점을 반환합니다.
	 */
	std::array<Vector2f, 2>& GetPoints() { return points_; }


	/**
	 * @brief 선분의 양 끝점을 얻습니다.
	 * 
	 * @return 선분의 양 끝점을 반환합니다.
	 */
	const std::array<Vector2f, 2>& GetPoints() const { return points_; }


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
	 * @brief 선분 오브젝트와의 충돌 여부를 검사합니다.
	 * 
	 * @param shape 충돌 여부를 검사할 선분 오브젝트입니다.
	 *
	 * @return 다른 선분 오브젝트와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsCollisionLineSegment(const IShape* shape) const;


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
	 * @brief 선분의 양 끝점입니다.
	 */
	std::array<Vector2f, 2> points_;
};