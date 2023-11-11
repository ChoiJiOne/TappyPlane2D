#include "EngineManager.h"

#include "AssertionMacro.h"
#include "CommandLineArg.h"
#include "FileManager.h"

#include <iostream>

void EngineManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup engine manager...");

	CommandLineArg::Parse(GetCommandLineA());

	FileManager::Get().Startup();

	std::string propertiesPath;
	ASSERT(CommandLineArg::GetStringValue("properties", propertiesPath), "failed to load properties json file...");

	Json::Value properties = FileManager::Get().ReadJsonFile(propertiesPath);
	std::cout << properties << std::endl;

	
	bIsStartup_ = true;
}

void EngineManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	FileManager::Get().Shutdown();

	bIsStartup_ = false;
}