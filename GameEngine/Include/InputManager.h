#pragma once

#include <functional>
#include <unordered_map>

#include "IManager.h"
#include "SingletonMacro.h"

class Window; // ������ Ŭ������ ����ϱ� ���� ���� �����Դϴ�.


/**
 * @biref �Է� ó���� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class InputManager : public IManager
{
	SINGLETON(InputManager);


public:
	/**
	 * @brief �Է� ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief �Է� ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Shutdown() override;
};