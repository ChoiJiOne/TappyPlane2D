#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "IManager.h"
#include "IScene.h"
#include "SingletonMacro.h"


/**
 * @brief 게임 내의 씬을 관리하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class SceneManager : public IManager
{
	SINGLETON(SceneManager);


public:
	/**
	 * @brief 씬을 관리하는 매니저의 사용을 시작합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 씬을 관리하는 매니저의 사용을 종료합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 씬을 생성합니다.
	 * 
	 * @param signature 매니저 내부에서 씬을 구분할 시그니처 값입니다.
	 * 
	 * @return 생성된 씬의 포인터를 반환합니다.
	 * 
	 * @note 씬의 시그니처 값은 중복을 허용하지 않습니다.
	 */
	template <typename TScene>
	TScene* CreateScene(const std::string& signature)
	{
		ASSERT(!VerifyScene(signature), "already exist scene signature key : %s", signature.c_str());

		std::unique_ptr<TScene> scene = std::make_unique<TScene>();
		scenes_.insert({ signature, std::move(scene) });

		return reinterpret_cast<TScene*>(scenes_.at(signature).get());
	}


	/**
	 * @brief 씬 매니저가 관리하는 리소스를 얻습니다.
	 * 
	 * @param signature 매니저 내부에서 씬들을 구분할 시그니처 값입니다.
	 * 
	 * @return 시그니처에 대응하는 씬 포인터를 얻습니다. 시그니처 값에 대응하는 씬이 없으면 널 포인터를 반환합니다.
	 */
	template <typename TScene>
	TScene* GetScene(const std::string& signature)
	{
		if (!VerifyScene(signature))
		{
			return nullptr;
		}

		return reinterpret_cast<TScene*>(scenes_.at(signature).get());
	}


	/**
	 * @brief 씬 매니저가 관리하는 씬을 삭제합니다.
	 * 
	 * @param signature 삭제할 씬의 시그니처 값입니다.
	 */
	void DestroyScene(const std::string& signature);


	/**
	 * @brief 현재 씬 매니저가 가리키는 씬을 얻습니다.
	 * 
	 * @return 현재 씬 매니저가 가리키는 씬의 포인터를 반환합니다.
	 */
	IScene* GetCurrentScene() { return currentScene_; }


	/**
	 * @brief 현재 씬 매니저가 가리키는 씬을 설정합니다.
	 * 
	 * @param currentScene 설정할 씬 포인터입니다.
	 */
	void SetCurrentScene(IScene* currentScene) { currentScene_ = currentScene; }


	/**
	 * @brief 현재 가리키는 씬에 연결된 다음 씬으로의 스위칭을 수행합니다.
	 */
	void SwitchNextScene();


private:
	/**
	 * @brief 시그니처 값에 대응하는 씬이 존재하는지 확인합니다.
	 *
	 * @param signature 씬이 존재하는 지 확인할 시그니처 값입니다.
	 *
	 * @return 시그니처 값이 유효하다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool VerifyScene(const std::string& signature);


private:
	/**
	 * @brief 씬 매니저가 관리하는 씬입니다.
	 */
	std::unordered_map<std::string, std::unique_ptr<IScene>> scenes_;


	/**
	 * @brief 씬 매니저가 가리키는 씬입니다.
	 */
	IScene* currentScene_ = nullptr;
};