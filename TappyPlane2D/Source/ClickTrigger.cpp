#include "ClickTrigger.h"

#include "AssertionMacro.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "StringUtils.h"

ClickTrigger::~ClickTrigger()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void ClickTrigger::Initialize(const std::wstring& text, const Vector2f& center, const Vector4f& color, const std::function<void()>& trigger)
{
	bIsClick_ = false;
	text_ = text;
	color_ = color;
	center_ = center;
	trigger_ = trigger;
	font_ = ResourceManager::Get().GetResource<TTFont>("kenvector_future_32");

	bIsInitialized_ = true;
}

void ClickTrigger::Update(float deltaSeconds)
{
	InputManager& inputManager = InputManager::Get();

	if (inputManager.GetMouseButtonPressState(EMouseButton::BUTTON_LEFT) == EPressState::Pressed ||
		inputManager.GetMouseButtonPressState(EMouseButton::BUTTON_RIGHT) == EPressState::Pressed)
	{
		trigger_();
		bIsClick_ = true;
	}
}

void ClickTrigger::Render()
{
	if (!bIsClick_)
	{
		RenderManager::Get().DrawText2D(font_, text_, center_, color_);
	}
}

void ClickTrigger::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");
	bIsInitialized_ = false;
}