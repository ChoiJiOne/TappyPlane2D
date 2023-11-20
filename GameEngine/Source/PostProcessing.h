#pragma once

#include <array>

#include "Shader.h"
#include "Vertex.h"

class Framebuffer; // ������ ���۸� ����ϱ� ���� ���� ����


/**
 * @brief ��ó�� ȿ���� �����ϴ� ���̴��Դϴ�.
 * 
 * @note ���̴��� ����ϴ� �͵� �߿� �����ϰ� �۸� ��Ģ�� ������ �ʽ��ϴ�. (ex. TextureShader2D, GeometryShader2D ...)
 */
class PostProcessing : public Shader
{
public:
	/**
	 * @brief ��ó�� ���̴��� ����Ʈ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	PostProcessing() = default;


	/**
	 * @brief ��ó�� ���̴��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���̴��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~PostProcessing();


	/**
	 * @brief ��ó�� ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(PostProcessing);


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
	 * @brief ��ó�� ����� ������ ���۸� ����ۿ� �����մϴ�.
	 * 
	 * @param framebuffer ����ۿ� ������ ������ �����Դϴ�.
	 */
	void Blit(Framebuffer* framebuffer);


private:
	/**
	 * @brief ������ ���� ���� ����� �ִ� ũ���Դϴ�.
	 */
	static const int32_t MAX_VERTEX_SIZE = 6;


	/**
	 * @brief ������ ������ ���� ����Դϴ�.
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
