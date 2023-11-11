#include "AssertionMacro.h"
#include "CommandLineArg.h"
#include "FileManager.h"
#include "StringUtils.h"

#include <iostream>

int main(int argc, char* argv[])
{
	CommandLineArg::Parse(argc, argv);

	FileManager::Get().Startup();
	FileManager::Get().Shutdown();
	return 0;
}