#pragma once

#include <array>

#include "IScene.h"
#include "IGameObject.h"


/**
 * @brief ���� ���� ���Դϴ�.
 */
class StartScene : public IScene
{
public:
	/**
	 * @brief ���� ���� ���� �����Դϴ�.
	 */
	enum class ESceneState : int32_t
	{
		Wait  = 0x00,
		Enter = 0x01,
		Play  = 0x02,
		Exit  = 0x03,
	};


public:
	/**
	 * @brief ���� ���� ���� ����Ʈ �������Դϴ�.
	 */
	StartScene() = default;


	/**
	 * @brief ���� ���� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~StartScene();


	/**
	 * @brief ���� ���� ���� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(StartScene);


	/**
	 * @brief ���� ���� ���� �����մϴ�.
	 */
	virtual void EnterScene() override;


	/**
	 * @brief ���� ���� ������ �����մϴ�.
	 */
	virtual void ExitScene() override;


	/**
	 * @brief ���� ���� ���� �����ߴ��� Ȯ���մϴ�.
	 *
	 * @return ���� ���� ���� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	virtual bool IsEnterScene() override { return bIsEnterScene_; }


	/**
	 * @brief ���� ���� ���� �� �������� �����մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð����Դϴ�.
	 */
	virtual void TickScene(float deltaSeconds) override;


	/**
	 * @brief ���� ���� ���� ���� ���� ���� �����մϴ�.
	 *
	 * @param scene ���� ���� ���� ���� ������ ���� ���Դϴ�.
	 */
	virtual void SetNextScene(IScene* scene) override;


	/**
	 * @brief ���� ���� ���� ���� ���� ���� ����ϴ�.
	 *
	 * @return ���� ���� ���� ���� ����� ���� ���� ������ ���� ��ȯ�մϴ�.
	 */
	virtual IScene* GetNextScene() override;


private:
	/**
	 * @brief ���� ���� ���� ���� �����ߴ��� Ȯ���մϴ�.
	 */
	bool bIsEnterScene_ = false;


	/**
	 * @brief ���� ���� ���� ���� �����Դϴ�.
	 */
	ESceneState currentSceneState_ = ESceneState::Wait;


	/**
	 * @brief ���� ���°� �Ǿ��� ���� ���� �ð����Դϴ�.
	 */
	float enterAccumulateTime_ = 0.0f;


	/**
	 * @brief ���� ���°� �Ǿ��� ���� ���� �ð����Դϴ�.
	 */
	float exitAccumulateTime_ = 0.0f;


	/**
	 * @brief ���� ���� ���� ���� ����� ���� ���Դϴ�.
	 */
	IScene* nextScene_ = nullptr;


	/**
	 * @brief ���� ���� ���� ������Ʈ���Դϴ�.
	 */
	std::array<IGameObject*, 3> objects_;
};