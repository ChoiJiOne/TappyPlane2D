#pragma once

#include "IManager.h"
#include "Macro.h"
#include "SingletonMacro.h"


/**
 * @brief ��ü ������ �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class EngineManager : public IManager
{
	SINGLETON(EngineManager);


public:
	/**
	 * @brief ���� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ���� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Shutdown() override;
};