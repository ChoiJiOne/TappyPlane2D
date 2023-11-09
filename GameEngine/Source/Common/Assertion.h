#pragma once

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <windows.h>


/**
 * @brief 디버그 창에 형식화된 문자열을 출력합니다.
 * 
 * @param format 형식 문자열입니다.
 * @param .. 문자열 내의 형식에 대응하는 가변인자입니다.
 * 
 * @note
 * - Debug와 Release모드에서만 디버그 창에 문자열이 출력됩니다.
 * - Shipping 모드에서는 디버그 창에 문자열이 출력되지 않습니다.
 */
inline void DebugPrintF(const char* format, ...)
{
	const int32_t BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];
	std::memset(buffer, 0, sizeof(buffer));

	va_list args;
	va_start(args, format);
	int32_t size = vsnprintf(buffer, BUFFER_SIZE, format, args);
	va_end(args);

	OutputDebugStringA(buffer);
}


/**
 * @brief 디버그 창에 형식화된 문자열을 출력합니다.
 * 
 * @param format 형식 문자열입니다.
 * @param .. 문자열 내의 형식에 대응하는 가변인자입니다.
 * 
 * @note
 * - Debug와 Release모드에서만 디버그 창에 문자열이 출력됩니다.
 * - Shipping 모드에서는 디버그 창에 문자열이 출력되지 않습니다.
 */
inline void DebugPrintF(const wchar_t* format, ...)
{
	const int32_t BUFFER_SIZE = 1024;
	wchar_t buffer[BUFFER_SIZE];
	std::memset(buffer, 0, sizeof(buffer));

	va_list args;
	va_start(args, format);
	int32_t size = _vsnwprintf_s(buffer, BUFFER_SIZE, format, args);
	va_end(args);

	OutputDebugStringW(buffer);
}


/**
 * @brief 평가식을 검사합니다.
 * 
 * @param EXPRESSION 검사할 평가식입니다.
 * @param ... 평가식을 만족하지 못할 경우 표시할 가변 인자 메시지입니다.
 * 
 * @note
 * - Debug 모드와 Release 모드에서는 평가식을 검사하지만 Shipping 모드에서는 평가식을 검사하지 않습니다.
 * - 디버거가 존재하면 브레이크 포인트가 걸립니다.
 * - 디버거가 존재하지 않으면 크래시 덤프 파일을 생성합니다.
 */
#if defined(DEBUG)
#ifndef ASSERTION // assertion(...);
#define ASSERTION(EXPRESSION, ...)\
{\
if (!(bool)(EXPRESSION))\
{\
DebugPrintF("\nAssertion check point failed!\nFILE : %s\nLINE : %d\nEXPRESSION : %s\nMESSAGE : ", __FILE__, __LINE__, #EXPRESSION);\
DebugPrintF(__VA_ARGS__);\
DebugPrintF("\n");\
__debugbreak(); \
ExitProcess(-1);\
}\
}
#endif
#elif defined(RELEASE)
#ifndef ASSERTION
#define ASSERTION(EXPRESSION, ...)\
{\
if (!(bool)(EXPRESSION))\
{\
DebugPrintF("\nAssertion check point failed!\nFILE : %s\nLINE : %d\nEXPRESSION : %s\nMESSAGE : ", __FILE__, __LINE__, #EXPRESSION);\
DebugPrintF(__VA_ARGS__);\
DebugPrintF("\n");\
__debugbreak(); \
}\
}
#endif
#else
#ifndef ASSERTION
#define ASSERTION(EXPRESSION, ...) ((void)(EXPRESSION))
#endif
#endif