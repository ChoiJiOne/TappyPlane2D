#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief ��ġ ������ ���� ����(Vertex)�Դϴ�.
 */
struct VertexPosition
{
	/**
	 * @brief ��ġ ������ ���� ������ �⺻ �������Դϴ�.
	 */
	VertexPosition() noexcept 
		: position_(0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 * 
	 * @param position ������ ��ġ�Դϴ�.
	 */
	VertexPosition(Vector3f&& position) noexcept 
		: position_(position) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 * 
	 * @param position ������ ��ġ�Դϴ�.
	 */
	VertexPosition(const Vector3f& position) noexcept 
		: position_(position) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 * 
	 * @param x ��ġ�� X��ǥ�Դϴ�.
	 * @param y ��ġ�� Y��ǥ�Դϴ�.
	 * @param z ��ġ�� Z��ǥ�Դϴ�.
	 */
	VertexPosition(float x, float y, float z) noexcept 
		: position_(x, y, z) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 * 
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPosition(VertexPosition&& instance) noexcept
		: position_(instance.position_) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPosition(const VertexPosition& instance) noexcept
		: position_(instance.position_) {}


	/**
	 * @brief ��ġ ������ ���� ������ ���� �������Դϴ�.
	 * 
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 * 
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPosition& operator=(VertexPosition&& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;

		return *this;
	}


	/**
	 * @brief ��ġ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPosition& operator=(const VertexPosition& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;

		return *this;
	}


	/**
	 * @brief ������ ����Ʈ ���� ���� ����ϴ�.
	 * 
	 * @return ������ ����Ʈ ����(Stride) ���� ��ȯ�մϴ�.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPosition);
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vector3f position_;
};


/**
 * @brief ��ġ�� ���� ������ ���� ����(Vertex)�Դϴ�.
 */
struct VertexPositionColor
{
	/**
	 * @brief ��ġ ������ ���� ������ �⺻ �������Դϴ�.
	 */
	VertexPositionColor() noexcept
		: position_(0.0f, 0.0f, 0.0f)
		, color_(0.0f, 0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param position ������ ��ġ�Դϴ�.
	 * @param color ������ �����Դϴ�.
	 */
	VertexPositionColor(Vector3f&& position, Vector4f&& color) noexcept
		: position_(position) 
		, color_(color) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param position ������ ��ġ�Դϴ�.
	 * @param color ������ �����Դϴ�.
	 */
	VertexPositionColor(const Vector3f& position, const Vector4f& color) noexcept
		: position_(position) 
		, color_(color) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param x ��ġ�� X��ǥ�Դϴ�.
	 * @param y ��ġ�� Y��ǥ�Դϴ�.
	 * @param z ��ġ�� Z��ǥ�Դϴ�.
	 * @param r ���� ������ R�Դϴ�.
	 * @param g ���� ������ G�Դϴ�.
	 * @param b ���� ������ B�Դϴ�.
	 * @param a ���� ������ A�Դϴ�.
	 */
	VertexPositionColor(
		float x, float y, float z,
		float r, float g, float b, float a
	) noexcept
		: position_(x, y, z) 
		, color_(r, g, b, a) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionColor(VertexPositionColor&& instance) noexcept
		: position_(instance.position_) 
		, color_(instance.color_) {}


	/**
	 * @brief ��ġ ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionColor(const VertexPositionColor& instance) noexcept
		: position_(instance.position_)
		, color_(instance.color_) {}


	/**
	 * @brief ��ġ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionColor& operator=(VertexPositionColor&& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		color_ = instance.color_;

		return *this;
	}


	/**
	 * @brief ��ġ ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionColor& operator=(const VertexPositionColor& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		color_ = instance.color_;

		return *this;
	}


	/**
	 * @brief ������ ����Ʈ ���� ���� ����ϴ�.
	 *
	 * @return ������ ����Ʈ ����(Stride) ���� ��ȯ�մϴ�.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPositionColor);
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vector3f position_;


	/**
	 * @brief ������ �����Դϴ�.
	 */
	Vector4f color_;
};