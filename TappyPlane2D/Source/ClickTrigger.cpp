#include "ClickTrigger.h"

#include "AssertionMacro.h"
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

void ClickTrigger::Initialize(const std::wstring& text, const Vector2f& center)
{
}

void ClickTrigger::Update(float deltaSeconds)
{
}

void ClickTrigger::Render()
{
}

void ClickTrigger::Release()
{
}