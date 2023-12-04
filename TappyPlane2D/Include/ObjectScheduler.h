#pragma once

#include <vector>

#include "Rock.h"
#include "Star.h"

class Plane;


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
	 * @brief ������Ʈ �����ٷ��� ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
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


	/**
	 * @brief ������ ���� ���� �浹�� �� ������Ʈ�� ����ϴ�.
	 * 
	 * @param plane �浹 �˻縦 ������ ������Դϴ�.
	 * 
	 * @return ������ ���� ���� �浹�� �� ������Ʈ�� ��ȯ�մϴ�. �浹���� �ʴ´ٸ� nullptr�� ��ȯ�մϴ�.
	 */
	Star* GetCollisionStar(const Plane* plane);


	/**
	 * @brief ������ ���� ������Ʈ��� �浹�ϴ��� Ȯ���մϴ�.
	 * 
	 * @param plane �浹 �˻縦 ������ ������Դϴ�.
	 * 
	 * @return ������ ���� ������Ʈ���� �浹�Ѵٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsCollisionRocks(const Plane* plane);


	/**
	 * @brief �����ٸ� Ȱ��ȭ ���θ� �����մϴ�.
	 * 
	 * @param bIsActive ������ �����ٸ� Ȱ��ȭ �����Դϴ�.
	 */
	void SetActive(bool bIsActive) { bIsActive_ = bIsActive; }


	/**
	 * @brief �����ٸ� Ȱ��ȭ�� �Ǿ��ִ��� Ȯ���մϴ�.
	 * 
	 * @return �����ٸ� Ȱ��ȭ�� �Ǿ� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsActive() const { return bIsActive_; }

	
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
	 * @brief �����ٸ� Ȱ��ȭ �����Դϴ�.
	 */
	bool bIsActive_ = false;


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