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


	/**
	 * @brief 프레임 렌더링을 시작합니다.
	 *
	 * @param red 색상 버퍼의 R 값입니다.
	 * @param green 색상 버퍼의 G 값입니다.
	 * @param blue 색상 버퍼의 B 값입니다.
	 * @param alpha 색상 버퍼의 A 값입니다.
	 * @param depth 깊이 버퍼의 초기화 값입니다.
	 * @param stencil 스텐실 버퍼의 초기화 값입니다.
	 */
	void BeginFrame(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);


	/**
	 * @brief 프레임 렌더링을 종료하고 백버퍼와 프론트버퍼를 스왑합니다.
	 */
	void EndFrame();


	/**
	 * @brief 수직 동기화 여부를 설정합니다.
	 *
	 * @param bIsEnable 수직 동기화 여부입니다.
	 */
	void SetVsyncMode(bool bIsEnable);


	/**
	 * @brief 깊이 테스트를 활성화 여부를 설정합니다.
	 *
	 * @param bIsEnable 깊이 테스트 활성화 여부입니다.
	 */
	void SetDepthMode(bool bIsEnable);


	/**
	 * @brief 알파 블랜딩을 활성화합니다.
	 *
	 * @param bIsEnable 알파 블랜딩 활성화 여부입니다.
	 */
	void SetAlphaBlend(bool bIsEnable);


	/**
	 * @brief 뷰포트를 설정합니다.
	 *
	 * @param x 뷰포트 사각형의 왼쪽 상단 x좌표입니다.
	 * @param y 뷰포트 사각형의 왼쪽 상단 y좌표입니다.
	 * @param width 뷰포트 사각형의 가로 크기입니다.
	 * @param height 뷰포트 사각형의 세로 크기입니다.
	 */
	void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);


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