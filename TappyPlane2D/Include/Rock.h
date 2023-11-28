#pragma once

#include "IGameObject.h"
#include "LineSegment.h"
#include "Texture2D.h"
#include "Vector2.h"

class Plane;


/**
 * @brief 바위 오브젝트입니다.
 */
class Rock : public IGameObject
{
public:
	/**
	 * @brief 바위 오브젝트의 종류입니다.
	 */
	enum class EType : int32_t
	{
		Plain = 0x00,
		Grass = 0x01,
		Ice = 0x02,
		Snow = 0x03,
	};


public:
	/**
	 * @brief 바위 오브젝트의 디폴트 생성자입니다.
	 */
	Rock() = default;


	/**
	 * @brief 바위 오브젝트의 가상 소멸자입니다.
	 *
	 * @note 바위 오브젝트 내부에서 할당된 리소스를 해제하기 위해서는 Release 메서드를 호출해야 합니다.
	 */
	virtual ~Rock();


	/**
	 * @brief 바위 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Rock);


	/**
	 * @brief 바위 오브젝트를 초기화합니다.
	 * 
	 * @param type 바위 오브젝트의 타입입니다.
	 * @param startXPosition 바위 오브젝트의 시작 X좌표입니다.
	 */
	void Initialize(const EType& type, const float& startXPosition);


	/**
	 * @brief 바위 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief 바위 오브젝트를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief 바위 오브젝트 내의 리소스를 할당 해제합니다.
	 *
	 * @note 바위 오브젝트 인터페이스를 상속받는 하위 클래스에서 반드시 구현해야 합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 비행기와 충돌했는지 검사합니다.
	 * 
	 * @param plane 충돌 검사를 수행할 비행기 오브젝트입니다.
	 */
	bool IsCollision(const Plane* plane) const;


	/**
	 * @brief 바위 오브젝트의 외곽선들을 얻습니다.
	 * 
	 * @return 바위 오브젝트 외곽선 배열의 상수 참조자를 반환합니다.
	 */
	const std::array<LineSegment, 4>& GetOutlines() const { return outlines_; }


private:
	/**
	 * @brief 내부 프로퍼티를 초기화합니다.
	 */
	void SetupProperties();


public:
	/**
	 * @brief 바위 오브젝트의 타입입니다.
	 */
	EType type_ = EType::Plain;


	/**
	 * @brief 바위의 시작 X좌표입니다.
	 */
	float startXPosition_ = 0.0f;


	/**
	 * @brief 상단 바위 텍스처 리소스입니다.
	 */
	Texture2D* topTexture_ = nullptr;


	/**
	 * @brief 상단 바위 영역의 중심 좌표입니다.
	 */
	Vector2f topCenter_;


	/**
	 * @brief 상단 바위의 가로 크기입니다.
	 */
	float topWidth_ = 0.0f;


	/**
	 * @brief 상단 바위의 세로 크기입니다.
	 */
	float topHeight_ = 0.0f;


	/**
	 * @brief 하단 바위 텍스처 리소스입니다.
	 */
	Texture2D* bottomTexture_ = nullptr;


	/**
	 * @brief 하단 바위 영역의 중심 좌표입니다.
	 */
	Vector2f bottomCenter_;


	/**
	 * @brief 하단 바위의 가로 크기입니다.
	 */
	float bottomWidth_ = 0.0f;


	/**
	 * @brief 하단 바위의 세로 크기입니다.
	 */
	float bottomHeight_ = 0.0f;


	/**
	 * @brief 바위의 외곽 라인입니다.
	 */
	std::array<LineSegment, 4> outlines_;


	/**
	 * @brief 바위의 이동 속도입니다.
	 */
	float speed_ = 0.0f;
};