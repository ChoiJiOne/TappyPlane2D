#include "EngineManager.h"

#include "Background.h"
#include "Ground.h"

void DrawObject(const AABB& object, const Vector4f& color)
{
	Vector2f size = object.GetMaxPosition() - object.GetMinPosition();
	
	Vector2f center = object.GetMinPosition() + Vector2f(size.x / 2.0f, size.y / 2.0f);
	float width = size.x;
	float height = size.y;

	RenderManager::Get().DrawWireframeRectangle2D(center, width, height, 0.0f, color);
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

	Vector2f center0 = Vector2f(500.0f, 0.0f);
	AABB object0(center0, 100.0f, 100.0f);

	Vector2f center1 = Vector2f(500.0f, 800.0f);
	AABB object1(center1, 100.0f, 100.0f);
	
	while (!InputManager::Get().ShouldCloseWindow())
	{
		globalTimer.Tick();
		InputManager::Get().Tick();

		background->Update(globalTimer.GetDeltaSeconds());
		bottomGround->Update(globalTimer.GetDeltaSeconds());
		topGround->Update(globalTimer.GetDeltaSeconds());

		center0.y += 100.0f * globalTimer.GetDeltaSeconds();
		center1.y -= 100.0f * globalTimer.GetDeltaSeconds();

		object0.SetProperty(center0, 100.0f, 100.0f);
		object1.SetProperty(center1, 100.0f, 100.0f);
		
		RenderManager::Get().SetViewport(0, 0, 1000, 800);
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		
		background->Render();
		bottomGround->Render();
		topGround->Render();

		if (object0.IsCollision(&object1))
		{
			DrawObject(object0, Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
			DrawObject(object1, Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else
		{
			DrawObject(object0, Vector4f(0.0f, 0.0f, 1.0f, 1.0f));
			DrawObject(object1, Vector4f(0.0f, 0.0f, 1.0f, 1.0f));
		}

		RenderManager::Get().EndFrame();
	}

	EngineManager::Get().Shutdown();
	return 0;
}