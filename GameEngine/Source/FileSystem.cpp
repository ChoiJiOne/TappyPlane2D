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
 * @brief ���丮 ������ ���ϰ� ���丮 ����� ����ϴ�.
 *
 * @param path ���ϰ� ���丮 ����� ���� ���� ���丮 ����Դϴ�.
 * @param bIsIncludeFile ��Ͽ� ������ �߰���ų���� �����Դϴ�. true�� �߰��ϰ�, �׷��� ������ �߰����� �ʽ��ϴ�.
 * @param bIsIncludeDirectory ��Ͽ� ���丮�� �߰���ų���� �����Դϴ�. true�� �߰��ϰ� �׷��� ������ �߰����� �ʽ��ϴ�.
 *
 * @return ���� ��ο� ���丮 ��ΰ� ���Ե� ���͸� ��ȯ�մϴ�.
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
		if (std::filesystem::is_regular_file(entry) && bIsIncludeFile) // �������� �˻�
		{
			contents.push_back(entry.path().string());
		}
		else if (std::filesystem::is_directory(entry) && bIsIncludeDirectory)	// ���丮���� �˻�
		{
			contents.push_back(entry.path().string());
		}
	}

	return contents;
}

/**
 * @brief ���丮 ������ ���ϰ� ���丮 ����� ����ϴ�.
 *
 * @param path ���ϰ� ���丮 ����� ���� ���� ���丮 ����Դϴ�.
 * @param bIsIncludeFile ��Ͽ� ������ �߰���ų���� �����Դϴ�. true�� �߰��ϰ�, �׷��� ������ �߰����� �ʽ��ϴ�.
 * @param bIsIncludeDirectory ��Ͽ� ���丮�� �߰���ų���� �����Դϴ�. true�� �߰��ϰ� �׷��� ������ �߰����� �ʽ��ϴ�.
 *
 * @return ���� ��ο� ���丮 ��ΰ� ���Ե� ���͸� ��ȯ�մϴ�.
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
		if (std::filesystem::is_regular_file(entry)) // �������� �˻�
		{
			if (bIsIncludeFile)
			{
				contents.push_back(entry.path().wstring());
			}
		}
		else if (std::filesystem::is_directory(entry))	// ���丮���� �˻�
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