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
	 * @brief ����(��) ���Դϴ�.
	 */
	const float Pi = 3.141592654f;


	/**
	 * @brief 2����(2��) ���Դϴ�.
	 */
	const float TwoPi = 6.283185307f;


	/**
	 * @brief ����(��) �� ���� ���Դϴ�.
	 */
	const float OneDivPi = 0.318309886f;


	/**
	 * @brief 2����(2��) �� ���� ���Դϴ�.
	 */
	const float OneDivTwoPi = 0.159154943f;


	/**
	 * @brief ����(��) �� �ݰ�(��/2)�Դϴ�.
	 */
	const float PiDiv2 = 1.570796327f;


	/**
	 * @brief ����(��) �� ���� �� ��(��/4)�Դϴ�.
	 */
	const float PiDiv4 = 0.785398163f;


	/**
	 * @brief ���� ���Ѵ� ���Դϴ�.
	 */
	const float Infinity = std::numeric_limits<float>::infinity();


	/**
	 * @brief ���� ���Ѵ� ���Դϴ�.
	 */
	const float NInfinity = -std::numeric_limits<float>::infinity();


	/**
	 * @brief ���Ƿ�(��) ���Դϴ�.
	 */
	const float Epsilon = std::numeric_limits<float>::epsilon();


	/**
	 * @brief ���� ���� ���ʺй� ������ ��ȯ�մϴ�.
	 *
	 * @param radian ��ȯ�� ���� ���Դϴ�.
	 *
	 * @return ��ȯ�� ���ʺй� ���Դϴ�.
	 */
	inline float ToDegree(float radian)
	{
		return (radian * 180.0f) / Pi;
	}


	/**
	 * @brief ���ʺй� ���� ���� ������ ��ȯ�մϴ�.
	 *
	 * @param degree ��ȯ�� ���ʺй� ���Դϴ�.
	 *
	 * @return ��ȯ�� ���� ���Դϴ�.
	 */
	inline float ToRadian(float degree)
	{
		return (degree * Pi) / 180.0f;
	}


	/**
	 * @brief �ε� �Ҽ��� ���� 0�� ������� Ȯ���մϴ�.
	 *
	 * @param value 0�� ������� Ȯ���� ���Դϴ�.
	 * @param epsilon �� Ȯ���� ���� ���Ƿ� ���Դϴ�.
	 *
	 * @return �ε� �Ҽ��� ���� 0�� �����ٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	inline bool NearZero(float value, float epsilon = Epsilon)
	{
		return (std::fabs(value) <= epsilon);
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
	 * @brief ���� ������ �����ϴ� ���� ���� ��ȯ�մϴ�.
	 *
	 * @param radian ���� ���� ���� ���� �����Դϴ�.
	 *
	 * @return ���� ������ �����ϴ� ���ΰ��� ��ȯ�մϴ�.
	 * 
	 * @note 
	 * - DirectXMath�� XMScalarSin ����
	 * - �˰����� 11���� �̴ϸƽ�(Minimax) �ٻ�ġ(1th-degree Minimax approximation) ���
	 * - https://gist.github.com/publik-void/067f7f2fef32dbe5c27d6e215f824c91
	 */
	inline float ScalarSin(float radian)
	{
		float quotient = OneDivTwoPi * radian;
		if (radian >= 0.0f)
		{
			quotient = static_cast<float>(static_cast<int>(quotient + 0.5f));
		}
		else
		{
			quotient = static_cast<float>(static_cast<int>(quotient - 0.5f));
		}

		float y = radian - TwoPi * quotient;

		if (y > PiDiv2)
		{
			y = Pi - y;
		}
		else if (y < -PiDiv2)
		{
			y = -Pi - y;
		}

		float y2 = y * y;
		return (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;
	}


	/**
	 * @brief ���� ������ �����ϴ� �ڻ��� ���� ��ȯ�մϴ�.
	 *
	 * @param radian �ڻ��� ���� ���� ���� �����Դϴ�.
	 *
	 * @return ���� ������ �����ϴ� �ڻ��ΰ��� ��ȯ�մϴ�.
	 *
	 * @note
	 * - DirectXMath�� XMScalarCos ����
	 * - �˰����� 11���� �̴ϸƽ�(Minimax) �ٻ�ġ(1th-degree Minimax approximation) ���
	 * - https://gist.github.com/publik-void/067f7f2fef32dbe5c27d6e215f824c91
	 */
	inline float ScalarCos(float radian)
	{
		float quotient = OneDivTwoPi * radian;
		if (radian >= 0.0f)
		{
			quotient = static_cast<float>(static_cast<int>(quotient + 0.5f));
		}
		else
		{
			quotient = static_cast<float>(static_cast<int>(quotient - 0.5f));
		}

		float y = radian - TwoPi * quotient;
		float sign = 1.0f;

		if (y > PiDiv2)
		{
			y = Pi - y;
			sign = -1.0f;
		}
		else if (y < -PiDiv2)
		{
			y = -Pi - y;
			sign = -1.0f;
		}

		float y2 = y * y;
		float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;

		return sign * p;
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
	 * @brief 2���� ������ ���� ������ �����մϴ�.
	 * 
	 * @param lhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * 
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 */
	template <typename T>
	inline T DotProduct(const Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}


	/**
	 * @brief 3���� ������ ���� ������ �����մϴ�.
	 *
	 * @param lhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 *
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 */
	template <typename T>
	inline T DotProduct(const Vector3<T>& lhs, const Vector3<T>& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}


	/**
	 * @brief 4���� ������ ���� ������ �����մϴ�.
	 *
	 * @param lhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 *
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 */
	template <typename T>
	inline T DotProduct(const Vector4<T>& lhs, const Vector4<T>& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
	}


	/**
	 * @brief 2���� ������ ���� ������ �����մϴ�.
	 *
	 * @param lhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 * @param rhs ������ ���� ������ ������ ���� �ǿ������Դϴ�.
	 *
	 * @return ���� ���� ����� ��ȯ�մϴ�.
	 * 
	 * @note �Ϲ����� 3���� ���� ����� �ٸ��ϴ�.
	 */
	template <typename T>
	inline T CrossProduct(const Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}


	/**
	 * @brief 2���� ������ ũ�� ���� ���� ����մϴ�.
	 * 
	 * @param v ũ�� ������ ����� �����Դϴ�.
	 * 
	 * @return ���� ũ�� ���� ���� ��ȯ�մϴ�.
	 */
	template <typename T>
	inline T LengthSquare(const Vector2<T>& v)
	{
		return v.x * v.x + v.y * v.y;
	}


	/**
	 * @brief 3���� ������ ũ�� ���� ���� ����մϴ�.
	 *
	 * @param v ũ�� ������ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ���� ��ȯ�մϴ�.
	 */
	template <typename T>
	inline T LengthSquare(const Vector3<T>& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}


	/**
	 * @brief 4���� ������ ũ�� ���� ���� ����մϴ�.
	 *
	 * @param v ũ�� ������ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ���� ��ȯ�մϴ�.
	 */
	template <typename T>
	inline T LengthSquare(const Vector4<T>& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
	}


	/**
	 * @brief 2���� ������ ũ�⸦ ����ϴ�.
	 * 
	 * @param v ũ�⸦ ����� �����Դϴ�.
	 * 
	 * @return ���� ũ�� ���� ��ȯ�մϴ�.
	 */
	inline float Length(const Vector2f& v)
	{
		float lengthSquare = LengthSquare<float>(v);
		return std::sqrtf(lengthSquare);
	}


	/**
	 * @brief 3���� ������ ũ�⸦ ����ϴ�.
	 *
	 * @param v ũ�⸦ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ��ȯ�մϴ�.
	 */
	inline float Length(const Vector3f& v)
	{
		float lengthSquare = LengthSquare<float>(v);
		return std::sqrtf(lengthSquare);
	}


	/**
	 * @brief 4���� ������ ũ�⸦ ����ϴ�.
	 *
	 * @param v ũ�⸦ ����� �����Դϴ�.
	 *
	 * @return ���� ũ�� ���� ��ȯ�մϴ�.
	 */
	inline float Length(const Vector4f& v)
	{
		float lengthSquare = LengthSquare<float>(v);
		return std::sqrtf(lengthSquare);
	}


	/**
	 * @brief 2���� ���͸� ����ȭ�մϴ�.
	 * 
	 * @param v ����ȭ �� �����Դϴ�.
	 * 
	 * @return ����ȭ�� ���͸� ��ȯ�մϴ�.
	 */
	inline Vector2f Normalize(const Vector2f& v)
	{
		float length = Length(v);
		return Vector2f(v.x / length, v.y / length);
	}


	/**
	 * @brief 3���� ���͸� ����ȭ�մϴ�.
	 *
	 * @param v ����ȭ �� �����Դϴ�.
	 *
	 * @return ����ȭ�� ���͸� ��ȯ�մϴ�.
	 */
	inline Vector3f Normalize(const Vector3f& v)
	{
		float length = Length(v);
		return Vector3f(v.x / length, v.y / length, v.z / length);
	}


	/**
	 * @brief 4���� ���͸� ����ȭ�մϴ�.
	 *
	 * @param v ����ȭ �� �����Դϴ�.
	 *
	 * @return ����ȭ�� ���͸� ��ȯ�մϴ�.
	 */
	inline Vector4f Normalize(const Vector4f& v)
	{
		float length = Length(v);
		return Vector4f(v.x / length, v.y / length, v.z / length, v.w / length);
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


	/**
	 * @brief ������ �Ǽ��� �����մϴ�.
	 *
	 * @param minValue ������ ���� ������ �ּڰ��Դϴ�.
	 * @param maxValue ������ ���� ������ �ִ��Դϴ�.
	 *
	 * @return ������ ������ �Ǽ��� ��ȯ�մϴ�.
	 */
	inline float GenerateRandomFloat(float minValue, float maxValue)
	{
		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		std::uniform_real_distribution<float> distribution(std::min<float>(minValue, maxValue), std::max<float>(minValue, maxValue));

		return distribution(generator);
	}


	/**
	 * @brief �̵� ��ȯ ����� �����մϴ�.
	 * 
	 * @param x �̵��� x ��ǥ���Դϴ�.
	 * @param y �̵��� y ��ǥ���Դϴ�.
	 * @param z �̵��� z ��ǥ���Դϴ�.
	 * 
	 * @return ������ �̵� ��ȯ ����� ��ȯ�մϴ�.
	 */
	inline Matrix4x4f CreateTranslation(float x, float y, float z)
	{
		return Matrix4x4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 
			   x,    y,    z, 1.0f
		);
	}


	/**
	 * @brief �̵� ��ȯ ����� �����մϴ�.
	 * 
	 * @param p �̵��� ��ġ ��ǥ�Դϴ�.
	 * 
	 * @return ������ �̵� ��ȯ ����� ��ȯ�մϴ�.
	 */
	inline Matrix4x4f CreateTranslation(const Vector3f& p)
	{
		return Matrix4x4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 
			 p.x,  p.y,  p.z, 1.0f
		);
	}


	/**
	 * @brief ������ ��ȯ ����� �����մϴ�.
	 * 
	 * @param xScale ��ȯ�� x�� ������ �������Դϴ�.
	 * @param yScale ��ȯ�� y�� ������ �������Դϴ�.
	 * @param zScale ��ȯ�� z�� ������ �������Դϴ�.
	 * 
	 * @return ������ ������ ��ȯ ����� ��ȯ�մϴ�.
	 */
	inline Matrix4x4f CreateScale(float xScale, float yScale, float zScale)
	{
		return Matrix4x4f(
			xScale,   0.0f,   0.0f, 0.0f,
			  0.0f, yScale,   0.0f, 0.0f,
			  0.0f,   0.0f, zScale, 0.0f,
			  0.0f,   0.0f,   0.0f, 1.0f
		);
	}


	/**
	 * @brief ������ ��ȯ ����� �����մϴ�.
	 *
	 * @param scale ��ȯ�� ������ �����Դϴ�.
	 *
	 * @return ������ ������ ��ȯ ����� ��ȯ�մϴ�.
	 */
	inline Matrix4x4f CreateScale(const Vector3f& scale)
	{
		return Matrix4x4f(
			scale.x,    0.0f,    0.0f, 0.0f,
			   0.0f, scale.y,    0.0f, 0.0f,
			   0.0f,    0.0f, scale.z, 0.0f,
			   0.0f,    0.0f,    0.0f, 1.0f
		);
	}


	/**
	 * @brief X������ ȸ����Ű�� ȸ�� ����� �����մϴ�.
	 * 
	 * @param radian ȸ���� ���� �����Դϴ�.
	 * 
	 * @return ������ ȸ�� ����� ��ȯ�մϴ�.
	 */
	inline Matrix4x4f CreateRotateX(float radian)
	{
		float s = ScalarSin(radian);
		float c = ScalarCos(radian);

		return Matrix4x4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,    c,    s, 0.0f,
			0.0f,   -s,    c, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	/**
	 * @brief Y������ ȸ����Ű�� ȸ�� ����� �����մϴ�.
	 *
	 * @param radian ȸ���� ���� �����Դϴ�.
	 *
	 * @return ������ ȸ�� ����� ��ȯ�մϴ�.
	 */
	inline Matrix4x4f CreateRotateY(float radian)
	{
		float s = ScalarSin(radian);
		float c = ScalarCos(radian);

		return Matrix4x4f(
			   c, 0.0f,   -s, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			   s, 0.0f,    c, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	/**
	 * @brief Z������ ȸ����Ű�� ȸ�� ����� �����մϴ�.
	 *
	 * @param radian ȸ���� ���� �����Դϴ�.
	 *
	 * @return ������ ȸ�� ����� ��ȯ�մϴ�.
	 */
	inline Matrix4x4f CreateRotateZ(float radian)
	{
		float s = ScalarSin(radian);
		float c = ScalarCos(radian);

		return Matrix4x4f(
			   c,    s, 0.0f, 0.0f,
			  -s,    c, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	/**
	 * @brief ���� ���� ����� �����մϴ�.
	 * 
	 * @param left   ���� ������ ���� ��� ��� ��
	 * @param right  ���� ������ ���� ��� ��� ��
	 * @param bottom ���� ������ �ϴ� ��� ��� ��
	 * @param top    ���� ������ ��� ��� ��� ��
	 * @param zNear  ���� ������ ���� ��� ��� ��
	 * @param zFar   ���� ������ �Ĺ� ��� ��� ��
	 * 
	 * @return ������ ���� ���� ����� ��ȯ�մϴ�.
	 */
	inline Matrix4x4f CreateOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		float diffRL = (right - left);
		float addRL = (right + left);
		float diffTB = (top - bottom);
		float addTB = (top + bottom);
		float diffFN = (zFar - zNear);
		float addFN = (zFar + zNear);
		
		return Matrix4x4f(
			  2.0f / diffRL,            0.0f,            0.0f, 0.0f,
			           0.0f,   2.0f / diffTB,            0.0f, 0.0f,
			           0.0f,            0.0f,  -2.0f / diffFN, 0.0f,
			-addRL / diffRL, -addTB / diffTB, -addFN / diffFN, 1.0f
		);
	}
}