#include "PostProcessing.h"

#include "GLAssertionMacro.h"
#include "Framebuffer.h"

#include <glad/glad.h>

PostProcessing::~PostProcessing()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void PostProcessing::Initialize(const std::string& vsPath, const std::string& fsPath, bool bCheckValid)
{
	ASSERT(!bIsInitialized_, "already initialize post processing shader resource...");
	
	Shader::Initialize(vsPath, fsPath, bCheckValid);

	vertices_ = {
		VertexPositionTexture(Vector3f(-1.0f, +1.0f, 0.0f), Vector2f(0.0f, 0.0f)),
		VertexPositionTexture(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(0.0f, 1.0f)),
		VertexPositionTexture(Vector3f(+1.0f, +1.0f, 0.0f), Vector2f(1.0f, 0.0f)),
		VertexPositionTexture(Vector3f(+1.0f, +1.0f, 0.0f), Vector2f(1.0f, 0.0f)),
		VertexPositionTexture(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(0.0f, 1.0f)),
		VertexPositionTexture(Vector3f(+1.0f, -1.0f, 0.0f), Vector2f(1.0f, 1.0f)),
	};

	GL_ASSERT(glGenVertexArrays(1, &vertexArrayObject_), "failed to generate frame buffer vertex array...");
	GL_ASSERT(glGenBuffers(1, &vertexBufferObject_), "failed to generate frame buffer vertex buffer...");

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind frame buffer vertex array...");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_), "failed to bind frame buffer vertex buffer...");
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, VertexPositionTexture::GetStride() * vertices_.size(), reinterpret_cast<const void*>(vertices_.data()), GL_STATIC_DRAW),
		"failed to create a new data store for vertex buffer object...");

	GL_ASSERT(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexPositionTexture::GetStride(), (void*)(offsetof(VertexPositionTexture, position_))),
		"failed to specify the location and data format of the array of generic vertex attributes at index...");
	GL_ASSERT(glEnableVertexAttribArray(0), "failed to enable vertex attrib array...");

	GL_ASSERT(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VertexPositionTexture::GetStride(), (void*)(offsetof(VertexPositionTexture, st_))),
		"failed to specify the location and data format of the array of generic vertex attributes at index...");
	GL_ASSERT(glEnableVertexAttribArray(1), "failed to enable vertex attrib array...");

	GL_ASSERT(glBindVertexArray(0), "failed to unbind frame buffer vertex array...");
}

void PostProcessing::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	Shader::Release();

	GL_ASSERT(glDeleteBuffers(1, &vertexBufferObject_), "failed to delete frame buffer vertex buffer...");
	GL_ASSERT(glDeleteVertexArrays(1, &vertexArrayObject_), "failed to delete frame buffer vertex array object...");
}

void PostProcessing::PostEffectInversion(Framebuffer* framebuffer)
{
	framebuffer->Active(0);

	Shader::Bind();
	Shader::SetIntParameter("effectOption", static_cast<int32_t>(EPostEffectType::Inversion));

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind frame buffer vertex array...");
	GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, MAX_VERTEX_SIZE), "failed to blit frame buffer...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind frame buffer vertex array...");

	Shader::Unbind();
}

void PostProcessing::PostEffectAverageGrayscale(Framebuffer* framebuffer)
{
	framebuffer->Active(0);

	Shader::Bind();
	Shader::SetIntParameter("effectOption", static_cast<int32_t>(EPostEffectType::AverageGrayscale));

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind frame buffer vertex array...");
	GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, MAX_VERTEX_SIZE), "failed to blit frame buffer...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind frame buffer vertex array...");

	Shader::Unbind();
}

void PostProcessing::PostEffectWeightGrayscale(Framebuffer* framebuffer)
{
	framebuffer->Active(0);

	Shader::Bind();
	Shader::SetIntParameter("effectOption", static_cast<int32_t>(EPostEffectType::WeightGrayscale));

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind frame buffer vertex array...");
	GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, MAX_VERTEX_SIZE), "failed to blit frame buffer...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind frame buffer vertex array...");

	Shader::Unbind();
}

void PostProcessing::PostEffectNormalBlur(Framebuffer* framebuffer, float blurBias)
{
	ASSERT(blurBias >= 0.0f, "invalid post processing blur bias : %f", blurBias);

	framebuffer->Active(0);

	Shader::Bind();
	Shader::SetIntParameter("effectOption", static_cast<int32_t>(EPostEffectType::NormalBlur));
	Shader::SetFloatParameter("blurBias", blurBias);

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind frame buffer vertex array...");
	GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, MAX_VERTEX_SIZE), "failed to blit frame buffer...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind frame buffer vertex array...");

	Shader::Unbind();
}

void PostProcessing::PostEffectGaussianBlur(Framebuffer* framebuffer, float blurBias)
{
	ASSERT((blurBias >= 0.0f && blurBias <= 1.0f), "invalid post processing gaussian blur bias : %f", blurBias);

	framebuffer->Active(0);

	Shader::Bind();
	Shader::SetIntParameter("effectOption", static_cast<int32_t>(EPostEffectType::GaussianBlur));
	Shader::SetFloatParameter("blurBias", blurBias);

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind frame buffer vertex array...");
	GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, MAX_VERTEX_SIZE), "failed to blit frame buffer...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind frame buffer vertex array...");

	Shader::Unbind();
}

void PostProcessing::PostEffectFadeEffect(Framebuffer* framebuffer, float fadeBias)
{
	ASSERT((fadeBias >= 0.0f && fadeBias <= 1.0f), "invalid post processing fade effect bias : %f", fadeBias);

	framebuffer->Active(0);
		
	Shader::Bind();
	Shader::SetIntParameter("effectOption", static_cast<int32_t>(EPostEffectType::Fade));
	Shader::SetFloatParameter("fadeBias", fadeBias);

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind frame buffer vertex array...");
	GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, MAX_VERTEX_SIZE), "failed to blit frame buffer...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind frame buffer vertex array...");

	Shader::Unbind();
}

void PostProcessing::Blit(Framebuffer* framebuffer)
{
	Shader::Bind();

	framebuffer->Active(0);
	Shader::SetIntParameter("effectOption", static_cast<int32_t>(EPostEffectType::None));

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind frame buffer vertex array...");
	GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, MAX_VERTEX_SIZE), "failed to blit frame buffer...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind frame buffer vertex array...");
	
	Shader::Unbind();
}