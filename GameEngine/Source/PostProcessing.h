#pragma once

#include <array>

#include "Shader.h"
#include "Vertex.h"

class Framebuffer; // 프레임 버퍼를 사용하기 위한 전방 선언


/**
 * @brief 후처리 효과를 적용하는 셰이더입니다.
 * 
 * @note 셰이더를 상속하는 것들 중에 유일하게 작명 규칙을 따르지 않습니다. (ex. TextureShader2D, GeometryShader2D ...)
 */
class PostProcessing : public Shader
{
public:
	/**
	 * @brief 후처리 셰이더의 디폴트 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	PostProcessing() = default;


	/**
	 * @brief 후처리 셰이더의 가상 소멸자입니다.
	 *
	 * @note 셰이더의 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~PostProcessing();


	/**
	 * @brief 후처리 셰이더의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(PostProcessing);


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
	 * @brief 후처리 적용된 프레임 버퍼를 백버퍼에 전송합니다.
	 * 
	 * @param framebuffer 백버퍼에 전송할 프레임 버퍼입니다.
	 */
	void Blit(Framebuffer* framebuffer);


private:
	/**
	 * @brief 프레임 버퍼 정점 목록의 최대 크기입니다.
	 */
	static const int32_t MAX_VERTEX_SIZE = 6;


	/**
	 * @brief 프레임 버퍼의 정점 목록입니다.
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
