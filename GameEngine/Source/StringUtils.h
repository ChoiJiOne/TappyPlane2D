#pragma once

#include <vector>
#include <string>
#include <cstdarg>


/**
 * @brief ǥ�� ���ڿ�(std::string, std::wstring)�� Ȯ�� ����� �����մϴ�.
 */
namespace StringUtils
{
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
	std::string PrintF(const char* format, ...);


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
	std::wstring PrintF(const wchar_t* format, ...);


	/**
	 * @brief Ư�� ���ڿ��� �������� �ؽ�Ʈ�� �и��մϴ�.
	 *
	 * @param text �и��� ��� ���ڿ��Դϴ�.
	 * @param delimiter �и��� ���� ���� ���ڿ��Դϴ�.
	 *
	 * @return �и��� ���ڿ��� ��� �ִ� ����(std::vector)�� ��ȯ�մϴ�.
	 */
	std::vector<std::string> Split(const std::string& text, const std::string& delimiter);


	/**
	 * @brief Ư�� ���ڿ��� �������� �ؽ�Ʈ�� �и��մϴ�.
	 *
	 * @param text �и��� ��� ���ڿ��Դϴ�.
	 * @param delimiter �и��� ���� ���� ���ڿ��Դϴ�.
	 *
	 * @return �и��� ���ڿ��� ��� �ִ� ����(std::vector)�Դϴ�.
	 */
	std::vector<std::wstring> Split(const std::wstring& text, const std::wstring& delimiter);


	/**
	 * @brief char ���ڿ��� wchar_t ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @see https://en.cppreference.com/w/cpp/string/multibyte/mbstowcs
	 *
	 * @param text ��ȯ�� ǥ�� �ؽ�Ʈ�Դϴ�.
	 *
	 * @return ��ȯ�� ���ڿ��� ��ȯ�մϴ�.
	 */
	std::wstring Convert(const std::string& text);


	/**
	 * @brief wchar_t ���ڿ��� char ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @see https://en.cppreference.com/w/cpp/string/multibyte/wcstombs
	 *
	 * @param text ��ȯ�� ǥ�� �ؽ�Ʈ�Դϴ�.
	 *
	 * @return ��ȯ�� ���ڿ��� ��ȯ�մϴ�.
	 */
	std::string Convert(const std::wstring& text);


	/**
	 * @brief ���ڿ��� ���ĺ��� ��� �ҹ��ڷ� ��ȯ�մϴ�.
	 *
	 * @param text ��ȯ�� ���ڿ��Դϴ�.
	 *
	 * @return ���ڿ� ���� ���ĺ��� ��� �ҹ��ڷ� ��ȯ�� ��ü ���ڿ��� ��ȯ�մϴ�.
	 */
	std::string ToLower(const std::string& text);


	/**
	 * @brief ���ڿ��� ���ĺ��� ��� �ҹ��ڷ� ��ȯ�մϴ�.
	 *
	 * @param text ��ȯ�� ���ڿ��Դϴ�.
	 *
	 * @return ���ڿ� ���� ���ĺ��� ��� �ҹ��ڷ� ��ȯ�� ��ü ���ڿ��� ��ȯ�մϴ�.
	 */
	std::wstring ToLower(const std::wstring& text);


	/**
	 * @brief ���ڿ��� ���ĺ��� ��� �빮�ڷ� ��ȯ�մϴ�.
	 *
	 * @param text ��ȯ�� ���ڿ��Դϴ�.
	 *
	 * @return ���ڿ� ���� ���ĺ��� ��� �빮�ڷ� ��ȯ�� ��ü ���ڿ��� ��ȯ�մϴ�.
	 */
	std::string ToUpper(const std::string& text);


	/**
	 * @brief ���ڿ��� ���ĺ��� ��� �빮�ڷ� ��ȯ�մϴ�.
	 *
	 * @param text ��ȯ�� ���ڿ��Դϴ�.
	 *
	 * @return ���ڿ� ���� ���ĺ��� ��� �빮�ڷ� ��ȯ�� ��ü ���ڿ��� ��ȯ�մϴ�.
	 */
	std::wstring ToUpper(const std::wstring& text);


	/**
	 * @brief ������ ������ ���ڿ��� 10���� ���� ������ ��ȯ�մϴ�.
	 * 
	 * @param integerStr ������ ������ ���ڿ��Դϴ�.
	 * @param integer ��ȯ�� ���� ���� ������ ���� �����Դϴ�.
	 * 
	 * @return ��ȯ�� �����ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 * 
	 * @see https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/strtol-wcstol-strtol-l-wcstol-l?view=msvc-170
	 */
	bool ToInt(const std::string& integerStr, int32_t& integer);
}