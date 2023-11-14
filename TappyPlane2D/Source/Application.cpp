#include "EngineManager.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

int main(int argc, char* argv[])
{
	EngineManager::Get().Startup();
	RenderManager::Get().SetDepthMode(false);
	
	GLFWwindow* window = EngineManager::Get().GetWindowPtr()->GetWindowPtr();

	std::string shaderPath;
	CommandLineArg::GetStringValue("glsl", shaderPath);

	GeometryShader2D* shader = ResourceManager::Get().CreateResource<GeometryShader2D>("Shader");
	shader->Initialize(shaderPath + "Geometry2D.vert", shaderPath + "Geometry2D.frag");

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
		shader->DrawGrid2D(ortho, 0.0f, 1000.0f, 10.0f, 0.0f, 800.0f, 10.0f, Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		shader->DrawCircle2D(ortho, Vector2f(500.0f, 400.0f), 100.0f, Vector4f(0.0f, 1.0f, 1.0f, 1.0f), 10);
		shader->DrawWireframeCircle2D(ortho, Vector2f(500.0f, 400.0f), 100.0f, Vector4f(0.0f, 0.0f, 1.0f, 1.0f));
		
		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}