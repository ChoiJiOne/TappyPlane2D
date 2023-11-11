#include "AssertionMacro.h"
#include "CommandLineArg.h"
#include "EngineManager.h"
#include "FileManager.h"
#include "StringUtils.h"

int main(int argc, char* argv[])
{
	EngineManager::Get().Startup();
	EngineManager::Get().Shutdown();

	return 0;
}