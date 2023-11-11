#pragma once

#include <cstdint>
#include <string>

#include "Macro.h"

typedef struct GLFWwindow GLFWwindow; // GLFWwindow를 사용하기 위한 전방 선언입니다.


/**
 * @brief GLFW 윈도우를 생성하고 관리합니다.
 * 
 * @note 이 윈도우 클래스는 GLFW를 기반으로 합니다.
 */
class Window
{
public:
	/**
	 * @brief 윈도우 생성을 위한 파라미터입니다.
	 */
	struct WindowCreationParam
	{
		std::string title;   // 윈도우 타이틀입니다.
		int32_t x;			 // 윈도우 위치의 X좌표 입니다.
		int32_t y;			 // 윈도우 위치의 Y좌표 입니다.
		int32_t width;		 // 윈도우의 가로 크기입니다.
		int32_t height;		 // 윈도우의 세로 크기입니다.
		bool bCanResize;	 // 윈도우 Resize 여부입니다.
	};


public:
	/**
	 * @brief 윈도우 창을 생성하고 관리하는 클래스의 기본 생성자입니다.
	 * 
	 * @note 반드시 클래스 내부 요소를 초기화하는 메서드를 호출해야 합니다.
	 */
	Window() = default;


	/**
	 * @brief 윈도우 창을 생성하고 관리하는 클래스의 가상 소멸자입니다.
	 */
	virtual ~Window();


	/**
	 * @brief 윈도우 창을 생성하고 관리하는 클래스의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Window);


	/**
	 * @brief 윈도우 창을 생성합니다.
	 *
	 * @param creationParam 윈도우 창 생성을 위한 파라미터입니다.
	 */
	void Create(const WindowCreationParam& creationParam);


	/**
	 * @brief 윈도우 창을 명시적으로 파괴합니다.
	 */
	void Destroy();


	/**
	 * @brief GLFW 윈도우 포인터 값을 얻습니다.
	 *
	 * @return GLFW 윈도우 포인터 값을 반환합니다.
	 */
	GLFWwindow* GetWindowPtr() { return window_; }


private:
	/**
	 * @brief GLFW 윈도우 포인터입니다.
	 */
	GLFWwindow* window_ = nullptr;
};