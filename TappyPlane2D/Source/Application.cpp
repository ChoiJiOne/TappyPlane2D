#include "AssertionMacro.h"
#include "CommandLineArg.h"
#include "StringUtils.h"

int main(int argc, char* argv[])
{
	CommandLineArg::Parse(argc, argv);

	int32_t value0;
	CommandLineArg::GetIntValue("C", value0);

	float value1;
	CommandLineArg::GetFloatValue("B", value1);

	std::string value2;
	CommandLineArg::GetStringValue("C", value2);

	return 0;
}