#pragma once

#include <string>

#include "IResource.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief GLSL 셰이더를 컴파일하고 셰이더 프로그램을 관리합니다.
 */
class Shader : public IResource
{
public:
	/**
	 * @brief GLSL 셰이더의 타입입니다.
	 */
	enum class EType : int32_t
	{
		Vertex = 0x00,   // 버텍스 셰이더입니다.
		Fragment = 0x01, // 프레그먼트 셰이더입니다.
	};


public:
	/**
	 * @brief 셰이더의 디폴트 생성자입니다.
	 * 
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	Shader() = default;


	/**
	 * @brief 셰이더의 가상 소멸자입니다.
	 *
	 * @note 셰이더의 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~Shader();


	/**
	 * @brief 셰이더의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Shader);


	/**
	 * @brief GLSL 셰이더 소스 파일을 컴파일하고 셰이더 프로그램을 생성합니다.
	 * 
	 * @param vsFile 버텍스 셰이더의 확장자(.vert)를 포함한 경로입니다.
	 * @param fsFile 프레그먼트 셰이더의 확장자(.frag)를 포함한 경로입니다.
	 * @param bCheckValid 셰이더 파일의 유효성 검사 여부입니다. 기본 값은 true입니다.
	 */
	virtual void Initialize(const std::string& vsPath, const std::string& fsPath, bool bCheckValid = true);


	/**
	 * @brief 셰이더의 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 셰이더를 파이프라인에 바인딩합니다.
	 */
	void Bind();


	/**
	 * @brief 셰이더를 바인딩 해제합니다.
	 */
	void Unbind();


	/**
	 * @brief 셰이더 내에 boolean 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetBoolParameter(const std::string& name, bool value);


	/**
	 * @brief 셰이더 내에 boolean 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetBoolParameter(const int32_t& location, bool value);


	/**
	 * @brief 셰이더 내에 int 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetIntParameter(const std::string& name, int32_t value);
	
	
	/**
	 * @brief 셰이더 내에 int 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetIntParameter(const int32_t& location, int32_t value);


	/**
	 * @brief 셰이더 내에 float 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetFloatParameter(const std::string& name, float value);


	/**
	 * @brief 셰이더 내에 float 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetFloatParameter(const int32_t& location, float value);


	/**
	 * @brief 셰이더 내에 2차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetVector2fParameter(const std::string& name, const Vector2f& value);


	/**
	 * @brief 셰이더 내에 2차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetVector2fParameter(const int32_t& location, const Vector2f& value);


	/**
	 * @brief 셰이더 내에 2차원 벡턴 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param x 유니폼 변수의 x 값입니다.
	 * @param y 유니폼 변수의 y 값입니다.
	 */
	void SetVector2fParameter(const std::string& name, float x, float y);


	/**
	 * @brief 셰이더 내에 2차원 벡턴 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param x 유니폼 변수의 x 값입니다.
	 * @param y 유니폼 변수의 y 값입니다.
	 */
	void SetVector2fParameter(const int32_t& location, float x, float y);


	/**
	 * @brief 셰이더 내에 2차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetVector2iParameter(const std::string& name, const Vector2i& value);


	/**
	 * @brief 셰이더 내에 2차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetVector2iParameter(const int32_t& location, const Vector2i& value);


	/**
	 * @brief 셰이더 내에 2차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param x 유니폼 변수의 x 값입니다.
	 * @param y 유니폼 변수의 y 값입니다.
	 */
	void SetVector2iParameter(const std::string& name, int32_t x, int32_t y);


	/**
	 * @brief 셰이더 내에 2차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param x 유니폼 변수의 x 값입니다.
	 * @param y 유니폼 변수의 y 값입니다.
	 */
	void SetVector2iParameter(const int32_t& location, int32_t x, int32_t y);


	/**
	 * @brief 셰이더 내에 3차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetVector3fParameter(const std::string& name, const Vector3f& value);


	/**
	 * @brief 셰이더 내에 3차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetVector3fParameter(const int32_t& location, const Vector3f& value);


	/**
	 * @brief 셰이더 내에 3차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param x 유니폼 변수의 x 값입니다.
	 * @param y 유니폼 변수의 y 값입니다.
	 * @param z 유니폼 변수의 z 값입니다.
	 */
	void SetVector3fParameter(const std::string& name, float x, float y, float z);


	/**
	 * @brief 셰이더 내에 3차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param x 유니폼 변수의 x 값입니다.
	 * @param y 유니폼 변수의 y 값입니다.
	 * @param z 유니폼 변수의 z 값입니다.
	 */
	void SetVector3fParameter(const int32_t& location, float x, float y, float z);


	/**
	 * @brief 셰이더 내에 3차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetVector3iParameter(const std::string& name, const Vector3i& value);


	/**
	 * @brief 셰이더 내에 3차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetVector3iParameter(const int32_t& location, const Vector3i& value);


	/**
	 * @brief 셰이더 내에 3차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param x 유니폼 변수의 x 값입니다.
	 * @param y 유니폼 변수의 y 값입니다.
	 * @param z 유니폼 변수의 z 값입니다.
	 */
	void SetVector3iParameter(const std::string& name, int32_t x, int32_t y, int32_t z);


	/**
	 * @brief 셰이더 내에 3차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param x 유니폼 변수의 x 값입니다.
	 * @param y 유니폼 변수의 y 값입니다.
	 * @param z 유니폼 변수의 z 값입니다.
	 */
	void SetVector3iParameter(const int32_t& location, int32_t x, int32_t y, int32_t z);


	/**
	 * @brief 셰이더 내에 4차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetVector4fParameter(const std::string& name, const Vector4f& value);


	/**
	 * @brief 셰이더 내에 4차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetVector4fParameter(const int32_t& location, const Vector4f& value);


	/**
	 * @brief 셰이더 내에 4차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param x 유니폼 변수의 x 값입니다.
	 * @param y 유니폼 변수의 y 값입니다.
	 * @param z 유니폼 변수의 z 값입니다.
	 * @param w 유니폼 변수의 w 값입니다.
	 */
	void SetVector4fParameter(const std::string& name, float x, float y, float z, float w);


	/**
	 * @brief 셰이더 내에 4차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param x 유니폼 변수의 x 값입니다.
	 * @param y 유니폼 변수의 y 값입니다.
	 * @param z 유니폼 변수의 z 값입니다.
	 * @param w 유니폼 변수의 w 값입니다.
	 */
	void SetVector4fParameter(const int32_t& location, float x, float y, float z, float w);


	/**
	 * @brief 셰이더 내에 4차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetVector4iParameter(const std::string& name, const Vector4i& value);


	/**
	 * @brief 셰이더 내에 4차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetVector4iParameter(const int32_t& location, const Vector4i& value);


	/**
	 * @brief 셰이더 내에 4차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param x 유니폼 변수의 x 값입니다.
	 * @param y 유니폼 변수의 y 값입니다.
	 * @param z 유니폼 변수의 z 값입니다.
	 * @param w 유니폼 변수의 w 값입니다.
	 */
	void SetVector4iParameter(const std::string& name, int32_t x, int32_t y, int32_t z, int32_t w);


	/**
	 * @brief 셰이더 내에 4차원 벡터 타입의 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param x 유니폼 변수의 x 값입니다.
	 * @param y 유니폼 변수의 y 값입니다.
	 * @param z 유니폼 변수의 z 값입니다.
	 * @param w 유니폼 변수의 w 값입니다.
	 */
	void SetVector4iParameter(const int32_t& location, int32_t x, int32_t y, int32_t z, int32_t w);


	/**
	 * @brief 셰이더 내에 2x2 타입의 행렬 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetMatrix2x2fParameter(const std::string& name, const Matrix2x2f& value);


	/**
	 * @brief 셰이더 내에 2x2 타입의 행렬 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetMatrix2x2fParameter(const int32_t& location, const Matrix2x2f& value);
		

	/**
	 * @brief 셰이더 내에 3x3 타입의 행렬 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetMatrix3x3fParameter(const std::string& name, const Matrix3x3f& value);


	/**
	 * @brief 셰이더 내에 3x3 타입의 행렬 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetMatrix3x3fParameter(const int32_t& location, const Matrix3x3f& value);


	/**
	 * @brief 셰이더 내에 4x4 타입의 행렬 유니폼 변수를 설정합니다.
	 *
	 * @param name 유니폼 변수의 이름입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetMatrix4x4fParameter(const std::string& name, const Matrix4x4f& value);


	/**
	 * @brief 셰이더 내에 4x4 타입의 행렬 유니폼 변수를 설정합니다.
	 *
	 * @param location 셰이더 내의 유니폼 변수의 위치입니다.
	 * @param value 유니폼 변수의 설정 값입니다.
	 */
	void SetMatrix4x4fParameter(const int32_t& location, const Matrix4x4f& value);


protected:
	/**
	 * @brief 셰이더 내 유니폼 객체의 위치를 얻습니다.
	 *
	 * @param uniformName 위치를 찾을 셰이더 내 유니폼 이름입니다.
	 *
	 * @return 셰이더 내 유니폼 객체의 위치를 반환합니다. 찾지 못하면 -1을 반환합니다.
	 *
	 * @see https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetUniformLocation.xhtml
	 */
	int32_t GetUniformLocation(const std::string& uniformName);


	/**
	 * @brief 다이나믹 버텍스 버퍼를 업데이트합니다.
	 * 
	 * @param vertexBufferID 업데이트할 버텍스 버퍼의 ID입니다.
	 * @param vertexPtr 업데이트할 버텍스 버퍼의 포인터입니다.
	 * @param bufferByteSize 버텍스 버퍼의 바이트 크기입니다.
	 */
	void UpdateDynamicVertexBuffer(uint32_t vertexBufferID, const void* vertexPtr, uint32_t bufferByteSize);


private:
	/**
	 * @brief 셰이더 파일의 유효성을 검사합니다.
	 * 
	 * @param vsPath 유효성을 검사할 버텍스 셰이더의 경로입니다.
	 * @param fsPath 유효성을 검사할 프레그먼트 셰이더의 경로입니다.
	 * 
	 * @return 셰이더 파일이 유효하다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool CheckValidShaderFile(const std::string& vsPath, const std::string& fsPath);


	/**
	 * @brief 셰이더 객체를 생성하고 셰이더 소스를 컴파일합니다.
	 *
	 * @note 셰이더 객체 생성에 성공하면 0이 아닌 값을 반환합니다.
	 *
	 * @param type 셰이더 타입입니다.
	 * @param source 셰이더 소스입니다.
	 *
	 * @return 컴파일된 셰이더 객체의 아이디를 반환합니다.
	 */
	uint32_t CreateAndCompileShader(const EType& type, const std::string& source);


private:
	/**
	 * @brief 셰이더 관련 로그를 기록하기 위한 문자열 버퍼의 최대 크기입니다.
	 */
	static const int32_t MAX_BUFFER_SIZE = 1024;


	/**
	 * @brief 셰이더 관련 로그를 기록하기 위한 문자열 버퍼입니다.
	 */
	static char buffer_[MAX_BUFFER_SIZE];


	/**
	 * @brief 셰이더 프로그램의 아이디입니다.
	 */
	uint32_t programID_ = 0;
};