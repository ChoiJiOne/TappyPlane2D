#pragma once

#include "Macro.h"


/**
 * @brief ���� �� �������̽��Դϴ�.
 * 
 * @note ���� ���� �� ������Ʈ�� ��� �� �������̽��� ��ӹ޾ƾ��մϴ�.
 */
class IScene
{
public:
	/**
	 * @brief ���� ���� ����Ʈ �������Դϴ�.
	 */
	IScene() = default;


	/**
	 * @brief ���� ���� ���� �Ҹ����Դϴ�.
	 */
	virtual ~IScene() {}


	/**
	 * @brief ���� ���� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(IScene);


	/**
	 * @brief ���� ���� �����մϴ�.
	 */
	virtual void EnterScene() = 0;


	/**
	 * @brief ���� ������ �����մϴ�.
	 */
	virtual void ExitScene() = 0;


	/**
	 * @brief ���� ���� �����ߴ��� Ȯ���մϴ�.
	 * 
	 * @return ���� ���� �����ߴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	virtual bool IsEnterScene() = 0;


	/**
	 * @brief ���� ���� �� �������� �����մϴ�.
	 * 
	 * @param deltaSeconds ��Ÿ �ð����Դϴ�.
	 */
	virtual void TickScene(float deltaSeconds) = 0;


	/**
	 * @brief ���� ���� ���� ���� ���� �����մϴ�.
	 * 
	 * @param scene ���� ���� ���� ������ ���� ���Դϴ�.
	 */
	virtual void SetNextScene(IScene* scene) = 0;


	/**
	 * @brief ���� ���� ���� ���� ���� ����ϴ�.
	 * 
	 * @return ���� ���� ���� ����� ���� ���� ������ ���� ��ȯ�մϴ�.
	 */
	virtual IScene* GetNextScene() = 0;
};