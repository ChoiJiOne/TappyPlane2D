#include "TextureShader2D.h"

#include "GLAssertionMacro.h"
#include "MathUtils.h"
#include "Texture2D.h"

#include <glad/glad.h>

TextureShader2D::~TextureShader2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void TextureShader2D::Initialize(const std::string& vsPath, const std::string& fsPath, bool bCheckValid)
{
	ASSERT(!bIsInitialized_, "already initialize texture shader 2d resource...");

	Shader::Initialize(vsPath, fsPath, bCheckValid);

	GL_ASSERT(glGenVertexArrays(1, &vertexArrayObject_), "failed to generate 2d texture vertex array...");
	GL_ASSERT(glGenBuffers(1, &vertexBufferObject_), "failed to generate 2d texture vertex buffer...");

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind 2d texture vertex array...");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_), "failed to bind 2d texture vertex buffer...");
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, VertexPositionTexture::GetStride() * vertices_.size(), reinterpret_cast<const void*>(vertices_.data()), GL_DYNAMIC_DRAW),
		"failed to create a new data store for a 2d texture buffer object...");

	GL_ASSERT(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexPositionTexture::GetStride(), (void*)(offsetof(VertexPositionTexture, position_))),
		"failed to specify the location and data format of the array of generic vertex attributes at index...");
	GL_ASSERT(glEnableVertexAttribArray(0), "failed to enable vertex attrib array...");

	GL_ASSERT(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VertexPositionTexture::GetStride(), (void*)(offsetof(VertexPositionTexture, st_))),
		"failed to specify the location and data format of the array of generic vertex attributes at index...");
	GL_ASSERT(glEnableVertexAttribArray(1), "failed to enable vertex attrib array...");

	GL_ASSERT(glBindVertexArray(0), "failed to unbind 2d texture vertex array...");
}

void TextureShader2D::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	Shader::Release();

	GL_ASSERT(glDeleteBuffers(1, &vertexBufferObject_), "failed to delete 2d texture vertex buffer...");
	GL_ASSERT(glDeleteVertexArrays(1, &vertexArrayObject_), "failed to delete 2d texture vertex array object...");
}

void TextureShader2D::DrawTexture2D(const Matrix4x4f& ortho, Texture2D* texture, const Vector2f& center, float width, float height, float rotate, float transparent)
{
	vertices_[0] = VertexPositionTexture(Vector3f(center.x - width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), Vector2f(0.0f, 0.0f));
	vertices_[1] = VertexPositionTexture(Vector3f(center.x - width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), Vector2f(0.0f, 1.0f));
	vertices_[2] = VertexPositionTexture(Vector3f(center.x + width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), Vector2f(1.0f, 0.0f));

	vertices_[3] = VertexPositionTexture(Vector3f(center.x + width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), Vector2f(1.0f, 0.0f));
	vertices_[4] = VertexPositionTexture(Vector3f(center.x - width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), Vector2f(0.0f, 1.0f));
	vertices_[5] = VertexPositionTexture(Vector3f(center.x + width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), Vector2f(1.0f, 1.0f));

	UpdateVertexBuffer();

	Matrix4x4f transform = MathUtils::CreateTranslation(Vector3f(-center.x, -center.y, 0.0f))
		* MathUtils::CreateRotateZ(rotate)
		* MathUtils::CreateTranslation(Vector3f(+center.x, +center.y, 0.0f));

	Shader::Bind();

	texture->Active(0);

	Shader::SetMatrix4x4fParameter("transform", transform);
	Shader::SetMatrix4x4fParameter("ortho", ortho);
	Shader::SetBoolParameter("bReverseTexCoord", false);
	Shader::SetFloatParameter("transparent", transparent);

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind 2d geometry vertex array...");
	GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, 6), "failed to draw 2d geometry...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind 2d geometry vertex array...");

	Shader::Unbind();
}

void TextureShader2D::UpdateVertexBuffer()
{
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_), "failed to bind 2d texture vertex buffer...");

	void* bufferPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	ASSERT(bufferPtr != nullptr, "failed to map the entire data store of a specified buffer object into the client's address space...");

	std::memcpy(bufferPtr, reinterpret_cast<const void*>(vertices_.data()), VertexPositionTexture::GetStride() * vertices_.size());
	GLboolean bSuccssed = glUnmapBuffer(GL_ARRAY_BUFFER);
	ASSERT(bSuccssed, "failed to unmap the entire data store of a specified buffer object into the client's address space...");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0), "failed to unbind 2d texture vertex buffer...");
}
