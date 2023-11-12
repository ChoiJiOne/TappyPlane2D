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
	 * @brief ���ҽ� �Ŵ����� �����ϴ� ���ҽ��Դϴ�.
	 */
	std::unordered_map<std::string, std::unique_ptr<IResource>> resources_;
};