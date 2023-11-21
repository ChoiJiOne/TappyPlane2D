#include "EngineManager.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stb_image.h>

#include "GLAssertionMacro.h"

int main(int argc, char* argv[])
{
	EngineManager::Get().Startup();

	RenderManager::Get().SetAlphaBlend(true);
	RenderManager::Get().SetDepthMode(false);

	GLFWwindow* window = EngineManager::Get().GetWindowPtr()->GetWindowPtr();

	std::string resourcePath;
	CommandLineArg::GetStringValue("resource", resourcePath);
	
	Texture2D* texture = ResourceManager::Get().CreateResource<Texture2D>("Test");
	texture->Initialize(resourcePath + "Test\\awesomeface_dxt1.dds");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		RenderManager::Get().DrawTexture2D(texture);

		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}