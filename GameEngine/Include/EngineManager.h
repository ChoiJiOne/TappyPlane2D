#pragma once

#include <memory>

#include "AssertionMacro.h"
#include "CommandLineArg.h"
#include "FileManager.h"
#include "IManager.h"
#include "Macro.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "SingletonMacro.h"
#include "StringUtils.h"
#include "Window.h"


/**
 * @brief ��ü ������ �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class EngineManager : public IManager
{
	SINGLETON(EngineManager);


public:
	/**
	 * @brief ���� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ���� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ������ �����ϴ� �����츦 ����ϴ�.
	 * 
	 * @return ������ �����ϴ� �������� �����͸� ��ȯ�մϴ�.
	 */
	Window* GetWindowPtr() { return window_.get(); }


private:
	/**
	 * @brief ������ �����ϴ� �����츦 �����մϴ�.
	 * 
	 * @param properties ���� ������ ���Ե� Json ��ü�Դϴ�. 
	 */
	void CreateEngineWindow(const Json::Value& properties);


	/**
	 * @brief ���� �Ŵ����� �ʱ�ȭ�մϴ�.
	 * 
	 * @param properties ���� ������ ���Ե� Json ��ü�Դϴ�. 
	 */
	void StartupRenderManager(const Json::Value& properties);
	

private:
	/**
	 * @brief ������ �÷��̵Ǵ� �������Դϴ�.
	 */
	std::unique_ptr<Window> window_ = nullptr;
};