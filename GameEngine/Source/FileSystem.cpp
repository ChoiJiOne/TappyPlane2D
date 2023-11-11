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

std::string FileSystem::GetFileExtension(const std::string& path)
{
	std::string filename = RemoveBasePath(path);
	std::size_t offset = filename.rfind('.');

	return (offset == std::string::npos) ? "" : filename.substr(offset + 1);
}

std::wstring FileSystem::GetFileExtension(const std::wstring& path)
{
	std::wstring filename = RemoveBasePath(path);
	std::size_t offset = filename.rfind('.');

	return (offset == std::wstring::npos) ? L"" : filename.substr(offset + 1);
}

std::string FileSystem::RemoveFileExtension(const std::string& path)
{
	return path.substr(0, path.rfind("."));
}

std::wstring FileSystem::RemoveFileExtension(const std::wstring& path)
{
	return path.substr(0, path.rfind(L"."));
}

/**
 * @brief 디렉토리 하위의 파일과 디렉토리 목록을 얻습니다.
 *
 * @param path 파일과 디렉토리 목록을 얻을 상위 디렉토리 경로입니다.
 * @param bIsIncludeFile 목록에 파일을 추가시킬지의 여부입니다. true면 추가하고, 그렇지 않으면 추가하지 않습니다.
 * @param bIsIncludeDirectory 목록에 디렉토리를 추가시킬지의 여부입니다. true면 추가하고 그렇지 않으면 추가하지 않습니다.
 *
 * @return 파일 경로와 디렉토리 경로가 포함된 벡터를 반환합니다.
 */
std::vector<std::string> GetDirectoryContentsA(const std::string& path, bool bIsIncludeFile, bool bIsIncludeDirectory)
{
	std::vector<std::string> contents;

	if (!FileSystem::IsDirectoryPath(path))
	{
		return contents;
	}

	for (auto& entry : std::filesystem::directory_iterator(path))
	{
		if (std::filesystem::is_regular_file(entry) && bIsIncludeFile) // 파일인지 검사
		{
			contents.push_back(entry.path().string());
		}
		else if (std::filesystem::is_directory(entry) && bIsIncludeDirectory)	// 디렉토리인지 검사
		{
			contents.push_back(entry.path().string());
		}
	}

	return contents;
}

/**
 * @brief 디렉토리 하위의 파일과 디렉토리 목록을 얻습니다.
 *
 * @param path 파일과 디렉토리 목록을 얻을 상위 디렉토리 경로입니다.
 * @param bIsIncludeFile 목록에 파일을 추가시킬지의 여부입니다. true면 추가하고, 그렇지 않으면 추가하지 않습니다.
 * @param bIsIncludeDirectory 목록에 디렉토리를 추가시킬지의 여부입니다. true면 추가하고 그렇지 않으면 추가하지 않습니다.
 *
 * @return 파일 경로와 디렉토리 경로가 포함된 벡터를 반환합니다.
 */
std::vector<std::wstring> GetDirectoryContentsW(const std::wstring& path, bool bIsIncludeFile, bool bIsIncludeDirectory)
{
	std::vector<std::wstring> contents;

	if (!FileSystem::IsDirectoryPath(path))
	{
		return contents;
	}

	for (auto& entry : std::filesystem::directory_iterator(path))
	{
		if (std::filesystem::is_regular_file(entry)) // 파일인지 검사
		{
			if (bIsIncludeFile)
			{
				contents.push_back(entry.path().wstring());
			}
		}
		else if (std::filesystem::is_directory(entry))	// 디렉토리인지 검사
		{
			if (bIsIncludeDirectory)
			{
				contents.push_back(entry.path().wstring());
			}
		}
	}

	return contents;
}

std::vector<std::string> FileSystem::GetDirectoryContents(const std::string& path)
{	
	return GetDirectoryContentsA(path, true, true);
}

std::vector<std::wstring> FileSystem::GetDirectoryContents(const std::wstring& path)
{
	return GetDirectoryContentsW(path, true, true);
}

std::vector<std::string> FileSystem::GetSubDirectories(const std::string& path)
{
	return GetDirectoryContentsA(path, false, true);
}

std::vector<std::wstring> FileSystem::GetSubDirectories(const std::wstring& path)
{
	return GetDirectoryContentsW(path, false, true);
}

std::vector<std::string> FileSystem::GetFilesInDirectory(const std::string& path)
{
	return GetDirectoryContentsA(path, true, false);
}

std::vector<std::wstring> FileSystem::GetFilesInDirectory(const std::wstring& path)
{
	return GetDirectoryContentsW(path, true, false);
}