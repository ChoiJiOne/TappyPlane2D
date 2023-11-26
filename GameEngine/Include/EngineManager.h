#pragma once

#include <memory>

#include "AABB.h"
#include "AssertionMacro.h"
#include "Circle.h"
#include "CommandLineArg.h"
#include "FileManager.h"
#include "GameTimer.h"
#include "IManager.h"
#include "InputManager.h"
#include "LineSegment.h"
#include "Macro.h"
#include "MathUtils.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "SingletonMacro.h"
#include "StringUtils.h"
#include "Texture2D.h"
#include "TTFont.h"
#include "Window.h"


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


	/**
	 * @brief 엔진이 관리하는 윈도우를 얻습니다.
	 * 
	 * @return 엔진이 관리하는 윈도우의 포인터를 반환합니다.
	 */
	Window* GetWindowPtr() { return window_.get(); }


private:
	/**
	 * @brief 엔진이 관리하는 윈도우를 생성합니다.
	 * 
	 * @param properties 게임 설정이 포함된 Json 객체입니다. 
	 */
	void CreateEngineWindow(const Json::Value& properties);


	/**
	 * @brief 렌더 매니저를 초기화합니다.
	 * 
	 * @param properties 게임 설정이 포함된 Json 객체입니다. 
	 */
	void StartupRenderManager(const Json::Value& properties);


	/**
	 * @brief 게임에서 사용할 텍스처 리소스를 로딩합니다.
	 * 
	 * @param properties 게임 설정이 포함된 Json 객체입니다. 
	 */
	void LoadTextureResource(const Json::Value& properties);


	/**
	 * @brief 게임에서 사용할 폰트 리소스를 로딩합니다.
	 * 
	 * @param properties 게임 설정이 포함된 Json 객체입니다. 
	 */
	void LoadFontResource(const Json::Value& properties);


private:
	/**
	 * @brief 게임이 플레이되는 윈도우입니다.
	 */
	std::unique_ptr<Window> window_ = nullptr;
};