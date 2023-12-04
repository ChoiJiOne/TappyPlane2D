#pragma once

#include "Macro.h"


/**
 * @brief 게임 씬 인터페이스입니다.
 * 
 * @note 게임 내의 씬 오브젝트는 모두 이 인터페이스를 상속받아야합니다.
 */
class IScene
{
public:
	/**
	 * @brief 게임 씬의 디폴트 생성자입니다.
	 */
	IScene() = default;


	/**
	 * @brief 게임 씬의 가상 소멸자입니다.
	 */
	virtual ~IScene() {}


	/**
	 * @brief 게임 씬의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(IScene);


	/**
	 * @brief 게임 씬에 입장합니다.
	 */
	virtual void EnterScene() = 0;


	/**
	 * @brief 게임 씬에서 퇴장합니다.
	 */
	virtual void ExitScene() = 0;


	/**
	 * @brief 게임 씬에 입장했는지 확인합니다.
	 * 
	 * @return 게임 씬에 입장했다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	virtual bool IsEnterScene() = 0;


	/**
	 * @brief 게임 씬의 한 프레임을 진행합니다.
	 * 
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	virtual void TickScene(float deltaSeconds) = 0;


	/**
	 * @brief 현재 게임 씬의 다음 씬을 설정합니다.
	 * 
	 * @param scene 현재 게임 씬에 연결할 다음 씬입니다.
	 */
	virtual void SetNextScene(IScene* scene) = 0;


	/**
	 * @brief 현재 게임 씬의 다음 씬을 얻습니다.
	 * 
	 * @return 현재 게임 씬에 연결된 다음 씬의 포인터 값을 반환합니다.
	 */
	virtual IScene* GetNextScene() = 0;
};