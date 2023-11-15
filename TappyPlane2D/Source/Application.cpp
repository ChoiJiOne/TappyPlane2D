#include "EngineManager.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stb_image.h>
#include <iostream>

#include "GLAssertionMacro.h"

uint32_t LoadTextureNoCompression(const std::string& filename)
{
	std::string resourcePath;
	CommandLineArg::GetStringValue("resource", resourcePath);
	resourcePath += filename;

	int32_t width;
	int32_t height;
	int32_t nrChannels;
	unsigned char* data = stbi_load(resourcePath.c_str(), &width, &height, &nrChannels, 0);

	uint32_t texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	data = nullptr;

	return texture;
}

struct ASTCHeader
{
	uint8_t magic[4];
	uint8_t blockdim_x;
	uint8_t blockdim_y;
	uint8_t blockdim_z;
	uint8_t xsize[3];
	uint8_t ysize[3];
	uint8_t zsize[3];
};

uint32_t LoadTextureCompression(const std::string& filename)
{
	std::string resourcePath;
	CommandLineArg::GetStringValue("resource", resourcePath);
	resourcePath += filename;

	unsigned int n_bytes_to_read = 0;
	int xblocks = 0;
	int yblocks = 0;
	int zblocks = 0;

	int xsize = 0;
	int ysize = 0;
	int zsize = 0;

	std::vector<uint8_t> buffer = FileManager::Get().ReadFileToBuffer(resourcePath);
	ASTCHeader* astc_data_ptr = (ASTCHeader*)(buffer.data());

	xsize = astc_data_ptr->xsize[0] + (astc_data_ptr->xsize[1] << 8) + (astc_data_ptr->xsize[2] << 16);
	ysize = astc_data_ptr->ysize[0] + (astc_data_ptr->ysize[1] << 8) + (astc_data_ptr->ysize[2] << 16);
	zsize = astc_data_ptr->zsize[0] + (astc_data_ptr->zsize[1] << 8) + (astc_data_ptr->zsize[2] << 16);

	xblocks = (xsize + astc_data_ptr->blockdim_x - 1) / astc_data_ptr->blockdim_x;
	yblocks = (ysize + astc_data_ptr->blockdim_y - 1) / astc_data_ptr->blockdim_y;
	zblocks = (zsize + astc_data_ptr->blockdim_z - 1) / astc_data_ptr->blockdim_z;

	n_bytes_to_read = xblocks * yblocks * zblocks << 4;

	uint32_t texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	GL_ASSERT(glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_ASTC_4x4_KHR, xsize, ysize, 0, n_bytes_to_read, (const GLvoid*)&astc_data_ptr[1])
	, "failed to compress texture...");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}

int main(int argc, char* argv[])
{
	EngineManager::Get().Startup();
	RenderManager::Get().SetDepthMode(false);
	
	GLFWwindow* window = EngineManager::Get().GetWindowPtr()->GetWindowPtr();

	std::string shaderPath;
	CommandLineArg::GetStringValue("glsl", shaderPath);

	GeometryShader2D* shader2d = ResourceManager::Get().CreateResource<GeometryShader2D>("Shader2D");
	shader2d->Initialize(shaderPath + "Geometry2D.vert", shaderPath + "Geometry2D.frag");

	Shader* shader = ResourceManager::Get().CreateResource<Shader>("Shader");
	shader->Initialize(shaderPath + "Texture2D.vert", shaderPath + "Texture2D.frag");

	std::string resourcePath;
	CommandLineArg::GetStringValue("resource", resourcePath);

	Texture2D* texture2d = ResourceManager::Get().CreateResource<Texture2D>("Texture");
	texture2d->Initialize(resourcePath + "awesomeface.png");
	
	std::vector<float> vertices = {
		// positions          // texture coords
		 1.0f,  1.0f, 0.0f,   1.0f, 1.0f, // top right
		 1.0f, -1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f  // top left 
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
			texture2d->Active(0);

			shader->SetMatrix4x4fParameter("transform", Matrix4x4f::GetIdentity());
			shader->SetMatrix4x4fParameter("ortho", Matrix4x4f::GetIdentity());
			shader->SetBoolParameter("bReverseTexCoord", true);

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, static_cast<uint32_t>(indices.size()), GL_UNSIGNED_INT, 0);
		}
		shader->Unbind();

		RenderManager::Get().EndFrame();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	EngineManager::Get().Shutdown();
	return 0;
}