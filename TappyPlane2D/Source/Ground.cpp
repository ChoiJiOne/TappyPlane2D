#include "Ground.h"

#include "AssertionMacro.h"
#include "CommandLineArg.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "MathUtils.h"

Ground::~Ground()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Ground::Initialize(const EType& type)
{
	ASSERT(!bIsInitialized_, "already initialize ground game object...");

	type_ = type;

	int32_t windowWidth = 0;
	int32_t windowHeight = 0;
	RenderManager::Get().GetRenderWindowSize(windowWidth, windowHeight);

	width_ = static_cast<float>(windowWidth);
	height_ = static_cast<float>(windowHeight) / 10.0f;

	std::string resourcePath;
	CommandLineArg::GetStringValue("resource", resourcePath);

	ResourceManager& manager = ResourceManager::Get();
	switch (type_)
	{
	case EType::Bottom:
		texture_ = manager.GetResource<Texture2D>("BottomGround");
		if (!texture_)
		{
			texture_ = manager.CreateResource<Texture2D>("BottomGround");
			texture_->Initialize(resourcePath + "Texture\\groundGrass.png");
		}

		rotate_ = 0.0f;
		center_ = Vector2f(width_ / 2.0f, static_cast<float>(windowHeight) - height_ / 2.0f);
		break;

	case EType::Top:
		texture_ = manager.GetResource<Texture2D>("TopGround");
		if (!texture_)
		{
			texture_ = manager.CreateResource<Texture2D>("TopGround");
			texture_->Initialize(resourcePath + "Texture\\groundDirt.png");
		}

		rotate_ = MathUtils::Pi;
		center_ = Vector2f(width_ / 2.0f, height_ / 2.0f);
		break;

	default:
		ASSERT(false, "undefined ground type : %d", static_cast<int32_t>(type));
	}
	
	scrollSpeed_ = 200.0f;
	scrollPosition_ = 0.0f;

	bIsInitialized_ = true;
}

void Ground::Update(float deltaSeconds)
{
	scrollPosition_ += scrollSpeed_ * deltaSeconds;

	if (scrollPosition_ >= width_)
	{
		scrollPosition_ -= width_;
	}
}

void Ground::Render()
{
	float rate = scrollPosition_ / width_;

	if (type_ == EType::Top)
	{
		rate = 1.0f - rate;
	}

	RenderManager::Get().DrawHorizonScrollTexture2D(texture_, center_, width_, height_, rotate_, rate);
}

void Ground::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");
	bIsInitialized_ = false;
}