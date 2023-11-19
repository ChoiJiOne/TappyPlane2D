#include "GameTimer.h"

#include "AssertionMacro.h"

#include <windows.h>

GameTimer::GameTimer()
{
	int64_t counterPerSeconds;
	ASSERT((QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&counterPerSeconds))), "failed to query performance frequency...");

	secondsPerCounter_ = 1.0 / static_cast<double>(counterPerSeconds);
}

float GameTimer::GetDeltaSeconds() const
{
	if (bIsStop_)
	{
		return 0.0f;
	}
	else
	{
		return static_cast<float>(currTime_ - prevTime_) * static_cast<float>(secondsPerCounter_);
	}
}

float GameTimer::GetTotalSeconds() const
{
	if (bIsStop_)
	{
		return static_cast<float>(stopTime_ - pausedTime_ - baseTime_) * static_cast<float>(secondsPerCounter_);
	}
	else
	{
		return static_cast<float>(currTime_ - pausedTime_ - baseTime_) * static_cast<float>(secondsPerCounter_);
	}
}

void GameTimer::Reset()
{
	uint64_t counter;
	ASSERT((QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&counter))), "failed to query performance counter...");

	bIsStop_ = false;
	baseTime_ = counter;
	pausedTime_ = 0ULL;
	stopTime_ = 0ULL;
	prevTime_ = counter;
	currTime_ = counter;
}

void GameTimer::Start()
{
	if (bIsStop_)
	{
		uint64_t counter;
		ASSERT((QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&counter))), "failed to query performance counter...");

		pausedTime_ += (counter - stopTime_);
		prevTime_ = counter;
		stopTime_ = 0ULL;

		bIsStop_ = false;
	}
}

void GameTimer::Stop()
{
	if (!bIsStop_)
	{
		uint64_t counter;
		ASSERT((QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&counter))), "failed to query performance counter...");

		stopTime_ = counter;

		bIsStop_ = true;
	}
}

void GameTimer::Tick()
{
	uint64_t counter;
	ASSERT((QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&counter))), "failed to query performance counter...");

	prevTime_ = currTime_;
	currTime_ = counter;
}