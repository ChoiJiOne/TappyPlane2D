#pragma once

#include "IManager.h"
#include "Macro.h"
#include "SingletonMacro.h"


/**
 * @brief 전체 엔진을 관리하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class EngineManager : public IManager
{
	SINGLETON(EngineManager);


public:
	/**
	 * @brief 엔진 매니저의 사용을 시작합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 엔진 매니저의 사용을 종료합니다.
	 */
	virtual void Shutdown() override;
};