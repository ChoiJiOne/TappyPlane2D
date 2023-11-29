#pragma once

#include <map>

#include "IGameObject.h"
#include "TTFont.h"
#include "Vector2.h"
#include "Vector4.h"


/**
 * @brief �÷��̾��� ���ھ ǥ���ϴ� ������Ʈ�Դϴ�.
 */
class ScoreBoard : public IGameObject
{
public:
	/**
	 * @brief ���ھ� ���� ������Ʈ�� ����Ʈ �������Դϴ�.
	 */
	ScoreBoard() = default;


	/**
	 * @brief ���ھ� ���� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���ھ� ���� ������Ʈ ���ο��� �Ҵ�� ���ҽ��� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~ScoreBoard();


	/**
	 * @brief ���ھ� ���� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ScoreBoard);


	/**
	 * @brief ���ھ� ���� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 * 
	 * @param center ���ھ� ������ �߽� ��ǥ�Դϴ�.
	 * @param color ���ھ� ���� �ؽ�Ʈ�� �����Դϴ�.
	 */
	void Initialize(const Vector2f& center, const Vector4f& color);


	/**
	 * @brief ���ھ� ���� ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief ���ھ� ���� ������Ʈ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ���ھ� ���� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ���ھ� ���� Ȱ��ȭ ���θ� �����մϴ�.
	 *
	 * @param bIsActive ������ ���ھ� ���� Ȱ��ȭ �����Դϴ�.
	 */
	void SetActive(bool bIsActive) { bIsActive_ = bIsActive; }


	/**
	 * @brief ���ھ� ���� Ȱ��ȭ�� �Ǿ��ִ��� Ȯ���մϴ�.
	 *
	 * @return ���ھ� ���� Ȱ��ȭ�� �Ǿ� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsActive() const { return bIsActive_; }


	/**
	 * @brief ���ھ� ������ ���ھ �����ϴ� ��� �߰�
	 * 
	 * @param score ������ ���ھ� ���Դϴ�.
	 */
	void SetScore(const int32_t& score) { score_ = score; }


private:
	/**
	 * @brief ���ھ� ������ Ȱ��ȭ �����Դϴ�.
	 */
	bool bIsActive_ = false;


	/**
	 * @brief ���ھ� ������ �߽� ��ǥ�Դϴ�.
	 */
	Vector2f center_;


	/**
	 * @brief ǥ���� �����Դϴ�.
	 */
	int32_t score_ = 0;


	/**
	 * @brief ǥ���� ������ �����Դϴ�.
	 */
	Vector4f color_;


	/**
	 * @brief ���ھ� ������ ��Ʈ�Դϴ�.
	 */
	TTFont* font_ = nullptr;
};