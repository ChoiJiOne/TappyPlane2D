#include "GeometryShader2D.h"

#include "AssertionMacro.h"
#include "MathUtils.h"

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

void GeometryShader2D::DrawPoints2D(const Matrix4x4f& ortho, const std::vector<Vector2f>& positions, const Vector4f& color, float pointSize)
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
	Shader::SetMatrix4x4fParameter("transform", Matrix4x4f::GetIdentity());
	Shader::SetMatrix4x4fParameter("ortho", ortho);
	
	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_POINTS, 0, static_cast<uint32_t>(positions.size()));
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::DrawLine2D(const Matrix4x4f& ortho, const Vector2f& fromPosition, const Vector2f& toPosition, const Vector4f& color)
{
	vertices_[0] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), color);
	vertices_[1] = VertexPositionColor(Vector3f(  toPosition.x + 0.5f,   toPosition.y + 0.5f, 0.0f), color);
	
	UpdateVertexBuffer();

	Shader::Bind();
	Shader::SetMatrix4x4fParameter("transform", Matrix4x4f::GetIdentity());
	Shader::SetMatrix4x4fParameter("ortho", ortho);

	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::DrawLine2D(const Matrix4x4f& ortho, const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& toPosition, const Vector4f& toColor)
{
	vertices_[0] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), fromColor);
	vertices_[1] = VertexPositionColor(Vector3f(  toPosition.x + 0.5f,   toPosition.y + 0.5f, 0.0f), toColor);

	UpdateVertexBuffer();

	Shader::Bind();
	Shader::SetMatrix4x4fParameter("transform", Matrix4x4f::GetIdentity());
	Shader::SetMatrix4x4fParameter("ortho", ortho);

	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::DrawTriangle2D(const Matrix4x4f& ortho, const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color)
{
	vertices_[0] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), color);
	vertices_[1] = VertexPositionColor(Vector3f(  byPosition.x + 0.5f,   byPosition.y + 0.5f, 0.0f), color);
	vertices_[2] = VertexPositionColor(Vector3f(  toPosition.x + 0.5f,   toPosition.y + 0.5f, 0.0f), color);

	UpdateVertexBuffer();

	Shader::Bind();
	Shader::SetMatrix4x4fParameter("transform", Matrix4x4f::GetIdentity());
	Shader::SetMatrix4x4fParameter("ortho", ortho);

	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::DrawTriangle2D(const Matrix4x4f& ortho, const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& byPosition, const Vector4f& byColor, const Vector2f& toPosition, const Vector4f& toColor)
{
	vertices_[0] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), fromColor);
	vertices_[1] = VertexPositionColor(Vector3f(  byPosition.x + 0.5f,   byPosition.y + 0.5f, 0.0f),   byColor);
	vertices_[2] = VertexPositionColor(Vector3f(  toPosition.x + 0.5f,   toPosition.y + 0.5f, 0.0f),   toColor);

	UpdateVertexBuffer();

	Shader::Bind();
	Shader::SetMatrix4x4fParameter("transform", Matrix4x4f::GetIdentity());
	Shader::SetMatrix4x4fParameter("ortho", ortho);

	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::DrawWireframeTriangle2D(const Matrix4x4f& ortho, const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color)
{
	vertices_[0] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), color);
	vertices_[1] = VertexPositionColor(Vector3f(  byPosition.x + 0.5f,   byPosition.y + 0.5f, 0.0f), color);
	vertices_[2] = VertexPositionColor(Vector3f(  toPosition.x + 0.5f,   toPosition.y + 0.5f, 0.0f), color);
	vertices_[3] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), color);

	UpdateVertexBuffer();

	Shader::Bind();
	Shader::SetMatrix4x4fParameter("transform", Matrix4x4f::GetIdentity());
	Shader::SetMatrix4x4fParameter("ortho", ortho);

	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::DrawWireframeTriangle2D(const Matrix4x4f& ortho, const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& byPosition, const Vector4f& byColor, const Vector2f& toPosition, const Vector4f& toColor)
{
	vertices_[0] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), fromColor);
	vertices_[1] = VertexPositionColor(Vector3f(  byPosition.x + 0.5f,   byPosition.y + 0.5f, 0.0f),   byColor);
	vertices_[2] = VertexPositionColor(Vector3f(  toPosition.x + 0.5f,   toPosition.y + 0.5f, 0.0f),   toColor);
	vertices_[3] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), fromColor);

	UpdateVertexBuffer();

	Shader::Bind();
	Shader::SetMatrix4x4fParameter("transform", Matrix4x4f::GetIdentity());
	Shader::SetMatrix4x4fParameter("ortho", ortho);

	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::DrawRectangle2D(const Matrix4x4f& ortho, const Vector2f& center, float width, float height, float rotate, const Vector4f& color)
{
	vertices_[0] = VertexPositionColor(Vector3f(center.x - width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), color);
	vertices_[1] = VertexPositionColor(Vector3f(center.x - width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), color);
	vertices_[2] = VertexPositionColor(Vector3f(center.x + width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), color);

	vertices_[3] = VertexPositionColor(Vector3f(center.x + width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), color);
	vertices_[4] = VertexPositionColor(Vector3f(center.x - width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), color);
	vertices_[5] = VertexPositionColor(Vector3f(center.x + width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), color);
	
	UpdateVertexBuffer();

	Matrix4x4f transform = MathUtils::CreateTranslation(Vector3f(-center.x, -center.y, 0.0f)) 
		* MathUtils::CreateRotateZ(rotate) 
		* MathUtils::CreateTranslation(Vector3f(+center.x, +center.y, 0.0f));

	Shader::Bind();
	Shader::SetMatrix4x4fParameter("transform", transform);
	Shader::SetMatrix4x4fParameter("ortho", ortho);

	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::DrawWireframeRectangle2D(const Matrix4x4f& ortho, const Vector2f& center, float width, float height, float rotate, const Vector4f& color)
{
	vertices_[0] = VertexPositionColor(Vector3f(center.x - width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), color);
	vertices_[1] = VertexPositionColor(Vector3f(center.x - width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), color);
	vertices_[2] = VertexPositionColor(Vector3f(center.x + width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), color);
	vertices_[3] = VertexPositionColor(Vector3f(center.x + width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), color);
	vertices_[4] = VertexPositionColor(Vector3f(center.x - width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), color);

	UpdateVertexBuffer();

	Matrix4x4f transform = MathUtils::CreateTranslation(Vector3f(-center.x, -center.y, 0.0f))
		* MathUtils::CreateRotateZ(rotate)
		* MathUtils::CreateTranslation(Vector3f(+center.x, +center.y, 0.0f));

	Shader::Bind();
	Shader::SetMatrix4x4fParameter("transform", transform);
	Shader::SetMatrix4x4fParameter("ortho", ortho);

	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_LINE_STRIP, 0, 5);
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::DrawCircle2D(const Matrix4x4f& ortho, const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount)
{
	ASSERT(radius >= 0.0f, "invalid circle radius : %f", radius);
	ASSERT(sliceCount <= MAX_VERTEX_SIZE - 2, "overflow circle slice count : %d", sliceCount);

	for (int32_t slice = 1; slice <= sliceCount; ++slice)
	{
		float radian = (static_cast<float>(slice - 1) * MathUtils::TwoPi) / static_cast<float>(sliceCount);
		float x = radius * MathUtils::ScalarCos(radian);
		float y = radius * MathUtils::ScalarSin(radian);

		vertices_[slice] = VertexPositionColor(Vector3f(center.x + x + 0.5f, center.y + y + 0.5f, 0.0f), color);
	}

	vertices_[0] = VertexPositionColor(Vector3f(center.x + 0.5f, center.y + 0.5f, 0.0f), color);
	vertices_[sliceCount + 1] = vertices_[1];
	uint32_t vertexCount = static_cast<uint32_t>(sliceCount + 2);

	UpdateVertexBuffer();

	Shader::Bind();
	Shader::SetMatrix4x4fParameter("transform", Matrix4x4f::GetIdentity());
	Shader::SetMatrix4x4fParameter("ortho", ortho);

	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::DrawWireframeCircle2D(const Matrix4x4f& ortho, const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount)
{
	ASSERT(radius >= 0.0f, "invalid circle radius : %f", radius);
	ASSERT(sliceCount <= MAX_VERTEX_SIZE, "overflow circle slice count : %d", sliceCount);

	for (int32_t index = 0; index < sliceCount; ++index)
	{
		float radian = (static_cast<float>(index) * MathUtils::TwoPi) / static_cast<float>(sliceCount);
		float x = radius * MathUtils::ScalarCos(radian);
		float y = radius * MathUtils::ScalarSin(radian);

		vertices_[index] = VertexPositionColor(Vector3f(center.x + x + 0.5f, center.y + y + 0.5f , 0.0f), color);
	}

	vertices_[sliceCount] = vertices_[0];
	uint32_t vertexCount = static_cast<uint32_t>(sliceCount + 1);

	UpdateVertexBuffer();

	Shader::Bind();
	Shader::SetMatrix4x4fParameter("transform", Matrix4x4f::GetIdentity());
	Shader::SetMatrix4x4fParameter("ortho", ortho);

	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_LINE_STRIP, 0, vertexCount);
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::DrawEllipse2D(const Matrix4x4f& ortho, const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount)
{
	ASSERT(xAxis >= 0.0f, "invalid ellipse x axis : %f", xAxis);
	ASSERT(yAxis >= 0.0f, "invalid ellipse y axis : %f", yAxis);
	ASSERT(sliceCount <= MAX_VERTEX_SIZE - 2, "overflow circle slice count : %d", sliceCount);

	float halfXAxis = xAxis / 2.0f;
	float haflYAxis = yAxis / 2.0f;

	for (int32_t slice = 1; slice <= sliceCount; ++slice)
	{
		float radian = (static_cast<float>(slice - 1) * MathUtils::TwoPi) / static_cast<float>(sliceCount);
		float x = halfXAxis * MathUtils::ScalarCos(radian);
		float y = haflYAxis * MathUtils::ScalarSin(radian);

		vertices_[slice] = VertexPositionColor(Vector3f(center.x + x + 0.5f, center.y + y + 0.5f, 0.0f), color);
	}

	vertices_[0] = VertexPositionColor(Vector3f(center.x + 0.5f, center.y + 0.5f, 0.0f), color);
	vertices_[sliceCount + 1] = vertices_[1];
	uint32_t vertexCount = static_cast<uint32_t>(sliceCount + 2);

	UpdateVertexBuffer();

	Shader::Bind();
	Shader::SetMatrix4x4fParameter("transform", Matrix4x4f::GetIdentity());
	Shader::SetMatrix4x4fParameter("ortho", ortho);

	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::DrawGrid2D(const Matrix4x4f& ortho, float minX, float maxX, float strideX, float minY, float maxY, float strideY, const Vector4f& color)
{
	ASSERT((strideX >= 1.0f && strideY >= 1.0f), "The values of strideX and strideY are too small : %f, %f", strideX, strideY);

	uint32_t vertexIndex = 0;
	for (float x = minX; x <= maxX; x += strideX)
	{
		ASSERT(vertexIndex < MAX_VERTEX_SIZE, "overflow grid vertex count : %d", vertexIndex + 1);
		vertices_[vertexIndex++] = VertexPositionColor(Vector3f(x + 0.5f, minY + 0.5f, 0.0f), color);
		vertices_[vertexIndex++] = VertexPositionColor(Vector3f(x + 0.5f, maxY + 0.5f, 0.0f), color);
	}

	for (float y = minY; y <= maxY; y += strideY)
	{
		ASSERT(vertexIndex < MAX_VERTEX_SIZE, "overflow grid vertex count : %d", vertexIndex + 1);
		vertices_[vertexIndex++] = VertexPositionColor(Vector3f(minX + 0.5f, y + 0.5f, 0.0f), color);
		vertices_[vertexIndex++] = VertexPositionColor(Vector3f(maxX + 0.5f, y + 0.5f, 0.0f), color);
	}

	UpdateVertexBuffer();
	
	Shader::Bind();
	Shader::SetMatrix4x4fParameter("transform", Matrix4x4f::GetIdentity());
	Shader::SetMatrix4x4fParameter("ortho", ortho);

	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_LINES, 0, vertexIndex + 1);
	glBindVertexArray(0);

	Shader::Unbind();
}

void GeometryShader2D::UpdateVertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_);

	void* bufferPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	std::memcpy(bufferPtr, reinterpret_cast<const void*>(vertices_.data()), VertexPositionColor::GetStride() * vertices_.size());
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}