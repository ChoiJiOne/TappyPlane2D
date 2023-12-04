#pragma once

#include <string>

#include "IGameObject.h"
#include "TTFont.h"
#include "Vector2.h"


/**
 * @brief ���콺 Ŭ���� �����ϴ� ������Ʈ�Դϴ�.
 */
class ClickTrigger : public IGameObject
{
public:
	/**
	 * @brief ���콺 Ŭ���� �����ϴ� ������Ʈ�� ����Ʈ �������Դϴ�.
	 */
	ClickTrigger() = default;


	/**
	 * @brief ���콺 Ŭ���� �����ϴ� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 * 
	 * @note ���콺 Ŭ���� �����ϴ� ������Ʈ ���ο��� �Ҵ�� ���ҽ��� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~ClickTrigger();


	/**
	 * @brief ���콺 Ŭ���� �����ϴ� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ClickTrigger);


	/**
	 * @brief ���콺 Ŭ���� �����ϴ� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 * 
	 * @param text Ŭ�� ���� ���θ� ǥ���� �� ����� �ؽ�Ʈ�Դϴ�.
	 * @param center Ŭ�� ���� ���θ� ǥ���� �� ����� �ؽ�Ʈ�� �߽� ��ġ�Դϴ�.
	 */
	void Initialize(const std::wstring& text, const Vector2f& center);


	/**
	 * @brief ���콺 Ŭ���� �����ϴ� ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief ���콺 Ŭ���� �����ϴ� ������Ʈ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ���콺 Ŭ���� �����ϴ� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief Ŭ���� ���� �Ǿ����� Ȯ���մϴ�.
	 * 
	 * @return Ŭ���� ���� �Ǿ��ٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsClick() const { return bIsClick_; }


private:
	/**
	 * @brief Ŭ�� ���� �����Դϴ�.
	 */
	bool bIsClick_ = false;


	/**
	 * @brief Ŭ�� ���� ���θ� ǥ���� �� ����� �ؽ�Ʈ�� ��Ʈ�Դϴ�.
	 */
	TTFont* font_ = nullptr;


	/**
	 * @brief Ŭ�� ���� ���θ� ǥ���� �� ����� �ؽ�Ʈ�Դϴ�.
	 */
	std::wstring text_;


	/**
	 * @brief �ؽ�Ʈ�� �߽� ��ġ�Դϴ�.
	 */
	Vector2f center_;
};