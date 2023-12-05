#include "ObjectScheduler.h"
#include "Background.h"
#include "Plane.h"
#include "Rock.h"
#include "Star.h"

#include "AssertionMacro.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "MathUtils.h"
#include "StringUtils.h"

ObjectScheduler::~ObjectScheduler()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void ObjectScheduler::Initialize(const Rock::EType& rockType, const float& startXPosition, const int32_t& countMaxObject)
{
	bIsActive_ = false;
	rockType_ = rockType;
	startXPosition_ = startXPosition;
	interval_ = 300.0f;
	countMaxObject_ = countMaxObject;

	rocks_ = std::vector<Rock*>();
	stars_ = std::vector<Star*>();

	for (int32_t count = 0; count < countMaxObject_; ++count)
	{
		Rock* rock = ObjectManager::Get().CreateGameObject<Rock>(StringUtils::PrintF("Rock%d", count));
		rock->Initialize(rockType_, startXPosition_);
		rocks_.push_back(rock);

		Star* star = ObjectManager::Get().CreateGameObject<Star>(StringUtils::PrintF("Star%d", count));
		star->Initialize(rock->GetEmptyMiddlePoint());
		stars_.push_back(star);
	}
	
	bIsInitialized_ = true;
}

void ObjectScheduler::Update(float deltaSeconds)
{
	if (!bIsActive_) return;

	for (auto& rock : rocks_)
	{
		rock->Update(deltaSeconds);
	}

	for (auto& star : stars_)
	{
		star->Update(deltaSeconds);
	}

	for (int32_t count = 0; count < countMaxObject_; ++count)
	{
		if (rocks_[count]->GetState() == Rock::EState::Wait && CanChangeWaitToMove(count))
		{
			rocks_[count]->SetState(Rock::EState::Move);
			stars_[count]->SetState(Star::EState::Move);
		}
		else if (rocks_[count]->GetState() == Rock::EState::Move && CheckOuterFromBackground(count))
		{
			rocks_[count]->SetupProperties();
			stars_[count]->SetupProperties(rocks_[count]->GetEmptyMiddlePoint());
		}
	}
}

void ObjectScheduler::Render()
{
	for (auto& rock : rocks_)
	{
		rock->Render();
	}

	for (auto& star : stars_)
	{
		star->Render();
	}
}

void ObjectScheduler::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	for (int32_t count = 0; count < countMaxObject_; ++count)
	{
		ObjectManager::Get().DestroyGameObject(StringUtils::PrintF("Rock%d", count));
		ObjectManager::Get().DestroyGameObject(StringUtils::PrintF("Star%d", count));
	}

	bIsInitialized_ = false;
}

Star* ObjectScheduler::GetCollisionStar(const Plane* plane)
{
	for (auto& star : stars_)
	{
		if(star->IsCollisionPlane(plane))
		{
			return star;
		}
	}

	return nullptr;
}

bool ObjectScheduler::IsCollisionRocks(const Plane* plane)
{
	for (auto& rock : rocks_)
	{
		if (rock->IsCollisionPlane(plane))
		{
			return true;
		}
	}

	return false;
}

bool ObjectScheduler::CanChangeWaitToMove(int32_t index)
{
	ASSERT(index >= 0 && index < countMaxObject_, "out of range index in object scheduler : %d", index);
	ASSERT(rocks_[index]->GetState() == Rock::EState::Wait, "%d object scheduler is not wait state...", index);

	Vector2f middlePoint = rocks_[index]->GetEmptyMiddlePoint();
	for (int32_t count = 0; count < countMaxObject_; ++count)
	{
		if (count == index) continue;

		Vector2f otherMiddlePoint = rocks_[count]->GetEmptyMiddlePoint();
	
		if (rocks_[count]->GetState() == Rock::EState::Move)
		{
			if (rocks_[count]->IsCollisionRock(rocks_[index]))
			{
				return false;
			}
			else
			{
				if (std::abs(middlePoint.x - otherMiddlePoint.x) <= interval_)
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool ObjectScheduler::CheckOuterFromBackground(int32_t index)
{
	ASSERT(index >= 0 && index < countMaxObject_, "out of range index in object scheduler : %d", index);
	ASSERT(rocks_[index]->GetState() == Rock::EState::Move, "%d object scheduler is not wait state...", index);

	Vector2f middlePoint = rocks_[index]->GetEmptyMiddlePoint();
	Background* background = ObjectManager::Get().GetGameObject<Background>("Background");

	return background->IsOuterRock(rocks_[index]) && middlePoint.x <= 0.0f;
}