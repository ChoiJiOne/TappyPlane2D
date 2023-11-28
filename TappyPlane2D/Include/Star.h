#pragma once

#include "AABB.h"
#include "IGameObject.h"
#include "Texture2D.h"
#include "Vector2.h"


/**
 * @brief 플레이어가 획득 가능한 별 오브젝트입니다.
 */
class Star : public IGameObject
{
public:
	/**
	 * @brief 별 오브젝트의 상태입니다.
	 */
	enum class EState : int32_t
	{
		Wait = 0x00,
		Move = 0x01,
	};


public:
	/**
	 * @brief 별 오브젝트의 디폴트 생성자입니다.
	 */
	Star() = default;


	/**
	 * @brief 별 오브젝트의 가상 소멸자입니다.
	 * 
	 * @note 별 오브젝트 내부에서 할당된 리소스를 해제하기 위해서는 Release 메서드를 호출해야 합니다.
	 */
	virtual ~Star();


	/**
	 * @brief 별 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Star);


	/**
	 * @brief 별 오브젝트를 초기화합니다.
	 * 
	 * @param center 별 오브젝트의 중심 위치입니다.
	 */
	void Initialize(const Vector2f& center);


	 /**
	  * @brief 별 오브젝트를 업데이트합니다.
	  *
	  * @param deltaSeconds 델타 시간 값입니다.
	  */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief 별 오브젝트를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 별 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;

	
	/**
	 * @brief 별 오브젝트의 충돌 경계 영역을 얻습니다.
	 *
	 * @return 별 오브젝트 충돌 경계 영역의 상수 참조자를 반환합니다.
	 */
	const AABB& GetCollisionBound() const { return collisionBound_; }


	/**
	 * @brief 별 오브젝트의 내부 프로퍼티를 초기화합니다.
	 * 
	 * @param center 별 오브젝트의 중심 위치입니다.
	 */
	void SetupProperties(const Vector2f& center);


	/**
	 * @brief 별 오브젝트의 상태를 얻습니다.
	 *
	 * @return 별 오브젝트의 상태를 반환합니다.
	 */
	EState GetState() const { return state_; }


	/**
	 * @brief 별 오브젝트의 상태를 설정합니다.
	 *
	 * @param state 설정할 별 오브젝트의 상태입니다.
	 */
	void SetState(const EState& state) { state_ = state; }


private:
	/**
	 * @brief 별 오브젝트의 상태입니다.
	 */
	EState state_ = EState::Wait;


	/**
	 * @brief 별 오브젝트의 중심 위치입니다.
	 */
	Vector2f center_;


	/**
	 * @brief 별 오브젝트의 가로 크기입니다.
	 */
	float width_ = 0.0f;


	/**
	 * @brief 별 오브젝트의 세로 크기입니다.
	 */
	float height_ = 0.0f;


	/**
	 * @brief 별 오브젝트의 이동 속도입니다.
	 */
	float speed_ = 0.0f;


	/**
	 * @brief 별 오브젝트의 경계 영역입니다.
	 */
	AABB collisionBound_;


	/**
	 * @brief 별 오브젝트의 텍스처입니다.
	 */
	Texture2D* texture_ = nullptr;
};