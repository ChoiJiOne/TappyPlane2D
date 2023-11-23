#pragma once

#include <string>
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


	/**
	 * @brief 빈 리소스를 생성합니다.
	 *
	 * @note
	 * - 리소스 매니저는 초기화를 수행하지 않으므로, 반환하는 포인터 변수를 이용해서 초기화를 따로 수행해야 합니다.
	 * - 리소스의 시그니처 값은 중복을 허용하지 않습니다.
	 *
	 * @param signature 매니저 내부에서 리소스들을 구분할 시그니처 값입니다.
	 *
	 * @return 생성된 리소스의 포인터를 반환합니다.
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
	 * @brief 리소스 매니저가 관리하는 리소스를 얻습니다.
	 *
	 * @param signature 매니저 내부에서 리소스들을 구분할 시그니처 값입니다.
	 *
	 * @return 시그니처에 대응하는 리소스의 포인터를 얻습니다. 시그니처 값에 대응하는 리소스가 없으면 널 포인터를 반환합니다.
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
	 * @brief 리소스 매니저가 관리하는 리소스를 삭제합니다.
	 *
	 * @param signature 삭제할 리소스의 시그니처 값입니다.
	 */
	void DestroyResource(const std::string& signature);
	

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