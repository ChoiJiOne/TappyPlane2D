#include "ObjectGenerator.h"

#include "AssertionMacro.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "MathUtils.h"
#include "StringUtils.h"

ObjectGenerator::~ObjectGenerator()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void ObjectGenerator::Initialize(const Rock::EType& rockType, const float& startXPosition)
{
	ASSERT(!bIsInitialized_, "already initialize object generator object...");

	rockType_ = rockType;
	startXPosition_ = startXPosition;
	countOfRock_ = 0;
	countOfStar_ = 0;

	rocks_ = std::list<Rock*>();
	stars_ = std::list<Star*>();

	bIsInitialized_ = true;
}

void ObjectGenerator::Update(float deltaSeconds)
{
}

void ObjectGenerator::Render()
{
}

void ObjectGenerator::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");
	bIsInitialized_ = false;
}

void ObjectGenerator::GenerateObject()
{
}

void ObjectGenerator::DestroyObject()
{
}
