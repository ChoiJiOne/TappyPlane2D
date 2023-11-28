#pragma once

#include <list>

#include "Rock.h"
#include "Star.h"


/**
 * @brief ������Ʈ�� �����ϴ� ������Ʈ�Դϴ�.
 * 
 * @note �� ������Ʈ�� ������ �� ������Ʈ�� �����մϴ�.
 */
class ObjectGenerator : public IGameObject
{
public:
	/**
	 * @brief ������Ʈ�� �����ϴ� ������Ʈ�� ����Ʈ �������Դϴ�.
	 */
	ObjectGenerator() = default;


	/**
	 * @brief ������Ʈ�� �����ϴ� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 *
	 * @note ������Ʈ�� �����ϴ� ������Ʈ ���ο��� �Ҵ�� ���ҽ��� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~ObjectGenerator();


	/**
	 * @brief ������Ʈ�� �����ϴ� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ObjectGenerator);


	/**
	 * @brief ������Ʈ�� �����ϴ� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 * 
	 * @param rockType ������ ���� ������Ʈ�� Ÿ���Դϴ�.
	 * @param startXPosition ������Ʈ�� ������ ��ġ�� X��ǥ�Դϴ�.
	 */
	void Initialize(const Rock::EType& rockType, const float& startXPosition);

	
	/**
	 * @brief ������Ʈ�� �����ϴ� ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief ������Ʈ�� �����ϴ� ������Ʈ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ������Ʈ�� �����ϴ� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief ������Ʈ�� �����մϴ�.
	 */
	void GenerateObject();


	/**
	 * @brief ������Ʈ�� �ı��մϴ�.
	 */
	void DestroyObject();


private:
	/**
	 * @brief ������ ���� ������Ʈ�� Ÿ���Դϴ�.
	 */
	Rock::EType rockType_ = Rock::EType::Plain;


	/**
	 * @brief ������Ʈ�� ������ ��ġ�� X��ǥ�Դϴ�.
	 */
	float startXPosition_ = 0.0f;


	/**
	 * @brief ���� ���� ���� ������Ʈ�Դϴ�.
	 */
	std::list<Rock*> rocks_;


	/**
	 * @brief ������ ���� ������Ʈ�� ���Դϴ�.
	 */
	int32_t countOfRock_ = 0;


	/**
	 * @brief ���� ���� �� ������Ʈ�Դϴ�.
	 */
	std::list<Star*> stars_;


	/**
	 * @brief ������ �� ������Ʈ�� ���Դϴ�.
	 */
	int32_t countOfStar_ = 0;
};