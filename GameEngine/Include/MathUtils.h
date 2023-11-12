#pragma once

#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>


/**
 * @brief 수학 관련 확장 기능을 제공합니다.
 */
namespace MathUtils
{
	/**
	 * @brief float 타입의 파이(π) 값입니다.
	 */
	const float PI_F = 3.1415926535F;


	/**
	 * @brief double 타입의 파이(π) 값입니다.
	 */
	const double PI_D = 3.1415926535897931;


	/**
	 * @brief float 타입의 무한대 값입니다.
	 */
	const float INFINITY_F = std::numeric_limits<float>::infinity();


	/**
	 * @brief double 타입의 무한대 값입니다.
	 */
	const double INFINITY_D = std::numeric_limits<double>::infinity();


	/**
	 * @brief float 타입의 음의 무한대 값입니다.
	 */
	const float NINFINITY_F = -std::numeric_limits<float>::infinity();


	/**
	 * @brief double 타입의 음의 무한대 값입니다.
	 */
	const double NINFINITY_D = -std::numeric_limits<double>::infinity();


	/**
	 * @brief float 타입의 타입의 엡실론(ε) 값입니다.
	 */
	const float EPSILON_F = std::numeric_limits<float>::epsilon();


	/**
	 * @brief double 타입의 엡실론(ε) 값입니다.
	 */
	const double EPSILON_D = std::numeric_limits<double>::epsilon();


	/**
	 * @brief 라디안 각을 육십분법 각으로 변환합니다.
	 *
	 * @param Radian 변환할 라디안 각입니다.
	 *
	 * @return 변환된 육십분법 각입니다.
	 */
	inline float ToDegree(float Radian)
	{
		return (Radian * 180.0f) / PI_F;
	}


	/**
	 * @brief 라디안 각을 육십분법 각으로 변환합니다.
	 *
	 * @param Radian 변환할 라디안 각입니다.
	 *
	 * @return 변환된 육십분법 각입니다.
	 */
	inline double ToDegree(double Radian)
	{
		return (Radian * 180.0) / PI_D;
	}


	/**
	 * @brief 육십분법 각을 라디안 각으로 변환합니다.
	 *
	 * @param Degree 변환할 육십분법 각입니다.
	 *
	 * @return 변환된 라디안 각입니다.
	 */
	inline float ToRadian(float Degree)
	{
		return (Degree * PI_F) / 180.0f;
	}


	/**
	 * @brief 육십분법 각을 라디안 각으로 변환합니다.
	 *
	 * @param Degree 변환할 육십분법 각입니다.
	 *
	 * @return 변환된 라디안 각입니다.
	 */
	inline double ToRadian(double Degree)
	{
		return (Degree * PI_D) / 180.0;
	}


	/**
	 * @brief 부동 소수점 값이 0에 가까운지 확인합니다.
	 *
	 * @param value 0에 가까운지 확인할 값입니다.
	 * @param epsilon 값 확인을 위한 엡실론 값입니다.
	 *
	 * @return 부동 소수점 값이 0에 가깝다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	inline bool NearZero(float value, float epsilon = EPSILON_F)
	{
		return (std::fabs(value) <= epsilon);
	}


	/**
	 * @brief 부동 소수점 값이 0에 가까운지 확인합니다.
	 *
	 * @param value 0에 가까운지 확인할 값입니다.
	 * @param epsilon 값 확인을 위한 엡실론 값입니다.
	 *
	 * @return 부동 소수점 값이 0에 가깝다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	inline bool NearZero(double value, double epsilon = EPSILON_D)
	{
		return (std::abs(value) <= epsilon);
	}


	/**
	 * @brief 두 값중 큰 값을 반환합니다.
	 *
	 * @param lhs 크기를 비교할 값 중 왼쪽 값입니다.
	 * @param rhs 크기를 비교할 값 중 오른쪽 값입니다.
	 *
	 * @return 두 값 중 큰 값을 반환합니다.
	 */
	template <typename T>
	T Max(const T& lhs, const T& rhs)
	{
		return (lhs < rhs ? rhs : lhs);
	}


	/**
	 * @brief 두 값중 작은 값을 반환합니다.
	 *
	 * @param lhs 크기를 비교할 값 중 왼쪽 값입니다.
	 * @param rhs 크기를 비교할 값 중 오른쪽 값입니다.
	 *
	 * @return 두 값 중 작은 값을 반환합니다.
	 */
	template <typename T>
	T Min(const T& lhs, const T& rhs)
	{
		return (lhs < rhs ? lhs : rhs);
	}


	/**
	 * @brief 값을 [lower, upper] 범위로 자릅니다.
	 * 
	 * @param value 범위로 자를 값입니다.
	 * @param lower 범위의 최소값입니다.
	 * @param upper 범위의 최대값입니다.
	 * 
	 * @return 범위로 잘려 나간 값을 반환합니다.
	 */
	template <typename T>
	T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, value));
	}
}