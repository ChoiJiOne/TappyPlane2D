#pragma once

#include "AABB.h"
#include "IGameObject.h"
#include "Texture2D.h"
#include "Vector2.h"


/**
 * @brief 그라운드 오브젝트입니다.
 */
class Ground : public IGameObject
{
public:
	/**
	 * @brief 그라운드 오브젝트의 종류입니다.
	 */
	enum class EType : int32_t
	{
		Dirt = 0x00,
		Grass = 0x01,
		Ice = 0x02,
		Rock = 0x03,
		Snow = 0x04,
	};


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
	 * 
	 * @param type 그라운드 오브젝트의 타입입니다.
	 */
	void Initialize(const EType& type);


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
	 */
	virtual void Release() override;


	/**
	 * @brief 그라운드의 움직임 여부를 설정합니다.
	 *
	 * @param bCanMove 설정할 그라운드 움직임 여부입니다.
	 */
	void SetCanMove(bool bCanMove) { bCanMove_ = bCanMove; }


	/**
	 * @brief 그라운드의 움직임 여부를 얻습니다.
	 *
	 * @return 그라운드가 움직일 수 있다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool CanMove() const { return bCanMove_; }


private:
	/**
	 * @brief 그라운드가 움직일 수 있는지 확인합니다.
	 */
	bool bCanMove_ = false;


	/**
	 * @brief 그라운드 텍스처 리소스입니다.
	 */
	Texture2D* texture_ = nullptr;

	
	/**
	 * @brief 그라운드 상단의 중심 위치입니다.
	 */
	Vector2f topCenter_;


	/**
	 * @brief 그라운드 하단의 중심 위치입니다.
	 */
	Vector2f bottomCenter_;


	/**
	 * @brief 그라운드의 가로 크기입니다.
	 */
	float width_ = 0.0f;
	

	/**
	 * @brief 그라운드의 세로 크기입니다.
	 */
	float height_ = 0.0f;


	/**
	 * @brief 그라운드의 스크롤 속도입니다.
	 *
	 * @note
	 * - 이 속도는 초당 움직이는 픽셀 수입니다.
	 * - 예를 들어 200 이라면 초당 200 픽셀 만큼 움직입니다.
	 */
	float scrollSpeed_ = 0.0f;


	/**
	 * @brief 그라운드의 스크롤 지점입니다.
	 */
	float scrollPosition_ = 0.0f;
};