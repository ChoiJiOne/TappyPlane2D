#pragma once

#include <cstdint>

#include "IResource.h"


/**
 * @brief ���������� ���� �� ������ ������ ������ �����Դϴ�.
 */
class Framebuffer : public IResource
{
public:
	/**
	 * @brief ������ ������ ����Ʈ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Framebuffer() = default;


	/**
	 * @brief ������ ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Framebuffer();


	/**
	 * @brief ������ ������ ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Framebuffer);


	/**
	 * @brief ������ ���۸� �����մϴ�.
	 * 
	 * @param bufferWidth ������ ������ ���� ũ���Դϴ�.
	 * @param bufferHeight ������ ������ ���� ũ���Դϴ�.
	 */
	void Initialize(int32_t bufferWidth, int32_t bufferHeight);


	/**
	 * @brief ������ ���� ������ ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ������ ���۸� �ʱ�ȭ�մϴ�.
	 * 
	 * @param red ���� ������ R ���Դϴ�.
	 * @param green ���� ������ G ���Դϴ�.
	 * @param blue ���� ������ B ���Դϴ�.
	 * @param alpha ���� ������ A ���Դϴ�.
	 * @param depth ���� ������ �ʱ�ȭ ���Դϴ�.
	 * @param stencil ���ٽ� ������ �ʱ�ȭ ���Դϴ�.
	 */
	void Clear(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);


	/**
	 * @brief ������ ���۸� ���ε��մϴ�.
	 */
	void Bind();


	/**
	 * @brief ������ ������ ���ε��� �����մϴ�.
	 */
	void Unbind();


	/**
	 * @brief ������ ������ �ؽ�ó�� Ȱ��ȭ�մϴ�.
	 *
	 * @param unit Ȱ��ȭ �� �ؽ�ó �����Դϴ�.
	 */
	void Active(uint32_t unit);


private:
	/**
	 * @brief ���ε� �Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsBind_ = false;


	/**
	 * @brief ������ ���� ������Ʈ�� ID�Դϴ�.
	 */
	uint32_t framebufferID_ = 0;


	/**
	 * @brief �÷� ���� ������Ʈ�� ID�Դϴ�.
	 */
	uint32_t colorBufferID_ = 0;


	/**
	 * @brief ���� ���ٽ� ���� ������Ʈ�� ID�Դϴ�.
	 */
	uint32_t depthStencilBufferID_ = 0;
};