#pragma once

#include "Macro.h"


/**
 * @brief �Ŵ��� �������̽��Դϴ�.
 * 
 * @note 
 * - ���̻�� �Ŵ������ ���� Ŭ������ �ݵ�� �� Ŭ������ ��ӹ޾ƾ� �մϴ�.
 * - �� Ŭ������ ��ӹ޴� Ŭ������ �̱������� �����Ǿ�� �մϴ�.
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
	 */
	virtual void Startup() = 0;


	/**
	 * @brief �Ŵ��� �������̽��� ����� �����մϴ�.
	 *
	 * @note 
	 * - ���α׷� ���� ���� �ݵ�� �� �޼��带 ȣ���ؾ� �մϴ�.
	 * - ���� Ŭ���������� �� �޼��带 ���� ���ҽ��� �����ؾ� �մϴ�.
	 */
	virtual void Shutdown() = 0;


protected:
	/**
	 * @brief �Ŵ��� �������̽��� ����Ʈ �����ڿ� ���� �Ҹ����Դϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(IManager);


protected:
	/**
	 * @brief �Ŵ��� �������̽��� ����� ���۵Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsStartup_ = false;
};