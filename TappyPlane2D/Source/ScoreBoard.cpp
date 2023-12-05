#include "ScoreBoard.h"

#include "AssertionMacro.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "MathUtils.h"

ScoreBoard::~ScoreBoard()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void ScoreBoard::Initialize(const Vector2f& center, const Vector4f& color)
{
	bIsActive_ = false;

	center_ = center;
	score_ = 0;
	color_ = color;
	font_ = ResourceManager::Get().GetResource<TTFont>("kenvector_future_128");

	bIsInitialized_ = true;
}

void ScoreBoard::Update(float deltaSeconds)
{
	if (!bIsActive_)
	{
		return;
	}
}

void ScoreBoard::Render()
{
	if (!bIsActive_)
	{
		return;
	}

	std::wstring score = std::to_wstring(score_);
	RenderManager::Get().DrawText2D(font_, score, center_, color_);
}

void ScoreBoard::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");
	bIsInitialized_ = false;
}