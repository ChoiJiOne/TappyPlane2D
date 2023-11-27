#pragma once

#include <array>

#include "Circle.h"
#include "IGameObject.h"
#include "Texture2D.h"
#include "Vector2.h"


/**
 * @brief �÷��̾ ���� ������ ������Դϴ�.
 */
class Plane : public IGameObject
{
public:
	/**
	 * @brief ������� ���� �����Դϴ�.
	 */
	enum class EColor : int32_t
	{
		Blue   = 0x00,
		Green  = 0x01,
		Red    = 0x02,
		Yellow = 0x03,
	};


	/**
	 * @brief ������� ���¸� ��Ÿ���ϴ�.
	 */
	enum class EState : int32_t
	{
		Wait = 0x00,    // ��� ����
		Flight = 0x01,  // ���� ��
		Landing = 0x02, // �ϰ� ��
		Crash = 0x03,   // �浹
	};


public:
	/**
	 * @brief ������� ����Ʈ �������Դϴ�.
	 */
	Plane() = default;


	/**
	 * @brief ������� ���� �Ҹ����Դϴ�.
	 *
	 * @note ����� ���ο��� �Ҵ�� ���ҽ��� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~Plane();


	/**
	 * @brief ������� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Plane);


	/**
	 * @brief ����⸦ �ʱ�ȭ�մϴ�.
	 * 
	 * @param colorType ����� ������ �����Դϴ�.
	 */
	void Initialize(const EColor& colorType);


	/**
	 * @brief ����⸦ ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief ����⸦ ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ����� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 *
	 * @note ����� �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief ������� �ִϸ��̼��� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	void UpdateAnimation(float deltaSeconds);


private:
	/**
	 * @brief ������� ���� �����Դϴ�.
	 */
	EColor colorType_ = EColor::Blue;
	

	/**
	 * @brief ������� �ִϸ��̼��� �����ϱ� ���� �ؽ�ó�Դϴ�.
	 */
	std::array<Texture2D*, 5> animationTextures_;


	/**
	 * @brief ���� �ִϸ��̼� �ؽ�ó �ε����Դϴ�.
	 */
	uint32_t animationTextureIndex_ = 0;


	/**
	 * @brief �ִϸ��̼��� �����ϱ� ���� �� �������� ���� �ð��Դϴ�.
	 */
	float animationFrameTime_ = 0.0f;


	/**
	 * @brief �ִϸ��̼��� �����ϱ� ���� ���� �ð��Դϴ�.
	 */
	float accumulateAnimationFrameTime_ = 0.0f;


	/**
	 * @brief ������� ��� ��ġ�Դϴ�.
	 */
	Vector2f waitPosition_;


	/**
	 * @brief ������� �߽� ��ǥ�Դϴ�.
	 */
	Vector2f center_;


	/**
	 * @brief ������� ���� ũ���Դϴ�.
	 */
	float width_ = 0.0f;


	/**
	 * @brief ������� ���� ũ���Դϴ�.
	 */
	float height_ = 0.0f;


	/**
	 * @brief ������� ȸ�� �����Դϴ�.
	 */
	float rotate_ = 0.0f;


	/**
	 * @brief �浹 ó���� ���� ���Դϴ�.
	 */
	Circle collisionBound_;


	/**
	 * @brief ������� ������ �ð��Դϴ�.
	 */
	float accumulateTime_ = 0.0f;


	/**
	 * @brief ���� ������� �����Դϴ�.
	 */
	EState state_ = EState::Wait;
};