#pragma once

#include <string>
#include <unordered_map>


/**
 * @brief Ŀ�ǵ� ���ο� ���� Ȯ�� ����� �����մϴ�.
 *
 * @note �� Ŭ������ ��� ������ �޼��� ��� ����(static) Ÿ���Դϴ�.
 */
class CommandLineUtils
{
public:
	/**
	 * @brief Ŀ�ǵ� ������ �Ľ��մϴ�.
	 *
	 * @param argc ����� �μ��� ���Դϴ�.
	 * @param argv ����� �μ��Դϴ�.
	 */
	static void Parse(int32_t argc, char* argv[]);


	/**
	 * @brief Ŀ�ǵ� ���� ������ �ɼ��� ��ȿ���� Ȯ���մϴ�.
	 *
	 * @note ����� ���� �ɼ��� "-<option>" �����Դϴ�.
	 *
	 * @param option ��ȿ���� Ȯ���� �ɼ��Դϴ�.
	 *
	 * @return �ɼ��� ��ȿ�ϴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool IsValidOption(const std::string& option);


	/**
	 * @brief Ŀ�ǵ� ���� ������ Ű ���� ��ȿ���� Ȯ���մϴ�.
	 *
	 * @param key ��ȿ���� Ȯ���� Ű ���Դϴ�.
	 *
	 * @return Ű ���� ��ȿ�ϴٸ�, �� Ű ���� �����ϴ� ���� �����ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool IsValidKey(const std::string& key);


	/**
	 * @brief Ŀ�ǵ� ���� ������ Ű ���� �����ϴ� ���� ����ϴ�.
	 *
	 * @param key Ŀ�ǵ� ���� ���� ��ȿ�� Ű ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ���� ��ȯ�մϴ�. �̶� Ű ���� ��ȿ���� ������ �� ���ڿ��� ��ȯ�մϴ�.
	 */
	static std::string GetValue(const std::string& key);


	/**
	 * @brief ���� ���� ��θ� ����ϴ�.
	 *
	 * @return ���� ���� ��θ� ��ȯ�մϴ�.
	 */
	static std::string GetExecutePath() { return executePath_; }


private:
	/**
	 * @brief ����� ������ �����Դϴ�.
	 *
	 * @note
	 * - NONE�� �������� �ʴ� �����Դϴ�.
	 * - OPTION�� ����� ���ڰ� "-<option>" �����Դϴ�.
	 * - KEYVALUE�� ����� ���ڰ� "<key>=<value>" �����Դϴ�.
	 */
	enum class EArgumentType
	{
		NONE = 0x00,
		OPTION = 0x01,
		KEYVALUE = 0x02,
	};


private:
	/**
	 * @brief Ŀ�ǵ� ���� �� ���ڰ� ���� ǥ���� ���ϰ� ��ġ�ϴ��� Ȯ���մϴ�.
	 *
	 * @param arg ������ �˻��� Ŀ�ǵ� ���� �� �����Դϴ�.
	 * @param pattern ���� ��ġ Ȯ���� ���� ���� ǥ���� �����Դϴ�.
	 *
	 * @return Ŀ�ǵ� ���� �� ���ڰ� ���ϰ� ��ġ�ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool CheckArgPatternMatch(const std::string& arg, const std::string& pattern);


	/**
	 * @brief Ŀ�ǵ� ���� �� ������ ������ ����ϴ�.
	 *
	 * @param arg ������ ���� Ŀ�ǵ� ���� �� �����Դϴ�.
	 *
	 * @return Ŀ�ǵ� ���� �� ������ ���� �������� ��ȯ�մϴ�.
	 */
	static EArgumentType GetArgType(const std::string& arg);


	/**
	 * @brief ����� ���ڸ� �Ľ��մϴ�.
	 *
	 * @note ����� ���ڰ� ��ȿ���� ������ �ƹ� ���۵� �������� �ʽ��ϴ�.
	 *
	 * @param arg �Ľ��� ����� �����Դϴ�.
	 */
	static void ParseArg(const std::string& arg);


private:
	/**
	 * @brief ���� ���� ����Դϴ�.
	 */
	static std::string executePath_;


	/**
	 * @brief Ŀ�ǵ� ���� ���� �ɼǵ��Դϴ�.
	 *
	 * @note �ɼ��� Ŀ�ǵ� ���� ���� "-<optiont>"�� ���� �����Դϴ�.
	 */
	static std::vector<std::string> options_;


	/**
	 * @brief Ŀ�ǵ� ���� ���� Ű-�� ���Դϴ�.
	 *
	 * @note Ű-�� ���� Ŀ�ǵ� ���� ���� "<key>=<value>"�� ���� �����Դϴ�.
	 */
	static std::unordered_map<std::string, std::string> keyValues_;


	/**
	 * @brief ����� ������ ���� ǥ���� �����Դϴ�.
	 */
	static std::unordered_map<EArgumentType, std::string> argPatterns_;
};