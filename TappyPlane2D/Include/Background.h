#pragma once

#include "IGameObject.h"
#include "Texture2D.h"


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
	 *
	 * @note ��׶��� ������Ʈ �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief ��׶��� �ؽ�ó ���ҽ��Դϴ�.
	 */
	Texture2D* texture_ = nullptr;
};