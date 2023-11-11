#pragma once

#include <codecvt>
#include <vector>
#include <string>

#include <json/json.h>

#include "IManager.h"
#include "Macro.h"
#include "SingletonMacro.h"


/**
 * @brief ���� �� ���丮 ���� ó���� �����ϴ� �Ŵ����Դϴ�.
 *
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class FileManager : public IManager
{
	SINGLETON(FileManager);


public:
	/**
	 * @brief ���� �� ���丮 ���� ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ���� �� ���丮 ���� ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ���� Ȥ�� ���丮 ��ΰ� ��ȿ���� Ȯ���մϴ�.
	 *
	 * @param path ���� Ȥ�� ���丮 ����Դϴ�.
	 *
	 * @return ���� Ȥ�� ���丮�� ��ȿ�ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsValidPath(const std::string& path);


	/**
	 * @brief ���� Ȥ�� ���丮 ��ΰ� ��ȿ���� Ȯ���մϴ�.
	 *
	 * @param path ���� Ȥ�� ���丮 ����Դϴ�.
	 *
	 * @return ���� Ȥ�� ���丮�� ��ȿ�ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsValidPath(const std::wstring& path);


	/**
	 * @brief ��ΰ� ���� ������� Ȯ���մϴ�.
	 *
	 * @param path ���� ������� Ȯ���� ��ü ����Դϴ�.
	 *
	 * @return ��ΰ� ���� ��ζ�� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsFilePath(const std::string& path);


	/**
	 * @brief ��ΰ� ���� ������� Ȯ���մϴ�.
	 *
	 * @param path ���� ������� Ȯ���� ��ü ����Դϴ�.
	 *
	 * @return ��ΰ� ���� ��ζ�� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsFilePath(const std::wstring& path);


	/**
	 * @brief ��ΰ� ���丮 ������� Ȯ���մϴ�.
	 *
	 * @param path ���丮 ������� Ȯ���� ��ü ����Դϴ�.
	 *
	 * @return ��ΰ� ���丮 ��ζ�� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsDirectoryPath(const std::string& path);


	/**
	 * @brief ��ΰ� ���丮 ������� Ȯ���մϴ�.
	 *
	 * @param path ���丮 ������� Ȯ���� ��ü ����Դϴ�.
	 *
	 * @return ��ΰ� ���丮 ��ζ�� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsDirectoryPath(const std::wstring& path);


	/**
	 * @brief ��ο��� �����̳� ���丮 �̸��� ������ ��θ� ����ϴ�.
	 *
	 * @param path �����̳� ���丮 ����Դϴ�.
	 *
	 * @return �����̳� ���丮 �̸��� ������ ��θ� ��ȯ�մϴ�.
	 *
	 * @example
	 * - ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "D:\\AAA\\BBB\\" �Դϴ�.
	 * - ���丮 ��ΰ� "D:\\AAA\\BBB\\CCC"���, ��ȯ�ϴ� ���� "D:\\AAA\\BBB\\" �Դϴ�.
	 */
	std::string GetBasePath(const std::string& path);


	/**
	 * @brief ��ο��� �����̳� ���丮 �̸��� ������ ��θ� ����ϴ�.
	 *
	 * @param path �����̳� ���丮 ����Դϴ�.
	 *
	 * @return �����̳� ���丮 �̸��� ������ ��θ� ��ȯ�մϴ�.
	 *
	 * @example
	 * - ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "D:\\AAA\\BBB\\" �Դϴ�.
	 * - ���丮 ��ΰ� "D:\\AAA\\BBB\\CCC"���, ��ȯ�ϴ� ���� "D:\\AAA\\BBB\\" �Դϴ�.
	 */
	std::wstring GetBasePath(const std::wstring& path);


	/**
	 * @brief ��ü �����̳� ���丮 ��ο��� ���̽� ��θ� �����մϴ�.
	 *
	 * @param path ���̽� ��θ� ������ ��ü �����̳� ���丮 ����Դϴ�.
	 *
	 * @return ���̽� ��ΰ� ������ ���� ��θ� ��ȯ�մϴ�.
	 *
	 * @example
	 * - ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "CCC.a" �Դϴ�.
	 * - ���丮 ��ΰ� "D:\\AAA\\BBB\\CCC"���, ��ȯ�ϴ� ���� "CCC" �Դϴ�.
	 */
	std::string RemoveBasePath(const std::string& path);


	/**
	 * @brief ��ü �����̳� ���丮 ��ο��� ���̽� ��θ� �����մϴ�.
	 *
	 * @param path ���̽� ��θ� ������ ��ü �����̳� ���丮 ����Դϴ�.
	 *
	 * @return ���̽� ��ΰ� ������ ���� ��θ� ��ȯ�մϴ�.
	 *
	 * @example
	 * - ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "CCC.a" �Դϴ�.
	 * - ���丮 ��ΰ� "D:\\AAA\\BBB\\CCC"���, ��ȯ�ϴ� ���� "CCC" �Դϴ�.
	 */
	std::wstring RemoveBasePath(const std::wstring& path);


	/**
	 * @brief ��ü ���� ��ο��� ���� Ȯ���ڸ� ����ϴ�.
	 *
	 * @param path ���� Ȯ���ڸ� ���� ��ü ���� ����Դϴ�.
	 *
	 * @return ��ü ���� ����� ���� Ȯ���ڸ� ��ȯ�մϴ�.
	 *
	 * @example
	 * - ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "a" �Դϴ�.
	 * - ���� ��ΰ� "D:/AAA/BBB/CCC.a"���, ��ȯ�ϴ� ���� "a" �Դϴ�.
	 */
	std::string GetFileExtension(const std::string& path);


	/**
	 * @brief ��ü ���� ��ο��� ���� Ȯ���ڸ� ����ϴ�.
	 *
	 * @param path ���� Ȯ���ڸ� ���� ��ü ���� ����Դϴ�.
	 *
	 * @return ��ü ���� ����� ���� Ȯ���ڸ� ��ȯ�մϴ�.
	 *
	 * @example
	 * - ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "a" �Դϴ�.
	 * - ���� ��ΰ� "D:/AAA/BBB/CCC.a"���, ��ȯ�ϴ� ���� "a" �Դϴ�.
	 */
	std::wstring GetFileExtension(const std::wstring& path);


	/**
	 * @brief ��ü ���� ��ο��� Ȯ���ڸ� �����մϴ�.
	 *
	 * @param path ���� Ȯ���ڸ� ������ ��ü ���� ����Դϴ�.
	 *
	 * @return ���� Ȯ���ڰ� ������ ��ü ���� ��θ� ��ȯ�մϴ�.
	 *
	 * @example
	 * - ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "D:\\AAA\\BBB\\CCC" �Դϴ�.
	 * - ���� ��ΰ� "D:/AAA/BBB/CCC.a"���, ��ȯ�ϴ� ���� "D:/AAA/BBB/CCC" �Դϴ�.
	 */
	std::string RemoveFileExtension(const std::string& path);


	/**
	 * @brief ��ü ���� ��ο��� Ȯ���ڸ� �����մϴ�.
	 *
	 * @param path ���� Ȯ���ڸ� ������ ��ü ���� ����Դϴ�.
	 *
	 * @return ���� Ȯ���ڰ� ������ ��ü ���� ��θ� ��ȯ�մϴ�.
	 *
	 * @example
	 * - ���� ��ΰ� "D:\\AAA\\BBB\\CCC.a"���, ��ȯ�ϴ� ���� "D:\\AAA\\BBB\\CCC" �Դϴ�.
	 * - ���� ��ΰ� "D:/AAA/BBB/CCC.a"���, ��ȯ�ϴ� ���� "D:/AAA/BBB/CCC" �Դϴ�.
	 */
	std::wstring RemoveFileExtension(const std::wstring& path);


	/**
	 * @brief ���丮 ������ ���ϰ� ���丮 ����� ����ϴ�.
	 * 
	 * @param path ���ϰ� ���丮 ����� ���� ���� ���丮 ����Դϴ�.
	 * 
	 * @return ���� ��ο� ���丮 ��ΰ� ���Ե� ���͸� ��ȯ�մϴ�.
	 */
	std::vector<std::string> GetDirectoryContents(const std::string& path);

	
	/**
	 * @brief ���丮 ������ ���ϰ� ���丮 ����� ����ϴ�.
	 * 
	 * @param path ���ϰ� ���丮 ����� ���� ���� ���丮 ����Դϴ�.
	 * 
	 * @return ���� ��ο� ���丮 ��ΰ� ���Ե� ���͸� ��ȯ�մϴ�.
	 */
	std::vector<std::wstring> GetDirectoryContents(const std::wstring& path);


	/**
	 * @brief ���丮 ������ ���丮 ����� ����ϴ�.
	 * 
	 * @param path ���� ���丮 ����� ���� ���� ���丮 ����Դϴ�.
	 * 
	 * @return ���� ���丮 ��ΰ� ���Ե� ���͸� ��ȯ�մϴ�.
	 */
	std::vector<std::string> GetSubDirectories(const std::string& path);
	

	/**
	 * @brief ���丮 ������ ���丮 ����� ����ϴ�.
	 * 
	 * @param path ���� ���丮 ����� ���� ���� ���丮 ����Դϴ�.
	 * 
	 * @return ���� ���丮 ��ΰ� ���Ե� ���͸� ��ȯ�մϴ�.
	 */
	std::vector<std::wstring> GetSubDirectories(const std::wstring& path);


	/**
	 * @brief ���丮�� ���� ����� ����ϴ�.
	 * 
	 * @param path ���� ����� ���� ���丮 ����Դϴ�.
	 * 
	 * @return ���丮 ������ ���ϵ��� ���Ե� ���͸� ��ȯ�մϴ�.
	 */
	std::vector<std::string> GetFilesInDirectory(const std::string& path);


	/**
	 * @brief ���丮�� ���� ����� ����ϴ�.
	 *
	 * @param path ���� ����� ���� ���丮 ����Դϴ�.
	 *
	 * @return ���丮 ������ ���ϵ��� ���Ե� ���͸� ��ȯ�մϴ�.
	 */
	std::vector<std::wstring> GetFilesInDirectory(const std::wstring& path);


	/**
	 * @brief �ؽ�Ʈ ������ �о� ���ڿ��� ��ȯ�մϴ�.
	 * 
	 * @param path ������ ����Դϴ�.
	 * 
	 * @return �ؽ�Ʈ ���� ������ ����� ���ڿ��� ��ȯ�մϴ�.
	 */
	std::string ReadTextFileToString(const std::string& path);


	/**
	 * @brief �ؽ�Ʈ ������ �о� ���ڿ��� ��ȯ�մϴ�.
	 *
	 * @param path ������ ����Դϴ�.
	 *
	 * @return �ؽ�Ʈ ���� ������ ����� ���ڿ��� ��ȯ�մϴ�.
	 * 
	 * @see https://stackoverflow.com/questions/4775437/read-unicode-utf-8-file-into-wstring
	 */
	std::wstring ReadTextFileToString(const std::wstring& path);


	/**
	 * @brief Json ������ �о� Json ��ü�� ��ȯ�մϴ�.
	 * 
	 * @param path Json ������ ����Դϴ�.
	 * 
	 * @return Json ���� ��ü�� ��ȯ�մϴ�.
	 */
	Json::Value ReadJsonFile(const std::string& path);


private:
	/**
	 * @brief ���丮 ������ ���ϰ� ���丮 ����� ����ϴ�.
	 *
	 * @param path ���ϰ� ���丮 ����� ���� ���� ���丮 ����Դϴ�.
	 * @param bIsIncludeFile ��Ͽ� ������ �߰���ų���� �����Դϴ�. true�� �߰��ϰ�, �׷��� ������ �߰����� �ʽ��ϴ�.
	 * @param bIsIncludeDirectory ��Ͽ� ���丮�� �߰���ų���� �����Դϴ�. true�� �߰��ϰ� �׷��� ������ �߰����� �ʽ��ϴ�.
	 *
	 * @return ���� ��ο� ���丮 ��ΰ� ���Ե� ���͸� ��ȯ�մϴ�.
	 */
	std::vector<std::string> GetDirectoryContents(const std::string& path, bool bIsIncludeFile, bool bIsIncludeDirectory);


	/**
	 * @brief ���丮 ������ ���ϰ� ���丮 ����� ����ϴ�.
	 *
	 * @param path ���ϰ� ���丮 ����� ���� ���� ���丮 ����Դϴ�.
	 * @param bIsIncludeFile ��Ͽ� ������ �߰���ų���� �����Դϴ�. true�� �߰��ϰ�, �׷��� ������ �߰����� �ʽ��ϴ�.
	 * @param bIsIncludeDirectory ��Ͽ� ���丮�� �߰���ų���� �����Դϴ�. true�� �߰��ϰ� �׷��� ������ �߰����� �ʽ��ϴ�.
	 *
	 * @return ���� ��ο� ���丮 ��ΰ� ���Ե� ���͸� ��ȯ�մϴ�.
	 */
	std::vector<std::wstring> GetDirectoryContents(const std::wstring& path, bool bIsIncludeFile, bool bIsIncludeDirectory);


private:
	/**
	 * @brief ����� �̿��� ���ڿ��� ó���ϱ� ���� locale�Դϴ�.
	 */
	std::locale locale_;
};