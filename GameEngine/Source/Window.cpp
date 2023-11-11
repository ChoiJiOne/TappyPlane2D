#include "Window.h"

#include "AssertionMacro.h"

#include <glfw/glfw3.h>

Window::~Window()
{
	Destroy();
}

void Window::Create(const WindowCreationParam& creationParam)
{
	glfwWindowHint(GLFW_RESIZABLE, static_cast<int32_t>(creationParam.bCanResize));

	window_ = glfwCreateWindow(creationParam.width, creationParam.height, creationParam.title.c_str(), nullptr, nullptr);
	ASSERT((window_ != nullptr), "failed to create window...");

	glfwSetWindowPos(window_, creationParam.x, creationParam.y);
}

void Window::Destroy()
{
	if (window_ != nullptr)
	{
		glfwDestroyWindow(window_);
		window_ = nullptr;
	}
}