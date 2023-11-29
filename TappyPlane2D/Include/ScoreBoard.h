#pragma once

#include <map>

#include "IGameObject.h"
#include "Texture2D.h"
#include "Vector2.h"


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
	 * @param numberWidth ǥ���� ������ ���� ũ���Դϴ�.
	 * @param numberHeight ǥ���� ������ ���� ũ���Դϴ�.
	 * @param numberGap ǥ���� ���� ���� �����Դϴ�.
	 */
	void Initialize(const Vector2f& center, const float& numberWidth, const float& numberHeight, const float& numberGap);


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
	 * @brief ǥ���� ������ ���� ũ���Դϴ�.
	 */
	float numberWidth_ = 0.0f;


	/**
	 * @brief ǥ���� ������ ���� ũ���Դϴ�.
	 */
	float numberHeight_ = 0.0f;


	/**
	 * @brief ǥ���� ���� ���� �� �����Դϴ�.
	 */
	float numberGap_ = 0.0f;


	/**
	 * @brief ������ �ؽ�ó ���ҽ��Դϴ�.
	 */
	std::map<char, Texture2D*> numberTextureMap_;
};