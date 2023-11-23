#pragma once

#include "IGameObject.h"
#include "Texture2D.h"
#include "Vector2.h"


/**
 * @brief 그라운드(바닥) 오브젝트입니다.
 */
class Ground : public IGameObject
{
public:
	/**
	 * @brief 그라운드 오브젝트의 디폴트 생성자입니다.
	 */
	Ground() = default;


	/**
	 * @brief 그라운드 오브젝트의 가상 소멸자입니다.
	 * 
	 * @note 그라운드 오브젝트 내부에서 할당된 리소스를 해제하기 위해서는 Release 메서드를 호출해야 합니다.
	 */
	virtual ~Ground();


	/**
	 * @brief 그라운드 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Ground);


	/**
	 * @brief 그라운드 오브젝트를 초기화합니다.
	 */
	void Initialize();


	/**
	 * @brief 그라운드 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief 그라운드 오브젝트를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 그라운드 오브젝트 내의 리소스를 할당 해제합니다.
	 *
	 * @note 그라운드 오브젝트 인터페이스를 상속받는 하위 클래스에서 반드시 구현해야 합니다.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief 그라운드 텍스처 리소스입니다.
	 */
	Texture2D* texture_ = nullptr;


	/**
	 * @brief 그라운드의 중심 위치입니다.
	 */
	Vector2f center_;


	/**
	 * @brief 그라운드의 가로 크기입니다.
	 */
	float width_ = 0.0f;
	

	/**
	 * @brief 그라운드의 세로 크기입니다.
	 */
	float height_ = 0.0f;
};