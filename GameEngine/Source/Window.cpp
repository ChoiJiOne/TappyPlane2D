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

void Window::GetPosition(int32_t& outX, int32_t& outY)
{
	glfwGetWindowPos(window_, &outX, &outY);
}

void Window::SetPosition(const int32_t& x, const int32_t& y)
{
	glfwSetWindowPos(window_, x, y);
}

void Window::GetSize(int32_t& outWidth, int32_t& outHeight)
{
	glfwGetWindowSize(window_, &outWidth, &outHeight);
}

void Window::SetSize(const int32_t& width, const int32_t& height)
{
	glfwSetWindowSize(window_, width, height);
}