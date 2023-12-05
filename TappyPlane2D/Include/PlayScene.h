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
 * @brief 게임의 플레이 씬입니다.
 */
class PlayScene : public IScene
{
public:
	/**
	 * @brief 게임 플레이 씬의 상태입니다.
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
	 * @brief 게임 플레이 씬의 디폴트 생성자입니다.
	 */
	PlayScene() = default;


	/**
	 * @brief 게임 플레이 씬의 가상 소멸자입니다.
	 */
	virtual ~PlayScene();


	/**
	 * @brief 게임 플레이 씬의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(PlayScene);


	/**
	 * @brief 게임 플레이 씬에 입장합니다.
	 */
	virtual void EnterScene() override;


	/**
	 * @brief 게임 플레이 씬에서 퇴장합니다.
	 */
	virtual void ExitScene() override;


	/**
	 * @brief 게임 플레이 씬에 입장했는지 확인합니다.
	 *
	 * @return 게임 플레이 씬에 입장했다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	virtual bool IsEnterScene() override { return bIsEnterScene_; }


	/**
	 * @brief 게임 플레이 씬의 한 프레임을 진행합니다.
	 *
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	virtual void TickScene(float deltaSeconds) override;


	/**
	 * @brief 현재 게임 플레이 씬의 다음 씬을 설정합니다.
	 *
	 * @param scene 현재 게임 플레이 씬에 연결할 다음 씬입니다.
	 */
	virtual void SetNextScene(IScene* scene) override;


	/**
	 * @brief 현재 게임 플레이 씬의 다음 씬을 얻습니다.
	 *
	 * @return 현재 게임 플레이 씬에 연결된 다음 씬의 포인터 값을 반환합니다.
	 */
	virtual IScene* GetNextScene() override;


private:
	/**
	 * @brief 현재 게임 플레이 씬에 진입했는지 확인합니다.
	 */
	bool bIsEnterScene_ = false;


	/**
	 * @brief 현재 게임 플레이 씬의 상태입니다.
	 */
	ESceneState currentSceneState_ = ESceneState::Wait;


	/**
	 * @brief 입장 상태가 되었을 때의 누적 시간값입니다.
	 */
	float enterAccumulateTime_ = 0.0f;

	
	/**
	 * @brief 현재 게임 플레이 씬에 연결된 다음 씬입니다.
	 */
	IScene* nextScene_ = nullptr;


	/**
	 * @brief 백그라운드 오브젝트입니다.
	 */
	Background* background_ = nullptr;


	/**
	 * @brief 그라운드 오브젝트입니다.
	 */
	Ground* ground_ = nullptr;


	/**
	 * @brief 오브젝트 스캐줄러(Rock, Star)입니다.
	 */
	ObjectScheduler* scheduler_ = nullptr;


	/**
	 * @brief 비행기 오브젝트입니다.
	 */
	Plane* plane_ = nullptr;


	/**
	 * @brief 스코어 보드 오브젝트입니다.
	 */
	ScoreBoard* board_ = nullptr;


	/**
	 * @brief 게임이 중지되었을 때 계속할 지 확인하는 트리거입니다.
	 */
	ClickTrigger* continueTrigger_ = nullptr;


	/**
	 * @brief 게임을 다시 시작하는 트리거입니다.
	 */
	ClickTrigger* restartTrigger_ = nullptr;
};