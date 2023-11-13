#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief 위치 정보를 가진 정점(Vertex)입니다.
 */
struct VertexPosition
{
	/**
	 * @brief 위치 정보를 가진 정점의 기본 생성자입니다.
	 */
	VertexPosition() noexcept 
		: position_(0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief 위치 정보를 가진 정점의 생성자입니다.
	 * 
	 * @param position 정점의 위치입니다.
	 */
	VertexPosition(Vector3f&& position) noexcept 
		: position_(position) {}


	/**
	 * @brief 위치 정보를 가진 정점의 생성자입니다.
	 * 
	 * @param position 정점의 위치입니다.
	 */
	VertexPosition(const Vector3f& position) noexcept 
		: position_(position) {}


	/**
	 * @brief 위치 정보를 가진 정점의 생성자입니다.
	 * 
	 * @param x 위치의 X좌표입니다.
	 * @param y 위치의 Y좌표입니다.
	 * @param z 위치의 Z좌표입니다.
	 */
	VertexPosition(float x, float y, float z) noexcept 
		: position_(x, y, z) {}


	/**
	 * @brief 위치 정보를 가진 정점의 생성자입니다.
	 * 
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPosition(VertexPosition&& instance) noexcept
		: position_(instance.position_) {}


	/**
	 * @brief 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPosition(const VertexPosition& instance) noexcept
		: position_(instance.position_) {}


	/**
	 * @brief 위치 정보를 가진 정점의 대입 연산자입니다.
	 * 
	 * @param instance 대입할 정점 인스턴스입니다.
	 * 
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPosition& operator=(VertexPosition&& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;

		return *this;
	}


	/**
	 * @brief 위치 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPosition& operator=(const VertexPosition& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;

		return *this;
	}


	/**
	 * @brief 정점의 바이트 보폭 값을 얻습니다.
	 * 
	 * @return 정점의 파이트 보폭(Stride) 값을 반환합니다.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPosition);
	}


	/**
	 * @brief 정점의 위치입니다.
	 */
	Vector3f position_;
};


/**
 * @brief 위치와 색상 정보를 가진 정점(Vertex)입니다.
 */
struct VertexPositionColor
{
	/**
	 * @brief 위치와 색상 정보를 가진 정점의 기본 생성자입니다.
	 */
	VertexPositionColor() noexcept
		: position_(0.0f, 0.0f, 0.0f)
		, color_(0.0f, 0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
	 *
	 * @param position 정점의 위치입니다.
	 * @param color 정점의 색상입니다.
	 */
	VertexPositionColor(Vector3f&& position, Vector4f&& color) noexcept
		: position_(position) 
		, color_(color) {}


	/**
	 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
	 *
	 * @param position 정점의 위치입니다.
	 * @param color 정점의 색상입니다.
	 */
	VertexPositionColor(const Vector3f& position, const Vector4f& color) noexcept
		: position_(position) 
		, color_(color) {}


	/**
	 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
	 *
	 * @param x 위치의 X좌표입니다.
	 * @param y 위치의 Y좌표입니다.
	 * @param z 위치의 Z좌표입니다.
	 * @param r 정점 색상의 R입니다.
	 * @param g 정점 색상의 G입니다.
	 * @param b 정점 색상의 B입니다.
	 * @param a 정점 색상의 A입니다.
	 */
	VertexPositionColor(
		float x, float y, float z,
		float r, float g, float b, float a
	) noexcept
		: position_(x, y, z) 
		, color_(r, g, b, a) {}


	/**
	 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPositionColor(VertexPositionColor&& instance) noexcept
		: position_(instance.position_) 
		, color_(instance.color_) {}


	/**
	 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPositionColor(const VertexPositionColor& instance) noexcept
		: position_(instance.position_)
		, color_(instance.color_) {}


	/**
	 * @brief 위치와 색상 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPositionColor& operator=(VertexPositionColor&& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		color_ = instance.color_;

		return *this;
	}


	/**
	 * @brief 위치와 색상 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPositionColor& operator=(const VertexPositionColor& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		color_ = instance.color_;

		return *this;
	}


	/**
	 * @brief 정점의 바이트 보폭 값을 얻습니다.
	 *
	 * @return 정점의 파이트 보폭(Stride) 값을 반환합니다.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPositionColor);
	}


	/**
	 * @brief 정점의 위치입니다.
	 */
	Vector3f position_;


	/**
	 * @brief 정점의 색상입니다.
	 */
	Vector4f color_;
};


/**
 * @brief 위치와 텍스처 정보를 가진 정점(Vertex)입니다.
 */
struct VertexPositionTexture
{
	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 기본 생성자입니다.
	 */
	VertexPositionTexture() noexcept
		: position_(0.0f, 0.0f, 0.0f) 
		, st_(0.0f, 0.0f) {}


	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
	 *
	 * @param position 정점의 위치입니다.
	 * @param st 정점의 텍스처 위치입니다.
	 */
	VertexPositionTexture(Vector3f&& position, Vector2f&& st) noexcept
		: position_(position) 
		, st_(st) {}


	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
	 *
	 * @param position 정점의 위치입니다.
	 * @param st 정점의 텍스처 위치입니다.
	 */
	VertexPositionTexture(const Vector3f& position, const Vector2f& st) noexcept
		: position_(position) 
		, st_(st) {}


	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
	 *
	 * @param x 위치의 X좌표입니다.
	 * @param y 위치의 Y좌표입니다.
	 * @param z 위치의 Z좌표입니다.
	 * @param s 텍스처 위치의 S좌표입니다.
	 * @param t 텍스처 위치의 T좌표입니다.
	 */
	VertexPositionTexture(
		float x, float y, float z,
		float s, float t
	) noexcept
		: position_(x, y, z) 
		, st_(s, t) {}


	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPositionTexture(VertexPositionTexture&& instance) noexcept
		: position_(instance.position_) 
		, st_(instance.st_) {}


	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPositionTexture(const VertexPositionTexture& instance) noexcept
		: position_(instance.position_)
		, st_(instance.st_) {}


	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPositionTexture& operator=(VertexPositionTexture&& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		st_ = instance.st_;

		return *this;
	}


	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPositionTexture& operator=(const VertexPositionTexture& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		st_ = instance.st_;

		return *this;
	}


	/**
	 * @brief 정점의 바이트 보폭 값을 얻습니다.
	 *
	 * @return 정점의 파이트 보폭(Stride) 값을 반환합니다.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPositionTexture);
	}


	/**
	 * @brief 정점의 위치입니다.
	 */
	Vector3f position_;


	/**
	 * @brief 정점의 텍스처 좌표입니다.
	 */
	Vector2f st_;
};