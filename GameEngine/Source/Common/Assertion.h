#pragma once

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <windows.h>


/**
 * @brief ����� â�� ����ȭ�� ���ڿ��� ����մϴ�.
 * 
 * @param format ���� ���ڿ��Դϴ�.
 * @param .. ���ڿ� ���� ���Ŀ� �����ϴ� ���������Դϴ�.
 * 
 * @note
 * - Debug�� Release��忡���� ����� â�� ���ڿ��� ��µ˴ϴ�.
 * - Shipping ��忡���� ����� â�� ���ڿ��� ��µ��� �ʽ��ϴ�.
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
 * @brief ����� â�� ����ȭ�� ���ڿ��� ����մϴ�.
 * 
 * @param format ���� ���ڿ��Դϴ�.
 * @param .. ���ڿ� ���� ���Ŀ� �����ϴ� ���������Դϴ�.
 * 
 * @note
 * - Debug�� Release��忡���� ����� â�� ���ڿ��� ��µ˴ϴ�.
 * - Shipping ��忡���� ����� â�� ���ڿ��� ��µ��� �ʽ��ϴ�.
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
 * @brief �򰡽��� �˻��մϴ�.
 * 
 * @param EXPRESSION �˻��� �򰡽��Դϴ�.
 * @param ... �򰡽��� �������� ���� ��� ǥ���� ���� ���� �޽����Դϴ�.
 * 
 * @note
 * - Debug ���� Release ��忡���� �򰡽��� �˻������� Shipping ��忡���� �򰡽��� �˻����� �ʽ��ϴ�.
 * - ����Ű� �����ϸ� �극��ũ ����Ʈ�� �ɸ��ϴ�.
 * - ����Ű� �������� ������ ũ���� ���� ������ �����մϴ�.
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