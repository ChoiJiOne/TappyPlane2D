#pragma once

#include "IManager.h"
#include "Macro.h"
#include "SingletonMacro.h"


/**
 * @brief ���� �� ���丮 ���� ó���� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class FileManager : public IManager
{
	SINGLETON(FileManager);


public:
	/**
	 * @brief ���� �� ���丮 ���� ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ���� �� ���丮 ���� ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Shutdown() override;
};
