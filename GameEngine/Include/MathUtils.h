#pragma once

#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>

#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


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


	/**
	 * @brief ���� ���� ���ʺй� ������ ��ȯ�մϴ�.
	 *
	 * @param Radian ��ȯ�� ���� ���Դϴ�.
	 *
	 * @return ��ȯ�� ���ʺй� ���Դϴ�.
	 */
	inline float ToDegree(float Radian)
	{
		return (Radian * 180.0f) / PI_F;
	}


	/**
	 * @brief ���� ���� ���ʺй� ������ ��ȯ�մϴ�.
	 *
	 * @param Radian ��ȯ�� ���� ���Դϴ�.
	 *
	 * @return ��ȯ�� ���ʺй� ���Դϴ�.
	 */
	inline double ToDegree(double Radian)
	{
		return (Radian * 180.0) / PI_D;
	}


	/**
	 * @brief ���ʺй� ���� ���� ������ ��ȯ�մϴ�.
	 *
	 * @param Degree ��ȯ�� ���ʺй� ���Դϴ�.
	 *
	 * @return ��ȯ�� ���� ���Դϴ�.
	 */
	inline float ToRadian(float Degree)
	{
		return (Degree * PI_F) / 180.0f;
	}


	/**
	 * @brief ���ʺй� ���� ���� ������ ��ȯ�մϴ�.
	 *
	 * @param Degree ��ȯ�� ���ʺй� ���Դϴ�.
	 *
	 * @return ��ȯ�� ���� ���Դϴ�.
	 */
	inline double ToRadian(double Degree)
	{
		return (Degree * PI_D) / 180.0;
	}


	/**
	 * @brief �ε� �Ҽ��� ���� 0�� ������� Ȯ���մϴ�.
	 *
	 * @param value 0�� ������� Ȯ���� ���Դϴ�.
	 * @param epsilon �� Ȯ���� ���� ���Ƿ� ���Դϴ�.
	 *
	 * @return �ε� �Ҽ��� ���� 0�� �����ٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	inline bool NearZero(float value, float epsilon = EPSILON_F)
	{
		return (std::fabs(value) <= epsilon);
	}


	/**
	 * @brief �ε� �Ҽ��� ���� 0�� ������� Ȯ���մϴ�.
	 *
	 * @param value 0�� ������� Ȯ���� ���Դϴ�.
	 * @param epsilon �� Ȯ���� ���� ���Ƿ� ���Դϴ�.
	 *
	 * @return �ε� �Ҽ��� ���� 0�� �����ٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	inline bool NearZero(double value, double epsilon = EPSILON_D)
	{
		return (std::abs(value) <= epsilon);
	}


	/**
	 * @brief �� ���� ū ���� ��ȯ�մϴ�.
	 *
	 * @param lhs ũ�⸦ ���� �� �� ���� ���Դϴ�.
	 * @param rhs ũ�⸦ ���� �� �� ������ ���Դϴ�.
	 *
	 * @return �� �� �� ū ���� ��ȯ�մϴ�.
	 */
	template <typename T>
	inline T Max(const T& lhs, const T& rhs)
	{
		return (lhs < rhs ? rhs : lhs);
	}


	/**
	 * @brief �� ���� ���� ���� ��ȯ�մϴ�.
	 *
	 * @param lhs ũ�⸦ ���� �� �� ���� ���Դϴ�.
	 * @param rhs ũ�⸦ ���� �� �� ������ ���Դϴ�.
	 *
	 * @return �� �� �� ���� ���� ��ȯ�մϴ�.
	 */
	template <typename T>
	inline T Min(const T& lhs, const T& rhs)
	{
		return (lhs < rhs ? lhs : rhs);
	}


	/**
	 * @brief ���� [lower, upper] ������ �ڸ��ϴ�.
	 * 
	 * @param value ������ �ڸ� ���Դϴ�.
	 * @param lower ������ �ּҰ��Դϴ�.
	 * @param upper ������ �ִ밪�Դϴ�.
	 * 
	 * @return ������ �߷� ���� ���� ��ȯ�մϴ�.
	 */
	template <typename T>
	inline T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, value));
	}


	/**
	 * @brief ������ ������ �����մϴ�.
	 *
	 * @param minValue ������ ���� ������ �ּڰ��Դϴ�.
	 * @param maxValue ������ ���� ������ �ִ��Դϴ�.
	 *
	 * @return ������ ������ ������ ��ȯ�մϴ�.
	 */
	inline int32_t GenerateRandomInt(int32_t minValue, int32_t maxValue)
	{
		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		std::uniform_int_distribution<int32_t> distribution(std::min<int32_t>(minValue, maxValue), std::max<int32_t>(minValue, maxValue));

		return distribution(generator);
	}
}