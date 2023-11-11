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
}