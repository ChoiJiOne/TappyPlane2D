#pragma once

#include <cstdint>


/**
 * @brief ���ø� ����� 2x2 ����Դϴ�.
 */
template <typename T>
struct Matrix2x2
{
	/**
	 * @brief 2x2 ����� �⺻ �������Դϴ�.
	 *
	 * @note ��� ������ ���� 0���� �ʱ�ȭ�մϴ�.
	 */
	Matrix2x2() noexcept
	{
		m[0][0] = static_cast<T>(0); m[0][1] = static_cast<T>(0);
		m[1][0] = static_cast<T>(0); m[1][1] = static_cast<T>(0);
	}


	/**
	 * @brief 2x2 ����� �������Դϴ�.
	 *
	 * @param m00 ����� (0, 0) �����Դϴ�.
	 * @param m01 ����� (0, 1) �����Դϴ�.
	 * @param m10 ����� (1, 0) �����Դϴ�.
	 * @param m11 ����� (1, 1) �����Դϴ�.
	 */
	Matrix2x2(
		T&& m00, T&& m01,
		T&& m10, T&& m11
	) noexcept
	{
		m[0][0] = m00; m[0][1] = m01;
		m[1][0] = m10; m[1][1] = m11;
	}


	/**
	 * @brief 2x2 ����� �������Դϴ�.
	 *
	 * @param m00 ����� (0, 0) �����Դϴ�.
	 * @param m01 ����� (0, 1) �����Դϴ�.
	 * @param m10 ����� (1, 0) �����Դϴ�.
	 * @param m11 ����� (1, 1) �����Դϴ�.
	 */
	Matrix2x2(
		const T& m00, const T& m01,
		const T& m10, const T& m11
	) noexcept
	{
		m[0][0] = m00; m[0][1] = m01;
		m[1][0] = m10; m[1][1] = m11;
	}


	/**
	 * @brief 2x2 ����� ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Matrix2x2(T&& e) noexcept
	{
		m[0][0] = e; m[0][1] = e;
		m[1][0] = e; m[1][1] = e;
	}


	/**
	 * @brief 2x2 ����� ���Ҹ� �ϳ��� ������ �ʱ�ȭ�մϴ�.
	 *
	 * @param e ��� ���Ҹ� �ʱ�ȭ �� ���Դϴ�.
	 */
	Matrix2x2(const T& e) noexcept
	{
		m[0][0] = e; m[0][1] = e;
		m[1][0] = e; m[1][1] = e;
	}


	/**
	 * @brief 2x2 ����� ���� �������Դϴ�.
	 *
	 * @param matrix ���Ҹ� ������ ����� �ν��Ͻ��Դϴ�.
	 */
	Matrix2x2(Matrix2x2<T>&& matrix) noexcept
	{
		m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1];
		m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1];
	}


	/**
	 * @brief 2x2 ����� ���� �������Դϴ�.
	 *
	 * @param matrix ���Ҹ� ������ ����� �ν��Ͻ��Դϴ�.
	 */
	Matrix2x2(const Matrix2x2<T>& matrix) noexcept
	{
		m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1];
		m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1];
	}


	/**
	 * @brief 2x2 ����� ���� �������Դϴ�.
	 *
	 * @param matrix ���Ҹ� ������ ����� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ����� �����ڸ� ��ȯ�մϴ�.
	 */
	Matrix2x2<T>& operator=(Matrix2x2<T>&& matrix) noexcept
	{
		if (this == &matrix) return *this;

		m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1];
		m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1];

		return *this;
	}


	/**
	 * @brief 2x2 ����� ���� �������Դϴ�.
	 *
	 * @param matrix ���Ҹ� ������ ����� �ν��Ͻ��Դϴ�.
	 *
	 * @return ������ ����� �����ڸ� ��ȯ�մϴ�.
	 */
	Matrix2x2<T>& operator=(const Matrix2x2<T>& matrix) noexcept
	{
		if (this == &matrix) return *this;

		m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1];
		m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1];

		return *this;
	}


	/**
	 * @brief 2x2 ����� ��� ���ҿ� - ��ȣ�� ���մϴ�.
	 *
	 * @return ��� ���ҿ� -��ȣ�� ���� ���ο� ����� ��ȯ�մϴ�.
	 */
	Matrix2x2<T> operator-() const
	{
		return Matrix2x2<T>(
			-m[0][0], -m[0][1],
			-m[1][0], -m[1][1]
		);
	}


	/**
	 * @brief �� 2x2 ����� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param matrix ����� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ����� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Matrix2x2<T> operator+(Matrix2x2<T>&& matrix) const
	{
		return Matrix2x2<T>(
			m[0][0] + matrix.m[0][0], m[0][1] + matrix.m[0][1],
			m[1][0] + matrix.m[1][0], m[1][1] + matrix.m[1][1]
		);
	}


	/**
	 * @brief �� 2x2 ����� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param matrix ����� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ����� �����ϴ� ���Ҹ� ���� ����� ��ȯ�մϴ�.
	 */
	Matrix2x2<T> operator+(const Matrix2x2<T>& matrix) const
	{
		return Matrix2x2<T>(
			m[0][0] + matrix.m[0][0], m[0][1] + matrix.m[0][1],
			m[1][0] + matrix.m[1][0], m[1][1] + matrix.m[1][1]
		);
	}


	/**
	 * @brief �� 2x2 ����� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param matrix ����� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ����� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Matrix2x2<T> operator-(Matrix2x2<T>&& matrix) const
	{
		return Matrix2x2<T>(
			m[0][0] - matrix.m[0][0], m[0][1] - matrix.m[0][1],
			m[1][0] - matrix.m[1][0], m[1][1] - matrix.m[1][1]
		);
	}


	/**
	 * @brief �� 2x2 ����� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param matrix ����� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ����� �����ϴ� ���Ҹ� �� ����� ��ȯ�մϴ�.
	 */
	Matrix2x2<T> operator-(const Matrix2x2<T>& matrix) const
	{
		return Matrix2x2<T>(
			m[0][0] - matrix.m[0][0], m[0][1] - matrix.m[0][1],
			m[1][0] - matrix.m[1][0], m[1][1] - matrix.m[1][1]
		);
	}


	/**
	 * @brief �� 2x2 ����� ���մϴ�.
	 *
	 * @param matrix ����� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ����� ���� ����� ��ȯ�մϴ�.
	 */
	Matrix2x2<T> operator*(Matrix2x2<T>&& matrix) const
	{
		return Matrix2x2(
			m[0][0] * matrix.m[0][0] + m[0][1] * matrix.m[1][0],
			m[0][0] * matrix.m[0][1] + m[0][1] * matrix.m[1][1],
			m[1][0] * matrix.m[0][0] + m[1][1] * matrix.m[1][0],
			m[1][0] * matrix.m[0][1] + m[1][1] * matrix.m[1][1]
		);
	}


	/**
	 * @brief �� 2x2 ����� ���մϴ�.
	 *
	 * @param matrix ����� ������ ������ �ǿ������Դϴ�.
	 *
	 * @return �� ����� ���� ����� ��ȯ�մϴ�.
	 */
	Matrix2x2<T> operator*(const Matrix2x2<T>& matrix) const
	{
		return Matrix2x2(
			m[0][0] * matrix.m[0][0] + m[0][1] * matrix.m[1][0],
			m[0][0] * matrix.m[0][1] + m[0][1] * matrix.m[1][1],
			m[1][0] * matrix.m[0][0] + m[1][1] * matrix.m[1][0],
			m[1][0] * matrix.m[0][1] + m[1][1] * matrix.m[1][1]
		);
	}


	/**
	 * @brief �� 2x2 ��Ŀ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param matrix ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ����� �����ڸ� ��ȯ�մϴ�.
	 */
	Matrix2x2<T>& operator+=(Matrix2x2<T>&& matrix) noexcept
	{
		m[0][0] += matrix.m[0][0]; m[0][1] += matrix.m[0][1];
		m[1][0] += matrix.m[1][0]; m[1][1] += matrix.m[1][1];

		return *this;
	}


	/**
	 * @brief �� 2x2 ��Ŀ� �����ϴ� ���Ҹ� ���մϴ�.
	 *
	 * @param matrix ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ����� �����ڸ� ��ȯ�մϴ�.
	 */
	Matrix2x2<T>& operator+=(const Matrix2x2<T>& matrix) noexcept
	{
		m[0][0] += matrix.m[0][0]; m[0][1] += matrix.m[0][1];
		m[1][0] += matrix.m[1][0]; m[1][1] += matrix.m[1][1];

		return *this;
	}


	/**
	 * @brief �� 2x2 ��Ŀ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param matrix ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ����� �����ڸ� ��ȯ�մϴ�.
	 */
	Matrix2x2<T>& operator-=(Matrix2x2<T>&& matrix) noexcept
	{
		m[0][0] -= matrix.m[0][0]; m[0][1] -= matrix.m[0][1];
		m[1][0] -= matrix.m[1][0]; m[1][1] -= matrix.m[1][1];

		return *this;
	}


	/**
	 * @brief �� 2x2 ��Ŀ� �����ϴ� ���Ҹ� ���ϴ�.
	 *
	 * @param matrix ������ ������ �ǿ������Դϴ�.
	 *
	 * @return ������ ������ ����� �����ڸ� ��ȯ�մϴ�.
	 */
	Matrix2x2<T>& operator-=(const Matrix2x2<T>& matrix) noexcept
	{
		m[0][0] -= matrix.m[0][0]; m[0][1] -= matrix.m[0][1];
		m[1][0] -= matrix.m[1][0]; m[1][1] -= matrix.m[1][1];

		return *this;
	}


	/**
	 * @brief 2x2 ��� ���� �迭�� �����͸� ����ϴ�.
	 * 
	 * @return 2x2 ��� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	const T* GetPtr() const { return &m[0][0]; }


	/**
	 * @brief 2x2 ��� ���� �迭�� �����͸� ����ϴ�.
	 * 
	 * @return 2x2 ��� ���� �迭�� �����͸� ��ȯ�մϴ�.
	 */
	T* GetPtr() { return &m[0][0]; }


	/**
	 * @brief 2x2 ����� �����Դϴ�.
	 */
	T m[2][2];
};


/**
 * @brief int32_t Ÿ���� 2x2 ����Դϴ�.
 */
using Matrix2x2i = Matrix2x2<int32_t>;


/**
 * @brief float Ÿ���� 2x2 ����Դϴ�.
 */
using Matrix2x2f = Matrix2x2<float>;