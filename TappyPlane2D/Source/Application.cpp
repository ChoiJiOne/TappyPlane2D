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
		Vector3f(10.0f, 10.0f, +0.0f), // left  
		Vector3f(300.0f, 200.0f, +0.0f), // right 
		Vector3f(500.0f, 50.0f, +0.0f)  // top   
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

	RenderManager::Get().SetDepthMode(false);
	
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
			//float time = static_cast<float>(glfwGetTime());
			//Matrix4x4f m(
			//	+std::cos(time), std::sin(time), 0.0f, 0.0f,
			//	-std::sin(time), std::cos(time), 0.0f, 0.0f,
			//	0.0f, 0.0f, 1.0f, 0.0f,
			//	0.0f, 0.0f, 0.0f, 1.0f
			//);
			//shader->SetMatrix4x4fParameter("transform", m);

			float left = 0.0f;
			float right = 1000.0f;
			float bottom = 800.0f;
			float top = 0.0f;
			float zNear = -0.1f;
			float zFar = 1.0f;

			Matrix4x4f m( 
				           2.0f / (right - left),                             0.0f,                             0.0f, 0.0f,
				                            0.0f,            2.0f / (top - bottom),                             0.0f, 0.0f,
			            	                0.0f,                             0.0f,           -2.0f / (zFar - zNear), 0.0f,
				-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(zFar + zNear) / (zFar - zNear), 1.0f
			);
			shader->SetMatrix4x4fParameter("transform", m);

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