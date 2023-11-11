#pragma once

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
};
