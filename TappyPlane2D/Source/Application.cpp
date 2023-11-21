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

	std::array<std::string, 14> astcTextures = {
		"awesomeface4x4",
		"awesomeface5x4",
		"awesomeface5x5",
		"awesomeface6x5",
		"awesomeface6x6",
		"awesomeface8x5",
		"awesomeface8x6",
		"awesomeface8x8",
		"awesomeface10x5",
		"awesomeface10x6",
		"awesomeface10x8",
		"awesomeface10x10",
		"awesomeface12x10",
		"awesomeface12x12",
	};

	for (const auto& astcTexture : astcTextures)
	{
		Texture2D* texture = ResourceManager::Get().CreateResource<Texture2D>(astcTexture);
		texture->Initialize(StringUtils::PrintF("%sTest\\%s.astc", resourcePath.c_str(), astcTexture.c_str()));
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

		float x = 100.0f;
		float y = 100.0f;
		float width = 200.0f;
		float height = 200.0f;

		for (std::size_t index = 0; index < astcTextures.size(); ++index)
		{
			Texture2D* texture = ResourceManager::Get().GetResource<Texture2D>(astcTextures[index]);
			RenderManager::Get().DrawTexture2D(texture, Vector2f(x, y), width, height, 0.0f);

			if (index % 4 == 3)
			{
				x = 100.0f;
				y += height;
			}
			else
			{
				x += width;
			}
		}
		
		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}