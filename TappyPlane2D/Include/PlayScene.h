#pragma once

#include <array>

#include "IScene.h"
#include "IGameObject.h"


/**
 * @brief ������ �÷��� ���Դϴ�.
 */
class PlayScene : public IScene
{
public:
	/**
	 * @brief ���� �÷��� ���� ����Ʈ �������Դϴ�.
	 */
	PlayScene() = default;


	/**
	 * @brief ���� �÷��� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~PlayScene();


	/**
	 * @brief ���� �÷��� ���� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(PlayScene);


	/**
	 * @brief ���� �÷��� ���� �����մϴ�.
	 */
	virtual void EnterScene() override;


	/**
	 * @brief ���� �÷��� ������ �����մϴ�.
	 */
	virtual void ExitScene() override;


	/**
	 * @brief ���� �÷��� ���� �� �������� �����մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð����Դϴ�.
	 */
	virtual void TickScene(float deltaSeconds) override;


	/**
	 * @brief ���� ���� �÷��� ���� ���� ���� �����մϴ�.
	 *
	 * @param scene ���� ���� �÷��� ���� ������ ���� ���Դϴ�.
	 */
	virtual void SetNextScene(IScene* scene) override;


	/**
	 * @brief ���� ���� �÷��� ���� ���� ���� ����ϴ�.
	 *
	 * @return ���� ���� �÷��� ���� ����� ���� ���� ������ ���� ��ȯ�մϴ�.
	 */
	virtual IScene* GetNextScene() override;


private:
	/**
	 * @brief ���� ���� �÷��� ���� �����ߴ��� Ȯ���մϴ�.
	 */
	bool bIsEnterScene_ = false;


	/**
	 * @brief ���� ���� �÷��� ���� ����� ���� ���Դϴ�.
	 */
	IScene* nextScene_ = nullptr;


	/**
	 * @brief ���� �÷��� ���� ������Ʈ���Դϴ�.
	 */
	std::array<IGameObject*, 5> objects_;
};