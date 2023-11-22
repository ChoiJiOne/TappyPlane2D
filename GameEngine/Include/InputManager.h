#pragma once

#include <functional>
#include <unordered_map>

#include "IManager.h"
#include "SingletonMacro.h"

class Window; // 윈도우 클래스를 사용하기 위한 전방 선언입니다.


/**
 * @biref 입력 처리를 수행하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class InputManager : public IManager
{
	SINGLETON(InputManager);


public:
	/**
	 * @brief 입력 처리를 수행하는 매니저의 사용을 시작합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 입력 처리를 수행하는 매니저의 사용을 종료합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 입력 처리를 수행하는 매니저의 사용 전 설정을 수행합니다.
	 * 
	 * @param window 입력 처리를 수행할 윈도우 포인터입니다.
	 */
	void PreStartup(Window* window);


private:
	/**
	 * @brief 입력 처리를 수행할 윈도우입니다.
	 */
	Window* window_ = nullptr;
};