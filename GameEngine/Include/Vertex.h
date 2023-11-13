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
	 * @brief ��ġ�� ���� ������ ���� ������ �⺻ �������Դϴ�.
	 */
	VertexPositionColor() noexcept
		: position_(0.0f, 0.0f, 0.0f)
		, color_(0.0f, 0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param position ������ ��ġ�Դϴ�.
	 * @param color ������ �����Դϴ�.
	 */
	VertexPositionColor(Vector3f&& position, Vector4f&& color) noexcept
		: position_(position) 
		, color_(color) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param position ������ ��ġ�Դϴ�.
	 * @param color ������ �����Դϴ�.
	 */
	VertexPositionColor(const Vector3f& position, const Vector4f& color) noexcept
		: position_(position) 
		, color_(color) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
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
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionColor(VertexPositionColor&& instance) noexcept
		: position_(instance.position_) 
		, color_(instance.color_) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionColor(const VertexPositionColor& instance) noexcept
		: position_(instance.position_)
		, color_(instance.color_) {}


	/**
	 * @brief ��ġ�� ���� ������ ���� ������ ���� �������Դϴ�.
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
	 * @brief ��ġ�� ���� ������ ���� ������ ���� �������Դϴ�.
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


/**
 * @brief ��ġ�� �ؽ�ó ������ ���� ����(Vertex)�Դϴ�.
 */
struct VertexPositionTexture
{
	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �⺻ �������Դϴ�.
	 */
	VertexPositionTexture() noexcept
		: position_(0.0f, 0.0f, 0.0f) 
		, st_(0.0f, 0.0f) {}


	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
	 *
	 * @param position ������ ��ġ�Դϴ�.
	 * @param st ������ �ؽ�ó ��ġ�Դϴ�.
	 */
	VertexPositionTexture(Vector3f&& position, Vector2f&& st) noexcept
		: position_(position) 
		, st_(st) {}


	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
	 *
	 * @param position ������ ��ġ�Դϴ�.
	 * @param st ������ �ؽ�ó ��ġ�Դϴ�.
	 */
	VertexPositionTexture(const Vector3f& position, const Vector2f& st) noexcept
		: position_(position) 
		, st_(st) {}


	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
	 *
	 * @param x ��ġ�� X��ǥ�Դϴ�.
	 * @param y ��ġ�� Y��ǥ�Դϴ�.
	 * @param z ��ġ�� Z��ǥ�Դϴ�.
	 * @param s �ؽ�ó ��ġ�� S��ǥ�Դϴ�.
	 * @param t �ؽ�ó ��ġ�� T��ǥ�Դϴ�.
	 */
	VertexPositionTexture(
		float x, float y, float z,
		float s, float t
	) noexcept
		: position_(x, y, z) 
		, st_(s, t) {}


	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionTexture(VertexPositionTexture&& instance) noexcept
		: position_(instance.position_) 
		, st_(instance.st_) {}


	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 */
	VertexPositionTexture(const VertexPositionTexture& instance) noexcept
		: position_(instance.position_)
		, st_(instance.st_) {}


	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionTexture& operator=(VertexPositionTexture&& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		st_ = instance.st_;

		return *this;
	}


	/**
	 * @brief ��ġ�� �ؽ�ó ������ ���� ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ���� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	VertexPositionTexture& operator=(const VertexPositionTexture& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		st_ = instance.st_;

		return *this;
	}


	/**
	 * @brief ������ ����Ʈ ���� ���� ����ϴ�.
	 *
	 * @return ������ ����Ʈ ����(Stride) ���� ��ȯ�մϴ�.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPositionTexture);
	}


	/**
	 * @brief ������ ��ġ�Դϴ�.
	 */
	Vector3f position_;


	/**
	 * @brief ������ �ؽ�ó ��ǥ�Դϴ�.
	 */
	Vector2f st_;
};