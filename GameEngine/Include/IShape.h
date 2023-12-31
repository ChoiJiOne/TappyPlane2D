#pragma once


/**
 * @brief 게임 오브젝트 형태의 인터페이스입니다.
 */
class IShape
{
public:
	/**
	 * @brief 게임 오브젝트 형태의 타입입니다.
	 */
	enum class EType
	{
		None = 0x00,
		AABB = 0x01,
		Circle = 0x02,
		LineSegment = 0x03,
	};


public:
	/**
	 * @brief 게임 오브젝트 형태를 나타내는 인터페이스의 디폴트 생성자입니다.
	 */
	IShape() = default;


	/**
	 * @brief 게임 오브젝트 형태를 나타내는 인터페이스의 가상 소멸자입니다.
	 */
	virtual ~IShape() {}


	/**
	 * @brief 게임 오브젝트 형태를 얻습니다.
	 * 
	 * @return 게임 오브젝트 형태를 반환합니다.
	 */
	virtual EType GetType() const = 0;


	/**
	 * @brief 다른 게임 오브젝트와의 충돌 여부를 검사합니다.
	 * 
	 * @param shape 충돌 검사를 수행할 오브젝트입니다.
	 * 
	 * @return 다른 오브젝트와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 * 
	 * @note 한 오브젝트가 다른 오브젝트 내부에 포함되어도 충돌로 판단합니다.
	 */
	virtual bool IsCollision(const IShape* shape) const = 0;
};