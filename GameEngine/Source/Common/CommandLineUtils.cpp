#include "Common/CommandLineUtils.h"
#include "Common/StringUtils.h"

#include <array>
#include <algorithm>
#include <regex>

std::string CommandLineUtils::executePath_;
std::vector<std::string> CommandLineUtils::options_;
std::unordered_map<std::string, std::string> CommandLineUtils::keyValues_;
std::unordered_map<CommandLineUtils::EArgumentType, std::string> CommandLineUtils::argPatterns_ =
{
	{ CommandLineUtils::EArgumentType::OPTION,   "^-[a-zA-Z]+$"  },
	{ CommandLineUtils::EArgumentType::KEYVALUE, "^[^=]+=[^=]+$" },
};

void CommandLineUtils::Parse(int32_t argc, char* argv[])
{
	executePath_ = argv[0];

	for (std::size_t index = 1; index < argc; ++index)
	{
		ParseArg(argv[index]);
	}
}

bool CommandLineUtils::IsValidOption(const std::string& option)
{
	return std::find(options_.begin(), options_.end(), option) != options_.end();
}

bool CommandLineUtils::IsValidKey(const std::string& key)
{
	return keyValues_.find(key) != keyValues_.end();
}

std::string CommandLineUtils::GetValue(const std::string& key)
{
	return (IsValidKey(key) ? keyValues_.at(key) : "");
}

bool CommandLineUtils::CheckArgPatternMatch(const std::string& arg, const std::string& pattern)
{
	return std::regex_match(arg, std::regex(pattern));
}

CommandLineUtils::EArgumentType CommandLineUtils::GetArgType(const std::string& arg)
{
	EArgumentType argType = EArgumentType::NONE;

	for (const auto& argPattern : argPatterns_)
	{
		if (CheckArgPatternMatch(arg, argPattern.second))
		{
			argType = argPattern.first;
			break;
		}
	}

	return argType;
}

void CommandLineUtils::ParseArg(const std::string& arg)
{
	EArgumentType argType = GetArgType(arg);

	switch (argType)
	{
	case EArgumentType::NONE:
		break;

	case EArgumentType::OPTION:
		options_.push_back(arg);
		break;

	case EArgumentType::KEYVALUE:
		std::vector<std::string> keyValue = StringUtils::Split(arg, "=");
		keyValues_.insert({ keyValue.front(), keyValue.back() });
		break;
	}
}