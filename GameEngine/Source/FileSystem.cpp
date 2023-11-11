#include "FileSystem.h"

#include "AssertionMacro.h"

#include <fstream>
#include <sstream>
#include <filesystem>

bool FileSystem::IsValidPath(const std::string& path)
{
	return std::filesystem::exists(std::filesystem::path(path));
}

bool FileSystem::IsValidPath(const std::wstring& path)
{
	return std::filesystem::exists(std::filesystem::path(path));
}