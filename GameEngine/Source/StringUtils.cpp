#include "StringUtils.h"

#include <algorithm>

const int32_t MAX_BUFFER_SIZE = 1024;	// 문자열 버퍼의 최대 크기입니다.
char charBuffer[MAX_BUFFER_SIZE];		// char 문자열 버퍼입니다.
wchar_t wcharBuffer[MAX_BUFFER_SIZE];	// wchar_t 문자열 버퍼입니다.

std::string StringUtils::PrintF(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int32_t size = vsnprintf(charBuffer, MAX_BUFFER_SIZE, format, args);
	va_end(args);

	return std::string(charBuffer, size);
}

std::wstring StringUtils::PrintF(const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	int32_t size = _vsnwprintf_s(wcharBuffer, MAX_BUFFER_SIZE, format, args);
	va_end(args);

	return std::wstring(wcharBuffer, size);
}

std::vector<std::string> StringUtils::Split(const std::string& text, const std::string& delimiter)
{
	std::vector<std::string> tokens;
	std::size_t position = 0ULL;
	std::string remain = text;

	while ((position = remain.find(delimiter)) != std::string::npos)
	{
		tokens.push_back(remain.substr(0, position));
		remain.erase(0, position + delimiter.length());
	}

	tokens.push_back(remain);
	return tokens;
}

std::vector<std::wstring> StringUtils::Split(const std::wstring& text, const std::wstring& delimiter)
{
	std::vector<std::wstring> tokens;
	std::size_t position = 0ULL;
	std::wstring remain = text;

	while ((position = remain.find(delimiter)) != std::string::npos)
	{
		tokens.push_back(remain.substr(0, position));
		remain.erase(0, position + delimiter.length());
	}

	tokens.push_back(remain);
	return tokens;
}

std::wstring StringUtils::Convert(const std::string& text)
{
	std::size_t size = std::mbstowcs(wcharBuffer, text.c_str(), MAX_BUFFER_SIZE);
	return std::wstring(wcharBuffer, size);
}

std::string StringUtils::Convert(const std::wstring& text)
{
	std::size_t size = std::wcstombs(charBuffer, text.c_str(), MAX_BUFFER_SIZE);
	return std::string(charBuffer, size);
}

std::string StringUtils::ToLower(const std::string& text)
{
	std::string lower = text;
	std::transform(lower.begin(), lower.end(), lower.begin(), std::tolower);
	return lower;
}

std::wstring StringUtils::ToLower(const std::wstring& text)
{
	std::wstring lower = text;
	std::transform(lower.begin(), lower.end(), lower.begin(), std::tolower);
	return lower;
}

std::string StringUtils::ToUpper(const std::string& text)
{
	std::string upper = text;
	std::transform(upper.begin(), upper.end(), upper.begin(), std::toupper);
	return upper;
}

std::wstring StringUtils::ToUpper(const std::wstring& text)
{
	std::wstring upper = text;
	std::transform(upper.begin(), upper.end(), upper.begin(), std::toupper);
	return upper;
}

bool StringUtils::ToInt(const std::string& integerStr, int32_t& integer)
{
	const char* strPtr = integerStr.c_str();
	char* endPtr = nullptr;
	const int32_t radix = 10; // 10진수 고정

	const long ans = strtol(strPtr, &endPtr, radix);
	if (strPtr == endPtr || ans < INT_MIN || ans > INT_MAX)
	{
		return false;
	}
	
	integer = static_cast<int32_t>(ans);
	return true;
}

bool StringUtils::ToInt(const std::wstring& integerStr, int32_t& integer)
{
	const wchar_t* strPtr = integerStr.c_str();
	wchar_t* endPtr = nullptr;
	const int32_t radix = 10; // 10진수 고정

	const long ans = wcstol(strPtr, &endPtr, radix);
	if (strPtr == endPtr || ans < INT_MIN || ans > INT_MAX)
	{
		return false;
	}

	integer = static_cast<int32_t>(ans);
	return true;
}

bool StringUtils::ToFloat(const std::string& floatStr, float& floating)
{
	const char* strPtr = floatStr.c_str();
	char* endPtr = nullptr;

	const float ans = strtof(strPtr, &endPtr);
	if (strPtr == endPtr)
	{
		return false;
	}

	floating = ans;
	return true;
}

bool StringUtils::ToFloat(const std::wstring& floatStr, float& floating)
{
	const wchar_t* strPtr = floatStr.c_str();
	wchar_t* endPtr = nullptr;

	const float ans = wcstof(strPtr, &endPtr);
	if (strPtr == endPtr)
	{
		return false;
	}

	floating = ans;
	return true;
}