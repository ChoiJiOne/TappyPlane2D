#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "IManager.h"
#include "IResource.h"
#include "SingletonMacro.h"


/**
 * @brief ���� ���� ���ҽ��� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class ResourceManager : public IManager
{
	SINGLETON(ResourceManager);


public:
	/**
	 * @brief ���ҽ��� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ���ҽ��� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief �� ���ҽ��� �����մϴ�.
	 *
	 * @note
	 * - ���ҽ� �Ŵ����� �ʱ�ȭ�� �������� �����Ƿ�, ��ȯ�ϴ� ������ ������ �̿��ؼ� �ʱ�ȭ�� ���� �����ؾ� �մϴ�.
	 * - ���ҽ��� �ñ״�ó ���� �ߺ��� ������� �ʽ��ϴ�.
	 *
	 * @param signature �Ŵ��� ���ο��� ���ҽ����� ������ �ñ״�ó ���Դϴ�.
	 *
	 * @return ������ ���ҽ��� �����͸� ��ȯ�մϴ�.
	 */
	template <typename TResource>
	TResource* CreateResource(const std::string& signature)
	{
		ASSERT(!VerifyResource(signature), "already exist resource signature key : %s", signature.c_str());

		std::unique_ptr<TResource> resource = std::make_unique<TResource>();
		resources_.insert({ signature, std::move(resource) });

		return reinterpret_cast<TResource*>(resources_.at(signature).get());
	}


	/**
	 * @brief ���ҽ� �Ŵ����� �����ϴ� ���ҽ��� ����ϴ�.
	 *
	 * @param signature �Ŵ��� ���ο��� ���ҽ����� ������ �ñ״�ó ���Դϴ�.
	 *
	 * @return �ñ״�ó�� �����ϴ� ���ҽ��� �����͸� ����ϴ�. �ñ״�ó ���� �����ϴ� ���ҽ��� ������ �� �����͸� ��ȯ�մϴ�.
	 */
	template <typename TResource>
	TResource* GetResource(const std::string& signature)
	{
		if (!VerifyResource(signature))
		{
			return nullptr;
		}

		return reinterpret_cast<TResource*>(resources_.at(signature).get());
	}


	/**
	 * @brief ���ҽ� �Ŵ����� �����ϴ� ���ҽ��� �����մϴ�.
	 *
	 * @param signature ������ ���ҽ��� �ñ״�ó ���Դϴ�.
	 */
	void DestroyResource(const std::string& signature);
	

private:
	/**
	 * @brief �ñ״�ó ���� �����ϴ� ���ҽ��� �����ϴ��� Ȯ���մϴ�.
	 * 
	 * @param signature ���ҽ��� �����ϴ� �� Ȯ���� �ñ״�ó ���Դϴ�.
	 * 
	 * @return �ñ״�ó ���� ��ȿ�ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool VerifyResource(const std::string& signature);


private:
	/**
	 * @brief ���ҽ� �Ŵ����� �����ϴ� ���ҽ��Դϴ�.
	 */
	std::unordered_map<std::string, std::unique_ptr<IResource>> resources_;
};