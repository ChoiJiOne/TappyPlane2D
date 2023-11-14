#include "EngineManager.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stb_image.h>

int main(int argc, char* argv[])
{
	EngineManager::Get().Startup();
	RenderManager::Get().SetDepthMode(false);
	
	GLFWwindow* window = EngineManager::Get().GetWindowPtr()->GetWindowPtr();

	std::string shaderPath;
	CommandLineArg::GetStringValue("glsl", shaderPath);

	//GeometryShader2D* shader = ResourceManager::Get().CreateResource<GeometryShader2D>("Shader");
	//shader->Initialize(shaderPath + "Geometry2D.vert", shaderPath + "Geometry2D.frag");

	Shader* shader = ResourceManager::Get().CreateResource<Shader>("Shader");
	shader->Initialize(shaderPath + "Texture2D.vert", shaderPath + "Texture2D.frag");
	
	std::vector<float> vertices = {
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};

	std::vector<uint32_t> indices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * static_cast<uint32_t>(vertices.size()), reinterpret_cast<const void*>(vertices.data()), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * static_cast<uint32_t>(indices.size()), reinterpret_cast<const void*>(indices.data()), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	std::string resourcePath;
	CommandLineArg::GetStringValue("resource", resourcePath);

	int32_t width;
	int32_t height;
	int32_t nrChannels;

	unsigned char* data = stbi_load((resourcePath + "awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	data = nullptr;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(1.0f, 0.0f, 0.0f, 1.0f);

		//Matrix4x4f ortho = MathUtils::CreateOrtho(0.0f, 1000.0f, 800.0f, 0.0f, -1.0f, 1.0f);

		shader->Bind();
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);

			shader->SetMatrix4x4fParameter("transform", Matrix4x4f::GetIdentity());
			shader->SetMatrix4x4fParameter("ortho", Matrix4x4f::GetIdentity());
			shader->SetBoolParameter("bReverseTexCoord", true);

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, static_cast<uint32_t>(indices.size()), GL_UNSIGNED_INT, 0);
		}
		shader->Unbind();

		RenderManager::Get().EndFrame();
	}

	glDeleteTextures(1, &texture);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	EngineManager::Get().Shutdown();
	return 0;
}