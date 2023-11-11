#include "AssertionMacro.h"
#include "CommandLineArg.h"
#include "StringUtils.h"

int main(int argc, char* argv[])
{
	CommandLineArg::Parse(argc, argv);

	return 0;
}