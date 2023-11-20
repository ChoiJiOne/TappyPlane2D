#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

#include "IManager.h"
#include "IResource.h"
#include "SingletonMacro.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class Texture2D; // 텍스처를 사용하기 위한 전방 선언입니다.
class TTFont;    // 트루 타입 폰트를 사용하기 위한 전방 선언입니다.
class Window;    // 윈도우 클래스를 사용하기 위한 전방 선언입니다.


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
	 * @brief 스텐실 테스트 활성화 여부를 검사합니다.
	 * 
	 * @param bIsEnable 스텐실 테스트 활성화 여부입니다.
	 */
	void SetStencilMode(bool bIsEnable);


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


	/**
	 * @brief 화면에 2D 점들을 그립니다.
	 *
	 * @note 2D 점들의 개수는 MAX_VERTEX_SIZE(10000)의 크기를 넘을 수 없습니다.
	 * 
	 * @param positions 화면 상의 2D 점들입니다.
	 * @param color 점들의 RGB 색상입니다.
	 * @param pointSize 점의 크기입니다. 기본 값은 1.0f입니다.
	 */
	void DrawPoints2D(const std::vector<Vector2f>& positions, const Vector4f& color, float pointSize = 1.0f);


	/**
	 * @brief 화면에 점들을 연결한 2D 선을 그립니다.
	 *
	 * @note 2D 점들의 개수는 MAX_VERTEX_SIZE(10000)의 크기를 넘을 수 없습니다.
	 * 
	 * @param positions 화면 상의 2D 점들입니다.
	 * @param color 점들의 RGB 색상입니다.
	 */
	void DrawConnectPoints2D(const std::vector<Vector2f>& positions, const Vector4f& color);


	/**
	 * @brief 화면에 2D 선을 그립니다.
	 * 
	 * @param fromPosition 선의 시작점입니다.
	 * @param toPosition 선의 끝점입니다.
	 * @param color 선의 RGBA색상입니다.
	 */
	void DrawLine2D(const Vector2f& fromPosition, const Vector2f& toPosition, const Vector4f& color);


	/**
	 * @brief 화면에 2D 선을 그립니다.
	 * 
	 * @param fromPosition 선의 시작점입니다.
	 * @param fromColor 선의 시작점 색상입니다.
	 * @param toPosition 선의 끝점입니다.
	 * @param toColor 선의 끝점 색상입니다.
	 */
	void DrawLine2D(const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& toPosition, const Vector4f& toColor);


	/**
	 * @brief 화면에 2D 삼각형을 그립니다.
	 * 
	 * @param fromPosition 삼각형 시작 점입니다.
	 * @param byPosition 삼각형 중간 점입니다.
	 * @param toPosition 삼각형 끝 점입니다.
	 * @param color 삼각형의 RGBA색상입니다.
	 */
	void DrawTriangle2D(const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color);


	/**
	 * @brief 화면에 2D 삼각형을 그립니다.
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param fromPosition 삼각형 시작 점입니다.
	 * @param fromColor 삼각형 시작 점의 색상입니다.
	 * @param byPosition 삼각형 중간 점입니다.
	 * @param byColor 삼각형 중간 점의 색상입니다.
	 * @param toPosition 삼각형 끝 점입니다.
	 * @param toColor 삼각형 끝 점의 색상입니다.
	 */
	void DrawTriangle2D(
		const Vector2f& fromPosition, const Vector4f& fromColor,
		const Vector2f& byPosition, const Vector4f& byColor,
		const Vector2f& toPosition, const Vector4f& toColor
	);


	/**
	 * @brief 화면에 2D 와이어 프레임 삼각형을 그립니다.
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param fromPosition 삼각형 시작 점입니다.
	 * @param byPosition 삼각형 중간 점입니다.
	 * @param toPosition 삼각형 끝 점입니다.
	 * @param color 삼각형의 RGBA색상입니다.
	 */
	void DrawWireframeTriangle2D(const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color);


	/**
	 * @brief 화면에 2D 와이어 프레임 삼각형을 그립니다.
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param fromPosition 삼각형 시작 점입니다.
	 * @param fromColor 삼각형 시작 점의 색상입니다.
	 * @param byPosition 삼각형 중간 점입니다.
	 * @param byColor 삼각형 중간 점의 색상입니다.
	 * @param toPosition 삼각형 끝 점입니다.
	 * @param toColor 삼각형 끝 점의 색상입니다.
	 */
	void DrawWireframeTriangle2D(
		const Vector2f& fromPosition, const Vector4f& fromColor,
		const Vector2f& byPosition, const Vector4f& byColor,
		const Vector2f& toPosition, const Vector4f& toColor
	);


	/**
	 * @brief 화면에 2D 직사각형을 그립니다.
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param center 직사각형의 중심 좌표입니다.
	 * @param width 직사각형의 가로 크기입니다.
	 * @param heigt 직사각형의 세로 크기입니다.
	 * @param rotate 직사각형의 라디안 회전 각도입니다.
	 * @param color 직사각형의 색상입니다.
	 */
	void DrawRectangle2D(const Vector2f& center, float width, float height, float rotate, const Vector4f& color);


	/**
	 * @brief 화면에 2D 와이어 프레임 직사각형을 그립니다.
	 * 
	 * @param center 직사각형의 중심 좌표입니다.
	 * @param width 직사각형의 가로 크기입니다.
	 * @param heigt 직사각형의 세로 크기입니다.
	 * @param rotate 직사각형의 라디안 회전 각도입니다.
	 * @param color 직사각형의 색상입니다.
	 */
	void DrawWireframeRectangle2D(const Vector2f& center, float width, float height, float rotate, const Vector4f& color);


	/**
	 * @brief 화면에 2D 원을 그립니다.
	 * 
	 * @param center 원의 중심 좌표입니다.
	 * @param radius 원의 반지름 길이입니다.
	 * @param color 원의 색상입니다.
	 * @param sliceCount 원의 둘레 절단 횟수입니다. 기본 값은 300입니다.
	 */
	void DrawCircle2D(const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 화면에 2D 와이어 프레임 원을 그립니다.
	 *
	 * @param center 원의 중심 좌표입니다.
	 * @param radius 원의 반지름 길이입니다.
	 * @param color 원의 색상입니다.
	 * @param sliceCount 원 둘레의 절단 횟수입니다. 기본 값은 300입니다.
	 */
	void DrawWireframeCircle2D(const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 화면에 2D 타원을 그립니다.
	 * 
	 * @param center 타원의 중심 좌표입니다.
	 * @param xAxis 타원의 x축 길이입니다. 만약, 이 길이가 y축 길이보다 크다면 장축이 되고, 그렇지 않으면 단축이 됩니다.
	 * @param yAxis 타원의 y축 길이입니다. 만약, 이 길이가 x축 길이보다 크다면 장축이 되고, 그렇지 않으면 단축이 됩니다.
	 * @param color 타원의 색상입니다.
	 * @param sliceCount 타원 둘레의 절단 횟수입니다. 기본 값은 300입니다.
	 */
	void DrawEllipse2D(const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 화면에 2D 와이어 프레임 타원을 그립니다.
	 *
	 * @param center 타원의 중심 좌표입니다.
	 * @param xAxis 타원의 x축 길이입니다. 만약, 이 길이가 y축 길이보다 크다면 장축이 되고, 그렇지 않으면 단축이 됩니다.
	 * @param yAxis 타원의 y축 길이입니다. 만약, 이 길이가 x축 길이보다 크다면 장축이 되고, 그렇지 않으면 단축이 됩니다.
	 * @param color 타원의 색상입니다.
	 * @param sliceCount 타원 둘레의 절단 횟수입니다. 기본 값은 300입니다.
	 */
	void DrawWireframeEllipse2D(const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 화면에 2D 격자를 그립니다.
	 * 
	 * @param minX X좌표의 최소값입니다.
	 * @param maxX X좌표의 최댓값입니다.
	 * @param strideX 격차의 X축 방향으로의 간격입니다.
	 * @param minY Y좌표의 최소값입니다.
	 * @param maxY Y좌표의 최댓값입니다.
	 * @param strideY 격차의 Y축 방향으로의 간격입니다.
	 * @param color 격자의 색상입니다.
	 */
	void DrawGrid2D(float minX, float maxX, float strideX, float minY, float maxY, float strideY, const Vector4f& color);


	/**
	 * @brief 2D 텍스처를 화면에 그립니다.
	 *
	 * @param texture 텍스처 리소스입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 라디안 회전 각도입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void DrawTexture2D(Texture2D* texture, const Vector2f& center, float width, float height, float rotate, float transparent = 1.0f);


	/**
	 * @brief 2D 텍스처를 화면에 그립니다.
	 *
	 * @note 2D 텍스처를 윈도우 전체에 채워지도록 그립니다.
	 *
	 * @param texture 텍스처 리소스입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void DrawTexture2D(Texture2D* texture, float transparent = 1.0f);


	/**
	 * @brief 가로로 스크롤된 2D 텍스처를 그립니다.
	 *
	 * @note
	 * - 2D 텍스처를 윈도우 전체에 채워지도록 그립니다.
	 * - 텍스처 분할 비율은 다음과 같습니다.
	 * ┌────────────┬──────────────────┐
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │ 1.0f - rate│       rate       │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * └────────────┴──────────────────┘
	 *
	 * @param texture 텍스처 리소스입니다.
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void DrawHorizonScrollTexture2D(Texture2D* texture, float rate, float transparent = 1.0f);


	/**
	 * @brief 가로로 스크롤된 2D 텍스처를 그립니다.
	 *
	 * @note
	 * - 텍스처 분할 비율은 다음과 같습니다.
	 * ┌────────────┬──────────────────┐
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │ 1.0f - rate│       rate       │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * └────────────┴──────────────────┘
	 * 
	 * @param texture 텍스처 리소스입니다.
	 * @param center
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void DrawHorizonScrollTexture2D(Texture2D* texture, const Vector2f& center, float width, float height, float rate, float transparent = 1.0f);


	/**
	 * @brief 세로로 스크롤된 2D 텍스처를 그립니다.
	 *
	 * @note
	 * - 2D 텍스처를 윈도우 전체에 채워지도록 그립니다.
	 * - 텍스처 분할 비율은 다음과 같습니다.
	 * ┌─────────────────────────────┐
	 * │                             │
	 * │                             │
	 * │              rate           │
	 * │                             │
	 * ├─────────────────────────────┤
	 * │                             │
	 * │          1.0f - rate        │
	 * │                             │
	 * └─────────────────────────────┘
	 *
	 * @param texture 텍스처 리소스입니다.
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void DrawVerticalScrollTexture2D(Texture2D* texture, float rate, float transparent = 1.0f);


	/**
	 * @brief 세로로 스크롤된 2D 텍스처를 그립니다.
	 *
	 * @note
	 * - 텍스처 분할 비율은 다음과 같습니다.
	 * ┌─────────────────────────────┐
	 * │                             │
	 * │                             │
	 * │              rate           │
	 * │                             │
	 * ├─────────────────────────────┤
	 * │                             │
	 * │          1.0f - rate        │
	 * │                             │
	 * └─────────────────────────────┘
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param texture 텍스처 리소스입니다.
	 * @param center
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void DrawVerticalScrollTexture2D(Texture2D* texture, const Vector2f& center, float width, float height, float rate, float transparent = 1.0f);


	/**
	 * @brief 2D 텍스트를 화면에 그립니다.
	 * 
	 * @param font 폰트 리소스입니다.
	 * @param text 렌더링할 텍스트입니다.
	 * @param center 텍스트의 중심 좌표입니다.
	 * @param color 텍스트의 RGBA 색상입니다.
	 */
	void DrawText2D(TTFont* font, const std::wstring& text, const Vector2f& center, const Vector4f& color);


	/**
	 * @brief 2D 텍스처의 실루엣을 화면에 그립니다.
	 * 
	 * @param texture 텍스처 리소스입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 라디안 회전 각도입니다.
	 * @param silhouetteRGB 텍스처 실루엣의 색상입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f 입니다.
	 */
	void DrawTextureSilhouette2D(
		Texture2D* texture,
		const Vector2f& center,
		float width,
		float height,
		float rotate,
		const Vector3f& silhouetteRGB,
		float transparent = 1.0f
	);


	/**
	 * @brief 2D 텍스처를 아웃라인과 함께 화면에 그립니다.
	 * 
	 * @param texture 텍스처 리소스입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 라디안 회전 각도입니다.
	 * @param outline 텍스처 오브젝트 아웃라인의 색상입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void DrawTextureOutline2D(
		Texture2D* texture, 
		const Vector2f& center, 
		float width, 
		float height, 
		float rotate, 
		const Vector4f& outline,
		float transparent = 1.0f
	);


	/**
	 * @brief Inversion 후처리 효과를 적용합니다.
	 * 
	 * @note 한 프레임에 한 가지 효과만 적용할 수 있습니다.
	 */
	void PostEffectInversion();


	/**
	 * @brief RGB값의 평균으로 그레이 스케일 효과를 적용합니다.
	 */
	void PostEffectAverageGrayscale();


private:
	/**
	 * @brief 셰이더를 사용하기 위한 초기화를 수행합니다.
	 */
	void StartupShaders();

	
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


	/**
	 * @brief 현재 스크린의 가로 크기입니다.
	 */
	int32_t screenWidth_ = 0;


	/**
	 * @brief 현재 스크린의 세로 크기입니다.
	 */
	int32_t screenHeight_ = 0;


	/**
	 * @brief 현재 스크린에 대응하는 직교 투영 행렬입니다.
	 */
	Matrix4x4f screenOrtho_;


	/**
	 * @brief 프레임 버퍼에서 백버퍼로 전송했는지 확인합니다.
	 */
	bool bIsBlit_ = false;


	/**
	 * @brief 렌더링에 사용할 리소스입니다.
	 */
	std::unordered_map<std::string, IResource*> resourceMaps_;
};