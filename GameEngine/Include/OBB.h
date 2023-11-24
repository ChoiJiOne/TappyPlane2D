#pragma once

#include "IShape.h"
#include "Vector2.h"


/**
 * @brief 회전 축 정렬 경계 상자(OBB) 형태입니다.
 */
class OBB : public IShape
{
public:
	/**
	 * @brief OBB의 생성자입니다.
	 * 
	 * @param center 경계 영역의 중심 좌표입니다.
	 * @param width 경계 영역의 가로 크기입니다.
	 * @param height 경계 영역의 세로 크기입니다.
	 * @param rotate 경계 영역의 라디안 회전 각도입니다.
	 */
	OBB(const Vector2f& center, const float& width, const float& height, const float& rotate)
		: center_(center)
		, width_(width)
		, height_(height)
		, rotate_(rotate) {}


	/**
	 * @brief OBB의 복사 생성자입니다.
	 *
	 * @param instance 복사할 OBB 인스턴스입니다.
	 */
	OBB(OBB&& instance) noexcept
		: center_(instance.center_)
		, width_(instance.width_)
		, height_(instance.height_)
		, rotate_(instance.rotate_) {}


	/**
	 * @brief OBB의 복사 생성자입니다.
	 *
	 * @param instance 복사할 OBB 인스턴스입니다.
	 */
	OBB(const OBB& instance) noexcept
		: center_(instance.center_)
		, width_(instance.width_)
		, height_(instance.height_)
		, rotate_(instance.rotate_) {}


	/**
	 * @brief OBB의 대입 연산자입니다.
	 *
	 * @param instance 복사할 OBB 인스턴스입니다.
	 *
	 * @return 대입한 OBB의 참조자를 반환합니다.
	 */
	OBB& operator=(OBB&& instance) noexcept
	{
		if (this == &instance) return *this;

		center_ = instance.center_;
		width_ = instance.width_;
		height_ = instance.height_;
		rotate_ = instance.rotate_;

		return *this;
	}


	/**
	 * @brief OBB의 대입 연산자입니다.
	 *
	 * @param instance 복사할 OBB 인스턴스입니다.
	 *
	 * @return 대입한 OBB의 참조자를 반환합니다.
	 */
	OBB& operator=(const OBB& instance) noexcept
	{
		if (this == &instance) return *this;

		center_ = instance.center_;
		width_ = instance.width_;
		height_ = instance.height_;
		rotate_ = instance.rotate_;

		return *this;
	}


	/**
	 * @brief OBB의 타입을 반환합니다.
	 * 
	 * @return OBB의 타입을 반환합니다.
	 */
	virtual EType GetType() const override { return IShape::EType::OBB; }


	/**
	 * @brief OBB와 다른 오브젝트와의 충돌 여부를 검사합니다.
	 *
	 * @param shape 충돌 검사를 수행할 오브젝트입니다.
	 *
	 * @return 다른 오브젝트와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	virtual bool IsCollision(const IShape* shape) const override;


	/**
	 * @brief 경계 영역의 중심 좌표를 설정합니다.
	 * 
	 * @param center 설정할 중심 좌표입니다.
	 */
	void SetCenter(const Vector2f& center) { center_ = center; }


	/**
	 * @brief 경계 영역의 가로 크기를 설정합니다.
	 * 
	 * @param width 설정할 가로 크기입니다.
	 */
	void SetWidth(const float& width) { width_ = width; }


	/**
	 * @brief 경계 영역의 세로 크기를 설정합니다.
	 *
	 * @param height 설정할 세로 크기입니다.
	 */
	void SetHeight(const float& height) { height_ = height; }


	/**
	 * @brief 경계 영역의 회전 각도를 설정합니다.
	 * 
	 * @param rotate 설정할 회전 각도 크기입니다.
	 */
	void SetRotate(const float& rotate) { rotate_ = rotate; }


	/**
	 * @brief OBB의 프로퍼티를 설정합니다.
	 * 
	 * @param center 경계 영역의 중심 좌표입니다.
	 * @param width 경계 영역의 가로 크기입니다.
	 * @param height 경계 영역의 세로 크기입니다.
	 * @param rotate 경계 영역의 라디안 회전 각도입니다.
	 */
	void SetProperty(const Vector2f& center, const float& width, const float& height, const float& rotate)
	{
		center_ = center;
		width_ = width;
		height_ = height;
		rotate_ = rotate;
	}


	/**
	 * @brief 경계 영역의 중심 좌표를 얻습니다.
	 *
	 * @return 경계 영역 중심 좌표를 반환합니다.
	 */
	Vector2f GetCenter() const { return center_; }


	/**
	 * @brief 경계 영역의 가로 크기 값을 얻습니다.
	 *
	 * @return 경계 영역의 가로 크기 값을 반환합니다.
	 */
	float GetWidth() const { return width_; }


	/**
	 * @brief 경계 영역의 세로 크기 값을 얻습니다.
	 *
	 * @return 경계 영역의 세로 크기 값을 반환합니다.
	 */
	float GetHeight() const { return height_; }


	/**
	 * @brief 경계 영역의 회전 각을 얻습니다.
	 *
	 * @return 경계 영역의 회전 각을 반환합니다.
	 */
	float GetRotate() const { return rotate_; }

		
private:
	/**
	 * @brief OBB 오브젝트와의 충돌 여부를 검사합니다.
	 *
	 * @param shape 충돌 여부를 검사할 OBB 오브젝트입니다.
	 *
	 * @return 다른 OBB 오브젝트와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsCollisionOBB(const IShape* shape) const;


private:
	/**
	 * @brief 경계 영역의 중심 좌표입니다.
	 */
	Vector2f center_;


	/**
	 * @brief 경계 영역의 가로 크기입니다.
	 */
	float width_ = 0.0f;


	/**
	 * @brief 경계 영역의 세로 크기입니다.
	 */
	float height_ = 0.0f;


	/**
	 * @brief 경계 영역의 회전 라디안 각도입니다.
	 */
	float rotate_ = 0.0f;
};