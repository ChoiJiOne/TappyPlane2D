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

}