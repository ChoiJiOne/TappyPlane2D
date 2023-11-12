#include "RenderManager.h"

#include "EngineManager.h"
#include "AssertionMacro.h"
#include "Window.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

void RenderManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup render manager...");

	bIsStartup_ = true;
}

void RenderManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	bIsStartup_ = false;
}

void RenderManager::PreStartup(Window* window, int32_t major, int32_t minor)
{
	ASSERT(window != nullptr, "invalid window pointer...");
	window_ = window;

	ASSERT((major == 4), "major version of OpenGL must be 4...");
	ASSERT((minor >= 3 && minor <= 6), "minor version of OpenGL must be between 3 and 6...");
	
	major_ = major;
	minor_ = minor;
}