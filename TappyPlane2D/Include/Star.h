#pragma once

#include "AABB.h"
#include "IGameObject.h"
#include "Texture2D.h"
#include "Vector2.h"


/**
 * @brief �÷��̾ ȹ�� ������ �� ������Ʈ�Դϴ�.
 */
class Star : public IGameObject
{
public:
	/**
	 * @brief �� ������Ʈ�� �����Դϴ�.
	 */
	enum class EState : int32_t
	{
		Wait = 0x00,
		Move = 0x01,
	};


public:
	/**
	 * @brief �� ������Ʈ�� ����Ʈ �������Դϴ�.
	 */
	Star() = default;


	/**
	 * @brief �� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 * 
	 * @note �� ������Ʈ ���ο��� �Ҵ�� ���ҽ��� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~Star();


	/**
	 * @brief �� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Star);


	/**
	 * @brief �� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 * 
	 * @param center �� ������Ʈ�� �߽� ��ġ�Դϴ�.
	 */
	void Initialize(const Vector2f& center);


	 /**
	  * @brief �� ������Ʈ�� ������Ʈ�մϴ�.
	  *
	  * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	  */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief �� ������Ʈ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief �� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;

	
	/**
	 * @brief �� ������Ʈ�� �浹 ��� ������ ����ϴ�.
	 *
	 * @return �� ������Ʈ �浹 ��� ������ ��� �����ڸ� ��ȯ�մϴ�.
	 */
	const AABB& GetCollisionBound() const { return collisionBound_; }


	/**
	 * @brief �� ������Ʈ�� ���� ������Ƽ�� �ʱ�ȭ�մϴ�.
	 * 
	 * @param center �� ������Ʈ�� �߽� ��ġ�Դϴ�.
	 */
	void SetupProperties(const Vector2f& center);


	/**
	 * @brief �� ������Ʈ�� ���¸� ����ϴ�.
	 *
	 * @return �� ������Ʈ�� ���¸� ��ȯ�մϴ�.
	 */
	EState GetState() const { return state_; }


	/**
	 * @brief �� ������Ʈ�� ���¸� �����մϴ�.
	 *
	 * @param state ������ �� ������Ʈ�� �����Դϴ�.
	 */
	void SetState(const EState& state) { state_ = state; }


private:
	/**
	 * @brief �� ������Ʈ�� �����Դϴ�.
	 */
	EState state_ = EState::Wait;


	/**
	 * @brief �� ������Ʈ�� �߽� ��ġ�Դϴ�.
	 */
	Vector2f center_;


	/**
	 * @brief �� ������Ʈ�� ���� ũ���Դϴ�.
	 */
	float width_ = 0.0f;


	/**
	 * @brief �� ������Ʈ�� ���� ũ���Դϴ�.
	 */
	float height_ = 0.0f;


	/**
	 * @brief �� ������Ʈ�� �̵� �ӵ��Դϴ�.
	 */
	float speed_ = 0.0f;


	/**
	 * @brief �� ������Ʈ�� ��� �����Դϴ�.
	 */
	AABB collisionBound_;


	/**
	 * @brief �� ������Ʈ�� �ؽ�ó�Դϴ�.
	 */
	Texture2D* texture_ = nullptr;
};