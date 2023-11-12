#pragma once

#include <cstdint>

#include "IManager.h"
#include "SingletonMacro.h"

class Window; // ������ Ŭ������ ����ϱ� ���� ���� �����Դϴ�.


/**
 * @brief ������ ó���� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class RenderManager : public IManager
{
	SINGLETON(RenderManager);


public:
	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ��� �� ������ �����մϴ�.
	 * 
	 * @note 
	 * - OpenGL�� 3.3 �̶�� major�� 3, minor�� 3�Դϴ�.
	 * - OpenGL�� 4.6 �̶�� major�� 4, minor�� 6�Դϴ�.
	 * 
	 * @param window �������� ������ ������ �������Դϴ�.
	 * @param major OpenGL�� �� �����Դϴ�.
	 * @param minor OpenGL�� �� �����Դϴ�.
	 */
	void PreStartup(Window* window, int32_t major, int32_t minor);


private:
	/**
	 * @brief �������� ������ �������Դϴ�.
	 */
	Window* window_ = nullptr;


	/**
	 * @brief OpepGL�� �� �����Դϴ�.
	 */
	int32_t major_ = 0;


	/**
	 * @brief OpenGL�� �� �����Դϴ�.
	 */
	int32_t minor_ = 0;
};