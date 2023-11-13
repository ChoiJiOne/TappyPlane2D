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

	std::vector<Vector3f> positions;
	for (int32_t count = 0; count < 10000; ++count)
	{
		positions.push_back(Vector3f(
			MathUtils::GenerateRandomFloat(0.0f, 1000.0f),
			MathUtils::GenerateRandomFloat(0.0f, 800.0f),
			0.0f
		));
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

		Matrix4x4f ortho = MathUtils::CreateOrtho(0.0f, 1000.0f, 800.0f, 0.0f, -1.0f, 1.0f);
		shader->DrawLine2D(ortho, Vector2f(0.0f, 0.0f), Vector2f(300.0f, 150.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
		//shader->DrawPoints2D(ortho, positions, Vector4f(0.0f, 1.0f, 0.0f, 1.0f), 3.0f);
		
		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}