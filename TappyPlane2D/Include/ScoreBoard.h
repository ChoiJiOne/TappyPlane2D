#pragma once

#include <map>

#include "IGameObject.h"
#include "TTFont.h"
#include "Vector2.h"
#include "Vector4.h"


/**
 * @brief 플레이어의 스코어를 표시하는 오브젝트입니다.
 */
class ScoreBoard : public IGameObject
{
public:
	/**
	 * @brief 스코어 보드 오브젝트의 디폴트 생성자입니다.
	 */
	ScoreBoard() = default;


	/**
	 * @brief 스코어 보드 오브젝트의 가상 소멸자입니다.
	 *
	 * @note 스코어 보드 오브젝트 내부에서 할당된 리소스를 해제하기 위해서는 Release 메서드를 호출해야 합니다.
	 */
	virtual ~ScoreBoard();


	/**
	 * @brief 스코어 보드 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ScoreBoard);


	/**
	 * @brief 스코어 보드 오브젝트를 초기화합니다.
	 * 
	 * @param center 스코어 보드의 중심 좌표입니다.
	 * @param color 스코어 보드 텍스트의 색상입니다.
	 */
	void Initialize(const Vector2f& center, const Vector4f& color);


	/**
	 * @brief 스코어 보드 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief 스코어 보드 오브젝트를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 스코어 보드 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 스코어 보드 활성화 여부를 설정합니다.
	 *
	 * @param bIsActive 설정할 스코어 보드 활성화 여부입니다.
	 */
	void SetActive(bool bIsActive) { bIsActive_ = bIsActive; }


	/**
	 * @brief 스코어 보드 활성화가 되어있는지 확인합니다.
	 *
	 * @return 스코어 보드 활성화가 되어 있다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsActive() const { return bIsActive_; }


	/**
	 * @brief 스코어 보드의 스코어를 설정하는 기능 추가
	 * 
	 * @param score 설정할 스코어 값입니다.
	 */
	void SetScore(const int32_t& score) { score_ = score; }


private:
	/**
	 * @brief 스코어 보드의 활성화 여부입니다.
	 */
	bool bIsActive_ = false;


	/**
	 * @brief 스코어 보드의 중심 좌표입니다.
	 */
	Vector2f center_;


	/**
	 * @brief 표시할 점수입니다.
	 */
	int32_t score_ = 0;


	/**
	 * @brief 표시할 숫자의 색상입니다.
	 */
	Vector4f color_;


	/**
	 * @brief 스코어 보드의 폰트입니다.
	 */
	TTFont* font_ = nullptr;
};