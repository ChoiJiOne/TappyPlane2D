#include "EngineManager.h"

#include "Background.h"
#include "Ground.h"

void DrawCircle(const Circle& circle, const Vector4f& color)
{
	RenderManager::Get().DrawWireframeCircle2D(
		circle.GetCenter(),
		circle.GetRadius(),
		color
	);
}

void DrawLine(const LineSegment& line, const Vector4f& color)
{
	const std::array<Vector2f, 2> points = line.GetPoints();
	RenderManager::Get().DrawLine2D(points[0], points[1], color);
}

int main(int argc, char* argv[])
{
	EngineManager::Get().Startup();

	RenderManager::Get().SetAlphaBlend(true);
	RenderManager::Get().SetDepthMode(false);

	GameTimer globalTimer;
	globalTimer.Reset();

	Background* background = ObjectManager::Get().CreateGameObject<Background>("Background");
	background->Initialize();

	Ground* bottomGround = ObjectManager::Get().CreateGameObject<Ground>("BottomGround");
	bottomGround->Initialize(Ground::EType::Bottom);

	Ground* topGround = ObjectManager::Get().CreateGameObject<Ground>("TopGround");
	topGround->Initialize(Ground::EType::Top);

	//std::array<Vector2f, 2> points = { Vector2f(100.0f, 300.0f), Vector2f(10.0f, 500.0f) };
	//LineSegment line0(points);

	//points = { Vector2f(600.0f, 400.0f), Vector2f(700.0f, 450.0f) };
	//LineSegment line1(points);

	std::array<Vector2f, 2> points = { Vector2f(100.0f, 300.0f), Vector2f(10.0f, 300.0f) };
	LineSegment line0(points);

	points = { Vector2f(600.0f, 300.0f), Vector2f(700.0f, 300.0f) };
	LineSegment line1(points);

	while (!InputManager::Get().ShouldCloseWindow())
	{
		globalTimer.Tick();
		InputManager::Get().Tick();

		background->Update(globalTimer.GetDeltaSeconds());
		bottomGround->Update(globalTimer.GetDeltaSeconds());
		topGround->Update(globalTimer.GetDeltaSeconds());

		std::array<Vector2f, 2>& refPoints0 = line0.GetPoints();
		for (auto& point : refPoints0)
		{
			point.x += 100.0f * globalTimer.GetDeltaSeconds();
		}

		std::array<Vector2f, 2>& refPoints1 = line1.GetPoints();
		for (auto& point : refPoints1)
		{
			point.x -= 100.0f * globalTimer.GetDeltaSeconds();
		}
		
		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		
		background->Render();
		bottomGround->Render();
		topGround->Render();

		if (line0.IsCollision(&line1))
		{
			DrawLine(line0, Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
			DrawLine(line1, Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else
		{
			DrawLine(line0, Vector4f(0.0f, 0.0f, 1.0f, 1.0f));
			DrawLine(line1, Vector4f(0.0f, 0.0f, 1.0f, 1.0f));
		}

		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}