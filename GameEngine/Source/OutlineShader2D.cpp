#include "OutlineShader2D.h"

#include "GLAssertionMacro.h"
#include "MathUtils.h"
#include "Texture2D.h"

#include <glad/glad.h>


OutlineShader2D::~OutlineShader2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void OutlineShader2D::Initialize(const std::string& vsPath, const std::string& fsPath, bool bCheckValid)
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

	Shader::Bind();
	transformLocation_ = GetUniformLocation("transform");
	orthoLocation_ = GetUniformLocation("ortho");
	reverseTexCoordLocation_ = GetUniformLocation("bReverseTexCoord");
	outlineRGBALocation_ = GetUniformLocation("outlineRGBA");
	transparentLocation_ = GetUniformLocation("transparent");
	Shader::Unbind();
}

void OutlineShader2D::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	Shader::Release();

	GL_ASSERT(glDeleteBuffers(1, &vertexBufferObject_), "failed to delete 2d texture vertex buffer...");
	GL_ASSERT(glDeleteVertexArrays(1, &vertexArrayObject_), "failed to delete 2d texture vertex array object...");
}

void OutlineShader2D::DrawTextureOutline2D(const Matrix4x4f& ortho, Texture2D* texture, const Vector2f& center, float width, float height, float rotate, const Vector4f& outline, float transparent)
{
	vertices_[0] = VertexPositionTexture(Vector3f(center.x - width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), Vector2f(0.0f, 0.0f));
	vertices_[1] = VertexPositionTexture(Vector3f(center.x - width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), Vector2f(0.0f, 1.0f));
	vertices_[2] = VertexPositionTexture(Vector3f(center.x + width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), Vector2f(1.0f, 0.0f));

	vertices_[3] = VertexPositionTexture(Vector3f(center.x + width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), Vector2f(1.0f, 0.0f));
	vertices_[4] = VertexPositionTexture(Vector3f(center.x - width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), Vector2f(0.0f, 1.0f));
	vertices_[5] = VertexPositionTexture(Vector3f(center.x + width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), Vector2f(1.0f, 1.0f));
	
	const void* bufferPtr = reinterpret_cast<const void*>(vertices_.data());
	uint32_t bufferByteSize = static_cast<uint32_t>(VertexPositionTexture::GetStride() * vertices_.size());
	UpdateDynamicVertexBuffer(vertexBufferObject_, bufferPtr, bufferByteSize);

	Matrix4x4f transform = MathUtils::CreateTranslation(Vector3f(-center.x, -center.y, 0.0f))
		* MathUtils::CreateRotateZ(rotate)
		* MathUtils::CreateTranslation(Vector3f(+center.x, +center.y, 0.0f));

	uint32_t vertexCount = 6;

	Shader::Bind();

	texture->Active(0);

	Shader::SetMatrix4x4fParameter(transformLocation_, transform);
	Shader::SetMatrix4x4fParameter(orthoLocation_, ortho);
	Shader::SetBoolParameter(reverseTexCoordLocation_, false);
	Shader::SetVector4fParameter(outlineRGBALocation_, outline);
	Shader::SetFloatParameter(transparentLocation_, transparent);

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind 2d texture vertex array...");
	GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, vertexCount), "failed to draw 2d texture...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind 2d texture vertex array...");

	Shader::Unbind();
}