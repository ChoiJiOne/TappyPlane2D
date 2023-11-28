#pragma once

#include "IGameObject.h"
#include "LineSegment.h"
#include "Texture2D.h"
#include "Vector2.h"

class Plane;


/**
 * @brief ���� ������Ʈ�Դϴ�.
 */
class Rock : public IGameObject
{
public:
	/**
	 * @brief ���� ������Ʈ�� �����Դϴ�.
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
	 * @brief ���� ������Ʈ�� ����Ʈ �������Դϴ�.
	 */
	Rock() = default;


	/**
	 * @brief ���� ������Ʈ�� ���� �Ҹ����Դϴ�.
	 *
	 * @note ���� ������Ʈ ���ο��� �Ҵ�� ���ҽ��� �����ϱ� ���ؼ��� Release �޼��带 ȣ���ؾ� �մϴ�.
	 */
	virtual ~Rock();


	/**
	 * @brief ���� ������Ʈ�� ���� �����ڿ� ���� �����ڸ� ��������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Rock);


	/**
	 * @brief ���� ������Ʈ�� �ʱ�ȭ�մϴ�.
	 * 
	 * @param type ���� ������Ʈ�� Ÿ���Դϴ�.
	 * @param startXPosition ���� ������Ʈ�� ���� X��ǥ�Դϴ�.
	 */
	void Initialize(const EType& type, const float& startXPosition);


	/**
	 * @brief ���� ������Ʈ�� ������Ʈ�մϴ�.
	 *
	 * @param deltaSeconds ��Ÿ �ð� ���Դϴ�.
	 */
	virtual void Update(float deltaSeconds) override;


	/**
	 * @brief ���� ������Ʈ�� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Render() override;


	/**
	 * @brief ���� ������Ʈ ���� ���ҽ��� �Ҵ� �����մϴ�.
	 *
	 * @note ���� ������Ʈ �������̽��� ��ӹ޴� ���� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief ������ �浹�ߴ��� �˻��մϴ�.
	 * 
	 * @param plane �浹 �˻縦 ������ ����� ������Ʈ�Դϴ�.
	 */
	bool IsCollision(const Plane* plane) const;


	/**
	 * @brief ���� ������Ʈ�� �ܰ������� ����ϴ�.
	 * 
	 * @return ���� ������Ʈ �ܰ��� �迭�� ��� �����ڸ� ��ȯ�մϴ�.
	 */
	const std::array<LineSegment, 4>& GetOutlines() const { return outlines_; }


private:
	/**
	 * @brief ���� ������Ƽ�� �ʱ�ȭ�մϴ�.
	 */
	void SetupProperties();


public:
	/**
	 * @brief ���� ������Ʈ�� Ÿ���Դϴ�.
	 */
	EType type_ = EType::Plain;


	/**
	 * @brief ������ ���� X��ǥ�Դϴ�.
	 */
	float startXPosition_ = 0.0f;


	/**
	 * @brief ��� ���� �ؽ�ó ���ҽ��Դϴ�.
	 */
	Texture2D* topTexture_ = nullptr;


	/**
	 * @brief ��� ���� ������ �߽� ��ǥ�Դϴ�.
	 */
	Vector2f topCenter_;


	/**
	 * @brief ��� ������ ���� ũ���Դϴ�.
	 */
	float topWidth_ = 0.0f;


	/**
	 * @brief ��� ������ ���� ũ���Դϴ�.
	 */
	float topHeight_ = 0.0f;


	/**
	 * @brief �ϴ� ���� �ؽ�ó ���ҽ��Դϴ�.
	 */
	Texture2D* bottomTexture_ = nullptr;


	/**
	 * @brief �ϴ� ���� ������ �߽� ��ǥ�Դϴ�.
	 */
	Vector2f bottomCenter_;


	/**
	 * @brief �ϴ� ������ ���� ũ���Դϴ�.
	 */
	float bottomWidth_ = 0.0f;


	/**
	 * @brief �ϴ� ������ ���� ũ���Դϴ�.
	 */
	float bottomHeight_ = 0.0f;


	/**
	 * @brief ������ �ܰ� �����Դϴ�.
	 */
	std::array<LineSegment, 4> outlines_;


	/**
	 * @brief ������ �̵� �ӵ��Դϴ�.
	 */
	float speed_ = 0.0f;
};