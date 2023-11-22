#include "InputManager.h"

#include "AssertionMacro.h"
#include "Window.h"

#include <glfw/glfw3.h>

void InputManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup render manager...");

	bIsStartup_ = true;
}

void InputManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	bIsStartup_ = false;
}

void InputManager::PreStartup(Window* window)
{
	ASSERT(window != nullptr, "invalid window pointer...");
	window_ = window;
}