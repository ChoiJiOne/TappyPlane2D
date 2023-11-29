#pragma once

#include <map>

#include "IGameObject.h"
#include "Texture2D.h"
#include "Vector2.h"


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
	 * @param numberWidth 표시할 숫자의 가로 크기입니다.
	 * @param numberHeight 표시할 숫자의 세로 크기입니다.
	 * @param numberGap 표시할 숫자 간의 간격입니다.
	 */
	void Initialize(const Vector2f& center, const float& numberWidth, const float& numberHeight, const float& numberGap);


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
	 * @brief 표시할 숫자의 가로 크기입니다.
	 */
	float numberWidth_ = 0.0f;


	/**
	 * @brief 표시할 숫자의 세로 크기입니다.
	 */
	float numberHeight_ = 0.0f;


	/**
	 * @brief 표시한 숫자 간의 갭 차이입니다.
	 */
	float numberGap_ = 0.0f;


	/**
	 * @brief 숫자의 텍스처 리소스입니다.
	 */
	std::map<char, Texture2D*> numberTextureMap_;
};