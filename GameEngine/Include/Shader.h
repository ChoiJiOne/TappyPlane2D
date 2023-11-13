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
 * @brief GLSL ���̴��� �������ϰ� ���̴� ���α׷��� �����մϴ�.
 */
class Shader : public IResource
{
public:
	/**
	 * @brief GLSL ���̴��� Ÿ���Դϴ�.
	 */
	enum class EType : int32_t
	{
		Vertex = 0x00,   // ���ؽ� ���̴��Դϴ�.
		Fragment = 0x01, // �����׸�Ʈ ���̴��Դϴ�.
	};


public:
	/**
	 * @brief ���̴��� ����Ʈ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Shader() = default;


	/**
	 * @brief ���̴��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���̴��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~Shader();


	/**
	 * @brief ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Shader);


	/**
	 * @brief GLSL ���̴� �ҽ� ������ �������ϰ� ���̴� ���α׷��� �����մϴ�.
	 * 
	 * @param vsFile ���ؽ� ���̴��� Ȯ����(.vert)�� ������ ����Դϴ�.
	 * @param fsFile �����׸�Ʈ ���̴��� Ȯ����(.frag)�� ������ ����Դϴ�.
	 * @param bCheckValid ���̴� ������ ��ȿ�� �˻� �����Դϴ�. �⺻ ���� true�Դϴ�.
	 */
	void Initialize(const std::string& vsPath, const std::string& fsPath, bool bCheckValid = true);


	/**
	 * @brief ���̴��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ���̴��� ���������ο� ���ε��մϴ�.
	 */
	void Bind();


	/**
	 * @brief ���̴��� ���ε� �����մϴ�.
	 */
	void Unbind();


	/**
	 * @brief ���̴� ���� boolean Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetBoolParameter(const std::string& name, bool value);


	/**
	 * @brief ���̴� ���� int Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetIntParameter(const std::string& name, int32_t value);


	/**
	 * @brief ���̴� ���� float Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetFloatParameter(const std::string& name, float value);


	/**
	 * @brief ���̴� ���� 2���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetVector2fParameter(const std::string& name, const Vector2f& value);


	/**
	 * @brief ���̴� ���� 2���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param x ������ ������ x ���Դϴ�.
	 * @param y ������ ������ y ���Դϴ�.
	 */
	void SetVector2fParameter(const std::string& name, float x, float y);


	/**
	 * @brief ���̴� ���� 2���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetVector2iParameter(const std::string& name, const Vector2i& value);


	/**
	 * @brief ���̴� ���� 2���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param x ������ ������ x ���Դϴ�.
	 * @param y ������ ������ y ���Դϴ�.
	 */
	void SetVector2iParameter(const std::string& name, int32_t x, int32_t y);


	/**
	 * @brief ���̴� ���� 3���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetVector3fParameter(const std::string& name, const Vector3f& value);


	/**
	 * @brief ���̴� ���� 3���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param x ������ ������ x ���Դϴ�.
	 * @param y ������ ������ y ���Դϴ�.
	 * @param z ������ ������ z ���Դϴ�.
	 */
	void SetVector3fParameter(const std::string& name, float x, float y, float z);


	/**
	 * @brief ���̴� ���� 3���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetVector3iParameter(const std::string& name, const Vector3i& value);


	/**
	 * @brief ���̴� ���� 3���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param x ������ ������ x ���Դϴ�.
	 * @param y ������ ������ y ���Դϴ�.
	 * @param z ������ ������ z ���Դϴ�.
	 */
	void SetVector3iParameter(const std::string& name, int32_t x, int32_t y, int32_t z);


	/**
	 * @brief ���̴� ���� 4���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetVector4fParameter(const std::string& name, const Vector4f& value);


	/**
	 * @brief ���̴� ���� 4���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param x ������ ������ x ���Դϴ�.
	 * @param y ������ ������ y ���Դϴ�.
	 * @param z ������ ������ z ���Դϴ�.
	 * @param w ������ ������ w ���Դϴ�.
	 */
	void SetVector4fParameter(const std::string& name, float x, float y, float z, float w);


	/**
	 * @brief ���̴� ���� 4���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetVector4iParameter(const std::string& name, const Vector4i& value);


	/**
	 * @brief ���̴� ���� 4���� ���� Ÿ���� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param x ������ ������ x ���Դϴ�.
	 * @param y ������ ������ y ���Դϴ�.
	 * @param z ������ ������ z ���Դϴ�.
	 * @param w ������ ������ w ���Դϴ�.
	 */
	void SetVector4iParameter(const std::string& name, int32_t x, int32_t y, int32_t z, int32_t w);


	/**
	 * @brief ���̴� ���� 2x2 Ÿ���� ��� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetMatrix2x2fParameter(const std::string& name, const Matrix2x2f& value);
		

	/**
	 * @brief ���̴� ���� 3x3 Ÿ���� ��� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetMatrix3x3fParameter(const std::string& name, const Matrix3x3f& value);


	/**
	 * @brief ���̴� ���� 4x4 Ÿ���� ��� ������ ������ �����մϴ�.
	 *
	 * @param name ������ ������ �̸��Դϴ�.
	 * @param value ������ ������ ���� ���Դϴ�.
	 */
	void SetMatrix4x4fParameter(const std::string& name, const Matrix4x4f& value);


protected:
	/**
	 * @brief ���̴� �� ������ ��ü�� ��ġ�� ����ϴ�.
	 *
	 * @param uniformName ��ġ�� ã�� ���̴� �� ������ �̸��Դϴ�.
	 *
	 * @return ���̴� �� ������ ��ü�� ��ġ�� ��ȯ�մϴ�. ã�� ���ϸ� -1�� ��ȯ�մϴ�.
	 *
	 * @see https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetUniformLocation.xhtml
	 */
	int32_t GetUniformLocation(const std::string& uniformName);


private:
	/**
	 * @brief ���̴� ������ ��ȿ���� �˻��մϴ�.
	 * 
	 * @param vsPath ��ȿ���� �˻��� ���ؽ� ���̴��� ����Դϴ�.
	 * @param fsPath ��ȿ���� �˻��� �����׸�Ʈ ���̴��� ����Դϴ�.
	 * 
	 * @return ���̴� ������ ��ȿ�ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool CheckValidShaderFile(const std::string& vsPath, const std::string& fsPath);


	/**
	 * @brief ���̴� ��ü�� �����ϰ� ���̴� �ҽ��� �������մϴ�.
	 *
	 * @note ���̴� ��ü ������ �����ϸ� 0�� �ƴ� ���� ��ȯ�մϴ�.
	 *
	 * @param type ���̴� Ÿ���Դϴ�.
	 * @param source ���̴� �ҽ��Դϴ�.
	 *
	 * @return �����ϵ� ���̴� ��ü�� ���̵� ��ȯ�մϴ�.
	 */
	uint32_t CreateAndCompileShader(const EType& type, const std::string& source);


private:
	/**
	 * @brief ���̴� ���� �α׸� ����ϱ� ���� ���ڿ� ������ �ִ� ũ���Դϴ�.
	 */
	static const int32_t MAX_BUFFER_SIZE = 1024;


	/**
	 * @brief ���̴� ���� �α׸� ����ϱ� ���� ���ڿ� �����Դϴ�.
	 */
	static char buffer_[MAX_BUFFER_SIZE];


	/**
	 * @brief ���̴� ���α׷��� ���̵��Դϴ�.
	 */
	uint32_t programID_ = 0;
};