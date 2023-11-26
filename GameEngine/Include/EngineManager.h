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


	/**
	 * @brief ���ӿ��� ����� �ؽ�ó ���ҽ��� �ε��մϴ�.
	 * 
	 * @param properties ���� ������ ���Ե� Json ��ü�Դϴ�. 
	 */
	void LoadTextureResource(const Json::Value& properties);


	/**
	 * @brief ���ӿ��� ����� ��Ʈ ���ҽ��� �ε��մϴ�.
	 * 
	 * @param properties ���� ������ ���Ե� Json ��ü�Դϴ�. 
	 */
	void LoadFontResource(const Json::Value& properties);


private:
	/**
	 * @brief ������ �÷��̵Ǵ� �������Դϴ�.
	 */
	std::unique_ptr<Window> window_ = nullptr;
};