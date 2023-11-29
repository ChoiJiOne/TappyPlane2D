#pragma once

#include <array>

#include "AABB.h"
#include "IGameObject.h"
#include "Texture2D.h"
#include "MathUtils.h"
#include "Vector2.h"


/**
 * @brief 플레이어가 조종 가능한 비행기입니다.
 */
class Plane : public IGameObject
{
public:
	/**
	 * @brief 비행기의 색상 종류입니다.
	 */
	enum class EColor : int32_t
	{
		Blue   = 0x00,
		Green  = 0x01,
		Red    = 0x02,
		Yellow = 0x03,
	};


	/**
	 * @brief 비행기의 상태를 나타냅니다.
	 */
	enum class EState : int32_t
	{
		Wait = 0x00,    // 대기 상태
		Flight = 0x01,  // 비행 중
		Crash = 0x02,   // 충돌
	};


public:
	/**
	 * @brief 비행기의 디폴트 생성자입니다.
	 */
	Plane() = default;


	/**
	 * @brief 비행기의 가상 소멸자입니다.
	 *
	 * @note 비행기 내부에서 할당된 리소스를 해제하기 위해서는 Release 메서드를 호출해야 합니다.
	 */
	virtual ~Plane();


	/**
	 * @brief 비행기의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Plane);


	/**
	 * @brief 비행기를 초기화합니다.
	 * 
	 * @param colorType 비행기 색상의 종류입니다.
	 */
	void Initialize(const EColor& colorType);


	/**
	 * @brief 비행기를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief 비행기를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 비행기 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 비행기의 충돌 경계 영역을 얻습니다.
	 * 
	 * @return 비행기 충돌 경계 영역의 상수 참조자를 반환합니다.
	 */
	const AABB& GetCollisionBound() const { return collisionBound_; }


	/**
	 * @brief 비행기와 별 오브젝트의 충돌 횟수를 얻습니다.
	 * 
	 * @return 비행기와 별 오브젝트의 충돌 횟수를 반환합니다.
	 */
	int32_t GetCountOfCollisionStar() const { return countOfCollisionStar_; }


private:
	/**
	 * @brief 비행기의 비행 애니메이션을 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	void UpdateFlightAnimation(float deltaSeconds);


	/**
	 * @brief 비행기의 폭발 애니메이션을 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	void UpdateExplosionAnimation(float deltaSeconds);


	/**
	 * @brief 비행기가 대기중인 상태를 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	void UpdateWaitState(float deltaSeconds);


	/**
	 * @brief 배행기가 나는 상태를 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	void UpdateFlightState(float deltaSeconds);


	/**
	 * @brief 비행기가 충돌했을 때 상태를 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	void UpdateCrashState(float deltaSeconds);

	
private:
	/**
	 * @brief 비행기의 색상 종류입니다.
	 * 
	 * @note 이 속성은 비행기의 기본 속성입니다.
	 */
	EColor colorType_ = EColor::Blue;


	/**
	 * @brief 비행기의 중심 좌표입니다.
	 * 
	 * @note 이 속성은 비행기의 기본 속성입니다.
	 */
	Vector2f center_;


	/**
	 * @brief 비행기의 가로 크기입니다.
	 * 
	 * @note 이 속성은 비행기의 기본 속성입니다.
	 */
	float width_ = 0.0f;


	/**
	 * @brief 비행기의 세로 크기입니다.
	 * 
	 * @note 이 속성은 비행기의 기본 속성입니다.
	 */
	float height_ = 0.0f;


	/**
	 * @brief 비행기의 회전 각도입니다.
	 * 
	 * @note 이 속성은 비행기의 기본 속성입니다.
	 */
	float rotate_ = 0.0f;


	/**
	 * @brief 현재 비행기의 상태입니다.
	 * 
	 * @note 이 속성은 비행기의 기본 속성입니다.
	 */
	EState state_ = EState::Wait;


	/**
	 * @brief 충돌 처리를 위한 AABB입니다.
	 * 
	 * @note 이 속성은 비행기의 기본 속성입니다.
	 */
	AABB collisionBound_;


	/**
	 * @brief 비행기의 애니메이션을 수행하기 위한 텍스처입니다.
	 */
	std::array<Texture2D*, 5> flightAnimationTextures_;


	/**
	 * @brief 현재 애니메이션 텍스처 인덱스입니다.
	 */
	uint32_t flightAnimationTextureIndex_ = 0;


	/**
	 * @brief 애니메이션을 수행하기 위한 한 프레임의 지속 시간입니다.
	 */
	float flightAnimationFrameTime_ = 0.0f;


	/**
	 * @brief 비행기의 폭발 애니메이션을 수행하기 위한 텍스처입니다.
	 */
	std::array<Texture2D*, 5> explosionAnimationTextures_;


	/**
	 * @brief 현재 애니메이션 텍스처 인덱스입니다.
	 */
	uint32_t explosionAnimationTextureIndex_ = 0;


	/**
	 * @brief 애니메이션을 수행하기 위한 한 프레임의 지속 시간입니다.
	 */
	float explosionAnimationFrameTime_ = 0.0f;


	/**
	 * @brief 애니메이션을 수행하기 위한 누적 시간입니다.
	 */
	float accumulateAnimationFrameTime_ = 0.0f;


	/**
	 * @brief 비행기의 대기 시간입니다.
	 */
	float waitAccumulateTime_ = 0.0f;


	/**
	 * @brief 비행기의 대기 위치입니다.
	 */
	Vector2f waitPosition_;

	
	/**
	 * @brief 비행기의 최대 속도입니다.
	 */
	float maxSpeed_ = 0.0f;


	/**
	 * @brief 비행기의 현재 속도입니다.
	 */
	float currentSpeed_ = 0.0f;


	/**
	 * @brief 비행기의 감속 속도입니다.
	 */
	float dampingSpeed_ = 0.0f;


	/**
	 * @brief 비행기와 별 오브젝트의 충돌 횟수입니다.
	 */
	int32_t countOfCollisionStar_ = 0;
};