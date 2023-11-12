#pragma once

#include <cstdint>


/**
 * @brief ���ø� ����� 3x3 ����Դϴ�.
 */
template <typename T>
struct Matrix3x3
{
	/**
	 * @brief 3x3 ����� �⺻ �������Դϴ�.
	 *
	 * @note ��� ������ ���� 0���� �ʱ�ȭ�մϴ�.
	 */
	Matrix3x3() noexcept
	{
		m[0][0] = static_cast<T>(0); m[0][1] = static_cast<T>(0); m[0][2] = static_cast<T>(0);
		m[1][0] = static_cast<T>(0); m[1][1] = static_cast<T>(0); m[1][2] = static_cast<T>(0);
		m[2][0] = static_cast<T>(0); m[2][1] = static_cast<T>(0); m[2][2] = static_cast<T>(0);
	}


	/**
	 * @brief 3x3 ����� �������Դϴ�.
	 *
	 * @param m00 ����� (0, 0) �����Դϴ�.
	 * @param m01 ����� (0, 1) �����Դϴ�.
	 * @param m02 ����� (0, 2) �����Դϴ�.
	 * @param m10 ����� (1, 0) �����Դϴ�.
	 * @param m11 ����� (1, 1) �����Դϴ�.
	 * @param m12 ����� (1, 2) �����Դϴ�.
	 * @param m20 ����� (2, 0) �����Դϴ�.
	 * @param m21 ����� (2, 1) �����Դϴ�.
	 * @param m22 ����� (2, 2) �����Դϴ�.
	 */
	Matrix3x3(
		T&& m00, T&& m01, T&& m02,
		T&& m10, T&& m11, T&& m12,
		T&& m20, T&& m21, T&& m22
	) noexcept
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
	}


	/**
	 * @brief 3x3 ����� �������Դϴ�.
	 *
	 * @param m00 ����� (0, 0) �����Դϴ�.
	 * @param m01 ����� (0, 1) �����Դϴ�.
	 * @param m02 ����� (0, 2) �����Դϴ�.
	 * @param m10 ����� (1, 0) �����Դϴ�.
	 * @param m11 ����� (1, 1) �����Դϴ�.
	 * @param m12 ����� (1, 2) �����Դϴ�.
	 * @param m20 ����� (2, 0) �����Դϴ�.
	 * @param m21 ����� (2, 1) �����Դϴ�.
	 * @param m22 ����� (2, 2) �����Դϴ�.
	 */
	Matrix3x3(
		const T& m00, const T& m01, const T& m02,
		const T& m10, const T& m11, const T& m12,
		const T& m20, const T& m21, const T& m22
	) noexcept
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
	}


	/**
	 * @brief 3x3 ����� ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Matrix3x3(T&& e) noexcept
	{
		m[0][0] = e; m[0][1] = e; m[0][2] = e;
		m[1][0] = e; m[1][1] = e; m[1][2] = e;
		m[2][0] = e; m[2][1] = e; m[2][2] = e;
	}


	/**
	 * @brief 3x3 ����� ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Matrix3x3(const T& e) noexcept
	{
		m[0][0] = e; m[0][1] = e; m[0][2] = e;
		m[1][0] = e; m[1][1] = e; m[1][2] = e;
		m[2][0] = e; m[2][1] = e; m[2][2] = e;
	}


	/**
	 * @brief 3x3 ����� ���� �������Դϴ�.
	 *
	 * @param matrix ���Ҹ� ������ ����� �ν��Ͻ��Դϴ�.
	 */
	Matrix3x3(Matrix3x3<T>&& matrix) noexcept
	{
		m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1]; m[0][2] = matrix.m[0][2];
		m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1]; m[1][2] = matrix.m[1][2];
		m[2][0] = matrix.m[2][0]; m[2][1] = matrix.m[2][1]; m[2][2] = matrix.m[2][2];
	}


	/**
	 * @brief 3x3 ����� ���� �������Դϴ�.
	 *
	 * @param matrix ���Ҹ� ������ ����� �ν��Ͻ��Դϴ�.
	 */
	Matrix3x3(const Matrix3x3<T>& matrix) noexcept
	{
		m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1]; m[0][2] = matrix.m[0][2];
		m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1]; m[1][2] = matrix.m[1][2];
		m[2][0] = matrix.m[2][0]; m[2][1] = matrix.m[2][1]; m[2][2] = matrix.m[2][2];
	}


	/**
	 * @brief 3x3 ����� ���� �������Դϴ�.
	 *
	 * @param matrix ���Ҹ� ������ ����� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ����� �����ڸ� ��ȯ�մϴ�.
	 */
	Matrix3x3<T>& operator=(Matrix3x3<T>&& matrix) noexcept
	{
		if (this == &matrix) return *this;

		m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1]; m[0][2] = matrix.m[0][2];
		m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1]; m[1][2] = matrix.m[1][2];
		m[2][0] = matrix.m[2][0]; m[2][1] = matrix.m[2][1]; m[2][2] = matrix.m[2][2];

		return *this;
	}


	/**
	 * @brief 3x3 ����� ���� �������Դϴ�.
	 *
	 * @param matrix ���Ҹ� ������ ����� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ����� �����ڸ� ��ȯ�մϴ�.
	 */
	Matrix3x3<T>& operator=(const Matrix3x3<T>& matrix) noexcept
	{
		if (this == &matrix) return *this;

		m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1]; m[0][2] = matrix.m[0][2];
		m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1]; m[1][2] = matrix.m[1][2];
		m[2][0] = matrix.m[2][0]; m[2][1] = matrix.m[2][1]; m[2][2] = matrix.m[2][2];

		return *this;
	}


	/**
	 * @brief 3x3 ����� ��� ���ҿ� -��ȣ�� ���մϴ�.
	 *
	 * @return ��� ���ҿ� -��ȣ�� ���� ���ο� ����� ��ȯ�մϴ�.
	 */
	Matrix3x3<T> operator-() const
	{
		return Matrix3x3<T>(
			-m[0][0], -m[0][1], -m[0][2],
			-m[1][0], -m[1][1], -m[1][2],
			-m[2][0], -m[2][1], -m[2][2]
		);
	}


	/**
	 * @brief �� 3x3 ����� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param matrix ����� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ����� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Matrix3x3<T> operator+(Matrix3x3<T>&& matrix) const
	{
		return Matrix3x3<T>(
			m[0][0] + matrix.m[0][0], m[0][1] + matrix.m[0][1], m[0][2] + matrix.m[0][2],
			m[1][0] + matrix.m[1][0], m[1][1] + matrix.m[1][1], m[1][2] + matrix.m[1][2],
			m[2][0] + matrix.m[2][0], m[2][1] + matrix.m[2][1], m[2][2] + matrix.m[2][2]
		);
	}


	/**
	 * @brief �� 3x3 ����� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param matrix ����� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ����� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Matrix3x3<T> operator+(const Matrix3x3<T>& matrix) const
	{
		return Matrix3x3<T>(
			m[0][0] + matrix.m[0][0], m[0][1] + matrix.m[0][1], m[0][2] + matrix.m[0][2],
			m[1][0] + matrix.m[1][0], m[1][1] + matrix.m[1][1], m[1][2] + matrix.m[1][2],
			m[2][0] + matrix.m[2][0], m[2][1] + matrix.m[2][1], m[2][2] + matrix.m[2][2]
		);
	}


	/**
	 * @brief �� 3x3 ����� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param matrix ����� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ����� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Matrix3x3<T> operator-(Matrix3x3<T>&& matrix) const
	{
		return Matrix3x3<T>(
			m[0][0] - matrix.m[0][0], m[0][1] - matrix.m[0][1], m[0][2] - matrix.m[0][2],
			m[1][0] - matrix.m[1][0], m[1][1] - matrix.m[1][1], m[1][2] - matrix.m[1][2],
			m[2][0] - matrix.m[2][0], m[2][1] - matrix.m[2][1], m[2][2] - matrix.m[2][2]
		);
	}


	/**
	 * @brief �� 3x3 ����� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param matrix ����� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ����� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Matrix3x3<T> operator-(const Matrix3x3<T>& matrix) const
	{
		return Matrix3x3<T>(
			m[0][0] - matrix.m[0][0], m[0][1] - matrix.m[0][1], m[0][2] - matrix.m[0][2],
			m[1][0] - matrix.m[1][0], m[1][1] - matrix.m[1][1], m[1][2] - matrix.m[1][2],
			m[2][0] - matrix.m[2][0], m[2][1] - matrix.m[2][1], m[2][2] - matrix.m[2][2]
		);
	}


	/**
	 * @brief �� 3x3 ����� ���մϴ�.
	 *
	 * @param matrix ����� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ����� ���� ����� ��ȯ�մϴ�.
	 */
	Matrix3x3<T> operator*(Matrix3x3<T>&& matrix) const
	{
		return Matrix3x3(
			m[0][0] * matrix.m[0][0] + m[0][1] * matrix.m[1][0] + m[0][2] * matrix.m[2][0],
			m[0][0] * matrix.m[0][1] + m[0][1] * matrix.m[1][1] + m[0][2] * matrix.m[2][1],
			m[0][0] * matrix.m[0][2] + m[0][1] * matrix.m[1][2] + m[0][2] * matrix.m[2][2],
			m[1][0] * matrix.m[0][0] + m[1][1] * matrix.m[1][0] + m[1][2] * matrix.m[2][0],
			m[1][0] * matrix.m[0][1] + m[1][1] * matrix.m[1][1] + m[1][2] * matrix.m[2][1],
			m[1][0] * matrix.m[0][2] + m[1][1] * matrix.m[1][2] + m[1][2] * matrix.m[2][2],
			m[2][0] * matrix.m[0][0] + m[2][1] * matrix.m[1][0] + m[2][2] * matrix.m[2][0],
			m[2][0] * matrix.m[0][1] + m[2][1] * matrix.m[1][1] + m[2][2] * matrix.m[2][1],
			m[2][0] * matrix.m[0][2] + m[2][1] * matrix.m[1][2] + m[2][2] * matrix.m[2][2],
		);
	}


	/**
	 * @brief �� 3x3 ����� ���մϴ�.
	 *
	 * @param matrix ����� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ����� ���� ����� ��ȯ�մϴ�.
	 */
	Matrix3x3<T> operator*(const Matrix3x3<T>& matrix) const
	{
		return Matrix3x3(
			m[0][0] * matrix.m[0][0] + m[0][1] * matrix.m[1][0] + m[0][2] * matrix.m[2][0],
			m[0][0] * matrix.m[0][1] + m[0][1] * matrix.m[1][1] + m[0][2] * matrix.m[2][1],
			m[0][0] * matrix.m[0][2] + m[0][1] * matrix.m[1][2] + m[0][2] * matrix.m[2][2],
			m[1][0] * matrix.m[0][0] + m[1][1] * matrix.m[1][0] + m[1][2] * matrix.m[2][0],
			m[1][0] * matrix.m[0][1] + m[1][1] * matrix.m[1][1] + m[1][2] * matrix.m[2][1],
			m[1][0] * matrix.m[0][2] + m[1][1] * matrix.m[1][2] + m[1][2] * matrix.m[2][2],
			m[2][0] * matrix.m[0][0] + m[2][1] * matrix.m[1][0] + m[2][2] * matrix.m[2][0],
			m[2][0] * matrix.m[0][1] + m[2][1] * matrix.m[1][1] + m[2][2] * matrix.m[2][1],
			m[2][0] * matrix.m[0][2] + m[2][1] * matrix.m[1][2] + m[2][2] * matrix.m[2][2],
		);
	}


	/**
	 * @brief �� 3x3 ��Ŀ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param matrix ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ����� �����ڸ� ��ȯ�մϴ�.
	 */
	Matrix3x3<T>& operator+=(Matrix3x3<T>&& matrix) noexcept
	{
		m[0][0] += matrix.m[0][0]; m[0][1] += matrix.m[0][1]; m[0][2] += matrix.m[0][2];
		m[1][0] += matrix.m[1][0]; m[1][1] += matrix.m[1][1]; m[1][2] += matrix.m[1][2];
		m[2][0] += matrix.m[2][0]; m[2][1] += matrix.m[2][1]; m[2][2] += matrix.m[2][2];

		return *this;
	}


	/**
	 * @brief �� 3x3 ��Ŀ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param matrix ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ����� �����ڸ� ��ȯ�մϴ�.
	 */
	Matrix3x3<T>& operator+=(const Matrix3x3<T>& matrix) noexcept
	{
		m[0][0] += matrix.m[0][0]; m[0][1] += matrix.m[0][1]; m[0][2] += matrix.m[0][2];
		m[1][0] += matrix.m[1][0]; m[1][1] += matrix.m[1][1]; m[1][2] += matrix.m[1][2];
		m[2][0] += matrix.m[2][0]; m[2][1] += matrix.m[2][1]; m[2][2] += matrix.m[2][2];

		return *this;
	}


	/**
	 * @brief �� 3x3 ��Ŀ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param matrix ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ����� �����ڸ� ��ȯ�մϴ�.
	 */
	Matrix3x3<T>& operator-=(Matrix3x3<T>&& matrix) noexcept
	{
		m[0][0] -= matrix.m[0][0]; m[0][1] -= matrix.m[0][1]; m[0][2] -= matrix.m[0][2];
		m[1][0] -= matrix.m[1][0]; m[1][1] -= matrix.m[1][1]; m[1][2] -= matrix.m[1][2];
		m[2][0] -= matrix.m[2][0]; m[2][1] -= matrix.m[2][1]; m[2][2] -= matrix.m[2][2];

		return *this;
	}


	/**
	 * @brief �� 3x3 ��Ŀ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param matrix ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ����� �����ڸ� ��ȯ�մϴ�.
	 */
	Matrix3x3<T>& operator-=(const Matrix3x3<T>& matrix) noexcept
	{
		m[0][0] -= matrix.m[0][0]; m[0][1] -= matrix.m[0][1]; m[0][2] -= matrix.m[0][2];
		m[1][0] -= matrix.m[1][0]; m[1][1] -= matrix.m[1][1]; m[1][2] -= matrix.m[1][2];
		m[2][0] -= matrix.m[2][0]; m[2][1] -= matrix.m[2][1]; m[2][2] -= matrix.m[2][2];

		return *this;
	}


	/**
	 * @brief 3x3 ��� ���� �迭�� �����͸� ����ϴ�.
	 *
	 * @return 3x3 ��� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	const T* GetPtr() const { return &m[0][0]; }


	/**
	 * @brief 3x3 ��� ���� �迭�� �����͸� ����ϴ�.
	 *
	 * @return 3x3 ��� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	T* GetPtr() { return &m[0][0]; }


	/**
	 * @brief 3x3 ����� ���� ����� ����ϴ�.
	 *
	 * @return 3x3 ����� ���� ��ĸ� ��ȯ�մϴ�.
	 */
	static Matrix3x3<T> GetIdentity()
	{
		return Matrix3x3(
			static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
			static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
			static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
		);
	}


	/**
	 * @brief 3x3 ����� �����Դϴ�.
	 */
	T m[3][3];
};


/**
 * @brief int32_t Ÿ���� 3x3 ����Դϴ�.
 */
using Matrix3x3i = Matrix3x3<int32_t>;


/**
 * @brief float Ÿ���� 3x3 ����Դϴ�.
 */
using Matrix3x3f = Matrix3x3<float>;