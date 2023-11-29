#include "ScoreBoard.h"

#include "AssertionMacro.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "MathUtils.h"

#include <stack>

ScoreBoard::~ScoreBoard()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void ScoreBoard::Initialize(const Vector2f& center, const float& numberWidth, const float& numberHeight, const float& numberGap)
{
	ASSERT(!bIsInitialized_, "already initialize rock game object...");

	bIsActive_ = false;

	center_ = center;
	numberWidth_ = numberWidth;
	numberHeight_ = numberHeight;
	numberGap_ = numberGap;

	numberTextureMap_ = {
		{ '0', ResourceManager::Get().GetResource<Texture2D>("number0") },
		{ '1', ResourceManager::Get().GetResource<Texture2D>("number1") },
		{ '2', ResourceManager::Get().GetResource<Texture2D>("number2") },
		{ '3', ResourceManager::Get().GetResource<Texture2D>("number3") },
		{ '4', ResourceManager::Get().GetResource<Texture2D>("number4") },
		{ '5', ResourceManager::Get().GetResource<Texture2D>("number5") },
		{ '6', ResourceManager::Get().GetResource<Texture2D>("number6") },
		{ '7', ResourceManager::Get().GetResource<Texture2D>("number7") },
		{ '8', ResourceManager::Get().GetResource<Texture2D>("number8") },
		{ '9', ResourceManager::Get().GetResource<Texture2D>("number9") },
	};

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

	std::string scoreStr = std::to_string(score_);

	float scoreWidth = numberWidth_ * static_cast<float>(scoreStr.size()) + numberGap_ * static_cast<float>(scoreStr.size() - 1);
	Vector2f center(center_.x - scoreWidth / 2.0f + numberWidth_ / 2.0f, center_.y);

	for (const auto& scoreChar : scoreStr)
	{
		RenderManager::Get().DrawTexture2D(numberTextureMap_.at(scoreChar), center, numberWidth_, numberHeight_, 0.0f);

		center.x += (numberWidth_ + numberGap_);
	}
}

void ScoreBoard::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");
	bIsInitialized_ = false;
}