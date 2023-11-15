#include "FileManager.h"

#include "AssertionMacro.h"

#include <codecvt>
#include <fstream>
#include <sstream>
#include <filesystem>

void FileManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup file manager...");

	locale_ = std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>);

	bIsStartup_ = true;
}

void FileManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	bIsStartup_ = false;
}

bool FileManager::IsValidPath(const std::string& path)
{
	return std::filesystem::exists(std::filesystem::path(path));
}

bool FileManager::IsValidPath(const std::wstring& path)
{
	return std::filesystem::exists(std::filesystem::path(path));
}

bool FileManager::IsFilePath(const std::string& path)
{
	return std::filesystem::is_regular_file(std::filesystem::path(path));
}

bool FileManager::IsFilePath(const std::wstring& path)
{
	return std::filesystem::is_regular_file(std::filesystem::path(path));
}

bool FileManager::IsDirectoryPath(const std::string& path)
{
	return std::filesystem::is_directory(std::filesystem::path(path));
}

bool FileManager::IsDirectoryPath(const std::wstring& path)
{
	return std::filesystem::is_directory(std::filesystem::path(path));
}

std::string FileManager::GetBasePath(const std::string& path)
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

std::wstring FileManager::GetBasePath(const std::wstring& path)
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

std::string FileManager::RemoveBasePath(const std::string& path)
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

std::wstring FileManager::RemoveBasePath(const std::wstring& path)
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

std::string FileManager::GetFileExtension(const std::string& path)
{
	std::string filename = RemoveBasePath(path);
	std::size_t offset = filename.rfind('.');

	return (offset == std::string::npos) ? "" : filename.substr(offset + 1);
}

std::wstring FileManager::GetFileExtension(const std::wstring& path)
{
	std::wstring filename = RemoveBasePath(path);
	std::size_t offset = filename.rfind('.');

	return (offset == std::wstring::npos) ? L"" : filename.substr(offset + 1);
}

std::string FileManager::RemoveFileExtension(const std::string& path)
{
	return path.substr(0, path.rfind("."));
}

std::wstring FileManager::RemoveFileExtension(const std::wstring& path)
{
	return path.substr(0, path.rfind(L"."));
}

std::vector<std::string> FileManager::GetDirectoryContents(const std::string& path)
{	
	return GetDirectoryContents(path, true, true);
}

std::vector<std::wstring> FileManager::GetDirectoryContents(const std::wstring& path)
{
	return GetDirectoryContents(path, true, true);
}

std::vector<std::string> FileManager::GetSubDirectories(const std::string& path)
{
	return GetDirectoryContents(path, false, true);
}

std::vector<std::wstring> FileManager::GetSubDirectories(const std::wstring& path)
{
	return GetDirectoryContents(path, false, true);
}

std::vector<std::string> FileManager::GetFilesInDirectory(const std::string& path)
{
	return GetDirectoryContents(path, true, false);
}

std::vector<std::wstring> FileManager::GetFilesInDirectory(const std::wstring& path)
{
	return GetDirectoryContents(path, true, false);
}

std::string FileManager::ReadTextFileToString(const std::string& path)
{
	ASSERT(IsValidPath(path), "invalid %s path...", path.c_str());
	ASSERT(IsFilePath(path), "%s is not file path...", path.c_str());

	std::ifstream fileStream(path);
	ASSERT(fileStream.is_open(), "failed to %s file open...", path.c_str());

	std::stringstream fileStringStream;
	fileStringStream << fileStream.rdbuf();

	fileStream.close();

	return fileStringStream.str();
}

std::wstring FileManager::ReadTextFileToString(const std::wstring& path)
{
	ASSERT(IsValidPath(path), "invalid %s path...", path.c_str());
	ASSERT(IsFilePath(path), "%s is not file path...", path.c_str());

	std::wifstream fileStream(path);
	ASSERT(fileStream.is_open(), "failed to %s file open...", path.c_str());

	fileStream.imbue(locale_);

	std::wstringstream fileStringStream;
	fileStringStream << fileStream.rdbuf();

	fileStream.close();

	return fileStringStream.str();
}

std::vector<uint8_t> FileManager::ReadFileToBuffer(const std::string& path)
{
	std::ifstream readFile(path, std::ios::binary);
	ASSERT(readFile.is_open(), "failed to read file : %s", path.c_str());

	std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(readFile), {});
	readFile.close();

	return buffer;
}

Json::Value FileManager::ReadJsonFile(const std::string& path)
{
	ASSERT(IsValidPath(path), "invalid %s path...", path.c_str());
	ASSERT(IsFilePath(path), "%s is not file path...", path.c_str());

	std::ifstream fileStream(path);
	ASSERT(fileStream.is_open(), "failed to %s file open...", path.c_str());
	
	Json::Value root;
	Json::CharReaderBuilder builder;
	ASSERT(Json::parseFromStream(builder, fileStream, &root, nullptr), "failed to parse %s json file...", path.c_str());

	fileStream.close();	

	return root;
}

std::vector<std::string> FileManager::GetDirectoryContents(const std::string& path, bool bIsIncludeFile, bool bIsIncludeDirectory)
{
	std::vector<std::string> contents;

	if (!IsDirectoryPath(path))
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

std::vector<std::wstring> FileManager::GetDirectoryContents(const std::wstring& path, bool bIsIncludeFile, bool bIsIncludeDirectory)
{
	std::vector<std::wstring> contents;

	if (!IsDirectoryPath(path))
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