#pragma once

#include <vector>
#include <string>
#include <cstdarg>


/**
 * @brief ǥ�� ���ڿ�(std::string, std::wstring)�� Ȯ�� ����� �����մϴ�.
 *
 * @note �� Ŭ������ ��� ���� �� ��� �Լ��� ��� ����(static)�Դϴ�.
 */
class StringUtils
{
public:
	/**
	 * @brief ����ȭ�� ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @note
	 * - �� �޼���� snprintf�� ���� �Լ��� ��ü�ϱ� ���� ���Դϴ�.
	 * - ���ڿ��� ���̴� �ִ� 1024 �Դϴ�.
	 *
	 * @param format ���� ���ڿ��Դϴ�.
	 * @param ... ���ڿ��� ���Ŀ� �����ϴ� ���������Դϴ�.
	 *
	 * @return ����ȭ�� ǥ�� ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @see https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/vsnprintf-vsnprintf-vsnprintf-l-vsnwprintf-vsnwprintf-l?view=msvc-170
	 */
	static std::string PrintF(const char* format, ...);


	/**
	 * @brief ����ȭ�� ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @note
	 * - �� �޼���� snprintf�� ���� �Լ��� ��ü�ϱ� ���� ���Դϴ�.
	 * - ���ڿ��� ���̴� �ִ� 1024 �Դϴ�.
	 *
	 * @param format ���� ���ڿ��Դϴ�.
	 * @param ... ���ڿ��� ���Ŀ� �����ϴ� ���������Դϴ�.
	 *
	 * @return ����ȭ�� ǥ�� ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @see https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/vsnprintf-vsnprintf-vsnprintf-l-vsnwprintf-vsnwprintf-l?view=msvc-170
	 */
	static std::wstring PrintF(const wchar_t* format, ...);


private:
	/**
	 * @brief ���ڿ� ������ �ִ� ũ���Դϴ�.
	 */
	static const uint32_t MAX_BUFFER_SIZE = 1024;


	/**
	 * @brief char ��� ���ڿ� �����Դϴ�.
	 */
	static char charBuffer_[MAX_BUFFER_SIZE];


	/**
	 * @brief wchar_t ��� ���ڿ� �����Դϴ�.
	 */
	static wchar_t wcharBuffer_[MAX_BUFFER_SIZE];
};