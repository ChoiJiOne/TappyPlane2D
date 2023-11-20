#include "RenderManager.h"

#include "CommandLineArg.h"
#include "EngineManager.h"
#include "AssertionMacro.h"
#include "GeometryShader2D.h"
#include "GLAssertionMacro.h"
#include "GlyphShader2D.h"
#include "OutlineShader2D.h"
#include "ResourceManager.h"
#include "SilhouetteShader2D.h"
#include "Texture2D.h"
#include "TextureShader2D.h"
#include "TTFont.h"
#include "Window.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

void RenderManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup render manager...");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* windowPtr = window_->GetWindowPtr();
	glfwMakeContextCurrent(windowPtr);

	ASSERT(gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)), "failed to initialize OpenGL function loader...");
	
	GL_ASSERT(glEnable(GL_PROGRAM_POINT_SIZE), "failed to enable shader program point size...");

	bIsStartup_ = true;
}

void RenderManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	bIsStartup_ = false;
}

void RenderManager::PreStartup(Window* window, int32_t major, int32_t minor)
{
	ASSERT(window != nullptr, "invalid window pointer...");
	window_ = window;

	ASSERT((major == 4), "major version of OpenGL must be 4...");
	ASSERT((minor >= 3 && minor <= 6), "minor version of OpenGL must be between 3 and 6...");
	
	major_ = major;
	minor_ = minor;

	int32_t screenWidth = 0;
	int32_t screenHeight = 0;
	window_->GetSize(screenWidth, screenHeight);

	float farZ = 1.0f;
	float nearZ = -1.0f;
	screenOrtho_ = MathUtils::CreateOrtho(0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight), 0.0f, nearZ, farZ);
}

void RenderManager::PostSetup()
{
	std::string shaderPath;
	ASSERT(CommandLineArg::GetStringValue("glsl", shaderPath), "invalid GLSL path in commandline argument...");

	shaderMaps_ = std::unordered_map<std::string, Shader*>();

	ResourceManager& resourceManager = ResourceManager::Get();

	GeometryShader2D* geometryShader = resourceManager.CreateResource<GeometryShader2D>("GeometryShader2D");
	geometryShader->Initialize(shaderPath + "Geometry2D.vert", shaderPath + "Geometry2D.frag");
	shaderMaps_.insert({ "GeometryShader2D" , geometryShader });

	TextureShader2D* textureShader = resourceManager.CreateResource<TextureShader2D>("TextureShader2D");
	textureShader->Initialize(shaderPath + "Texture2D.vert", shaderPath + "Texture2D.frag");
	shaderMaps_.insert({ "TextureShader2D", textureShader });

	GlyphShader2D* glyphShader = resourceManager.CreateResource<GlyphShader2D>("GlyphShader2D");
	glyphShader->Initialize(shaderPath + "Glyph2D.vert", shaderPath + "Glyph2D.frag");
	shaderMaps_.insert({ "GlyphShader2D", glyphShader });

	SilhouetteShader2D* silhouetteShader = resourceManager.CreateResource<SilhouetteShader2D>("SilhouetteShader2D");
	silhouetteShader->Initialize(shaderPath + "Silhouette2D.vert", shaderPath + "Silhouette2D.frag");
	shaderMaps_.insert({ "SilhouetteShader2D", silhouetteShader });

	OutlineShader2D* outlineShader = resourceManager.CreateResource<OutlineShader2D>("OutlineShader2D");
	outlineShader->Initialize(shaderPath + "Outline2D.vert", shaderPath + "Outline2D.frag");
	shaderMaps_.insert({ "OutlineShader2D", outlineShader });
}

void RenderManager::BeginFrame(float red, float green, float blue, float alpha, float depth, uint8_t stencil)
{
	glClearColor(red, green, blue, alpha);
	glClearDepth(depth);
	glClearStencil(stencil);

	GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT), "failed to clear bitplane area of the window...");
}

void RenderManager::EndFrame()
{
	glfwSwapBuffers(window_->GetWindowPtr());
}

void RenderManager::SetVsyncMode(bool bIsEnable)
{
	glfwSwapInterval(static_cast<int32_t>(bIsEnable));
}

void RenderManager::SetDepthMode(bool bIsEnable)
{
	if (bIsEnable)
	{
		GL_ASSERT(glEnable(GL_DEPTH_TEST), "failed to enable depth test...");
	}
	else
	{
		GL_ASSERT(glDisable(GL_DEPTH_TEST), "failed to disable depth test...");
	}
}

void RenderManager::SetStencilMode(bool bIsEnable)
{
	if (bIsEnable)
	{
		GL_ASSERT(glEnable(GL_STENCIL_TEST), "failed to enable stencil test...");
	}
	else
	{
		GL_ASSERT(glDisable(GL_STENCIL_TEST), "failed to disable stencil test...");
	}
}

void RenderManager::SetAlphaBlend(bool bIsEnable)
{
	if (bIsEnable)
	{
		GL_ASSERT(glEnable(GL_BLEND), "failed to enable alpha blend...");
		GL_ASSERT(glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO), "failed to Separate blend func...");
	}
	else
	{
		GL_ASSERT(glDisable(GL_BLEND), "failedto disable alpha blend...");
	}
}

void RenderManager::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
	GL_ASSERT(glViewport(x, y, width, height), "invalid viewport parameter : x=%d, y=%d, w=%d, h=%d", x, y, width, height);
}

void RenderManager::DrawPoints2D(const std::vector<Vector2f>& positions, const Vector4f& color, float pointSize)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawPoints2D(screenOrtho_, positions, color, pointSize);
}

void RenderManager::DrawConnectPoints2D(const std::vector<Vector2f>& positions, const Vector4f& color)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawConnectPoints2D(screenOrtho_, positions, color);
}

void RenderManager::DrawLine2D(const Vector2f& fromPosition, const Vector2f& toPosition, const Vector4f& color)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawLine2D(screenOrtho_, fromPosition, toPosition, color);
}

void RenderManager::DrawLine2D(const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& toPosition, const Vector4f& toColor)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawLine2D(screenOrtho_, fromPosition, fromColor, toPosition, toColor);
}

void RenderManager::DrawTriangle2D(const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawTriangle2D(screenOrtho_, fromPosition, byPosition, toPosition, color);
}

void RenderManager::DrawTriangle2D(const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& byPosition, const Vector4f& byColor, const Vector2f& toPosition, const Vector4f& toColor)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawTriangle2D(screenOrtho_, 
		fromPosition, fromColor, 
		byPosition, byColor, 
		toPosition, toColor
	);
}

void RenderManager::DrawWireframeTriangle2D(const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawWireframeTriangle2D(screenOrtho_, fromPosition, byPosition, toPosition, color);
}

void RenderManager::DrawWireframeTriangle2D(const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& byPosition, const Vector4f& byColor, const Vector2f& toPosition, const Vector4f& toColor)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawWireframeTriangle2D(screenOrtho_, fromPosition, fromColor, byPosition, byColor, toPosition, toColor);
}

void RenderManager::DrawRectangle2D(const Vector2f& center, float width, float height, float rotate, const Vector4f& color)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawRectangle2D(screenOrtho_, center, width, height, rotate, color);
}

void RenderManager::DrawWireframeRectangle2D(const Vector2f& center, float width, float height, float rotate, const Vector4f& color)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawWireframeRectangle2D(screenOrtho_, center, width, height, rotate, color);
}

void RenderManager::DrawCircle2D(const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawCircle2D(screenOrtho_, center, radius, color, sliceCount);
}

void RenderManager::DrawWireframeCircle2D(const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawWireframeCircle2D(screenOrtho_, center, radius, color, sliceCount);
}

void RenderManager::DrawEllipse2D(const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawEllipse2D(screenOrtho_, center, xAxis, yAxis, color, sliceCount);
}

void RenderManager::DrawWireframeEllipse2D(const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawWireframeEllipse2D(screenOrtho_, center, xAxis, yAxis, color, sliceCount);
}

void RenderManager::DrawGrid2D(float minX, float maxX, float strideX, float minY, float maxY, float strideY, const Vector4f& color)
{
	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderMaps_["GeometryShader2D"]);
	shader->DrawGrid2D(screenOrtho_, minX, maxX, strideX, minY, maxY, strideY, color);
}

void RenderManager::DrawTexture2D(Texture2D* texture, const Vector2f& center, float width, float height, float rotate, float transparent)
{
	TextureShader2D* shader = reinterpret_cast<TextureShader2D*>(shaderMaps_["TextureShader2D"]);
	shader->DrawTexture2D(screenOrtho_, texture, center, width, height, rotate, transparent);
}

void RenderManager::DrawTexture2D(Texture2D* texture, float transparent)
{
	TextureShader2D* shader = reinterpret_cast<TextureShader2D*>(shaderMaps_["TextureShader2D"]);
	shader->DrawTexture2D(texture, transparent);
}

void RenderManager::DrawHorizonScrollTexture2D(Texture2D* texture, float rate, float transparent)
{
	TextureShader2D* shader = reinterpret_cast<TextureShader2D*>(shaderMaps_["TextureShader2D"]);
	shader->DrawHorizonScrollTexture2D(texture, rate, transparent);
}

void RenderManager::DrawHorizonScrollTexture2D(Texture2D* texture, const Vector2f& center, float width, float height, float rate, float transparent)
{
	TextureShader2D* shader = reinterpret_cast<TextureShader2D*>(shaderMaps_["TextureShader2D"]);
	shader->DrawHorizonScrollTexture2D(screenOrtho_, texture, center, width, height, rate, transparent);
}

void RenderManager::DrawVerticalScrollTexture2D(Texture2D* texture, float rate, float transparent)
{
	TextureShader2D* shader = reinterpret_cast<TextureShader2D*>(shaderMaps_["TextureShader2D"]);
	shader->DrawVerticalScrollTexture2D(texture, rate, transparent);
}

void RenderManager::DrawVerticalScrollTexture2D(Texture2D* texture, const Vector2f& center, float width, float height, float rate, float transparent)
{
	TextureShader2D* shader = reinterpret_cast<TextureShader2D*>(shaderMaps_["TextureShader2D"]);
	shader->DrawVerticalScrollTexture2D(screenOrtho_, texture, center, width, height, rate, transparent);
}

void RenderManager::DrawText2D(TTFont* font, const std::wstring& text, const Vector2f& center, const Vector4f& color)
{
	GlyphShader2D* shader = reinterpret_cast<GlyphShader2D*>(shaderMaps_["GlyphShader2D"]);
	shader->DrawText2D(screenOrtho_, font, text, center, color);
}

void RenderManager::DrawTextureSilhouette2D(Texture2D* texture, const Vector2f& center, float width, float height, float rotate, const Vector3f& silhouetteRGB, float transparent)
{
	SilhouetteShader2D* silhouetteShader = reinterpret_cast<SilhouetteShader2D*>(shaderMaps_["SilhouetteShader2D"]);
	silhouetteShader->DrawTextureSilhouette2D(
		screenOrtho_,
		texture,
		center,
		width,
		height,
		rotate,
		silhouetteRGB,
		transparent
	);
}

void RenderManager::DrawTextureOutline2D(Texture2D* texture, const Vector2f& center, float width, float height, float rotate, const Vector4f& outline, float transparent)
{
	OutlineShader2D* shader = reinterpret_cast<OutlineShader2D*>(shaderMaps_["OutlineShader2D"]);
	shader->DrawTextureOutline2D(screenOrtho_, texture, center, width, height, rotate, outline, transparent);
}