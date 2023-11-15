#include "RenderManager.h"

#include "EngineManager.h"
#include "AssertionMacro.h"
#include "GLAssertionMacro.h"
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
	
	GL_ASSERT(glEnable(GL_PROGRAM_POINT_SIZE), "failed to enable shader program point size...");

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

	GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT), "failed to clear bitplane area of the window...");
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
		GL_ASSERT(glEnable(GL_DEPTH_TEST), "failed to enable depth test...");
	}
	else
	{
		GL_ASSERT(glDisable(GL_DEPTH_TEST), "failed to disable depth test...");
	}
}

void RenderManager::SetAlphaBlend(bool bIsEnable)
{
	if (bIsEnable)
	{
		GL_ASSERT(glEnable(GL_BLEND), "failed to enable alpha blend...");
		GL_ASSERT(glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO), "failed to Separate blend func...");
	}
	else
	{
		GL_ASSERT(glDisable(GL_BLEND), "failedto disable alpha blend...");
	}
}

void RenderManager::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
	GL_ASSERT(glViewport(x, y, width, height), "invalid viewport parameter : x=%d, y=%d, w=%d, h=%d", x, y, width, height);
}