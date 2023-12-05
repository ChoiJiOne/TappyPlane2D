#include "MainTitle.h"

#include "AssertionMacro.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "StringUtils.h"

MainTitle::~MainTitle()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void MainTitle::Initialize()
{
	int32_t windowWidth = 0;
	int32_t windowHeight = 0;
	RenderManager::Get().GetRenderWindowSize(windowWidth, windowHeight);

	center_ = Vector2f(static_cast<float>(windowWidth) / 2.0f, 200.0f);
	font_ = ResourceManager::Get().GetResource<TTFont>("kenvector_future_100");
	titleText_ = L"Tappy Plane 2D";

	bIsInitialized_ = true;
}

void MainTitle::Update(float deltaSeconds)
{
}

void MainTitle::Render()
{
	RenderManager& renderManager = RenderManager::Get();

	renderManager.DrawText2D(font_, titleText_, Vector2f(center_.x + 5.0f, center_.y + 5.0f), Vector4f(0.5f, 0.5f, 0.5f, 1.0f));
	renderManager.DrawText2D(font_, titleText_, center_, Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
}

void MainTitle::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");
	bIsInitialized_ = false;
}