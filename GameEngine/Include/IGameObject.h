#pragma once

#include "Macro.h"


/**
 * @brief ���� ���� ������Ʈ �������̽��Դϴ�.
 */
class IGameObject
{
public:
	/**
	 * @brief ���� ������Ʈ �������̽��� ����Ʈ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	IGameObject() = default;


	/**
	 * @brief ���� ������Ʈ �������̽��� ���� �Ҹ����Դϴ�.
	 * 
	 * @note ���� ������Ʈ ���ο��� �Ҵ�� ���ҽ��� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~IGameObject() {}


	/**
	 * @brief ���� ������Ʈ �������̽��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(IGameObject);


	/**
	 * @brief ���� ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 * 
	 * @note
	 * - ���� ������Ʈ �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 * - ��Ÿ �ð� ���� �ʴ����Դϴ�.
	 */
	virtual void Update(float deltaSeconds) = 0;


	/**
	 * @brief ���� ������Ʈ�� ȭ�鿡 �׸��ϴ�.
	 *
	 * @note ���� ������Ʈ �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Render() = 0;


	/**
	 * @brief ���� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 *
	 * @note ���� ������Ʈ �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Release() = 0;


	/**
	 * @brief ���� ������Ʈ�� �ʱ�ȭ�� ���� �ִ��� Ȯ���մϴ�.
	 *
	 * @return ���� ������Ʈ�� �ʱ�ȭ�� ���� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsInitialized() const { return bIsInitialized_; }


protected:
	/**
	 * @brief ���� ������Ʈ�� �ʱ�ȭ�Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsInitialized_ = false;
};