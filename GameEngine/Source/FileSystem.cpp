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

bool FileSystem::IsFilePath(const std::string& path)
{
	return std::filesystem::is_regular_file(std::filesystem::path(path));
}

bool FileSystem::IsFilePath(const std::wstring& path)
{
	return std::filesystem::is_regular_file(std::filesystem::path(path));
}

bool FileSystem::IsDirectoryPath(const std::string& path)
{
	return std::filesystem::is_directory(std::filesystem::path(path));
}

bool FileSystem::IsDirectoryPath(const std::wstring& path)
{
	return std::filesystem::is_directory(std::filesystem::path(path));
}

std::string FileSystem::GetBasePath(const std::string& path)
{
	std::size_t lastSlash;

	if ((lastSlash = path.rfind('/')) != std::string::npos)
	{
		return path.substr(0, lastSlash + 1);
	}
	else if ((lastSlash = path.rfind('\\')) != std::string::npos)
	{
		return path.substr(0, lastSlash + 1);
	}
	else
	{
		return "";
	}
}

std::wstring FileSystem::GetBasePath(const std::wstring& path)
{
	std::size_t lastSlash;

	if ((lastSlash = path.rfind(L'/')) != std::wstring::npos)
	{
		return path.substr(0, lastSlash + 1);
	}
	else if ((lastSlash = path.rfind(L'\\')) != std::wstring::npos)
	{
		return path.substr(0, lastSlash + 1);
	}
	else
	{
		return L"";
	}
}

std::string FileSystem::RemoveBasePath(const std::string& path)
{
	std::size_t lastSlash;

	if ((lastSlash = path.rfind('/')) != std::string::npos)
	{
		return path.substr(lastSlash + 1, std::string::npos);
	}
	else if ((lastSlash = path.rfind('\\')) != std::string::npos)
	{
		return path.substr(lastSlash + 1, std::string::npos);
	}
	else
	{
		return path;
	}
}

std::wstring FileSystem::RemoveBasePath(const std::wstring& path)
{
	std::size_t lastSlash;

	if ((lastSlash = path.rfind(L'/')) != std::string::npos)
	{
		return path.substr(lastSlash + 1, std::string::npos);
	}
	else if ((lastSlash = path.rfind(L'\\')) != std::string::npos)
	{
		return path.substr(lastSlash + 1, std::string::npos);
	}
	else
	{
		return path;
	}
}