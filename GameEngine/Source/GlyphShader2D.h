#pragma once

#include <array>

#include "Shader.h"
#include "Vertex.h"

class TTFont; // TTFont를 사용하기 위한 전방 선언입니다.


/**
 * @brief 글리프를 이용해서 텍스트를 렌더링하는 셰이더입니다.
 * 
 * @note
 * - 2D 텍스트 렌더링 시 기준이 되는 좌표계는 윈도우 좌표계입니다.
 */
class GlyphShader2D : public Shader
{
public:
	/**
	 * @brief 2D 텍스트를 렌더링하는 셰이더의 디폴트 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	GlyphShader2D() = default;


	/**
	 * @brief 2D 텍스트를 렌더링하는 셰이더의 가상 소멸자입니다.
	 *
	 * @note 셰이더의 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~GlyphShader2D();


	/**
	 * @brief 2D 텍스트를 렌더링하는 셰이더의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GlyphShader2D);


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
	 * @brief 2D 텍스트를 화면에 그립니다.
	 * 
	 * @param ortho 직교 투영 행렬입니다.
	 * @param font 폰트 리소스입니다.
	 * @param text 렌더링할 텍스트입니다.
	 * @param center 텍스트의 중심 좌표입니다.
	 * @param color 텍스트의 RGBA 색상입니다.
	 */
	void DrawText2D(const Matrix4x4f& ortho, const TTFont* font, const std::wstring& text, const Vector2f& center, const Vector4f& color);


private:
	/**
	 * @brief 텍스트에 맞게 버텍스 버퍼를 업데이트합니다.
	 * 
	 * @param font 폰트 리소스입니다.
	 * @param text 렌더링할 텍스트입니다.
	 * @param center 텍스트의 중심 좌표입니다.
	 * 
	 * @return 텍스트에 맞는 버텍스의 수를 반환합니다.
	 */
	uint32_t UpdateGlyphVertexBuffer(const TTFont* font, const std::wstring& text, const Vector2f& center);


private:
	/**
	 * @brief 최대 문자열의 길이입니다.
	 */
	static const int32_t MAX_STRING_LEN = 1000;


	/**
	 * @brief 글리프 정점 목록의 최대 크기입니다.
	 * 
	 * @note
	 * - 문자 하나 그리는 데 필요한 정점의 수 : 6개
	 * - 만약, 최대 문자열의 길이가 1000이라면, 필요한 정점의 수 : 6 X 1000 = 6000개
	 * - 즉, 이 글리프 셰이더가 지원하는 최대 문자열의 길이는 1000이다.
	 */
	static const int32_t MAX_VERTEX_SIZE = MAX_STRING_LEN * 6;
	

	/**
	 * @brief 정점 목록입니다.
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


	/**
	 * @brief 스크린 직교 투영 행렬을 나타내는 유니폼 변수의 위치입니다.
	 */
	int32_t orthoLocation_ = -1;


	/**
	 * @brief 글리프의 색상을 나타내는 유니폼 변수의 위치입니다.
	 */
	int32_t glyphColorLocation_ = -1;
};