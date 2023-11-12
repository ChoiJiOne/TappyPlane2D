#pragma once

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