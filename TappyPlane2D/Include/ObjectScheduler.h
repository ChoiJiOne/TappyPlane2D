#pragma once

#include <vector>

#include "Rock.h"
#include "Star.h"

class Plane;


/**
 * @brief 오브젝트 스케줄러입니다.
 * 
 * @note 이 오브젝트는 바위와 별 오브젝트를 생성/관리합니다.
 */
class ObjectScheduler : public IGameObject
{
public:
	/**
	 * @brief 오브젝트 스케줄러의 디폴트 생성자입니다.
	 */
	ObjectScheduler() = default;


	/**
	 * @brief 오브젝트 스케줄러의 가상 소멸자입니다.
	 *
	 * @note 오브젝트 스케줄러 내부에서 할당된 리소스를 해제하기 위해서는 Release 메서드를 호출해야 합니다.
	 */
	virtual ~ObjectScheduler();


	/**
	 * @brief 오브젝트 스케줄러의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ObjectScheduler);


	/**
	 * @brief 오브젝트 스케줄러를 초기화합니다.
	 * 
	 * @param rockType 생성할 바위 오브젝트의 타입입니다.
	 * @param startXPosition 오브젝트를 생성할 위치의 X좌표입니다.
	 * @param countMaxObject 생성할 오브젝트의 최대 개수입니다.
	 */
	void Initialize(const Rock::EType& rockType, const float& startXPosition, const int32_t& countMaxObject = 15);

	
	/**
	 * @brief 오브젝트 스케줄러를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief 오브젝트 스케줄러를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 오브젝트 스케줄러 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 비행기와 가장 먼저 충돌한 별 오브젝트를 얻습니다.
	 * 
	 * @param plane 충돌 검사를 수행할 비행기입니다.
	 * 
	 * @return 비행기와 가장 먼저 충돌한 별 오브젝트를 반환합니다. 충돌하지 않는다면 nullptr를 반환합니다.
	 */
	Star* GetCollisionStar(const Plane* plane);


	/**
	 * @brief 비행기와 바위 오브젝트들과 충돌하는지 확인합니다.
	 * 
	 * @param plane 충돌 검사를 수행할 비행기입니다.
	 * 
	 * @return 비행기와 바위 오브젝트들이 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsCollisionRocks(const Plane* plane);


	/**
	 * @brief 스케줄링 활성화 여부를 설정합니다.
	 * 
	 * @param bIsActive 설정할 스케줄링 활성화 여부입니다.
	 */
	void SetActive(bool bIsActive) { bIsActive_ = bIsActive; }


	/**
	 * @brief 스케줄링 활성화가 되어있는지 확인합니다.
	 * 
	 * @return 스케줄링 활성화가 되어 있다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsActive() const { return bIsActive_; }

	
private:
	/**
	 * @brief 오브젝트의 상태를 Wait에서 Move로 변경할 수 있는지 확인합니다.
	 * 
	 * @param index 상태를 변경할 수 있는지 확인할 오브젝트의 인덱스입니다.
	 */
	bool CanChangeWaitToMove(int32_t index);


	/**
	 * @brief 오브젝트가 백그라운드 밖으로 나갔는지 확인합니다.
	 * 
	 * @param index 백그라운드 밖으로 나갔는지 확인할 오브젝트의 인덱스입니다.
	 */
	bool CheckOuterFromBackground(int32_t index);
	

private:
	/**
	 * @brief 스케줄링 활성화 여부입니다.
	 */
	bool bIsActive_ = false;


	/**
	 * @brief 생성할 바위 오브젝트의 타입입니다.
	 */
	Rock::EType rockType_ = Rock::EType::Plain;


	/**
	 * @brief 오브젝트를 생성할 위치의 X좌표입니다.
	 */
	float startXPosition_ = 0.0f;


	/**
	 * @brief 오브젝트 사이의 거리입니다.
	 */
	float interval_ = 0.0f;


	/**
	 * @brief 오브젝트의 최대 개수입니다.
	 */
	int32_t countMaxObject_ = 0;


	/**
	 * @brief 관리 중인 바위 오브젝트입니다.
	 */
	std::vector<Rock*> rocks_;


	/**
	 * @brief 관리 중인 별 오브젝트입니다.
	 */
	std::vector<Star*> stars_;
};