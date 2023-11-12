#pragma once

#include <memory>
#include <unordered_map>

#include "IManager.h"
#include "IResource.h"
#include "SingletonMacro.h"


/**
 * @brief 게임 내의 리소스를 관리하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class ResourceManager : public IManager
{
	SINGLETON(ResourceManager);


public:
	/**
	 * @brief 리소스를 관리하는 매니저의 사용을 시작합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 리소스를 관리하는 매니저의 사용을 종료합니다.
	 */
	virtual void Shutdown() override;
	

private:
	/**
	 * @brief 시그니처 값에 대응하는 리소스가 존재하는지 확인합니다.
	 * 
	 * @param signature 리소스가 존재하는 지 확인할 시그니처 값입니다.
	 * 
	 * @return 시그니처 값이 유효하다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool VerifyResource(const std::string& signature);


private:
	/**
	 * @brief 리소스 매니저가 관리하는 리소스입니다.
	 */
	std::unordered_map<std::string, std::unique_ptr<IResource>> resources_;
};