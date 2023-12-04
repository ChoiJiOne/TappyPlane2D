#pragma once

#include <string>

#include "IGameObject.h"
#include "TTFont.h"
#include "Vector2.h"


/**
 * @brief 메인 타이틀입니다.
 */
class MainTitle : public IGameObject
{
public:
	/**
	 * @brief 메인 타이틀의 디폴트 생성자입니다.
	 */
	MainTitle() = default;


	/**
	 * @brief 메인 타이틀의 가상 소멸자입니다.
	 * 
	 * @note 메인 타이틀 내부에서 할당된 리소스를 해제하기 위해서는 Release 메서드를 호출해야 합니다.
	 */
	virtual ~MainTitle();


	/**
	 * @brief 메인 타이틀의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(MainTitle);


	/**
	 * @brief 메인 타이틀을 초기화합니다.
	 */
	void Initialize();


	/**
	 * @brief 메인 타이틀을 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief 메인 타이틀을 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 메인 타이틀 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief 메인 타이틀의 중심 위치입니다.
	 */
	Vector2f center_;


	/**
	 * @brief 메인 타이틀 텍스트의 폰트입니다.
	 */
	TTFont* font_ = nullptr;


	/**
	 * @brief 메인 타이틀의 텍스트입니다.
	 */
	std::wstring titleText_;
};