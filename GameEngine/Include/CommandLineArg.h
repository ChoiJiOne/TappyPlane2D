#pragma once

#include <string>


/**
 * @brief Ŀ�ǵ� ����(�����)�� ���� Ȯ�� ����� �����մϴ�.
 * 
 * @note 
 * - �� Ȯ�� ����� "<key>=<value>" ������� �����մϴ�.
 * - �� Ȯ�� ����� std::string ǥ�� ���ڿ��� ������� �����մϴ�.
 */
namespace CommandLineArg
{
	/**
	 * @brief Ŀ�ǵ� ����(�����)�� �Ľ��մϴ�.
	 * 
	 * @note 
	 * - �� �Լ��� ���α׷� ���� �� �� �� ���� ȣ���� �� �ֽ��ϴ�.
	 * - Parse(const char* commandline)�� ������ ȣ���� ���� �ִٸ� �� �Լ��� ����� �� �����ϴ�.
	 * 
	 * @param argc ����� �μ��� ���Դϴ�. 
	 * @param argv ����� �μ��Դϴ�.
	 */
	void Parse(int32_t argc, char* argv[]);


	/**
	 * @brief Ŀ�ǵ� ����(�����)�� �Ľ��մϴ�.
	 * 
	 * @note 
	 * - �� �Լ��� ���α׷� ���� �� �� �� ���� ȣ���� �� �ֽ��ϴ�.
	 * - Parse(int32_t argc, char* argv[])�� ������ ȣ���� ���� �ִٸ� �� �Լ��� ����� �� �����ϴ�.
	 * 
	 * @param commandline ��ü Ŀ�ǵ� ����(�����)�Դϴ�.
	 */
	void Parse(const char* commandline);


	/**
	 * @brief Ű ���� �����ϴ� �Ҹ��� Ÿ�� ���� ����ϴ�.
	 */
	bool GetBoolValue(const std::string& key, bool& value);


	/**
	 * @brief Ű ���� �����ϴ� ���� Ÿ�� ���� ����ϴ�.
	 */
	bool GetIntValue(const std::string& key, int32_t& value);


	/**
	 * @brief Ű ���� �����ϴ� �ε� �Ҽ��� �� Ÿ�� ���� ����ϴ�.
	 */
	bool GetFloatValue(const std::string& key, float& value);


	/**
	 * @brief Ű ���� �����ϴ� ���ڿ� Ÿ�� ���� ����ϴ�.
	 */
	bool GetStringValue(const std::string& key, std::string& value);


	/**
	 * @brief ���� ���� ��θ� ����ϴ�.
	 * 
	 * @return ���� ���� ��θ� ��ȯ�մϴ�.
	 */
	std::string GetExecutePath();
}