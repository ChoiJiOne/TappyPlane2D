#pragma once

#include "IShape.h"
#include "Vector2.h"


/**
 * @brief ȸ�� �� ���� ��� ����(OBB) �����Դϴ�.
 */
class OBB : public IShape
{
public:
	/**
	 * @brief OBB�� �������Դϴ�.
	 * 
	 * @param center ��� ������ �߽� ��ǥ�Դϴ�.
	 * @param width ��� ������ ���� ũ���Դϴ�.
	 * @param height ��� ������ ���� ũ���Դϴ�.
	 * @param rotate ��� ������ ���� ȸ�� �����Դϴ�.
	 */
	OBB(const Vector2f& center, const float& width, const float& height, const float& rotate)
		: center_(center)
		, width_(width)
		, height_(height)
		, rotate_(rotate) {}


	/**
	 * @brief OBB�� ���� �������Դϴ�.
	 *
	 * @param instance ������ OBB �ν��Ͻ��Դϴ�.
	 */
	OBB(OBB&& instance) noexcept
		: center_(instance.center_)
		, width_(instance.width_)
		, height_(instance.height_)
		, rotate_(instance.rotate_) {}


	/**
	 * @brief OBB�� ���� �������Դϴ�.
	 *
	 * @param instance ������ OBB �ν��Ͻ��Դϴ�.
	 */
	OBB(const OBB& instance) noexcept
		: center_(instance.center_)
		, width_(instance.width_)
		, height_(instance.height_)
		, rotate_(instance.rotate_) {}


	/**
	 * @brief OBB�� ���� �������Դϴ�.
	 *
	 * @param instance ������ OBB �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ OBB�� �����ڸ� ��ȯ�մϴ�.
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
	 * @brief OBB�� ���� �������Դϴ�.
	 *
	 * @param instance ������ OBB �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ OBB�� �����ڸ� ��ȯ�մϴ�.
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
	 * @brief OBB�� Ÿ���� ��ȯ�մϴ�.
	 * 
	 * @return OBB�� Ÿ���� ��ȯ�մϴ�.
	 */
	virtual EType GetType() const override { return IShape::EType::OBB; }


	/**
	 * @brief OBB�� �ٸ� ������Ʈ���� �浹 ���θ� �˻��մϴ�.
	 *
	 * @param shape �浹 �˻縦 ������ ������Ʈ�Դϴ�.
	 *
	 * @return �ٸ� ������Ʈ�� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	virtual bool IsCollision(const IShape* shape) const override;


	/**
	 * @brief ��� ������ �߽� ��ǥ�� �����մϴ�.
	 * 
	 * @param center ������ �߽� ��ǥ�Դϴ�.
	 */
	void SetCenter(const Vector2f& center) { center_ = center; }


	/**
	 * @brief ��� ������ ���� ũ�⸦ �����մϴ�.
	 * 
	 * @param width ������ ���� ũ���Դϴ�.
	 */
	void SetWidth(const float& width) { width_ = width; }


	/**
	 * @brief ��� ������ ���� ũ�⸦ �����մϴ�.
	 *
	 * @param height ������ ���� ũ���Դϴ�.
	 */
	void SetHeight(const float& height) { height_ = height; }


	/**
	 * @brief ��� ������ ȸ�� ������ �����մϴ�.
	 * 
	 * @param rotate ������ ȸ�� ���� ũ���Դϴ�.
	 */
	void SetRotate(const float& rotate) { rotate_ = rotate; }


	/**
	 * @brief OBB�� ������Ƽ�� �����մϴ�.
	 * 
	 * @param center ��� ������ �߽� ��ǥ�Դϴ�.
	 * @param width ��� ������ ���� ũ���Դϴ�.
	 * @param height ��� ������ ���� ũ���Դϴ�.
	 * @param rotate ��� ������ ���� ȸ�� �����Դϴ�.
	 */
	void SetProperty(const Vector2f& center, const float& width, const float& height, const float& rotate)
	{
		center_ = center;
		width_ = width;
		height_ = height;
		rotate_ = rotate;
	}


	/**
	 * @brief ��� ������ �߽� ��ǥ�� ����ϴ�.
	 *
	 * @return ��� ���� �߽� ��ǥ�� ��ȯ�մϴ�.
	 */
	Vector2f GetCenter() const { return center_; }


	/**
	 * @brief ��� ������ ���� ũ�� ���� ����ϴ�.
	 *
	 * @return ��� ������ ���� ũ�� ���� ��ȯ�մϴ�.
	 */
	float GetWidth() const { return width_; }


	/**
	 * @brief ��� ������ ���� ũ�� ���� ����ϴ�.
	 *
	 * @return ��� ������ ���� ũ�� ���� ��ȯ�մϴ�.
	 */
	float GetHeight() const { return height_; }


	/**
	 * @brief ��� ������ ȸ�� ���� ����ϴ�.
	 *
	 * @return ��� ������ ȸ�� ���� ��ȯ�մϴ�.
	 */
	float GetRotate() const { return rotate_; }

		
private:
	/**
	 * @brief OBB ������Ʈ���� �浹 ���θ� �˻��մϴ�.
	 *
	 * @param shape �浹 ���θ� �˻��� OBB ������Ʈ�Դϴ�.
	 *
	 * @return �ٸ� OBB ������Ʈ�� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsCollisionOBB(const IShape* shape) const;


private:
	/**
	 * @brief ��� ������ �߽� ��ǥ�Դϴ�.
	 */
	Vector2f center_;


	/**
	 * @brief ��� ������ ���� ũ���Դϴ�.
	 */
	float width_ = 0.0f;


	/**
	 * @brief ��� ������ ���� ũ���Դϴ�.
	 */
	float height_ = 0.0f;


	/**
	 * @brief ��� ������ ȸ�� ���� �����Դϴ�.
	 */
	float rotate_ = 0.0f;
};