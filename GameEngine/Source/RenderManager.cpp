#include "RenderManager.h"

#include "EngineManager.h"
#include "AssertionMacro.h"
#include "Window.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

void RenderManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup render manager...");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* windowPtr = window_->GetWindowPtr();
	glfwMakeContextCurrent(windowPtr);

	ASSERT(gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)), "failed to initialize OpenGL function loader...");
	
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

void RenderManager::BeginFrame(float red, float green, float blue, float alpha, float depth, uint8_t stencil)
{
	glClearColor(red, green, blue, alpha);
	glClearDepth(depth);
	glClearStencil(stencil);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void RenderManager::EndFrame()
{
	glfwSwapBuffers(window_->GetWindowPtr());
}

void RenderManager::SetVsyncMode(bool bIsEnable)
{
	glfwSwapInterval(static_cast<int32_t>(bIsEnable));
}

void RenderManager::SetDepthMode(bool bIsEnable)
{
	if (bIsEnable)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
}

void RenderManager::SetAlphaBlend(bool bIsEnable)
{
	if (bIsEnable)
	{
		glEnable(GL_BLEND);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	}
	else
	{
		glDisable(GL_BLEND);
	}
}

void RenderManager::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
	glViewport(x, y, width, height);
}