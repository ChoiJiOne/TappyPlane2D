#pragma once

#include <array>
#include <vector>

#include "Shader.h"
#include "Vertex.h"


/**
 * @brief 기본 도형을 렌더링하는 셰이더입니다.
 * 
 * @note
 * - 이 셰이더가 지원하는 기본 도형은 점, 선, 삼각형, 사각형, 원, 타원입니다. 
 * - 기본 도형 중 삼각형을 렌더링 할 때 삼각형의 방향은 오른손 기준 CCW입니다.
 * - 2차원 좌표계는 윈도우 좌표계를 기준으로 따릅니다.
 */
class GeometryShader2D : public Shader
{
public:
	/**
	 * @brief 기본 도형을 렌더링하는 셰이더의 디폴트 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	GeometryShader2D() = default;


	/**
	 * @brief 기본 도형을 렌더링하는 셰이더의 가상 소멸자입니다.
	 *
	 * @note 셰이더의 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~GeometryShader2D();


	/**
	 * @brief 기본 도형을 렌더링하는 셰이더의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GeometryShader2D);


	/**
	 * @brief GLSL 셰이더 소스 파일을 컴파일하고 셰이더 프로그램을 생성합니다.
	 *
	 * @param vsFile 버텍스 셰이더의 확장자(.vert)를 포함한 경로입니다.
	 * @param fsFile 프레그먼트 셰이더의 확장자(.frag)를 포함한 경로입니다.
	 * @param bCheckValid 셰이더 파일의 유효성 검사 여부입니다. 기본 값은 true입니다.
	 */
	virtual void Initialize(const std::string & vsPath, const std::string & fsPath, bool bCheckValid = true) override;


	/**
	 * @brief 셰이더의 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 화면에 2D 점들을 그립니다.
	 * 
	 * @note 2D 점들의 개수는 MAX_VERTEX_SIZE(10000)의 크기를 넘을 수 없습니다.
	 * 
	 * @param ortho 직교 투영 행렬입니다.
	 * @param positions 화면 상의 2D 점들입니다.
	 * @param color 점들의 RGB 색상입니다.
	 * @param pointSize 점의 크기입니다. 기본 값은 1.0f입니다.
	 */
	void DrawPoints2D(const Matrix4x4f& ortho, const std::vector<Vector2f>& positions, const Vector4f& color, float pointSize = 1.0f);


	/**
	 * @brief 화면에 2D 선을 그립니다.
	 * 
	 * @param ortho 직교 투영 행렬입니다.
	 * @param fromPosition 선의 시작점입니다.
	 * @param toPosition 선의 끝점입니다.
	 * @param color 선의 RGBA색상입니다.
	 */
	void DrawLine2D(const Matrix4x4f& ortho, const Vector2f& fromPosition, const Vector2f& toPosition, const Vector4f& color);


	/**
	 * @brief 화면에 2D 삼각형을 그립니다.
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param fromPosition 삼각형 시작 점입니다.
	 * @param byPosition 삼각형 중간 점입니다.
	 * @param toPosition 삼각형 끝 점입니다.
	 * @param color 삼각형의 RGBA색상입니다.
	 */
	void DrawTriangle2D(
		const Matrix4x4f& ortho,
		const Vector2f& fromPosition,
		const Vector2f& byPosition,
		const Vector2f& toPosition,
		const Vector4f& color
	);


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
		const Matrix4x4f& ortho,
		const Vector2f& fromPosition,
		const Vector4f& fromColor,
		const Vector2f& byPosition,
		const Vector4f& byColor,
		const Vector2f& toPosition,
		const Vector4f& toColor
	);

	
private:
	/**
	 * @brief 버텍스 버퍼를 업데이트합니다.
	 */
	void UpdateVertexBuffer();


private:
	/**
	 * @brief 도형 정점 목록의 최대 크기입니다.
	 */
	static const int32_t MAX_VERTEX_SIZE = 10000;


	/**
	 * @brief 도형의 정점 목록입니다.
	 */
	std::array<VertexPositionColor, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief 정점 버퍼의 오브젝트입니다.
	 */
	uint32_t vertexBufferObject_ = 0;


	/**
	 * @brief 정점 버퍼 목록의 오브젝트입니다.
	 */
	uint32_t vertexArrayObject_ = 0;
};