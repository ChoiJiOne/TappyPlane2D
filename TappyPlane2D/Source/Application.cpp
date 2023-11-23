#include "EngineManager.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stb_image.h>

#include "GLAssertionMacro.h"

int main(int argc, char* argv[])
{
	EngineManager::Get().Startup();

	RenderManager::Get().SetAlphaBlend(true);
	RenderManager::Get().SetDepthMode(false);

	GLFWwindow* window = EngineManager::Get().GetWindowPtr()->GetWindowPtr();

	std::string resourcePath;
	CommandLineArg::GetStringValue("resource", resourcePath);

	Texture2D* background = ResourceManager::Get().CreateResource<Texture2D>("Background");
	background->Initialize(resourcePath + "Texture\\background.png");

	Texture2D* ground = ResourceManager::Get().CreateResource<Texture2D>("Ground");
	ground->Initialize(resourcePath + "Texture\\groundGrass.png");

	TTFont* font = ResourceManager::Get().CreateResource<TTFont>("Font");
	font->Initialize(resourcePath + "Font\\kenvector_future.ttf", 32, 127, 64.0f);

	std::array<Texture2D*, 5> planes = {
		ResourceManager::Get().CreateResource<Texture2D>("Plane1"),
		ResourceManager::Get().CreateResource<Texture2D>("Plane2"),
		ResourceManager::Get().CreateResource<Texture2D>("Plane3"),
		nullptr,
		nullptr,
	};

	planes[0]->Initialize(resourcePath + "Texture\\planeBlue1.png");
	planes[1]->Initialize(resourcePath + "Texture\\planeBlue2.png");
	planes[2]->Initialize(resourcePath + "Texture\\planeBlue3.png");
	planes[3] = planes[1];
	planes[4] = planes[0];
	float accumulateTime = 0.0f;
	int32_t currentPlaneIndex = 0;

	GameTimer timer;
	timer.Reset();

	while (!glfwWindowShouldClose(window))
	{
		timer.Tick();
		InputManager::Get().Tick();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

		float time = static_cast<float>(glfwGetTime() / 10.0f);
		float value = time - static_cast<float>(static_cast<int32_t>(time));

		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

		RenderManager::Get().DrawHorizonScrollTexture2D(background, static_cast<float>(value));
		RenderManager::Get().DrawHorizonScrollTexture2D(ground, Vector2f(500.0f, 770.0f), 1000.0f, 60.0f, value);

		accumulateTime += timer.GetDeltaSeconds();
		if (accumulateTime >= 0.1f)
		{
			accumulateTime = 0.0f;
			currentPlaneIndex = (currentPlaneIndex + 1) % (planes.size());
		}
		RenderManager::Get().DrawTexture2D(
			planes[currentPlaneIndex],
			Vector2f(500.0f, 400.0f),
			88.0f,
			73.0f,
			0.0f
		);
		 
		if (InputManager::Get().GetMouseButtonPressState(EMouseButton::BUTTON_LEFT) == EPressState::Held)
		{
			RenderManager::Get().PostEffectGaussianBlur(0.5f);
		}

		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}