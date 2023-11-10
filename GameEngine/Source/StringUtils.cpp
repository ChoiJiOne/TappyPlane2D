#include "StringUtils.h"

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