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
