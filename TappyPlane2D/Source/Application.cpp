#include "EngineManager.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stb_image.h>

#include "GLAssertionMacro.h"

int main(int argc, char* argv[])
{
	EngineManager::Get().Startup();
	RenderManager::Get().SetDepthMode(false);
	
	GLFWwindow* window = EngineManager::Get().GetWindowPtr()->GetWindowPtr();

	std::string resourcePath;
	CommandLineArg::GetStringValue("resource", resourcePath);

	Texture2D* background = ResourceManager::Get().CreateResource<Texture2D>("Background");
	background->Initialize(resourcePath + "Texture\\background.png");

	Texture2D* ground = ResourceManager::Get().CreateResource<Texture2D>("Ground");
	ground->Initialize(resourcePath + "Texture\\groundGrass.png");

	TTFont* font = ResourceManager::Get().CreateResource<TTFont>("Font");
	font->Initialize(resourcePath + "Font\\kenvector_future.ttf", 32, 127, 64.0f);
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		float time = static_cast<float>(glfwGetTime() / 10.0f);
		float value = time - static_cast<float>(static_cast<int32_t>(time));

		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

		RenderManager::Get().DrawLine2D(Vector2f(0.0f, 0.0f), Vector2f(1000.0f, 800.0f), Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		//RenderManager::Get().DrawHorizonScrollTexture2D(background, static_cast<float>(value));
		//RenderManager::Get().DrawHorizonScrollTexture2D(ground, Vector2f(500.0f, 770.0f), 1000.0f, 60.0f, value);
		//RenderManager::Get().DrawText2D(font, L"Hello, World!", Vector2f(500.0f, 400.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
		//RenderManager::Get().DrawGrid2D(0.0f, 1000.0f, 10.0f, 0.0f, 800.0f, 10.0f, Vector4f(0.0f, 0.0f, 1.0f, 1.0f));

		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}