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


	/**
	 * @brief ������ �������� �����մϴ�.
	 *
	 * @param red ���� ������ R ���Դϴ�.
	 * @param green ���� ������ G ���Դϴ�.
	 * @param blue ���� ������ B ���Դϴ�.
	 * @param alpha ���� ������ A ���Դϴ�.
	 * @param depth ���� ������ �ʱ�ȭ ���Դϴ�.
	 * @param stencil ���ٽ� ������ �ʱ�ȭ ���Դϴ�.
	 */
	void BeginFrame(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);


	/**
	 * @brief ������ �������� �����ϰ� ����ۿ� ����Ʈ���۸� �����մϴ�.
	 */
	void EndFrame();


	/**
	 * @brief ���� ����ȭ ���θ� �����մϴ�.
	 *
	 * @param bIsEnable ���� ����ȭ �����Դϴ�.
	 */
	void SetVsyncMode(bool bIsEnable);


	/**
	 * @brief ���� �׽�Ʈ�� Ȱ��ȭ ���θ� �����մϴ�.
	 *
	 * @param bIsEnable ���� �׽�Ʈ Ȱ��ȭ �����Դϴ�.
	 */
	void SetDepthMode(bool bIsEnable);


	/**
	 * @brief ���� ������ Ȱ��ȭ�մϴ�.
	 *
	 * @param bIsEnable ���� ���� Ȱ��ȭ �����Դϴ�.
	 */
	void SetAlphaBlend(bool bIsEnable);


	/**
	 * @brief ����Ʈ�� �����մϴ�.
	 *
	 * @param x ����Ʈ �簢���� ���� ��� x��ǥ�Դϴ�.
	 * @param y ����Ʈ �簢���� ���� ��� y��ǥ�Դϴ�.
	 * @param width ����Ʈ �簢���� ���� ũ���Դϴ�.
	 * @param height ����Ʈ �簢���� ���� ũ���Դϴ�.
	 */
	void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);


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