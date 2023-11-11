#include "AssertionMacro.h"
#include "CommandLineArg.h"
#include "FileManager.h"
#include "StringUtils.h"

#include <iostream>

int main(int argc, char* argv[])
{
	CommandLineArg::Parse(argc, argv);

	FileManager::Get().Startup();

	std::string propertiesPath;
	ASSERT(CommandLineArg::GetStringValue("properties", propertiesPath), "failed to load properties json file...");

	Json::Value properties = FileManager::Get().ReadJsonFile(propertiesPath);

	FileManager::Get().Shutdown();
	return 0;
}