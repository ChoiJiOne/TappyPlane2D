#pragma once

#include <string>

#include "IResource.h"


/**
 * @brief �̹��� ������ �ε��ϰ� OpenGL ���������ο� ���ε� ������ �ؽ�ó ���ҽ��� ���� �� �����մϴ�.
 * 
 * @note
 * - �̹��� ������ .jpeg, .jpg, .png, .tga, .bmp �� �����մϴ�.
 * - ���� ������ ASTC ���ĸ� �����ϰ� �ݵ�� astcenc.exe�� �̿��ؼ� ������ �����̿��� �մϴ�.
 */
class Texture2D : public IResource
{
public:
	/**
	 * @brief �ؽ�ó�� ����Ʈ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Texture2D() = default;


	/**
	 * @brief �ؽ�ó�� ���� �Ҹ����Դϴ�.
	 * 
	 * @note �ؽ�ó ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~Texture2D();


	/**
	 * @brief �ؽ�ó�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Texture2D);


	/**
	 * @brief �̹��� ������ �а� �ؽ�ó ���ҽ��� �����մϴ�.
	 * 
	 * @param path �̹��� ������ ����Դϴ�.
	 * @param bCheckValid ������ ��ȿ�� �˻��Դϴ�. �⺻������ �˻��ϵ��� true���Դϴ�.
	 * 
	 * @note
	 * - �̹��� ������ .jpeg, .jpg, .png, .tga, .bmp �� �����մϴ�.
	 * - ���� ������ �ݵ�� astcenc.exe�� �̿��ؼ� ������ �����̿��� �մϴ�.
	 * - ���� ������ ASTC ���ĸ� �����ϰ� Ȯ���ڴ� .astc�� �Ǿ� �־�� �մϴ�.
	 */
	void Initialize(const std::string& path, bool bCheckValid = true);


	/**
	 * @brief �ؽ�ó�� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �ؽ�ó�� Ȱ��ȭ�մϴ�.
	 * 
	 * @param unit Ȱ��ȭ �� �ؽ�ó �����Դϴ�.
	 */
	void Active(uint32_t unit);


private:
	/**
	 * @brief ����� �ؽ�ó ���ҽ��� �����մϴ�.
	 * 
	 * @param path �̹��� ������ ����Դϴ�.
	 */
	uint32_t CreateNonCompressionTexture(const std::string& path);


	/**
	 * @brief ASTC ���� �ؽ�ó ���ҽ��� �����մϴ�.
	 * 
	 * @param path �̹��� ������ ����Դϴ�.
	 */
	uint32_t CreateASTCCompressionTexture(const std::string& path);


	/**
	 * @brief DXT ���� �ؽ�ó ���ҽ��� �����մϴ�.
	 * 
	 * @param path �̹��� ������ ����Դϴ�.
	 * 
	 * @see 
	 * - https://gist.github.com/tilkinsc/13191c0c1e5d6b25fbe79bbd2288a673
	 * - https://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/#compressed-textures
	 */
	uint32_t CreateDXTCompressionTexture(const std::string& path);


private:
	/**
	 * @brief �ؽ�ó ���ҽ��� ID�Դϴ�.
	 */
	uint32_t textureID_ = 0;
};