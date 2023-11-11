#pragma once

#include <codecvt>
#include <vector>
#include <string>

#include <json/json.h>

#include "IManager.h"
#include "Macro.h"
#include "SingletonMacro.h"


/**
 * @brief 파일 및 디렉토리 관련 처리를 수행하는 매니저입니다.
 *
 * @note 이 클래스는 싱글턴입니다.
 */
class FileManager : public IManager
{
	SINGLETON(FileManager);


public:
	/**
	 * @brief 파일 및 디렉토리 관련 처리를 수행하는 매니저의 사용을 시작합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 파일 및 디렉토리 관련 처리를 수행하는 매니저의 사용을 종료합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 파일 혹은 디렉토리 경로가 유효한지 확인합니다.
	 *
	 * @param path 파일 혹은 디렉토리 경로입니다.
	 *
	 * @return 파일 혹은 디렉토리가 유효하다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsValidPath(const std::string& path);


	/**
	 * @brief 파일 혹은 디렉토리 경로가 유효한지 확인합니다.
	 *
	 * @param path 파일 혹은 디렉토리 경로입니다.
	 *
	 * @return 파일 혹은 디렉토리가 유효하다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsValidPath(const std::wstring& path);


	/**
	 * @brief 경로가 파일 경로인지 확인합니다.
	 *
	 * @param path 파일 경로인지 확인할 전체 경로입니다.
	 *
	 * @return 경로가 파일 경로라면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsFilePath(const std::string& path);


	/**
	 * @brief 경로가 파일 경로인지 확인합니다.
	 *
	 * @param path 파일 경로인지 확인할 전체 경로입니다.
	 *
	 * @return 경로가 파일 경로라면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsFilePath(const std::wstring& path);


	/**
	 * @brief 경로가 디렉토리 경로인지 확인합니다.
	 *
	 * @param path 디렉토리 경로인지 확인할 전체 경로입니다.
	 *
	 * @return 경로가 디렉토리 경로라면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsDirectoryPath(const std::string& path);


	/**
	 * @brief 경로가 디렉토리 경로인지 확인합니다.
	 *
	 * @param path 디렉토리 경로인지 확인할 전체 경로입니다.
	 *
	 * @return 경로가 디렉토리 경로라면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsDirectoryPath(const std::wstring& path);


	/**
	 * @brief 경로에서 파일이나 디렉토리 이름을 제외한 경로를 얻습니다.
	 *
	 * @param path 파일이나 디렉토리 경로입니다.
	 *
	 * @return 파일이나 디렉토리 이름을 제외한 경로를 반환합니다.
	 *
	 * @example
	 * - 파일 경로가 "D:\\AAA\\BBB\\CCC.a"라면, 반환하는 값은 "D:\\AAA\\BBB\\" 입니다.
	 * - 디렉토리 경로가 "D:\\AAA\\BBB\\CCC"라면, 반환하는 값은 "D:\\AAA\\BBB\\" 입니다.
	 */
	std::string GetBasePath(const std::string& path);


	/**
	 * @brief 경로에서 파일이나 디렉토리 이름을 제외한 경로를 얻습니다.
	 *
	 * @param path 파일이나 디렉토리 경로입니다.
	 *
	 * @return 파일이나 디렉토리 이름을 제외한 경로를 반환합니다.
	 *
	 * @example
	 * - 파일 경로가 "D:\\AAA\\BBB\\CCC.a"라면, 반환하는 값은 "D:\\AAA\\BBB\\" 입니다.
	 * - 디렉토리 경로가 "D:\\AAA\\BBB\\CCC"라면, 반환하는 값은 "D:\\AAA\\BBB\\" 입니다.
	 */
	std::wstring GetBasePath(const std::wstring& path);


	/**
	 * @brief 전체 파일이나 디렉토리 경로에서 베이스 경로를 삭제합니다.
	 *
	 * @param path 베이스 경로를 삭제할 전체 파일이나 디렉토리 경로입니다.
	 *
	 * @return 베이스 경로가 삭제된 파일 경로를 반환합니다.
	 *
	 * @example
	 * - 파일 경로가 "D:\\AAA\\BBB\\CCC.a"라면, 반환하는 값은 "CCC.a" 입니다.
	 * - 디렉토리 경로가 "D:\\AAA\\BBB\\CCC"라면, 반환하는 값은 "CCC" 입니다.
	 */
	std::string RemoveBasePath(const std::string& path);


	/**
	 * @brief 전체 파일이나 디렉토리 경로에서 베이스 경로를 삭제합니다.
	 *
	 * @param path 베이스 경로를 삭제할 전체 파일이나 디렉토리 경로입니다.
	 *
	 * @return 베이스 경로가 삭제된 파일 경로를 반환합니다.
	 *
	 * @example
	 * - 파일 경로가 "D:\\AAA\\BBB\\CCC.a"라면, 반환하는 값은 "CCC.a" 입니다.
	 * - 디렉토리 경로가 "D:\\AAA\\BBB\\CCC"라면, 반환하는 값은 "CCC" 입니다.
	 */
	std::wstring RemoveBasePath(const std::wstring& path);


	/**
	 * @brief 전체 파일 경로에서 파일 확장자를 얻습니다.
	 *
	 * @param path 파일 확장자를 얻을 전체 파일 경로입니다.
	 *
	 * @return 전체 파일 경로의 파일 확장자를 반환합니다.
	 *
	 * @example
	 * - 파일 경로가 "D:\\AAA\\BBB\\CCC.a"라면, 반환하는 값은 "a" 입니다.
	 * - 파일 경로가 "D:/AAA/BBB/CCC.a"라면, 반환하는 값은 "a" 입니다.
	 */
	std::string GetFileExtension(const std::string& path);


	/**
	 * @brief 전체 파일 경로에서 파일 확장자를 얻습니다.
	 *
	 * @param path 파일 확장자를 얻을 전체 파일 경로입니다.
	 *
	 * @return 전체 파일 경로의 파일 확장자를 반환합니다.
	 *
	 * @example
	 * - 파일 경로가 "D:\\AAA\\BBB\\CCC.a"라면, 반환하는 값은 "a" 입니다.
	 * - 파일 경로가 "D:/AAA/BBB/CCC.a"라면, 반환하는 값은 "a" 입니다.
	 */
	std::wstring GetFileExtension(const std::wstring& path);


	/**
	 * @brief 전체 파일 경로에서 확장자를 삭제합니다.
	 *
	 * @param path 파일 확장자를 삭제할 전체 파일 경로입니다.
	 *
	 * @return 파일 확장자가 삭제된 전체 파일 경로를 반환합니다.
	 *
	 * @example
	 * - 파일 경로가 "D:\\AAA\\BBB\\CCC.a"라면, 반환하는 값은 "D:\\AAA\\BBB\\CCC" 입니다.
	 * - 파일 경로가 "D:/AAA/BBB/CCC.a"라면, 반환하는 값은 "D:/AAA/BBB/CCC" 입니다.
	 */
	std::string RemoveFileExtension(const std::string& path);


	/**
	 * @brief 전체 파일 경로에서 확장자를 삭제합니다.
	 *
	 * @param path 파일 확장자를 삭제할 전체 파일 경로입니다.
	 *
	 * @return 파일 확장자가 삭제된 전체 파일 경로를 반환합니다.
	 *
	 * @example
	 * - 파일 경로가 "D:\\AAA\\BBB\\CCC.a"라면, 반환하는 값은 "D:\\AAA\\BBB\\CCC" 입니다.
	 * - 파일 경로가 "D:/AAA/BBB/CCC.a"라면, 반환하는 값은 "D:/AAA/BBB/CCC" 입니다.
	 */
	std::wstring RemoveFileExtension(const std::wstring& path);


	/**
	 * @brief 디렉토리 하위의 파일과 디렉토리 목록을 얻습니다.
	 * 
	 * @param path 파일과 디렉토리 목록을 얻을 상위 디렉토리 경로입니다.
	 * 
	 * @return 파일 경로와 디렉토리 경로가 포함된 벡터를 반환합니다.
	 */
	std::vector<std::string> GetDirectoryContents(const std::string& path);

	
	/**
	 * @brief 디렉토리 하위의 파일과 디렉토리 목록을 얻습니다.
	 * 
	 * @param path 파일과 디렉토리 목록을 얻을 상위 디렉토리 경로입니다.
	 * 
	 * @return 파일 경로와 디렉토리 경로가 포함된 벡터를 반환합니다.
	 */
	std::vector<std::wstring> GetDirectoryContents(const std::wstring& path);


	/**
	 * @brief 디렉토리 하위의 디렉토리 목록을 얻습니다.
	 * 
	 * @param path 하위 디렉토리 목록을 얻을 상위 디렉토리 경로입니다.
	 * 
	 * @return 하위 디렉토리 경로가 포함된 벡터를 반환합니다.
	 */
	std::vector<std::string> GetSubDirectories(const std::string& path);
	

	/**
	 * @brief 디렉토리 하위의 디렉토리 목록을 얻습니다.
	 * 
	 * @param path 하위 디렉토리 목록을 얻을 상위 디렉토리 경로입니다.
	 * 
	 * @return 하위 디렉토리 경로가 포함된 벡터를 반환합니다.
	 */
	std::vector<std::wstring> GetSubDirectories(const std::wstring& path);


	/**
	 * @brief 디렉토리의 파일 목록을 얻습니다.
	 * 
	 * @param path 파일 목록을 얻을 디렉토리 경로입니다.
	 * 
	 * @return 디렉토리 하위의 파일들이 포함된 벡터를 반환합니다.
	 */
	std::vector<std::string> GetFilesInDirectory(const std::string& path);


	/**
	 * @brief 디렉토리의 파일 목록을 얻습니다.
	 *
	 * @param path 파일 목록을 얻을 디렉토리 경로입니다.
	 *
	 * @return 디렉토리 하위의 파일들이 포함된 벡터를 반환합니다.
	 */
	std::vector<std::wstring> GetFilesInDirectory(const std::wstring& path);


	/**
	 * @brief 텍스트 파일을 읽어 문자열로 반환합니다.
	 * 
	 * @param path 파일의 경로입니다.
	 * 
	 * @return 텍스트 파일 내용이 저장된 문자열을 반환합니다.
	 */
	std::string ReadTextFileToString(const std::string& path);


	/**
	 * @brief 텍스트 파일을 읽어 문자열로 반환합니다.
	 *
	 * @param path 파일의 경로입니다.
	 *
	 * @return 텍스트 파일 내용이 저장된 문자열을 반환합니다.
	 * 
	 * @see https://stackoverflow.com/questions/4775437/read-unicode-utf-8-file-into-wstring
	 */
	std::wstring ReadTextFileToString(const std::wstring& path);


	/**
	 * @brief Json 파일을 읽어 Json 객체를 반환합니다.
	 * 
	 * @param path Json 파일의 경로입니다.
	 * 
	 * @return Json 파일 객체를 반환합니다.
	 */
	Json::Value ReadJsonFile(const std::string& path);


private:
	/**
	 * @brief 디렉토리 하위의 파일과 디렉토리 목록을 얻습니다.
	 *
	 * @param path 파일과 디렉토리 목록을 얻을 상위 디렉토리 경로입니다.
	 * @param bIsIncludeFile 목록에 파일을 추가시킬지의 여부입니다. true면 추가하고, 그렇지 않으면 추가하지 않습니다.
	 * @param bIsIncludeDirectory 목록에 디렉토리를 추가시킬지의 여부입니다. true면 추가하고 그렇지 않으면 추가하지 않습니다.
	 *
	 * @return 파일 경로와 디렉토리 경로가 포함된 벡터를 반환합니다.
	 */
	std::vector<std::string> GetDirectoryContents(const std::string& path, bool bIsIncludeFile, bool bIsIncludeDirectory);


	/**
	 * @brief 디렉토리 하위의 파일과 디렉토리 목록을 얻습니다.
	 *
	 * @param path 파일과 디렉토리 목록을 얻을 상위 디렉토리 경로입니다.
	 * @param bIsIncludeFile 목록에 파일을 추가시킬지의 여부입니다. true면 추가하고, 그렇지 않으면 추가하지 않습니다.
	 * @param bIsIncludeDirectory 목록에 디렉토리를 추가시킬지의 여부입니다. true면 추가하고 그렇지 않으면 추가하지 않습니다.
	 *
	 * @return 파일 경로와 디렉토리 경로가 포함된 벡터를 반환합니다.
	 */
	std::vector<std::wstring> GetDirectoryContents(const std::wstring& path, bool bIsIncludeFile, bool bIsIncludeDirectory);


private:
	/**
	 * @brief 영어권 이외의 문자열을 처리하기 위한 locale입니다.
	 */
	std::locale locale_;
};