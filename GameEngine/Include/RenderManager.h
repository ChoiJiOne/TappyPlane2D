#pragma once

#include <cstdint>

#include "IManager.h"
#include "SingletonMacro.h"

class Window; // 윈도우 클래스를 사용하기 위한 전방 선언입니다.


/**
 * @brief 렌더링 처리를 수행하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class RenderManager : public IManager
{
	SINGLETON(RenderManager);


public:
	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 사용을 시작합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 사용을 종료합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 사용 전 설정을 수행합니다.
	 * 
	 * @note 
	 * - OpenGL이 3.3 이라면 major는 3, minor는 3입니다.
	 * - OpenGL이 4.6 이라면 major는 4, minor는 6입니다.
	 * 
	 * @param window 렌더링을 수행할 윈도우 포인터입니다.
	 * @param major OpenGL의 주 버전입니다.
	 * @param minor OpenGL의 부 버전입니다.
	 */
	void PreStartup(Window* window, int32_t major, int32_t minor);


private:
	/**
	 * @brief 렌더링을 수행할 윈도우입니다.
	 */
	Window* window_ = nullptr;


	/**
	 * @brief OpepGL의 주 버전입니다.
	 */
	int32_t major_ = 0;


	/**
	 * @brief OpenGL의 부 버전입니다.
	 */
	int32_t minor_ = 0;
};