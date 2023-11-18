#include "EngineManager.h"

#include <glfw/glfw3.h>

void EngineManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup engine manager...");
	ASSERT(glfwInit() != 0, "failed to initialzie GLFW...");

	CommandLineArg::Parse(GetCommandLineA());

	FileManager::Get().Startup();

	std::string propertiesPath;
	ASSERT(CommandLineArg::GetStringValue("properties", propertiesPath), "failed to load properties json file...");

	Json::Value properties = FileManager::Get().ReadJsonFile(propertiesPath);

	CreateEngineWindow(properties);
	StartupRenderManager(properties);

	ResourceManager::Get().Startup();
	RenderManager::Get().PostSetup();
	
	bIsStartup_ = true;
}

void EngineManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	ResourceManager::Get().Shutdown();
	RenderManager::Get().Shutdown();
	FileManager::Get().Shutdown();

	window_->Destroy();
	window_.reset();

	glfwTerminate();
	bIsStartup_ = false;
}

void EngineManager::CreateEngineWindow(const Json::Value& properties)
{
	ASSERT((properties["title"].isString() && !properties["title"].isNull()), "invalid properties json : %s...", "title");
	ASSERT((properties["x"].isInt() && !properties["x"].isNull()), "invalid properties json : %s...", "x");
	ASSERT((properties["y"].isInt() && !properties["y"].isNull()), "invalid properties json : %s...", "y");
	ASSERT((properties["width"].isInt() && !properties["width"].isNull()), "invalid properties json : %s...", "width");
	ASSERT((properties["height"].isInt() && !properties["height"].isNull()), "invalid properties json : %s...", "height");
	ASSERT((properties["resize"].isBool() && !properties["resize"].isNull()), "invalid properties json : %s...", "resize");

	Window::WindowCreationParam windowParam {
		properties["title"].asCString(),
		static_cast<int32_t>(properties["x"].asInt()),
		static_cast<int32_t>(properties["y"].asInt()),
		static_cast<int32_t>(properties["width"].asInt()),
		static_cast<int32_t>(properties["height"].asInt()),
		properties["resize"].asBool()
	};

	window_ = std::make_unique<Window>();
	window_->Create(windowParam);
}

void EngineManager::StartupRenderManager(const Json::Value& properties)
{
	ASSERT((properties["opengl"].isString() && !properties["opengl"].isNull()), "invalid properties json : %s...", "opengl");
	ASSERT((properties["vsync"].isBool() && !properties["vsync"].isNull()), "invalid properties json : %s...", "vsync");

	std::string glVersion = std::string(properties["opengl"].asCString());
	std::vector<std::string> tokens = StringUtils::Split(glVersion, ".");

	int32_t major = 0;
	ASSERT(StringUtils::ToInt(tokens.front(), major), "OpenGL major is not integer : %s", tokens.front().c_str());

	int32_t minor = 0;
	ASSERT(StringUtils::ToInt(tokens.back(), minor), "OpenGL minor is not integer : %s", tokens.back().c_str());

	RenderManager& renderManager = RenderManager::Get();

	renderManager.PreStartup(window_.get(), major, minor);
	renderManager.Startup();

	bool bIsEnableVsync = properties["vsync"].asBool();
	renderManager.SetVsyncMode(bIsEnableVsync);
	renderManager.SetAlphaBlend(true);
}