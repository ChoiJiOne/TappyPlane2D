#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "IManager.h"
#include "IScene.h"
#include "SingletonMacro.h"


/**
 * @brief ���� ���� ���� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class SceneManager : public IManager
{
	SINGLETON(SceneManager);


public:
	/**
	 * @brief ���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ���� �����մϴ�.
	 * 
	 * @param signature �Ŵ��� ���ο��� ���� ������ �ñ״�ó ���Դϴ�.
	 * 
	 * @return ������ ���� �����͸� ��ȯ�մϴ�.
	 * 
	 * @note ���� �ñ״�ó ���� �ߺ��� ������� �ʽ��ϴ�.
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
	 * @brief �� �Ŵ����� �����ϴ� ���ҽ��� ����ϴ�.
	 * 
	 * @param signature �Ŵ��� ���ο��� ������ ������ �ñ״�ó ���Դϴ�.
	 * 
	 * @return �ñ״�ó�� �����ϴ� �� �����͸� ����ϴ�. �ñ״�ó ���� �����ϴ� ���� ������ �� �����͸� ��ȯ�մϴ�.
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
	 * @brief �� �Ŵ����� �����ϴ� ���� �����մϴ�.
	 * 
	 * @param signature ������ ���� �ñ״�ó ���Դϴ�.
	 */
	void DestroyScene(const std::string& signature);


	/**
	 * @brief ���� �� �Ŵ����� ����Ű�� ���� ����ϴ�.
	 * 
	 * @return ���� �� �Ŵ����� ����Ű�� ���� �����͸� ��ȯ�մϴ�.
	 */
	IScene* GetCurrentScene() { return currentScene_; }


	/**
	 * @brief ���� �� �Ŵ����� ����Ű�� ���� �����մϴ�.
	 * 
	 * @param currentScene ������ �� �������Դϴ�.
	 */
	void SetCurrentScene(IScene* currentScene) { currentScene_ = currentScene; }


	/**
	 * @brief ���� ����Ű�� ���� ����� ���� �������� ����Ī�� �����մϴ�.
	 */
	void SwitchNextScene();


private:
	/**
	 * @brief �ñ״�ó ���� �����ϴ� ���� �����ϴ��� Ȯ���մϴ�.
	 *
	 * @param signature ���� �����ϴ� �� Ȯ���� �ñ״�ó ���Դϴ�.
	 *
	 * @return �ñ״�ó ���� ��ȿ�ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool VerifyScene(const std::string& signature);


private:
	/**
	 * @brief �� �Ŵ����� �����ϴ� ���Դϴ�.
	 */
	std::unordered_map<std::string, std::unique_ptr<IScene>> scenes_;


	/**
	 * @brief �� �Ŵ����� ����Ű�� ���Դϴ�.
	 */
	IScene* currentScene_ = nullptr;
};