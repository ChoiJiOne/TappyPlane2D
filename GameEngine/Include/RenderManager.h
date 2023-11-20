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

class Texture2D; // �ؽ�ó�� ����ϱ� ���� ���� �����Դϴ�.
class TTFont;    // Ʈ�� Ÿ�� ��Ʈ�� ����ϱ� ���� ���� �����Դϴ�.
class Window;    // ������ Ŭ������ ����ϱ� ���� ���� �����Դϴ�.


/**
 * @brief ������ ó���� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class RenderManager : public IManager
{
	SINGLETON(RenderManager);


public:
	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ��� �� ������ �����մϴ�.
	 * 
	 * @note 
	 * - OpenGL�� 3.3 �̶�� major�� 3, minor�� 3�Դϴ�.
	 * - OpenGL�� 4.6 �̶�� major�� 4, minor�� 6�Դϴ�.
	 * 
	 * @param window �������� ������ ������ �������Դϴ�.
	 * @param major OpenGL�� �� �����Դϴ�.
	 * @param minor OpenGL�� �� �����Դϴ�.
	 */
	void PreStartup(Window* window, int32_t major, int32_t minor);


	/**
	 * @brief ������ �������� �����մϴ�.
	 *
	 * @param red ���� ������ R ���Դϴ�.
	 * @param green ���� ������ G ���Դϴ�.
	 * @param blue ���� ������ B ���Դϴ�.
	 * @param alpha ���� ������ A ���Դϴ�.
	 * @param depth ���� ������ �ʱ�ȭ ���Դϴ�.
	 * @param stencil ���ٽ� ������ �ʱ�ȭ ���Դϴ�.
	 */
	void BeginFrame(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);


	/**
	 * @brief ������ �������� �����ϰ� ����ۿ� ����Ʈ���۸� �����մϴ�.
	 */
	void EndFrame();


	/**
	 * @brief ���� ����ȭ ���θ� �����մϴ�.
	 *
	 * @param bIsEnable ���� ����ȭ �����Դϴ�.
	 */
	void SetVsyncMode(bool bIsEnable);


	/**
	 * @brief ���� �׽�Ʈ�� Ȱ��ȭ ���θ� �����մϴ�.
	 *
	 * @param bIsEnable ���� �׽�Ʈ Ȱ��ȭ �����Դϴ�.
	 */
	void SetDepthMode(bool bIsEnable);


	/**
	 * @brief ���ٽ� �׽�Ʈ Ȱ��ȭ ���θ� �˻��մϴ�.
	 * 
	 * @param bIsEnable ���ٽ� �׽�Ʈ Ȱ��ȭ �����Դϴ�.
	 */
	void SetStencilMode(bool bIsEnable);


	/**
	 * @brief ���� ������ Ȱ��ȭ�մϴ�.
	 *
	 * @param bIsEnable ���� ���� Ȱ��ȭ �����Դϴ�.
	 */
	void SetAlphaBlend(bool bIsEnable);


	/**
	 * @brief ����Ʈ�� �����մϴ�.
	 *
	 * @param x ����Ʈ �簢���� ���� ��� x��ǥ�Դϴ�.
	 * @param y ����Ʈ �簢���� ���� ��� y��ǥ�Դϴ�.
	 * @param width ����Ʈ �簢���� ���� ũ���Դϴ�.
	 * @param height ����Ʈ �簢���� ���� ũ���Դϴ�.
	 */
	void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);


	/**
	 * @brief ȭ�鿡 2D ������ �׸��ϴ�.
	 *
	 * @note 2D ������ ������ MAX_VERTEX_SIZE(10000)�� ũ�⸦ ���� �� �����ϴ�.
	 * 
	 * @param positions ȭ�� ���� 2D �����Դϴ�.
	 * @param color ������ RGB �����Դϴ�.
	 * @param pointSize ���� ũ���Դϴ�. �⺻ ���� 1.0f�Դϴ�.
	 */
	void DrawPoints2D(const std::vector<Vector2f>& positions, const Vector4f& color, float pointSize = 1.0f);


	/**
	 * @brief ȭ�鿡 ������ ������ 2D ���� �׸��ϴ�.
	 *
	 * @note 2D ������ ������ MAX_VERTEX_SIZE(10000)�� ũ�⸦ ���� �� �����ϴ�.
	 * 
	 * @param positions ȭ�� ���� 2D �����Դϴ�.
	 * @param color ������ RGB �����Դϴ�.
	 */
	void DrawConnectPoints2D(const std::vector<Vector2f>& positions, const Vector4f& color);


	/**
	 * @brief ȭ�鿡 2D ���� �׸��ϴ�.
	 * 
	 * @param fromPosition ���� �������Դϴ�.
	 * @param toPosition ���� �����Դϴ�.
	 * @param color ���� RGBA�����Դϴ�.
	 */
	void DrawLine2D(const Vector2f& fromPosition, const Vector2f& toPosition, const Vector4f& color);


	/**
	 * @brief ȭ�鿡 2D ���� �׸��ϴ�.
	 * 
	 * @param fromPosition ���� �������Դϴ�.
	 * @param fromColor ���� ������ �����Դϴ�.
	 * @param toPosition ���� �����Դϴ�.
	 * @param toColor ���� ���� �����Դϴ�.
	 */
	void DrawLine2D(const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& toPosition, const Vector4f& toColor);


	/**
	 * @brief ȭ�鿡 2D �ﰢ���� �׸��ϴ�.
	 * 
	 * @param fromPosition �ﰢ�� ���� ���Դϴ�.
	 * @param byPosition �ﰢ�� �߰� ���Դϴ�.
	 * @param toPosition �ﰢ�� �� ���Դϴ�.
	 * @param color �ﰢ���� RGBA�����Դϴ�.
	 */
	void DrawTriangle2D(const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color);


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
		const Vector2f& fromPosition, const Vector4f& fromColor,
		const Vector2f& byPosition, const Vector4f& byColor,
		const Vector2f& toPosition, const Vector4f& toColor
	);


	/**
	 * @brief ȭ�鿡 2D ���̾� ������ �ﰢ���� �׸��ϴ�.
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param fromPosition �ﰢ�� ���� ���Դϴ�.
	 * @param byPosition �ﰢ�� �߰� ���Դϴ�.
	 * @param toPosition �ﰢ�� �� ���Դϴ�.
	 * @param color �ﰢ���� RGBA�����Դϴ�.
	 */
	void DrawWireframeTriangle2D(const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color);


	/**
	 * @brief ȭ�鿡 2D ���̾� ������ �ﰢ���� �׸��ϴ�.
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param fromPosition �ﰢ�� ���� ���Դϴ�.
	 * @param fromColor �ﰢ�� ���� ���� �����Դϴ�.
	 * @param byPosition �ﰢ�� �߰� ���Դϴ�.
	 * @param byColor �ﰢ�� �߰� ���� �����Դϴ�.
	 * @param toPosition �ﰢ�� �� ���Դϴ�.
	 * @param toColor �ﰢ�� �� ���� �����Դϴ�.
	 */
	void DrawWireframeTriangle2D(
		const Vector2f& fromPosition, const Vector4f& fromColor,
		const Vector2f& byPosition, const Vector4f& byColor,
		const Vector2f& toPosition, const Vector4f& toColor
	);


	/**
	 * @brief ȭ�鿡 2D ���簢���� �׸��ϴ�.
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param center ���簢���� �߽� ��ǥ�Դϴ�.
	 * @param width ���簢���� ���� ũ���Դϴ�.
	 * @param heigt ���簢���� ���� ũ���Դϴ�.
	 * @param rotate ���簢���� ���� ȸ�� �����Դϴ�.
	 * @param color ���簢���� �����Դϴ�.
	 */
	void DrawRectangle2D(const Vector2f& center, float width, float height, float rotate, const Vector4f& color);


	/**
	 * @brief ȭ�鿡 2D ���̾� ������ ���簢���� �׸��ϴ�.
	 * 
	 * @param center ���簢���� �߽� ��ǥ�Դϴ�.
	 * @param width ���簢���� ���� ũ���Դϴ�.
	 * @param heigt ���簢���� ���� ũ���Դϴ�.
	 * @param rotate ���簢���� ���� ȸ�� �����Դϴ�.
	 * @param color ���簢���� �����Դϴ�.
	 */
	void DrawWireframeRectangle2D(const Vector2f& center, float width, float height, float rotate, const Vector4f& color);


	/**
	 * @brief ȭ�鿡 2D ���� �׸��ϴ�.
	 * 
	 * @param center ���� �߽� ��ǥ�Դϴ�.
	 * @param radius ���� ������ �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 * @param sliceCount ���� �ѷ� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void DrawCircle2D(const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief ȭ�鿡 2D ���̾� ������ ���� �׸��ϴ�.
	 *
	 * @param center ���� �߽� ��ǥ�Դϴ�.
	 * @param radius ���� ������ �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 * @param sliceCount �� �ѷ��� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void DrawWireframeCircle2D(const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief ȭ�鿡 2D Ÿ���� �׸��ϴ�.
	 * 
	 * @param center Ÿ���� �߽� ��ǥ�Դϴ�.
	 * @param xAxis Ÿ���� x�� �����Դϴ�. ����, �� ���̰� y�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param yAxis Ÿ���� y�� �����Դϴ�. ����, �� ���̰� x�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param color Ÿ���� �����Դϴ�.
	 * @param sliceCount Ÿ�� �ѷ��� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void DrawEllipse2D(const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief ȭ�鿡 2D ���̾� ������ Ÿ���� �׸��ϴ�.
	 *
	 * @param center Ÿ���� �߽� ��ǥ�Դϴ�.
	 * @param xAxis Ÿ���� x�� �����Դϴ�. ����, �� ���̰� y�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param yAxis Ÿ���� y�� �����Դϴ�. ����, �� ���̰� x�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param color Ÿ���� �����Դϴ�.
	 * @param sliceCount Ÿ�� �ѷ��� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void DrawWireframeEllipse2D(const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief ȭ�鿡 2D ���ڸ� �׸��ϴ�.
	 * 
	 * @param minX X��ǥ�� �ּҰ��Դϴ�.
	 * @param maxX X��ǥ�� �ִ��Դϴ�.
	 * @param strideX ������ X�� ���������� �����Դϴ�.
	 * @param minY Y��ǥ�� �ּҰ��Դϴ�.
	 * @param maxY Y��ǥ�� �ִ��Դϴ�.
	 * @param strideY ������ Y�� ���������� �����Դϴ�.
	 * @param color ������ �����Դϴ�.
	 */
	void DrawGrid2D(float minX, float maxX, float strideX, float minY, float maxY, float strideY, const Vector4f& color);


	/**
	 * @brief 2D �ؽ�ó�� ȭ�鿡 �׸��ϴ�.
	 *
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param center �ؽ�ó�� �߽� ��ǥ�Դϴ�.
	 * @param width �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param height �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param rotate �ؽ�ó�� ���� ȸ�� �����Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void DrawTexture2D(Texture2D* texture, const Vector2f& center, float width, float height, float rotate, float transparent = 1.0f);


	/**
	 * @brief 2D �ؽ�ó�� ȭ�鿡 �׸��ϴ�.
	 *
	 * @note 2D �ؽ�ó�� ������ ��ü�� ä�������� �׸��ϴ�.
	 *
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void DrawTexture2D(Texture2D* texture, float transparent = 1.0f);


	/**
	 * @brief ���η� ��ũ�ѵ� 2D �ؽ�ó�� �׸��ϴ�.
	 *
	 * @note
	 * - 2D �ؽ�ó�� ������ ��ü�� ä�������� �׸��ϴ�.
	 * - �ؽ�ó ���� ������ ������ �����ϴ�.
	 * ������������������������������������������������������������������
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * �� 1.0f - rate��       rate       ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ������������������������������������������������������������������
	 *
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param rate ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f �Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void DrawHorizonScrollTexture2D(Texture2D* texture, float rate, float transparent = 1.0f);


	/**
	 * @brief ���η� ��ũ�ѵ� 2D �ؽ�ó�� �׸��ϴ�.
	 *
	 * @note
	 * - �ؽ�ó ���� ������ ������ �����ϴ�.
	 * ������������������������������������������������������������������
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * �� 1.0f - rate��       rate       ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ������������������������������������������������������������������
	 * 
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param center
	 * @param rate ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f �Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void DrawHorizonScrollTexture2D(Texture2D* texture, const Vector2f& center, float width, float height, float rate, float transparent = 1.0f);


	/**
	 * @brief ���η� ��ũ�ѵ� 2D �ؽ�ó�� �׸��ϴ�.
	 *
	 * @note
	 * - 2D �ؽ�ó�� ������ ��ü�� ä�������� �׸��ϴ�.
	 * - �ؽ�ó ���� ������ ������ �����ϴ�.
	 * ��������������������������������������������������������������
	 * ��                             ��
	 * ��                             ��
	 * ��              rate           ��
	 * ��                             ��
	 * ��������������������������������������������������������������
	 * ��                             ��
	 * ��          1.0f - rate        ��
	 * ��                             ��
	 * ��������������������������������������������������������������
	 *
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param rate ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f �Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void DrawVerticalScrollTexture2D(Texture2D* texture, float rate, float transparent = 1.0f);


	/**
	 * @brief ���η� ��ũ�ѵ� 2D �ؽ�ó�� �׸��ϴ�.
	 *
	 * @note
	 * - �ؽ�ó ���� ������ ������ �����ϴ�.
	 * ��������������������������������������������������������������
	 * ��                             ��
	 * ��                             ��
	 * ��              rate           ��
	 * ��                             ��
	 * ��������������������������������������������������������������
	 * ��                             ��
	 * ��          1.0f - rate        ��
	 * ��                             ��
	 * ��������������������������������������������������������������
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param center
	 * @param rate ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f �Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void DrawVerticalScrollTexture2D(Texture2D* texture, const Vector2f& center, float width, float height, float rate, float transparent = 1.0f);


	/**
	 * @brief 2D �ؽ�Ʈ�� ȭ�鿡 �׸��ϴ�.
	 * 
	 * @param font ��Ʈ ���ҽ��Դϴ�.
	 * @param text �������� �ؽ�Ʈ�Դϴ�.
	 * @param center �ؽ�Ʈ�� �߽� ��ǥ�Դϴ�.
	 * @param color �ؽ�Ʈ�� RGBA �����Դϴ�.
	 */
	void DrawText2D(TTFont* font, const std::wstring& text, const Vector2f& center, const Vector4f& color);


	/**
	 * @brief 2D �ؽ�ó�� �Ƿ翧�� ȭ�鿡 �׸��ϴ�.
	 * 
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param center �ؽ�ó�� �߽� ��ǥ�Դϴ�.
	 * @param width �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param height �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param rotate �ؽ�ó�� ���� ȸ�� �����Դϴ�.
	 * @param silhouetteRGB �ؽ�ó �Ƿ翧�� �����Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f �Դϴ�.
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
	 * @brief 2D �ؽ�ó�� �ƿ����ΰ� �Բ� ȭ�鿡 �׸��ϴ�.
	 * 
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param center �ؽ�ó�� �߽� ��ǥ�Դϴ�.
	 * @param width �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param height �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param rotate �ؽ�ó�� ���� ȸ�� �����Դϴ�.
	 * @param outline �ؽ�ó ������Ʈ �ƿ������� �����Դϴ�.
	 * @param transparent �ؽ�ó�� �����Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
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
	 * @brief Inversion ��ó�� ȿ���� �����մϴ�.
	 * 
	 * @note �� �����ӿ� �� ���� ȿ���� ������ �� �ֽ��ϴ�.
	 */
	void PostEffectInversion();


	/**
	 * @brief RGB���� ������� �׷��� ������ ȿ���� �����մϴ�.
	 */
	void PostEffectAverageGrayscale();


private:
	/**
	 * @brief ���̴��� ����ϱ� ���� �ʱ�ȭ�� �����մϴ�.
	 */
	void StartupShaders();

	
private:
	/**
	 * @brief �������� ������ �������Դϴ�.
	 */
	Window* window_ = nullptr;


	/**
	 * @brief OpepGL�� �� �����Դϴ�.
	 */
	int32_t major_ = 0;


	/**
	 * @brief OpenGL�� �� �����Դϴ�.
	 */
	int32_t minor_ = 0;


	/**
	 * @brief ���� ��ũ���� ���� ũ���Դϴ�.
	 */
	int32_t screenWidth_ = 0;


	/**
	 * @brief ���� ��ũ���� ���� ũ���Դϴ�.
	 */
	int32_t screenHeight_ = 0;


	/**
	 * @brief ���� ��ũ���� �����ϴ� ���� ���� ����Դϴ�.
	 */
	Matrix4x4f screenOrtho_;


	/**
	 * @brief ������ ���ۿ��� ����۷� �����ߴ��� Ȯ���մϴ�.
	 */
	bool bIsBlit_ = false;


	/**
	 * @brief �������� ����� ���ҽ��Դϴ�.
	 */
	std::unordered_map<std::string, IResource*> resourceMaps_;
};