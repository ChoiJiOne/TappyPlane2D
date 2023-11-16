#pragma once

#include <array>

#include "Shader.h"
#include "Vertex.h"

class Texture2D; // Texture2D를 사용하기 위한 전방 선언입니다.


/**
 * @brief 2D 텍스처를 렌더링하는 셰이더입니다.
 * 
 * @note 
 * - 2D 텍스처 렌더링 시 기준이 되는 좌표계는 윈도우 좌표계입니다.
 * - 위치나 크기 관련 인자를 받지 않고 렌더링하는 메서드는 윈도우 화면 전체를 기준으로 합니다.
 */
class TextureShader2D : public Shader
{
public:
	/**
	 * @brief 2D 텍스처를 렌더링하는 셰이더의 디폴트 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	TextureShader2D() = default;


	/**
	 * @brief 2D 텍스처를 렌더링하는 셰이더의 가상 소멸자입니다.
	 *
	 * @note 셰이더의 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~TextureShader2D();


	/**
	 * @brief 2D 텍스처를 렌더링하는 셰이더의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(TextureShader2D);


	/**
	 * @brief GLSL 셰이더 소스 파일을 컴파일하고 셰이더 프로그램을 생성합니다.
	 *
	 * @param vsFile 버텍스 셰이더의 확장자(.vert)를 포함한 경로입니다.
	 * @param fsFile 프레그먼트 셰이더의 확장자(.frag)를 포함한 경로입니다.
	 * @param bCheckValid 셰이더 파일의 유효성 검사 여부입니다. 기본 값은 true입니다.
	 */
	virtual void Initialize(const std::string& vsPath, const std::string& fsPath, bool bCheckValid = true) override;


	/**
	 * @brief 셰이더의 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 2D 텍스처를 화면에 그립니다.
	 * 
	 * @param ortho 직교 투영 행렬입니다.
	 * @param texture 텍스처 리소스입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 라디안 회전 각도입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void DrawTexture2D(
		const Matrix4x4f& ortho,
		Texture2D* texture,
		const Vector2f& center,
		float width,
		float height,
		float rotate,
		float transparent = 1.0f
	);


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
	void DrawHorizonScrollTexture2D(
		const Matrix4x4f& ortho,
		Texture2D* texture,
		const Vector2f& center,
		float width,
		float height,
		float rotate,
		float rate, 
		float transparent = 1.0f
	);


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


private:
	/**
	 * @brief 버텍스 버퍼를 업데이트합니다.
	 */
	void UpdateVertexBuffer();


	/**
	 * @brief 텍스처 그리기를 수행합니다.
	 * 
	 * @param transform 변환 행렬입니다.
	 * @param ortho 투영 행렬입니다.
	 * @param texture 텍스처 리소스입니다.
	 * @param vertexCount 정점 수입니다.
	 * @param transparent 텍스처의 투명도입니다.
	 */
	void DrawTexture2D(const Matrix4x4f& transform, const Matrix4x4f& ortho, uint32_t vertexCount, Texture2D* texture, float transparent);


private:
	/**
	 * @brief 텍스처 정점 목록의 최대 크기입니다.
	 */
	static const int32_t MAX_VERTEX_SIZE = 12;


	/**
	 * @brief 텍스처의 정점 목록입니다.
	 */
	std::array<VertexPositionTexture, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief 정점 버퍼의 오브젝트입니다.
	 */
	uint32_t vertexBufferObject_ = 0;


	/**
	 * @brief 정점 버퍼 목록의 오브젝트입니다.
	 */
	uint32_t vertexArrayObject_ = 0;
};