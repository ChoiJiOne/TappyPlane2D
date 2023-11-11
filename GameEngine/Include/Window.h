#pragma once

#include <cstdint>
#include <string>

#include "Macro.h"

typedef struct GLFWwindow GLFWwindow; // GLFWwindow�� ����ϱ� ���� ���� �����Դϴ�.


/**
 * @brief GLFW �����츦 �����ϰ� �����մϴ�.
 * 
 * @note �� ������ Ŭ������ GLFW�� ������� �մϴ�.
 */
class Window
{
public:
	/**
	 * @brief ������ ������ ���� �Ķ�����Դϴ�.
	 */
	struct WindowCreationParam
	{
		std::string title;   // ������ Ÿ��Ʋ�Դϴ�.
		int32_t x;			 // ������ ��ġ�� X��ǥ �Դϴ�.
		int32_t y;			 // ������ ��ġ�� Y��ǥ �Դϴ�.
		int32_t width;		 // �������� ���� ũ���Դϴ�.
		int32_t height;		 // �������� ���� ũ���Դϴ�.
		bool bCanResize;	 // ������ Resize �����Դϴ�.
	};


public:
	/**
	 * @brief ������ â�� �����ϰ� �����ϴ� Ŭ������ �⺻ �������Դϴ�.
	 * 
	 * @note �ݵ�� Ŭ���� ���� ��Ҹ� �ʱ�ȭ�ϴ� �޼��带 ȣ���ؾ� �մϴ�.
	 */
	Window() = default;


	/**
	 * @brief ������ â�� �����ϰ� �����ϴ� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Window();


	/**
	 * @brief ������ â�� �����ϰ� �����ϴ� Ŭ������ ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Window);


	/**
	 * @brief ������ â�� �����մϴ�.
	 *
	 * @param creationParam ������ â ������ ���� �Ķ�����Դϴ�.
	 */
	void Create(const WindowCreationParam& creationParam);


	/**
	 * @brief ������ â�� ��������� �ı��մϴ�.
	 */
	void Destroy();


	/**
	 * @brief GLFW ������ ������ ���� ����ϴ�.
	 *
	 * @return GLFW ������ ������ ���� ��ȯ�մϴ�.
	 */
	GLFWwindow* GetWindowPtr() { return window_; }


private:
	/**
	 * @brief GLFW ������ �������Դϴ�.
	 */
	GLFWwindow* window_ = nullptr;
};