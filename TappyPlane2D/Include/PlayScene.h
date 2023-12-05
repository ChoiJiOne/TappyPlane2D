#pragma once

#include <array>

#include "IScene.h"
#include "IGameObject.h"

class Background;
class Ground;
class ObjectScheduler;
class Plane;
class ScoreBoard;
class ClickTrigger;


/**
 * @brief ������ �÷��� ���Դϴ�.
 */
class PlayScene : public IScene
{
public:
	/**
	 * @brief ���� �÷��� ���� �����Դϴ�.
	 */
	enum class ESceneState : int32_t
	{
		Wait  = 0x00,
		Enter = 0x01,
		Play  = 0x02,
		Pause = 0x03,
		Crash = 0x04,
		Exit  = 0x05,
	};


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
	 * @brief ���� �÷��� ���� �����ߴ��� Ȯ���մϴ�.
	 *
	 * @return ���� �÷��� ���� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	virtual bool IsEnterScene() override { return bIsEnterScene_; }


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
	 * @brief ���� ���� �÷��� ���� �����Դϴ�.
	 */
	ESceneState currentSceneState_ = ESceneState::Wait;


	/**
	 * @brief ���� ���°� �Ǿ��� ���� ���� �ð����Դϴ�.
	 */
	float enterAccumulateTime_ = 0.0f;

	
	/**
	 * @brief ���� ���� �÷��� ���� ����� ���� ���Դϴ�.
	 */
	IScene* nextScene_ = nullptr;


	/**
	 * @brief ��׶��� ������Ʈ�Դϴ�.
	 */
	Background* background_ = nullptr;


	/**
	 * @brief �׶��� ������Ʈ�Դϴ�.
	 */
	Ground* ground_ = nullptr;


	/**
	 * @brief ������Ʈ ��ĳ�ٷ�(Rock, Star)�Դϴ�.
	 */
	ObjectScheduler* scheduler_ = nullptr;


	/**
	 * @brief ����� ������Ʈ�Դϴ�.
	 */
	Plane* plane_ = nullptr;


	/**
	 * @brief ���ھ� ���� ������Ʈ�Դϴ�.
	 */
	ScoreBoard* board_ = nullptr;


	/**
	 * @brief ������ �����Ǿ��� �� ����� �� Ȯ���ϴ� Ʈ�����Դϴ�.
	 */
	ClickTrigger* continueTrigger_ = nullptr;


	/**
	 * @brief ������ �ٽ� �����ϴ� Ʈ�����Դϴ�.
	 */
	ClickTrigger* restartTrigger_ = nullptr;
};