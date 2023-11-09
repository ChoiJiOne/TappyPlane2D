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


	/**
	 * @brief Ư�� ���ڿ��� �������� �ؽ�Ʈ�� �и��մϴ�.
	 *
	 * @param text �и��� ��� ���ڿ��Դϴ�.
	 * @param delimiter �и��� ���� ���� ���ڿ��Դϴ�.
	 *
	 * @return �и��� ���ڿ��� ��� �ִ� ����(std::vector)�� ��ȯ�մϴ�.
	 */
	static std::vector<std::string> Split(const std::string& text, const std::string& delimiter);


	/**
	 * @brief Ư�� ���ڿ��� �������� �ؽ�Ʈ�� �и��մϴ�.
	 *
	 * @param text �и��� ��� ���ڿ��Դϴ�.
	 * @param delimiter �и��� ���� ���� ���ڿ��Դϴ�.
	 *
	 * @return �и��� ���ڿ��� ��� �ִ� ����(std::vector)�Դϴ�.
	 */
	static std::vector<std::wstring> Split(const std::wstring& text, const std::wstring& delimiter);


	/**
	 * @brief char ���ڿ��� wchar_t ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @see https://en.cppreference.com/w/cpp/string/multibyte/mbstowcs
	 *
	 * @param text ��ȯ�� ǥ�� �ؽ�Ʈ�Դϴ�.
	 *
	 * @return ��ȯ�� ���ڿ��� ��ȯ�մϴ�.
	 */
	static std::wstring Convert(const std::string& text);


	/**
	 * @brief wchar_t ���ڿ��� char ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @see https://en.cppreference.com/w/cpp/string/multibyte/wcstombs
	 *
	 * @param text ��ȯ�� ǥ�� �ؽ�Ʈ�Դϴ�.
	 *
	 * @return ��ȯ�� ���ڿ��� ��ȯ�մϴ�.
	 */
	static std::string Convert(const std::wstring& text);


	/**
	 * @brief �� ���ڿ��� �������� Ȯ���մϴ�.
	 *
	 * @param ���� �� ���ڿ� �� ���� ���ڿ��Դϴ�.
	 * @param ���� �� ���ڿ� �� ������ ���ڿ��Դϴ�.
	 *
	 * @return �� ���ڿ��� �����ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool IsEqual(const std::string& lhs, const std::string& rhs);


	/**
	 * @brief �� ���ڿ��� �������� Ȯ���մϴ�.
	 *
	 * @param ���� �� ���ڿ� �� ���� ���ڿ��Դϴ�.
	 * @param ���� �� ���ڿ� �� ������ ���ڿ��Դϴ�.
	 *
	 * @return �� ���ڿ��� �����ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool IsEqual(const std::wstring& lhs, const std::wstring& rhs);


	/**
	 * @brief ���ڿ��� ���ĺ��� ��� �ҹ��ڷ� ��ȯ�մϴ�.
	 *
	 * @param text ��ȯ�� ���ڿ��Դϴ�.
	 *
	 * @return ���ڿ� ���� ���ĺ��� ��� �ҹ��ڷ� ��ȯ�� ��ü ���ڿ��� ��ȯ�մϴ�.
	 */
	static std::string ToLower(const std::string& text);


	/**
	 * @brief ���ڿ��� ���ĺ��� ��� �ҹ��ڷ� ��ȯ�մϴ�.
	 *
	 * @param text ��ȯ�� ���ڿ��Դϴ�.
	 *
	 * @return ���ڿ� ���� ���ĺ��� ��� �ҹ��ڷ� ��ȯ�� ��ü ���ڿ��� ��ȯ�մϴ�.
	 */
	static std::wstring ToLower(const std::wstring& text);


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