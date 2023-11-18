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


	/**
	 * @brief ������ â�� ��ġ�� ����ϴ�.
	 * 
	 * @param outX ������ â�� X��ǥ�� ������ ���Դϴ�.
	 * @param outY ������ â�� Y��ǥ�� ������ ���Դϴ�.
	 */
	void GetPosition(int32_t& outX, int32_t& outY);


	/**
	 * @brief ������ â�� ��ġ�� �����մϴ�.
	 * 
	 * @param x ������ ��ġ�� X��ǥ�Դϴ�.
	 * @param y ������ ��ġ�� Y��ǥ�Դϴ�.
	 */
	void SetPosition(const int32_t& x, const int32_t& y);


	/**
	 * @brief ������ â�� ũ�⸦ ����ϴ�.
	 * 
	 * @param outWidth ������ â�� ���� ũ�⸦ ������ ���Դϴ�.
	 * @param outHeight ������ â�� ���� ũ�⸦ ������ ���Դϴ�.
	 */
	void GetSize(int32_t& outWidth, int32_t& outHeight);


	/**
	 * @brief ������ â�� ũ�⸦ �����մϴ�.
	 * 
	 * @param width ������ ���� ũ���Դϴ�.
	 * @param height ������ ���� ũ���Դϴ�.
	 */
	void SetSize(const int32_t& width, const int32_t& height);


private:
	/**
	 * @brief GLFW ������ �������Դϴ�.
	 */
	GLFWwindow* window_ = nullptr;
};