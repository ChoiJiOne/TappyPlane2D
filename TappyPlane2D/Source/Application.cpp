#include "EngineManager.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

int main(int argc, char* argv[])
{
	EngineManager::Get().Startup();
	
	GLFWwindow* window = EngineManager::Get().GetWindowPtr()->GetWindowPtr();

	std::string shaderPath;
	CommandLineArg::GetStringValue("glsl", shaderPath);

	Shader* shader = ResourceManager::Get().CreateResource<Shader>("Shader");
	shader->Initialize(shaderPath + "shader.vert", shaderPath + "shader.frag");

	std::vector<Vector3f> vertices = {
		Vector3f(-0.2f, -0.2f, +0.0f), // left  
		Vector3f(+0.2f, -0.2f, +0.0f), // right 
		Vector3f(+0.0f, +0.2f, +0.0f)  // top   
	};

	unsigned int VAO;
	unsigned int VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f) * static_cast<uint32_t>(vertices.size()), reinterpret_cast<const void*>(vertices.data()), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

		shader->Bind();
		{
			float time = static_cast<float>(glfwGetTime());
			Matrix4x4f m(
				+std::cos(time),  std::sin(time), 0.0f, 0.0f,
				-std::sin(time),  std::cos(time), 0.0f, 0.0f,
				           0.0f,           0.0f,  1.0f, 0.0f,
				           0.0f,           0.0f,  0.0f, 1.0f
			);

			uint32_t location = glGetUniformLocation(shader->programID_, "transform");
			glUniformMatrix4fv(location, 1, GL_FALSE, m.GetPtr());
			
			Vector4f color(0.0f, 1.0f, 1.0f, 1.0f);
			shader->SetVector4fParameter("color", color);

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, static_cast<uint32_t>(vertices.size()));
		}
		shader->Unbind();


		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}