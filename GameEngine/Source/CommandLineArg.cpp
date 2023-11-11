#include "CommandLineArg.h"
#include "StringUtils.h"

#include <array>
#include <algorithm>
#include <regex>
#include <unordered_map>

std::string executePath;									// 실행 파일 경로입니다.
std::unordered_map<std::string, std::string> argumentMaps;  // 명령행 인자의 키-값 쌍입니다.

void CommandLineArg::Parse(int32_t argc, char* argv[])
{
	executePath = argv[0];

	std::regex pattern("^[^=]+=[^=]+$"); // <key>=<value> 패턴
	for (std::size_t index = 1; index < argc; ++index)
	{
		if (std::regex_match(argv[index], pattern))
		{
			std::vector<std::string> keyValue = StringUtils::Split(argv[index], "=");
			argumentMaps.insert({ keyValue.front(), keyValue.back() });
		}
	}
}

bool IsValid(const std::string& key)
{
	return argumentMaps.find(key) != argumentMaps.end();
}

bool CommandLineArg::GetBoolValue(const std::string& key, bool& value)
{
	if (!IsValid(key))
	{
		return false;
	}

	std::string valueStr = StringUtils::ToLower(argumentMaps.at(key));
	if (valueStr == "true" || valueStr == "false") // true, True, TRUE, false, False, FALSE 모두 가능.
	{
		value = (valueStr == "true");
		return true;
	}
	else
	{
		return false;
	}
}

bool CommandLineArg::GetIntValue(const std::string& key, int32_t& value)
{
	if (!IsValid(key))
	{
		return false;
	}

	return StringUtils::ToInt(argumentMaps.at(key), value);
}

bool CommandLineArg::GetFloatValue(const std::string& key, float& value)
{
	if (!IsValid(key))
	{
		return false;
	}

	return StringUtils::ToFloat(argumentMaps.at(key), value);
}

bool CommandLineArg::GetStringValue(const std::string& key, std::string& value)
{
	if (!IsValid(key))
	{
		return false;
	}

	value = argumentMaps.at(key);

	return true;
}

std::string CommandLineArg::GetExecutePath()
{
	return executePath;
}