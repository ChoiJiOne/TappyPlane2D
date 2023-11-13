#pragma once

#include <array>
#include <vector>

#include "Shader.h"
#include "Vertex.h"


/**
 * @brief �⺻ ������ �������ϴ� ���̴��Դϴ�.
 * 
 * @note
 * - �� ���̴��� �����ϴ� �⺻ ������ ��, ��, �ﰢ��, �簢��, ��, Ÿ���Դϴ�. 
 * - �⺻ ���� �� �ﰢ���� ������ �� �� �ﰢ���� ������ ������ ���� CCW�Դϴ�.
 * - 2���� ��ǥ��� ������ ��ǥ�踦 �������� �����ϴ�.
 */
class GeometryShader2D : public Shader
{
public:
	/**
	 * @brief �⺻ ������ �������ϴ� ���̴��� ����Ʈ �������Դϴ�.
	 *
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	GeometryShader2D() = default;


	/**
	 * @brief �⺻ ������ �������ϴ� ���̴��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���̴��� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~GeometryShader2D();


	/**
	 * @brief �⺻ ������ �������ϴ� ���̴��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GeometryShader2D);


	/**
	 * @brief GLSL ���̴� �ҽ� ������ �������ϰ� ���̴� ���α׷��� �����մϴ�.
	 *
	 * @param vsFile ���ؽ� ���̴��� Ȯ����(.vert)�� ������ ����Դϴ�.
	 * @param fsFile �����׸�Ʈ ���̴��� Ȯ����(.frag)�� ������ ����Դϴ�.
	 * @param bCheckValid ���̴� ������ ��ȿ�� �˻� �����Դϴ�. �⺻ ���� true�Դϴ�.
	 */
	virtual void Initialize(const std::string & vsPath, const std::string & fsPath, bool bCheckValid = true) override;


	/**
	 * @brief ���̴��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ȭ�鿡 2D ������ �׸��ϴ�.
	 * 
	 * @note 2D ������ ������ MAX_VERTEX_SIZE(10000)�� ũ�⸦ ���� �� �����ϴ�.
	 * 
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param positions ȭ�� ���� 2D �����Դϴ�.
	 * @param color ������ RGB �����Դϴ�.
	 * @param pointSize ���� ũ���Դϴ�. �⺻ ���� 1.0f�Դϴ�.
	 */
	void DrawPoints2D(const Matrix4x4f& ortho, const std::vector<Vector2f>& positions, const Vector4f& color, float pointSize = 1.0f);


	/**
	 * @brief ȭ�鿡 2D ���� �׸��ϴ�.
	 * 
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param fromPosition ���� �������Դϴ�.
	 * @param toPosition ���� �����Դϴ�.
	 * @param color ���� RGBA�����Դϴ�.
	 */
	void DrawLine2D(const Matrix4x4f& ortho, const Vector2f& fromPosition, const Vector2f& toPosition, const Vector4f& color);


	/**
	 * @brief ȭ�鿡 2D �ﰢ���� �׸��ϴ�.
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param fromPosition �ﰢ�� ���� ���Դϴ�.
	 * @param byPosition �ﰢ�� �߰� ���Դϴ�.
	 * @param toPosition �ﰢ�� �� ���Դϴ�.
	 * @param color �ﰢ���� RGBA�����Դϴ�.
	 */
	void DrawTriangle2D(
		const Matrix4x4f& ortho,
		const Vector2f& fromPosition,
		const Vector2f& byPosition,
		const Vector2f& toPosition,
		const Vector4f& color
	);


	/**
	 * @brief ȭ�鿡 2D �ﰢ���� �׸��ϴ�.
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param fromPosition �ﰢ�� ���� ���Դϴ�.
	 * @param fromColor �ﰢ�� ���� ���� �����Դϴ�.
	 * @param byPosition �ﰢ�� �߰� ���Դϴ�.
	 * @param byColor �ﰢ�� �߰� ���� �����Դϴ�.
	 * @param toPosition �ﰢ�� �� ���Դϴ�.
	 * @param toColor �ﰢ�� �� ���� �����Դϴ�.
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
	 * @brief ���ؽ� ���۸� ������Ʈ�մϴ�.
	 */
	void UpdateVertexBuffer();


private:
	/**
	 * @brief ���� ���� ����� �ִ� ũ���Դϴ�.
	 */
	static const int32_t MAX_VERTEX_SIZE = 10000;


	/**
	 * @brief ������ ���� ����Դϴ�.
	 */
	std::array<VertexPositionColor, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief ���� ������ ������Ʈ�Դϴ�.
	 */
	uint32_t vertexBufferObject_ = 0;


	/**
	 * @brief ���� ���� ����� ������Ʈ�Դϴ�.
	 */
	uint32_t vertexArrayObject_ = 0;
};