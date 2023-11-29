#pragma once

#include "IGameObject.h"
#include "Texture2D.h"
#include "LineSegment.h"

class Plane;
class Rock;
class Star;


/**
 * @brief ��׶��� ������Ʈ�Դϴ�.
 * 
 * @note �������� �ٸ� ������Ʈ�麸�� �켱�Ǿ�� �մϴ�.
 */
class Background : public IGameObject
{
public:
	/**
	 * @brief ��׶��� ������Ʈ�� ����Ʈ �������Դϴ�.
	 * 
	 * @note ������ �̿��� �޼��忡�� ������ �ʱ�ȭ�� �����ؾ� �մϴ�.
	 */
	Background() = default;


	/**
	 * @brief ��׶��� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 * 
	 * @note ��׶��� ������Ʈ ���ο��� �Ҵ�� ���ҽ��� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~Background();


	/**
	 * @brief ��׶��� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Background);


	/**
	 * @brief ��׶��� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 */
	void Initialize();


	/**
	 * @brief ��׶��� ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief ��׶��� ������Ʈ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ��׶��� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ����Ⱑ ��׶��� ���ο� �ִ��� Ȯ���մϴ�.
	 * 
	 * @param plane ��׶��� ���ο� �ִ��� Ȯ���� ����� ������Ʈ�Դϴ�.
	 */
	bool IsInnerPlane(const Plane* plane) const;


	/**
	 * @brief ������ ��׶��� �ܺο� �ִ��� Ȯ���մϴ�.
	 * 
	 * @param rock ��׶��� �ܺο� �ִ��� Ȯ���� ���� ������Ʈ�Դϴ�.
	 */
	bool IsOuterRock(const Rock* rock) const;


	/**
	 * @brief ���� ��׶��� �ܺο� �ִ��� Ȯ���մϴ�.
	 * 
	 * @param star ��׶��� �ܺο� �ִ��� Ȯ���� �� ������Ʈ�Դϴ�.
	 */
	bool IsOuterStar(const Star* star) const;


	/**
	 * @brief ��׶����� ������ ���θ� �����մϴ�.
	 * 
	 * @param bCanMove ������ ��׶��� ������ �����Դϴ�.
	 */
	void SetCanMove(bool bCanMove) { bCanMove_ = bCanMove; }


	/**
	 * @brief ��׶����� ������ ���θ� ����ϴ�.
	 * 
	 * @return ��׶��尡 ������ �� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool CanMove() const { return bCanMove_; }


private:
	/**
	 * @brief ��׶��尡 ������ �� �ִ��� Ȯ���մϴ�.
	 */
	bool bCanMove_ = false;


	/**
	 * @brief ��׶����� ���� ũ���Դϴ�.
	 */
	float width_ = 0.0f;


	/**
	 * @brief ��׶����� ���� ũ���Դϴ�.
	 */
	float height_ = 0.0f;


	/**
	 * @brief ��׶��� �ؽ�ó ���ҽ��Դϴ�.
	 */
	Texture2D* texture_ = nullptr;


	/**
	 * @brief ��׶����� ��ũ�� �ӵ��Դϴ�.
	 * 
	 * @note 
	 * - �� �ӵ��� �ʴ� �����̴� �ȼ� ���Դϴ�.
	 * - ���� ��� 200 �̶�� �ʴ� 200 �ȼ� ��ŭ �����Դϴ�.
	 */
	float scrollSpeed_ = 0.0f;


	/**
	 * @brief ��׶����� ��ũ�� �����Դϴ�.
	 */
	float scrollPosition_ = 0.0f;


	/**
	 * @brief ��׶����� ��ũ�� �ִ� �����Դϴ�.
	 */
	float maxScrollPosition_ = 0.0f;


	/**
	 * @brief ��׶����� �ܰ����Դϴ�.
	 */
	std::array<LineSegment, 4> outlines_;
};