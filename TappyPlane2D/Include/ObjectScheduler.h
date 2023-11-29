#pragma once

#include <vector>

#include "Rock.h"
#include "Star.h"


/**
 * @brief ������Ʈ �����ٷ��Դϴ�.
 * 
 * @note �� ������Ʈ�� ������ �� ������Ʈ�� ����/�����մϴ�.
 */
class ObjectScheduler : public IGameObject
{
public:
	/**
	 * @brief ������Ʈ �����ٷ��� ����Ʈ �������Դϴ�.
	 */
	ObjectScheduler() = default;


	/**
	 * @brief ������Ʈ �����ٷ��� ���� �Ҹ����Դϴ�.
	 *
	 * @note ������Ʈ �����ٷ� ���ο��� �Ҵ�� ���ҽ��� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~ObjectScheduler();


	/**
	 * @brief ������Ʈ �����ٷ��� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(ObjectScheduler);


	/**
	 * @brief ������Ʈ �����ٷ��� �ʱ�ȭ�մϴ�.
	 * 
	 * @param rockType ������ ���� ������Ʈ�� Ÿ���Դϴ�.
	 * @param startXPosition ������Ʈ�� ������ ��ġ�� X��ǥ�Դϴ�.
	 * @param countMaxObject ������ ������Ʈ�� �ִ� �����Դϴ�.
	 */
	void Initialize(const Rock::EType& rockType, const float& startXPosition, const int32_t& countMaxObject = 15);

	
	/**
	 * @brief ������Ʈ �����ٷ��� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief ������Ʈ �����ٷ��� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ������Ʈ �����ٷ� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief ������Ʈ�� ���¸� Wait���� Move�� ������ �� �ִ��� Ȯ���մϴ�.
	 * 
	 * @param index ���¸� ������ �� �ִ��� Ȯ���� ������Ʈ�� �ε����Դϴ�.
	 */
	bool CanChangeWaitToMove(int32_t index);


	/**
	 * @brief ������Ʈ�� ��׶��� ������ �������� Ȯ���մϴ�.
	 * 
	 * @param index ��׶��� ������ �������� Ȯ���� ������Ʈ�� �ε����Դϴ�.
	 */
	bool CheckOuterFromBackground(int32_t index);
	

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
	 * @brief ������Ʈ ������ �Ÿ��Դϴ�.
	 */
	float interval_ = 0.0f;


	/**
	 * @brief ������Ʈ�� �ִ� �����Դϴ�.
	 */
	int32_t countMaxObject_ = 0;


	/**
	 * @brief ���� ���� ���� ������Ʈ�Դϴ�.
	 */
	std::vector<Rock*> rocks_;


	/**
	 * @brief ���� ���� �� ������Ʈ�Դϴ�.
	 */
	std::vector<Star*> stars_;
};