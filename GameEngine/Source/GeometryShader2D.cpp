#include "GeometryShader2D.h"

#include "AssertionMacro.h"

#include <glad/glad.h>

GeometryShader2D::~GeometryShader2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void GeometryShader2D::Initialize(const std::string& vsPath, const std::string& fsPath, bool bCheckValid)
{
	ASSERT(!bIsInitialized_, "already initialize geometry shader 2d resource...");

	Shader::Initialize(vsPath, fsPath, bCheckValid);

	glGenVertexArrays(1, &vertexArrayObject_);
	glGenBuffers(1, &vertexBufferObject_);

	glBindVertexArray(vertexArrayObject_);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_);
	glBufferData(GL_ARRAY_BUFFER, VertexPositionColor::GetStride() * vertices_.size(), reinterpret_cast<const void*>(vertices_.data()), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexPositionColor::GetStride(), (void*)(offsetof(VertexPositionColor, position_)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexPositionColor::GetStride(), (void*)(offsetof(VertexPositionColor, color_)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void GeometryShader2D::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	Shader::Release();

	glDeleteBuffers(1, &vertexBufferObject_);
	glDeleteVertexArrays(1, &vertexArrayObject_);
}

void GeometryShader2D::DrawPoints2D(const Matrix4x4f& ortho, const std::vector<Vector3f>& positions, const Vector4f& color, float pointSize)
{
	ASSERT(positions.size() <= MAX_VERTEX_SIZE, "overflow 2d point count : %d", static_cast<int32_t>(positions.size()));
	ASSERT(pointSize >= 0.0f, "invalid 2d point size : %d", pointSize);

	for (std::size_t index = 0; index < positions.size(); ++index)
	{
		vertices_[index] = VertexPositionColor(Vector3f(positions[index].x + 0.5f, positions[index].y + 0.5f, 0.0f), color);
	}

	UpdateVertexBuffer();

	Shader::Bind();
	Shader::SetFloatParameter("pointSize", pointSize);
	Shader::SetMatrix4x4fParameter("ortho", ortho);
	
	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_POINTS, 0, static_cast<uint32_t>(positions.size()));
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::DrawLine2D(const Matrix4x4f& ortho, const Vector3f& fromPosition, const Vector3f& toPosition, const Vector4f& color)
{
	vertices_[0] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), color);
	vertices_[1] = VertexPositionColor(Vector3f(  toPosition.x + 0.5f,   toPosition.y + 0.5f, 0.0f), color);
	
	UpdateVertexBuffer();

	Shader::Bind();
	Shader::SetMatrix4x4fParameter("ortho", ortho);

	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::UpdateVertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_);

	void* bufferPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	std::memcpy(bufferPtr, reinterpret_cast<const void*>(&vertices_[0]), VertexPositionColor::GetStride() * vertices_.size());
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}