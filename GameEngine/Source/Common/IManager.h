#pragma once

#include "Common/Macro.h"


/**
 * @brief �Ŵ��� �������̽� �Դϴ�.
 *
 * @note ���̻�� �Ŵ������ ���� Ŭ������ �ݵ�� �� Ŭ������ ��ӹ޾ƾ� �մϴ�.
 */
class IManager
{
public:
	/**
	 * @brief �Ŵ��� �������̽��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(IManager);


	/**
	 * @brief �Ŵ��� �������̽��� ����� �����մϴ�.
	 *
	 * @note 
	 * - �� �������̽��� ��ӹ޴� ���� �Ŵ����� �ݵ�� �� �޼��带 �̿��ؼ� ����� �����ؾ� �մϴ�.
	 * - �� �������̽��� ��ӹ޴� ���� �Ŵ����� �� �޼��带 �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Shutdown() = 0;


	/**
	 * @brief �Ŵ����� �ʱ�ȭ�Ǿ����� Ȯ���մϴ�.
	 *
	 * @return �Ŵ����� �ʱ�ȭ �Ǿ��ٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsStartup() const { return bIsStartup; }


protected:
	/**
	 * @brief �Ŵ��� �������̽��� ����Ʈ �����ڿ� ���� �Ҹ����Դϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(IManager);


protected:
	/**
	 * @brief �Ŵ��� �������̽��� �ʱ�ȭ�Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsStartup = false;
};