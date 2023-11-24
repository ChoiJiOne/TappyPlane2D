#pragma once


/**
 * @brief ���� ������Ʈ ������ �������̽��Դϴ�.
 */
class IShape
{
public:
	/**
	 * @brief ���� ������Ʈ ������ Ÿ���Դϴ�.
	 */
	enum class EType
	{
		None = 0x00,
		AABB = 0x01,
	};


public:
	/**
	 * @brief ���� ������Ʈ ���¸� ��Ÿ���� �������̽��� ����Ʈ �������Դϴ�.
	 */
	IShape() = default;


	/**
	 * @brief ���� ������Ʈ ���¸� ��Ÿ���� �������̽��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~IShape() {}


	/**
	 * @brief ���� ������Ʈ ������ Ÿ���� �����մϴ�.
	 * 
	 * @param type ������ Ÿ���Դϴ�.
	 */
	virtual void SetType(const EType& type) = 0;


	/**
	 * @brief ���� ������Ʈ ���¸� ����ϴ�.
	 * 
	 * @return ���� ������Ʈ ���¸� ��ȯ�մϴ�.
	 */
	virtual EType GetType() = 0;


	/**
	 * @brief �ٸ� ���� ������Ʈ���� �浹 ���θ� �˻��մϴ�.
	 * 
	 * @note �ٸ� ������Ʈ�� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 * 
	 * @note �� ������Ʈ�� �ٸ� ������Ʈ ���ο� ���ԵǾ �浹�� �Ǵ��մϴ�.
	 */
	virtual bool IsCollision(const IShape* shape) = 0;
};