#pragma once

#include "AABB.h"
#include "IGameObject.h"
#include "Texture2D.h"
#include "Vector2.h"


/**
 * @brief �׶��� ������Ʈ�Դϴ�.
 */
class Ground : public IGameObject
{
public:
	/**
	 * @brief �׶��� ������Ʈ�� �����Դϴ�.
	 */
	enum class EType : int32_t
	{
		Top = 0x00,
		Bottom = 0x01,
	};


public:
	/**
	 * @brief �׶��� ������Ʈ�� ����Ʈ �������Դϴ�.
	 */
	Ground() = default;


	/**
	 * @brief �׶��� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 * 
	 * @note �׶��� ������Ʈ ���ο��� �Ҵ�� ���ҽ��� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~Ground();


	/**
	 * @brief �׶��� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Ground);


	/**
	 * @brief �׶��� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 * 
	 * @param type �׶��� ������Ʈ�� Ÿ���Դϴ�.
	 */
	void Initialize(const EType& type);


	/**
	 * @brief �׶��� ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief �׶��� ������Ʈ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief �׶��� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 *
	 * @note �׶��� ������Ʈ �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief �׶����� Ÿ���Դϴ�.
	 */
	EType type_;


	/**
	 * @brief �׶��� �ؽ�ó ���ҽ��Դϴ�.
	 */
	Texture2D* texture_ = nullptr;


	/**
	 * @brief �׶����� �߽� ��ġ�Դϴ�.
	 */
	Vector2f center_;


	/**
	 * @brief �׶����� ���� ũ���Դϴ�.
	 */
	float width_ = 0.0f;
	

	/**
	 * @brief �׶����� ���� ũ���Դϴ�.
	 */
	float height_ = 0.0f;


	/**
	 * @brief �׶����� ȸ�� �����Դϴ�.
	 */
	float rotate_ = 0.0f;


	/**
	 * @brief �׶����� ��ũ�� �ӵ��Դϴ�.
	 *
	 * @note
	 * - �� �ӵ��� �ʴ� �����̴� �ȼ� ���Դϴ�.
	 * - ���� ��� 200 �̶�� �ʴ� 200 �ȼ� ��ŭ �����Դϴ�.
	 */
	float scrollSpeed_ = 0.0f;


	/**
	 * @brief ��׶����� ��ũ�� �����Դϴ�.
	 */
	float scrollPosition_ = 0.0f;
};