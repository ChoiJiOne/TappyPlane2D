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

	std::string shaderPath;
	CommandLineArg::GetStringValue("glsl", shaderPath);

	GeometryShader2D* geometryShader = ResourceManager::Get().CreateResource<GeometryShader2D>("GeometryShader2D");
	geometryShader->Initialize(shaderPath + "Geometry2D.vert", shaderPath + "Geometry2D.frag");

	TextureShader2D* textureShader = ResourceManager::Get().CreateResource<TextureShader2D>("TextureShader2D");
	textureShader->Initialize(shaderPath + "Texture2D.vert", shaderPath + "Texture2D.frag");

	std::string resourcePath;
	CommandLineArg::GetStringValue("resource", resourcePath);

	Texture2D* texture2d = ResourceManager::Get().CreateResource<Texture2D>("Texture");
	texture2d->Initialize(resourcePath + "Texture\\background.png");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

		Matrix4x4f ortho = MathUtils::CreateOrtho(0.0f, 1000.0f, 800.0f, 0.0f, -1.0f, 1.0f);
		float time = static_cast<float>(glfwGetTime());
		float value = time - static_cast<float>(static_cast<int32_t>(time));
		textureShader->DrawVerticalScrollTexture2D(texture2d, value);
		//textureShader->DrawTexture2D(ortho, texture2d, Vector2f(500.0f, 400.0f), 100.0f, 100.0f, 0.0f, 1.0f);
		//textureShader->DrawTexture2D(texture2d);
		//textureShader->DrawHorizonScrollTexture2D(texture2d, static_cast<float>(glfwGetTime()) / 10.0f);
		//textureShader->DrawVerticalScrollTexture2D(texture2d, static_cast<float>(glfwGetTime()) / 10.0f);

		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}