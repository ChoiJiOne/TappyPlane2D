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