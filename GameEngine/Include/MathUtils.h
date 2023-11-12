#pragma once

#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>


/**
 * @brief ���� ���� Ȯ�� ����� �����մϴ�.
 */
namespace MathUtils
{
	/**
	 * @brief float Ÿ���� ����(��) ���Դϴ�.
	 */
	const float PI_F = 3.1415926535F;


	/**
	 * @brief double Ÿ���� ����(��) ���Դϴ�.
	 */
	const double PI_D = 3.1415926535897931;


	/**
	 * @brief float Ÿ���� ���Ѵ� ���Դϴ�.
	 */
	const float INFINITY_F = std::numeric_limits<float>::infinity();


	/**
	 * @brief double Ÿ���� ���Ѵ� ���Դϴ�.
	 */
	const double INFINITY_D = std::numeric_limits<double>::infinity();


	/**
	 * @brief float Ÿ���� ���� ���Ѵ� ���Դϴ�.
	 */
	const float NINFINITY_F = -std::numeric_limits<float>::infinity();


	/**
	 * @brief double Ÿ���� ���� ���Ѵ� ���Դϴ�.
	 */
	const double NINFINITY_D = -std::numeric_limits<double>::infinity();


	/**
	 * @brief float Ÿ���� Ÿ���� ���Ƿ�(��) ���Դϴ�.
	 */
	const float EPSILON_F = std::numeric_limits<float>::epsilon();


	/**
	 * @brief double Ÿ���� ���Ƿ�(��) ���Դϴ�.
	 */
	const double EPSILON_D = std::numeric_limits<double>::epsilon();
}