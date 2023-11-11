#pragma once

#include <string>

#include "IManager.h"
#include "Macro.h"
#include "SingletonMacro.h"


/**
 * @brief ���� �� ���丮 Ȯ�� ����� �����մϴ�.
 */
namespace FileSystem
{
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
}