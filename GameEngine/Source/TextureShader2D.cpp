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

	Shader::Bind();
	transformLocation_ = GetUniformLocation("transform");
	orthoLocation_ = GetUniformLocation("ortho");
	reverseTexCoordLocation_ = GetUniformLocation("bReverseTexCoord");
	transparentLocation_ = GetUniformLocation("transparent");
	Shader::Unbind();
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

	Matrix4x4f transform = MathUtils::CreateTranslation(Vector3f(-center.x, -center.y, 0.0f))
		* MathUtils::CreateRotateZ(rotate)
		* MathUtils::CreateTranslation(Vector3f(+center.x, +center.y, 0.0f));

	uint32_t vertexCount = 6;
	DrawTexture2D(transform, ortho, vertexCount, texture, transparent);
}

void TextureShader2D::DrawTexture2D(Texture2D* texture, float transparent)
{
	vertices_[0] = VertexPositionTexture(Vector3f(-1.0f, +1.0f, 0.0f), Vector2f(0.0f, 0.0f));
	vertices_[1] = VertexPositionTexture(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(0.0f, 1.0f));
	vertices_[2] = VertexPositionTexture(Vector3f(+1.0f, +1.0f, 0.0f), Vector2f(1.0f, 0.0f));

	vertices_[3] = VertexPositionTexture(Vector3f(+1.0f, +1.0f, 0.0f), Vector2f(1.0f, 0.0f));
	vertices_[4] = VertexPositionTexture(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(0.0f, 1.0f));
	vertices_[5] = VertexPositionTexture(Vector3f(+1.0f, -1.0f, 0.0f), Vector2f(1.0f, 1.0f));

	uint32_t vertexCount = 6;
	DrawTexture2D(Matrix4x4f::GetIdentity(), Matrix4x4f::GetIdentity(), vertexCount, texture, transparent);
}

void TextureShader2D::DrawHorizonScrollTexture2D(Texture2D* texture, float rate, float transparent)
{
	rate = MathUtils::Clamp<float>(rate, 0.0f, 1.0f);
	float x = -1.0f + 2.0f * (1.0f - rate);

	vertices_[0]  = VertexPositionTexture(Vector3f(-1.0f, +1.0f, 0.0f), Vector2f(rate, 0.0f));
	vertices_[1]  = VertexPositionTexture(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(rate, 1.0f));
	vertices_[2]  = VertexPositionTexture(Vector3f(   +x, +1.0f, 0.0f), Vector2f(1.0f, 0.0f));

	vertices_[3]  = VertexPositionTexture(Vector3f(   +x, +1.0f, 0.0f), Vector2f(1.0f, 0.0f));
	vertices_[4]  = VertexPositionTexture(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(rate, 1.0f));
	vertices_[5]  = VertexPositionTexture(Vector3f(   +x, -1.0f, 0.0f), Vector2f(1.0f, 1.0f));

	vertices_[6]  = VertexPositionTexture(Vector3f(   +x, +1.0f, 0.0f), Vector2f(0.0f, 0.0f));
	vertices_[7]  = VertexPositionTexture(Vector3f(   +x, -1.0f, 0.0f), Vector2f(0.0f, 1.0f));
	vertices_[8]  = VertexPositionTexture(Vector3f(+1.0f, +1.0f, 0.0f), Vector2f(rate, 0.0f));

	vertices_[9]  = VertexPositionTexture(Vector3f(+1.0f, +1.0f, 0.0f), Vector2f(rate, 0.0f));
	vertices_[10] = VertexPositionTexture(Vector3f(   +x, -1.0f, 0.0f), Vector2f(0.0f, 1.0f));
	vertices_[11] = VertexPositionTexture(Vector3f(+1.0f, -1.0f, 0.0f), Vector2f(rate, 1.0f));

	uint32_t vertexCount = 12;
	DrawTexture2D(Matrix4x4f::GetIdentity(), Matrix4x4f::GetIdentity(), vertexCount, texture, transparent);
}

void TextureShader2D::DrawHorizonScrollTexture2D(const Matrix4x4f& ortho, Texture2D* texture, const Vector2f& center, float width, float height, float rate, float transparent)
{
	rate = MathUtils::Clamp<float>(rate, 0.0f, 1.0f);

	float x0 = center.x - width / 2.0f;
	float y0 = center.y - height / 2.0f;
	float x1 = center.x + width / 2.0f;
	float y1 = center.y + height / 2.0f;

	float x = x0 + (x1 - x0) * (1.0f - rate);

	vertices_[0]  = VertexPositionTexture(Vector3f(x0 + 0.5f, y0 + 0.5f, 0.0f), Vector2f(rate, 0.0f));
	vertices_[1]  = VertexPositionTexture(Vector3f(x0 + 0.5f, y1 + 0.5f, 0.0f), Vector2f(rate, 1.0f));
	vertices_[2]  = VertexPositionTexture(Vector3f(+x + 0.5f, y0 + 0.5f, 0.0f), Vector2f(1.0f, 0.0f));

	vertices_[3]  = VertexPositionTexture(Vector3f(+x + 0.5f, y0 + 0.5f, 0.0f), Vector2f(1.0f, 0.0f));
	vertices_[4]  = VertexPositionTexture(Vector3f(x0 + 0.5f, y1 + 0.5f, 0.0f), Vector2f(rate, 1.0f));
	vertices_[5]  = VertexPositionTexture(Vector3f(+x + 0.5f, y1 + 0.5f, 0.0f), Vector2f(1.0f, 1.0f));

	vertices_[6]  = VertexPositionTexture(Vector3f(+x + 0.5f, y0 + 0.5f, 0.0f), Vector2f(0.0f, 0.0f));
	vertices_[7]  = VertexPositionTexture(Vector3f(+x + 0.5f, y1 + 0.5f, 0.0f), Vector2f(0.0f, 1.0f));
	vertices_[8]  = VertexPositionTexture(Vector3f(x1 + 0.5f, y0 + 0.5f, 0.0f), Vector2f(rate, 0.0f));

	vertices_[9]  = VertexPositionTexture(Vector3f(x1 + 0.5f, y0 + 0.5f, 0.0f), Vector2f(rate, 0.0f));
	vertices_[10] = VertexPositionTexture(Vector3f(+x + 0.5f, y1 + 0.5f, 0.0f), Vector2f(0.0f, 1.0f));
	vertices_[11] = VertexPositionTexture(Vector3f(x1 + 0.5f, y1 + 0.5f, 0.0f), Vector2f(rate, 1.0f));

	uint32_t vertexCount = 12;
	DrawTexture2D(Matrix4x4f::GetIdentity(), ortho, vertexCount, texture, transparent);
}

void TextureShader2D::DrawVerticalScrollTexture2D(Texture2D* texture, float rate, float transparent)
{
	rate = MathUtils::Clamp<float>(rate, 0.0f, 1.0f);
	float y = -1.0f + 2.0f * (1.0f - rate);

	vertices_[0]  = VertexPositionTexture(Vector3f(+1.0f, +1.0f, 0.0f), Vector2f(1.0f, 1.0f - rate));
	vertices_[1]  = VertexPositionTexture(Vector3f(-1.0f, +1.0f, 0.0f), Vector2f(0.0f, 1.0f - rate));
	vertices_[2]  = VertexPositionTexture(Vector3f(-1.0f,    +y, 0.0f), Vector2f(0.0f,        1.0f));

	vertices_[3]  = VertexPositionTexture(Vector3f(+1.0f, +1.0f, 0.0f), Vector2f(1.0f, 1.0f - rate));
	vertices_[4]  = VertexPositionTexture(Vector3f(-1.0f,    +y, 0.0f), Vector2f(0.0f,        1.0f));
	vertices_[5]  = VertexPositionTexture(Vector3f(+1.0f,    +y, 0.0f), Vector2f(1.0f,        1.0f));

	vertices_[6]  = VertexPositionTexture(Vector3f(+1.0f,    +y, 0.0f), Vector2f(1.0f,        0.0f));
	vertices_[7]  = VertexPositionTexture(Vector3f(-1.0f,    +y, 0.0f), Vector2f(0.0f,        0.0f));
	vertices_[8]  = VertexPositionTexture(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(0.0f, 1.0f - rate));

	vertices_[9]  = VertexPositionTexture(Vector3f(+1.0f,    +y, 0.0f), Vector2f(1.0f,        0.0f));
	vertices_[10] = VertexPositionTexture(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(0.0f, 1.0f - rate));
	vertices_[11] = VertexPositionTexture(Vector3f(+1.0f, -1.0f, 0.0f), Vector2f(1.0f, 1.0f - rate));

	uint32_t vertexCount = 12;
	DrawTexture2D(Matrix4x4f::GetIdentity(), Matrix4x4f::GetIdentity(), vertexCount, texture, transparent);
}

void TextureShader2D::DrawVerticalScrollTexture2D(const Matrix4x4f& ortho, Texture2D* texture, const Vector2f& center, float width, float height, float rate, float transparent)
{
	rate = MathUtils::Clamp<float>(rate, 0.0f, 1.0f);

	float x0 = center.x - width / 2.0f;
	float y0 = center.y - height / 2.0f;
	float x1 = center.x + width / 2.0f;
	float y1 = center.y + height / 2.0f;

	float y = y0 + (y1 - y0) * rate;

	vertices_[0]  = VertexPositionTexture(Vector3f(x1, y0, 0.0f), Vector2f(1.0f, 1.0f - rate));
	vertices_[1]  = VertexPositionTexture(Vector3f(x0, y0, 0.0f), Vector2f(0.0f, 1.0f - rate));
	vertices_[2]  = VertexPositionTexture(Vector3f(x0, +y, 0.0f), Vector2f(0.0f,        1.0f));

	vertices_[3]  = VertexPositionTexture(Vector3f(x1, y0, 0.0f), Vector2f(1.0f, 1.0f - rate));
	vertices_[4]  = VertexPositionTexture(Vector3f(x0, +y, 0.0f), Vector2f(0.0f,        1.0f));
	vertices_[5]  = VertexPositionTexture(Vector3f(x1, +y, 0.0f), Vector2f(1.0f,        1.0f));

	vertices_[6]  = VertexPositionTexture(Vector3f(x1, +y, 0.0f), Vector2f(1.0f,        0.0f));
	vertices_[7]  = VertexPositionTexture(Vector3f(x0, +y, 0.0f), Vector2f(0.0f,        0.0f));
	vertices_[8]  = VertexPositionTexture(Vector3f(x0, y1, 0.0f), Vector2f(0.0f, 1.0f - rate));

	vertices_[9]  = VertexPositionTexture(Vector3f(x1, +y, 0.0f), Vector2f(1.0f,        0.0f));
	vertices_[10] = VertexPositionTexture(Vector3f(x0, y1, 0.0f), Vector2f(0.0f, 1.0f - rate));
	vertices_[11] = VertexPositionTexture(Vector3f(x1, y1, 0.0f), Vector2f(1.0f, 1.0f - rate));

	uint32_t vertexCount = 12;
	DrawTexture2D(Matrix4x4f::GetIdentity(), ortho, vertexCount, texture, transparent);
}

void TextureShader2D::DrawTexture2D(const Matrix4x4f& transform, const Matrix4x4f& ortho, uint32_t vertexCount, Texture2D* texture, float transparent)
{
	const void* bufferPtr = reinterpret_cast<const void*>(vertices_.data());
	uint32_t bufferByteSize = static_cast<uint32_t>(VertexPositionTexture::GetStride() * vertices_.size());
	UpdateDynamicVertexBuffer(vertexBufferObject_, bufferPtr, bufferByteSize);

	Shader::Bind();

	texture->Active(0);

	Shader::SetMatrix4x4fParameter(transformLocation_, transform);
	Shader::SetMatrix4x4fParameter(orthoLocation_, ortho);
	Shader::SetBoolParameter(reverseTexCoordLocation_, false);
	Shader::SetFloatParameter(transparentLocation_, transparent);

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind 2d texture vertex array...");
	GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, vertexCount), "failed to draw 2d texture...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind 2d texture vertex array...");

	Shader::Unbind();
}