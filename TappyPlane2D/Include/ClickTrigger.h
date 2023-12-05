#pragma once

#include <string>
#include <functional>

#include "IGameObject.h"
#include "TTFont.h"
#include "Vector2.h"
#include "Vector4.h"


/**
 * @brief 마우스 클릭을 감지하는 오브젝트입니다.
 */
class ClickTrigger : public IGameObject
{
public:
	/**
	 * @brief 마우스 클릭을 감지하는 오브젝트의 디폴트 생성자입니다.
	 */
	ClickTrigger() = default;


	/**
	 * @brief 마우스 클릭을 감지하는 오브젝트의 가상 소멸자입니다.
	 * 
	 * @note 마우스 클릭을 감지하는 오브젝트 내부에서 할당된 리소스를 해제하기 위해서는 Release 메서드를 호출해야 합니다.
	 */
	virtual ~ClickTrigger();


	/**
	 * @brief 마우스 클릭을 감지하는 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ClickTrigger);


	/**
	 * @brief 마우스 클릭을 감지하는 오브젝트를 초기화합니다.
	 * 
	 * @param text 클릭 감지 여부를 표시할 때 사용할 텍스트입니다.
	 * @param center 클릭 감지 여부를 표시할 때 사용할 텍스트의 중심 위치입니다.
	 * @param color 텍스트의 색상입니다.
	 * @param trigger 클릭 감지 시 수행할 트리거 이벤트입니다.
	 */
	void Initialize(const std::wstring& text, const Vector2f& center, const Vector4f& color, const std::function<void()>& trigger);


	/**
	 * @brief 마우스 클릭을 감지하는 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief 마우스 클릭을 감지하는 오브젝트를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 마우스 클릭을 감지하는 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 클릭이 감지 되었는지 확인합니다.
	 * 
	 * @return 클릭이 감지 되었다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsClick() const { return bIsClick_; }


private:
	/**
	 * @brief 클릭 감지 여부입니다.
	 */
	bool bIsClick_ = false;


	/**
	 * @brief 클릭 감지 여부를 표시할 때 사용할 텍스트의 폰트입니다.
	 */
	TTFont* font_ = nullptr;


	/**
	 * @brief 클릭 감지 여부를 표시할 때 사용할 텍스트입니다.
	 */
	std::wstring text_;


	/**
	 * @brief 텍스트의 색상입니다.
	 */
	Vector4f color_;


	/**
	 * @brief 텍스트의 중심 위치입니다.
	 */
	Vector2f center_;


	/**
	 * @brief 이벤트 감지 시 수행할 트리거 이벤트입니다.
	 */
	std::function<void()> trigger_;
};