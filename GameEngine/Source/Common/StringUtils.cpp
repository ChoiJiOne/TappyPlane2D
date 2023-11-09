#include "Common/StringUtils.h"

#include <algorithm>

char StringUtils::charBuffer_[StringUtils::MAX_BUFFER_SIZE];
wchar_t StringUtils::wcharBuffer_[StringUtils::MAX_BUFFER_SIZE];

std::string StringUtils::PrintF(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int32_t size = vsnprintf(charBuffer_, MAX_BUFFER_SIZE, format, args);
	va_end(args);

	return std::string(charBuffer_, size);
}

std::wstring StringUtils::PrintF(const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	int32_t size = _vsnwprintf_s(wcharBuffer_, MAX_BUFFER_SIZE, format, args);
	va_end(args);

	return std::wstring(wcharBuffer_, size);
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
	std::size_t size = std::mbstowcs(wcharBuffer_, text.c_str(), MAX_BUFFER_SIZE);
	return std::wstring(wcharBuffer_, size);
}

std::string StringUtils::Convert(const std::wstring& text)
{
	std::size_t size = std::wcstombs(charBuffer_, text.c_str(), MAX_BUFFER_SIZE);
	return std::string(charBuffer_, size);
}

bool StringUtils::IsEqual(const std::string& lhs, const std::string& rhs)
{
	return lhs.compare(rhs) == 0;
}

bool StringUtils::IsEqual(const std::wstring& lhs, const std::wstring& rhs)
{
	return lhs.compare(rhs) == 0;
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