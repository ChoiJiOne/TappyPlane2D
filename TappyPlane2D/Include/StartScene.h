#pragma once

#include <array>

#include "IScene.h"
#include "IGameObject.h"


/**
 * @brief 게임 시작 씬입니다.
 */
class StartScene : public IScene
{
public:
	/**
	 * @brief 게임 시작 씬의 상태입니다.
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
	 * @brief 게임 시작 씬의 디폴트 생성자입니다.
	 */
	StartScene() = default;


	/**
	 * @brief 게임 시작 씬의 가상 소멸자입니다.
	 */
	virtual ~StartScene();


	/**
	 * @brief 게임 시작 씬의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(StartScene);


	/**
	 * @brief 게임 시작 씬에 입장합니다.
	 */
	virtual void EnterScene() override;


	/**
	 * @brief 게임 시작 씬에서 퇴장합니다.
	 */
	virtual void ExitScene() override;


	/**
	 * @brief 게임 시작 씬에 입장했는지 확인합니다.
	 *
	 * @return 게임 시작 씬에 입장했다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	virtual bool IsEnterScene() override { return bIsEnterScene_; }


	/**
	 * @brief 게임 시작 씬의 한 프레임을 진행합니다.
	 *
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	virtual void TickScene(float deltaSeconds) override;


	/**
	 * @brief 현재 게임 시작 씬의 다음 씬을 설정합니다.
	 *
	 * @param scene 현재 게임 시작 씬에 연결할 다음 씬입니다.
	 */
	virtual void SetNextScene(IScene* scene) override;


	/**
	 * @brief 현재 게임 시작 씬의 다음 씬을 얻습니다.
	 *
	 * @return 현재 게임 시작 씬에 연결된 다음 씬의 포인터 값을 반환합니다.
	 */
	virtual IScene* GetNextScene() override;


private:
	/**
	 * @brief 현재 게임 시작 씬에 진입했는지 확인합니다.
	 */
	bool bIsEnterScene_ = false;


	/**
	 * @brief 현재 게임 시작 씬의 상태입니다.
	 */
	ESceneState currentSceneState_ = ESceneState::Wait;


	/**
	 * @brief 입장 상태가 되었을 때의 누적 시간값입니다.
	 */
	float enterAccumulateTime_ = 0.0f;


	/**
	 * @brief 퇴장 상태가 되었을 때의 누적 시간값입니다.
	 */
	float exitAccumulateTime_ = 0.0f;


	/**
	 * @brief 현재 게임 시작 씬에 연결된 다음 씬입니다.
	 */
	IScene* nextScene_ = nullptr;


	/**
	 * @brief 게임 시작 씬의 오브젝트들입니다.
	 */
	std::array<IGameObject*, 3> objects_;
};