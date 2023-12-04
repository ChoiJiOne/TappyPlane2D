#pragma once

#include <string>

#include "IGameObject.h"
#include "TTFont.h"
#include "Vector2.h"


/**
 * @brief ���� Ÿ��Ʋ�Դϴ�.
 */
class MainTitle : public IGameObject
{
public:
	/**
	 * @brief ���� Ÿ��Ʋ�� ����Ʈ �������Դϴ�.
	 */
	MainTitle() = default;


	/**
	 * @brief ���� Ÿ��Ʋ�� ���� �Ҹ����Դϴ�.
	 * 
	 * @note ���� Ÿ��Ʋ ���ο��� �Ҵ�� ���ҽ��� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~MainTitle();


	/**
	 * @brief ���� Ÿ��Ʋ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(MainTitle);


	/**
	 * @brief ���� Ÿ��Ʋ�� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief ���� Ÿ��Ʋ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief ���� Ÿ��Ʋ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ���� Ÿ��Ʋ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief ���� Ÿ��Ʋ�� �߽� ��ġ�Դϴ�.
	 */
	Vector2f center_;


	/**
	 * @brief ���� Ÿ��Ʋ �ؽ�Ʈ�� ��Ʈ�Դϴ�.
	 */
	TTFont* font_ = nullptr;


	/**
	 * @brief ���� Ÿ��Ʋ�� �ؽ�Ʈ�Դϴ�.
	 */
	std::wstring titleText_;
};