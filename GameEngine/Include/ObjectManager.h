#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "IManager.h"
#include "IGameObject.h"
#include "SingletonMacro.h"


/**
 * @brief ���� ���� ������Ʈ�� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class ObjectManager : public IManager
{
	SINGLETON(ObjectManager);


public:
	/**
	 * @brief ���� ������Ʈ�� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ���� ������Ʈ�� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief �� ���� ������Ʈ�� �����մϴ�.
	 *
	 * @note
	 * - ���� ������Ʈ �Ŵ����� �ʱ�ȭ�� �������� �����Ƿ�, ��ȯ�ϴ� ������ ������ �̿��ؼ� �ʱ�ȭ�� ���� �����ؾ� �մϴ�.
	 * - ���� ������Ʈ�� �ñ״�ó ���� �ߺ��� ������� �ʽ��ϴ�.
	 *
	 * @param signature �Ŵ��� ���ο��� ������Ʈ�� ������ �ñ״�ó ���Դϴ�.
	 *
	 * @return ������ ���� ������Ʈ�� �����͸� ��ȯ�մϴ�.
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
	 * @brief ���� ������Ʈ �Ŵ����� �����ϴ� ���� ������Ʈ�� �����͸� ����ϴ�.
	 *
	 * @param signature �Ŵ��� ���ο��� ���� ������Ʈ�� ������ �ñ״�ó ���Դϴ�.
	 *
	 * @return �ñ״�ó�� �����ϴ� ���� ������Ʈ�� �����͸� ����ϴ�. �ñ״�ó ���� �����ϴ� ���� ������Ʈ�� ������ �� �����͸� ��ȯ�մϴ�.
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
	 * @brief ���� ������Ʈ �Ŵ����� �����ϴ� ���� ������Ʈ�� �����մϴ�.
	 *
	 * @param signature ������ ���ҽ��� �ñ״�ó ���Դϴ�.
	 */
	void DestroyGameObject(const std::string& signature);


private:
	/**
	 * @brief �ñ״�ó ���� �����ϴ� ���� ������Ʈ�� �����ϴ��� Ȯ���մϴ�.
	 *
	 * @param signature ���� ������Ʈ�� �����ϴ� �� Ȯ���� �ñ״�ó ���Դϴ�.
	 *
	 * @return �ñ״�ó ���� ��ȿ�ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool VerifyGameObject(const std::string& signature);


private:
	/**
	 * @brief ���ҽ� �Ŵ����� �����ϴ� ���ҽ��Դϴ�.
	 */
	std::unordered_map<std::string, std::unique_ptr<IGameObject>> gameObjects_;
};