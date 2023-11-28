#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "IManager.h"
#include "IGameObject.h"
#include "SingletonMacro.h"


/**
 * @brief 게임 내의 오브제트를 관리하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class ObjectManager : public IManager
{
	SINGLETON(ObjectManager);


public:
	/**
	 * @brief 게임 오브젝트를 관리하는 매니저의 사용을 시작합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 게임 오브젝트를 관리하는 매니저의 사용을 종료합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 빈 게임 오브젝트를 생성합니다.
	 *
	 * @note
	 * - 게임 오브젝트 매니저는 초기화를 수행하지 않으므로, 반환하는 포인터 변수를 이용해서 초기화를 따로 수행해야 합니다.
	 * - 게임 오브젝트의 시그니처 값은 중복을 허용하지 않습니다.
	 *
	 * @param signature 매니저 내부에서 오브젝트를 구분할 시그니처 값입니다.
	 *
	 * @return 생성된 게임 오브젝트의 포인터를 반환합니다.
	 */
	template <typename TGameObject>
	TGameObject* CreateGameObject(const std::string& signature)
	{
		ASSERT(!VerifyGameObject(signature), "already exist game object signature key : %s", signature.c_str());

		std::unique_ptr<TGameObject> gameObject = std::make_unique<TGameObject>();
		gameObjects_.insert({ signature, std::move(gameObject) });

		return reinterpret_cast<TGameObject*>(gameObjects_.at(signature).get());
	}


	/**
	 * @brief 게임 오브젝트 매니저가 관리하는 게임 오브젝트의 포인터를 얻습니다.
	 *
	 * @param signature 매니저 내부에서 게임 오브젝트를 구분할 시그니처 값입니다.
	 *
	 * @return 시그니처에 대응하는 게임 오브젝트의 포인터를 얻습니다. 시그니처 값에 대응하는 게임 오브젝트가 없으면 널 포인터를 반환합니다.
	 */
	template <typename TGameObject>
	TGameObject* GetGameObject(const std::string& signature)
	{
		if (!VerifyGameObject(signature))
		{
			return nullptr;
		}

		return reinterpret_cast<TGameObject*>(gameObjects_.at(signature).get());
	}


	/**
	 * @brief 게임 오브젝트 매니저가 관리하는 게임 오브젝트를 삭제합니다.
	 *
	 * @param signature 삭제할 리소스의 시그니처 값입니다.
	 */
	void DestroyGameObject(const std::string& signature);


private:
	/**
	 * @brief 시그니처 값에 대응하는 게임 오브젝트가 존재하는지 확인합니다.
	 *
	 * @param signature 게임 오브젝트가 존재하는 지 확인할 시그니처 값입니다.
	 *
	 * @return 시그니처 값이 유효하다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool VerifyGameObject(const std::string& signature);


private:
	/**
	 * @brief 리소스 매니저가 관리하는 리소스입니다.
	 */
	std::unordered_map<std::string, std::unique_ptr<IGameObject>> gameObjects_;
};