#pragma once

#include <cstdint>


/**
 * @brief ���� ������ �ð��� �����ϴ� Ÿ�̸��Դϴ�.
 */
class GameTimer
{
public:
	/**
	 * @brief Ÿ�̸� Ŭ������ �������Դϴ�.
	 *
	 * @note Ÿ�̸� Ŭ������ �����ڴ� �ʱ�ȭ�� �������� �����Ƿ� �ݵ�� Start Ȥ�� Reset �޼��带 ȣ���ؾ� �մϴ�.
	 */
	GameTimer();


	/**
	 * @brief Ÿ�̸� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ��ü�Դϴ�.
	 */
	GameTimer(GameTimer&& instance) noexcept
		: bIsStop_(instance.bIsStop_)
		, baseTime_(instance.baseTime_)
		, pausedTime_(instance.pausedTime_)
		, stopTime_(instance.stopTime_)
		, prevTime_(instance.prevTime_)
		, currTime_(instance.currTime_) {}


	/**
	 * @brief Ÿ�̸� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ��ü�Դϴ�.
	 */
	GameTimer(const GameTimer& instance) noexcept
		: bIsStop_(instance.bIsStop_)
		, baseTime_(instance.baseTime_)
		, pausedTime_(instance.pausedTime_)
		, stopTime_(instance.stopTime_)
		, prevTime_(instance.prevTime_)
		, currTime_(instance.currTime_) {}


	/**
	 * @brief Ÿ�̸� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~GameTimer() = default;


	/**
	 * @brief Ÿ�̸� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ��ü�Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	GameTimer& operator=(GameTimer&& instance) noexcept
	{
		if (this == &instance) return *this;

		bIsStop_ = instance.bIsStop_;
		baseTime_ = instance.baseTime_;
		pausedTime_ = instance.pausedTime_;
		stopTime_ = instance.stopTime_;
		prevTime_ = instance.prevTime_;
		currTime_ = instance.currTime_;

		return *this;
	}


	/**
	 * @brief Ÿ�̸� Ŭ������ ���� �������Դϴ�.
	 *
	 * @param instance ������ ��ü�Դϴ�.
	 *
	 * @return ������ ��ü�� �����ڸ� ��ȯ�մϴ�.
	 */
	GameTimer& operator=(const GameTimer& instance) noexcept
	{
		if (this == &instance) return *this;

		bIsStop_ = instance.bIsStop_;
		baseTime_ = instance.baseTime_;
		pausedTime_ = instance.pausedTime_;
		stopTime_ = instance.stopTime_;
		prevTime_ = instance.prevTime_;
		currTime_ = instance.currTime_;

		return *this;
	}


	/**
	 * @brief Ÿ�̸��� �� ���� ��Ÿ �ð����� ����ϴ�.
	 *
	 * @return �� ������ ��Ÿ �ð����� ��ȯ�մϴ�.
	 */
	float GetDeltaSeconds() const;


	/**
	 * @brief Ÿ�̸Ӱ� ������ �ð��� ������ ��ü �ʴ��� �ð����� ��ȯ�մϴ�.
	 *
	 * @return Ÿ�̸Ӱ� ���۵� ������ ������ �ð��� ������ ��ü �ð����� ��ȯ�մϴ�.
	 */
	float GetTotalSeconds() const;


	/**
	 * @brief Ÿ�̸��� ��� ���¸� �����մϴ�.
	 */
	void Reset();


	/**
	 * @brief Ÿ�̸Ӹ� �����մϴ�.
	 *
	 * @note Ÿ�̸Ӱ� �����Ǿ� �ִٸ� �߽õ� �������� ���۵˴ϴ�.
	 */
	void Start();


	/**
	 * @brief Ÿ�̸Ӹ� ������ŵ�ϴ�.
	 */
	void Stop();


	/**
	 * @brief Ÿ�̸Ӹ� ������Ʈ�մϴ�.
	 */
	void Tick();


private:
	/**
	 * @brief Ÿ�̸��� ���� ���θ� Ȯ���մϴ�.
	 */
	bool bIsStop_ = false;


	/**
	 * @brief Ÿ�̸Ӱ� ���۵� �ð��Դϴ�.
	 */
	uint64_t baseTime_ = 0LL;


	/**
	 * @brief Ÿ�̸Ӱ� ������ ������ ���� �ð��� �Դϴ�.
	 */
	uint64_t pausedTime_ = 0LL;


	/**
	 * @brief Ÿ�̸Ӱ� ������ �ð��Դϴ�.
	 */
	uint64_t stopTime_ = 0LL;


	/**
	 * @brief ������ Tick ȣ�� �ð��Դϴ�.
	 */
	uint64_t prevTime_ = 0LL;


	/**
	 * @brief Tick ȣ�� �ð��Դϴ�.
	 */
	uint64_t currTime_ = 0LL;


	/**
	 * @brief ���� ī���� ���� �������Դϴ�.
	 */
	double secondsPerCounter_ = 0.0;
};