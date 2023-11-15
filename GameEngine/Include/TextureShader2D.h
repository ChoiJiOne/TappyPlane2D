#pragma once

#include <array>

#include "Shader.h"
#include "Vertex.h"

class Texture2D; // Texture2D�� ����ϱ� ���� ���� �����Դϴ�.


/**
 * @brief 2D �ؽ�ó�� �������ϴ� ���̴��Դϴ�.
 * 
 * @note 2D �ؽ�ó ������ �� ������ �Ǵ� ��ǥ��� ������ ��ǥ���Դϴ�.
 */
class TextureShader2D : public Shader
{
public:
	/**
	 * @brief 2D �ؽ�ó�� �������ϴ� ���̴��� ����Ʈ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	TextureShader2D() = default;


	/**
	 * @brief 2D �ؽ�ó�� �������ϴ� ���̴��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���̴��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~TextureShader2D();


	/**
	 * @brief 2D �ؽ�ó�� �������ϴ� ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(TextureShader2D);


	/**
	 * @brief GLSL ���̴� �ҽ� ������ �������ϰ� ���̴� ���α׷��� �����մϴ�.
	 *
	 * @param vsFile ���ؽ� ���̴��� Ȯ����(.vert)�� ������ ����Դϴ�.
	 * @param fsFile �����׸�Ʈ ���̴��� Ȯ����(.frag)�� ������ ����Դϴ�.
	 * @param bCheckValid ���̴� ������ ��ȿ�� �˻� �����Դϴ�. �⺻ ���� true�Դϴ�.
	 */
	virtual void Initialize(const std::string& vsPath, const std::string& fsPath, bool bCheckValid = true) override;


	/**
	 * @brief ���̴��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief 2D �ؽ�ó�� ȭ�鿡 �׸��ϴ�.
	 * 
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param center �ؽ�ó�� �߽� ��ǥ�Դϴ�.
	 * @param width �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param height �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param rotate �ؽ�ó�� ���� ȸ�� �����Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
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


private:
	/**
	 * @brief ���ؽ� ���۸� ������Ʈ�մϴ�.
	 */
	void UpdateVertexBuffer();


private:
	/**
	 * @brief �ؽ�ó ���� ����� �ִ� ũ���Դϴ�.
	 */
	static const int32_t MAX_VERTEX_SIZE = 6;


	/**
	 * @brief �ؽ�ó�� ���� ����Դϴ�.
	 */
	std::array<VertexPositionTexture, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief ���� ������ ������Ʈ�Դϴ�.
	 */
	uint32_t vertexBufferObject_ = 0;


	/**
	 * @brief ���� ���� ����� ������Ʈ�Դϴ�.
	 */
	uint32_t vertexArrayObject_ = 0;
};