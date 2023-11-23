#pragma once

#include "IGameObject.h"
#include "Texture2D.h"


/**
 * @brief 백그라운드 오브젝트입니다.
 * 
 * @note 렌더링이 다른 오브젝트들보다 우선되어야 합니다.
 */
class Background : public IGameObject
{
public:
	/**
	 * @brief 백그라운드 오브젝트의 디폴트 생성자입니다.
	 * 
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	Background() = default;


	/**
	 * @brief 백그라운드 오브젝트의 가상 소멸자입니다.
	 * 
	 * @note 백그라운드 오브젝트 내부에서 할당된 리소스를 해제하기 위해서는 Release 메서드를 호출해야 합니다.
	 */
	virtual ~Background();


	/**
	 * @brief 백그라운드 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Background);


	/**
	 * @brief 백그라운드 오브젝트를 초기화합니다.
	 */
	void Initialize();


	/**
	 * @brief 백그라운드 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief 백그라운드 오브젝트를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 백그라운드 오브젝트 내의 리소스를 할당 해제합니다.
	 *
	 * @note 백그라운드 오브젝트 인터페이스를 상속받는 하위 클래스에서 반드시 구현해야 합니다.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief 백그라운드 텍스처 리소스입니다.
	 */
	Texture2D* texture_ = nullptr;


	/**
	 * @brief 백그라운드의 스크롤 속도입니다.
	 * 
	 * @note 
	 * - 이 속도는 초당 움직이는 픽셀 수입니다.
	 * - 예를 들어 200 이라면 초당 200 픽셀 만큼 움직입니다.
	 */
	float scrollSpeed_ = 0.0f;


	/**
	 * @brief 백그라운드의 스크롤 지점입니다.
	 */
	float scrollPosition_ = 0.0f;


	/**
	 * @brief 백그라운드의 스크롤 최대 지점입니다.
	 */
	float maxScrollPosition_ = 0.0f;
};