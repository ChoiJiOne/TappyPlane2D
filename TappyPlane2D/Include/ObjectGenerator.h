#pragma once

#include <list>

#include "Rock.h"
#include "Star.h"


/**
 * @brief 오브젝트를 생성하는 오브젝트입니다.
 * 
 * @note 이 오브젝트는 바위와 별 오브젝트를 생성합니다.
 */
class ObjectGenerator : public IGameObject
{
public:
	/**
	 * @brief 오브젝트를 생성하는 오브젝트의 디폴트 생성자입니다.
	 */
	ObjectGenerator() = default;


	/**
	 * @brief 오브젝트를 생성하는 오브젝트의 가상 소멸자입니다.
	 *
	 * @note 오브젝트를 생성하는 오브젝트 내부에서 할당된 리소스를 해제하기 위해서는 Release 메서드를 호출해야 합니다.
	 */
	virtual ~ObjectGenerator();


	/**
	 * @brief 오브젝트를 생성하는 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ObjectGenerator);


	/**
	 * @brief 오브젝트를 생성하는 오브젝트를 초기화합니다.
	 * 
	 * @param rockType 생성할 바위 오브젝트의 타입입니다.
	 * @param startXPosition 오브젝트를 생성할 위치의 X좌표입니다.
	 */
	void Initialize(const Rock::EType& rockType, const float& startXPosition);

	
	/**
	 * @brief 오브젝트를 생성하는 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief 오브젝트를 생성하는 오브젝트를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 오브젝트를 생성하는 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief 오브젝트를 생성합니다.
	 */
	void GenerateObject();


	/**
	 * @brief 오브젝트를 파괴합니다.
	 */
	void DestroyObject();


private:
	/**
	 * @brief 생성할 바위 오브젝트의 타입입니다.
	 */
	Rock::EType rockType_ = Rock::EType::Plain;


	/**
	 * @brief 오브젝트를 생성할 위치의 X좌표입니다.
	 */
	float startXPosition_ = 0.0f;


	/**
	 * @brief 관리 중인 바위 오브젝트입니다.
	 */
	std::list<Rock*> rocks_;


	/**
	 * @brief 생성한 바위 오브젝트의 수입니다.
	 */
	int32_t countOfRock_ = 0;


	/**
	 * @brief 관리 중인 별 오브젝트입니다.
	 */
	std::list<Star*> stars_;


	/**
	 * @brief 생성한 별 오브젝트의 수입니다.
	 */
	int32_t countOfStar_ = 0;
};