#include "AssertionMacro.h"
#include "CommandLineArg.h"
#include "FileSystem.h"
#include "StringUtils.h"

int main(int argc, char* argv[])
{
	CommandLineArg::Parse(argc, argv);

	std::wstring dir = L"D:\\Work\\TappyPlane2D\\TappyPlane2D";
	std::vector<std::wstring> contents0 = FileSystem::GetSubDirectories(dir);
	std::vector<std::wstring> contents1 = FileSystem::GetFilesInDirectory(dir);
	std::vector<std::wstring> contents2 = FileSystem::GetDirectoryContents(dir);

	std::wstring text = FileSystem::ReadTextFileToString(L"D:\\Work\\TappyPlane2D\\TappyPlane2D\\korean.txt");

	return 0;
}