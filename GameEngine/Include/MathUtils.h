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
}