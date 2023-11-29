#pragma once

#include <array>

#include "AABB.h"
#include "IGameObject.h"
#include "Texture2D.h"
#include "MathUtils.h"
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
		Crash = 0x02,   // �浹
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
	 */
	virtual void Release() override;


	/**
	 * @brief ������� �浹 ��� ������ ����ϴ�.
	 * 
	 * @return ����� �浹 ��� ������ ��� �����ڸ� ��ȯ�մϴ�.
	 */
	const AABB& GetCollisionBound() const { return collisionBound_; }


	/**
	 * @brief ������ �� ������Ʈ�� �浹 Ƚ���� ����ϴ�.
	 * 
	 * @return ������ �� ������Ʈ�� �浹 Ƚ���� ��ȯ�մϴ�.
	 */
	int32_t GetCountOfCollisionStar() const { return countOfCollisionStar_; }


private:
	/**
	 * @brief ������� ���� �ִϸ��̼��� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	void UpdateFlightAnimation(float deltaSeconds);


	/**
	 * @brief ������� ���� �ִϸ��̼��� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	void UpdateExplosionAnimation(float deltaSeconds);


	/**
	 * @brief ����Ⱑ ������� ���¸� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	void UpdateWaitState(float deltaSeconds);


	/**
	 * @brief ����Ⱑ ���� ���¸� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	void UpdateFlightState(float deltaSeconds);


	/**
	 * @brief ����Ⱑ �浹���� �� ���¸� ������Ʈ�մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	void UpdateCrashState(float deltaSeconds);

	
private:
	/**
	 * @brief ������� ���� �����Դϴ�.
	 * 
	 * @note �� �Ӽ��� ������� �⺻ �Ӽ��Դϴ�.
	 */
	EColor colorType_ = EColor::Blue;


	/**
	 * @brief ������� �߽� ��ǥ�Դϴ�.
	 * 
	 * @note �� �Ӽ��� ������� �⺻ �Ӽ��Դϴ�.
	 */
	Vector2f center_;


	/**
	 * @brief ������� ���� ũ���Դϴ�.
	 * 
	 * @note �� �Ӽ��� ������� �⺻ �Ӽ��Դϴ�.
	 */
	float width_ = 0.0f;


	/**
	 * @brief ������� ���� ũ���Դϴ�.
	 * 
	 * @note �� �Ӽ��� ������� �⺻ �Ӽ��Դϴ�.
	 */
	float height_ = 0.0f;


	/**
	 * @brief ������� ȸ�� �����Դϴ�.
	 * 
	 * @note �� �Ӽ��� ������� �⺻ �Ӽ��Դϴ�.
	 */
	float rotate_ = 0.0f;


	/**
	 * @brief ���� ������� �����Դϴ�.
	 * 
	 * @note �� �Ӽ��� ������� �⺻ �Ӽ��Դϴ�.
	 */
	EState state_ = EState::Wait;


	/**
	 * @brief �浹 ó���� ���� AABB�Դϴ�.
	 * 
	 * @note �� �Ӽ��� ������� �⺻ �Ӽ��Դϴ�.
	 */
	AABB collisionBound_;


	/**
	 * @brief ������� �ִϸ��̼��� �����ϱ� ���� �ؽ�ó�Դϴ�.
	 */
	std::array<Texture2D*, 5> flightAnimationTextures_;


	/**
	 * @brief ���� �ִϸ��̼� �ؽ�ó �ε����Դϴ�.
	 */
	uint32_t flightAnimationTextureIndex_ = 0;


	/**
	 * @brief �ִϸ��̼��� �����ϱ� ���� �� �������� ���� �ð��Դϴ�.
	 */
	float flightAnimationFrameTime_ = 0.0f;


	/**
	 * @brief ������� ���� �ִϸ��̼��� �����ϱ� ���� �ؽ�ó�Դϴ�.
	 */
	std::array<Texture2D*, 5> explosionAnimationTextures_;


	/**
	 * @brief ���� �ִϸ��̼� �ؽ�ó �ε����Դϴ�.
	 */
	uint32_t explosionAnimationTextureIndex_ = 0;


	/**
	 * @brief �ִϸ��̼��� �����ϱ� ���� �� �������� ���� �ð��Դϴ�.
	 */
	float explosionAnimationFrameTime_ = 0.0f;


	/**
	 * @brief �ִϸ��̼��� �����ϱ� ���� ���� �ð��Դϴ�.
	 */
	float accumulateAnimationFrameTime_ = 0.0f;


	/**
	 * @brief ������� ��� �ð��Դϴ�.
	 */
	float waitAccumulateTime_ = 0.0f;


	/**
	 * @brief ������� ��� ��ġ�Դϴ�.
	 */
	Vector2f waitPosition_;

	
	/**
	 * @brief ������� �ִ� �ӵ��Դϴ�.
	 */
	float maxSpeed_ = 0.0f;


	/**
	 * @brief ������� ���� �ӵ��Դϴ�.
	 */
	float currentSpeed_ = 0.0f;


	/**
	 * @brief ������� ���� �ӵ��Դϴ�.
	 */
	float dampingSpeed_ = 0.0f;


	/**
	 * @brief ������ �� ������Ʈ�� �浹 Ƚ���Դϴ�.
	 */
	int32_t countOfCollisionStar_ = 0;
};