#pragma once

#include <string>


/**
 * @brief 커맨드 라인(명령행)에 대한 확장 기능을 제공합니다.
 * 
 * @note 
 * - 이 확장 기능은 "<key>=<value>" 기반으로 동작합니다.
 * - 이 확장 기능은 std::string 표준 문자열을 기반으로 동작합니다.
 */
namespace CommandLineArg
{
	/**
	 * @brief 커맨드 라인(명령행)을 파싱합니다.
	 * 
	 * @note 이 함수는 프로그램 시작 후 단 한 번만 호출할 수 있습니다.
	 * 
	 * @param argc 명령행 인수의 수입니다. 
	 * @param argv 명령행 인수입니다.
	 */
	void Parse(int32_t argc, char* argv[]);


	/**
	 * @brief 키 값에 대응하는 불리언 타입 값을 얻습니다.
	 */
	bool GetBoolValue(const std::string& key, bool& value);


	/**
	 * @brief 키 값에 대응하는 정수 타입 값을 얻습니다.
	 */
	bool GetIntValue(const std::string& key, int32_t& value);


	/**
	 * @brief 키 값에 대응하는 부동 소수점 수 타입 값을 얻습니다.
	 */
	bool GetFloatValue(const std::string& key, float& value);


	/**
	 * @brief 키 값에 대응하는 문자열 타입 값을 얻습니다.
	 */
	bool GetStringValue(const std::string& key, std::string& value);


	/**
	 * @brief 실행 파일 경로를 얻습니다.
	 * 
	 * @return 실행 파일 경로를 반환합니다.
	 */
	std::string GetExecutePath();
}