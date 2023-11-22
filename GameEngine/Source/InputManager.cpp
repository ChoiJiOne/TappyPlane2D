#include "InputManager.h"

#include "AssertionMacro.h"
#include "Window.h"

#include <array>

#include <glfw/glfw3.h>

const int32_t NUM_OF_KEY_CODES = 121; // 키 코드 값의 수입니다.
const int32_t NUM_OF_MOUSEBUTTON = 2; // 마우스 버튼의 수입니다.

/**
 * @brief 키 코드 값의 배열입니다.
 */
const std::array<EKeyCode, NUM_OF_KEY_CODES> KEY_CODES = 
{
	EKeyCode::KEY_UNKNOWN,
	EKeyCode::KEY_SPACE,
	EKeyCode::KEY_APOSTROPHE,
	EKeyCode::KEY_COMMA,
	EKeyCode::KEY_MINUS,
	EKeyCode::KEY_PERIOD,
	EKeyCode::KEY_SLASH,
	EKeyCode::KEY_0,
	EKeyCode::KEY_1,
	EKeyCode::KEY_2,
	EKeyCode::KEY_3,
	EKeyCode::KEY_4,
	EKeyCode::KEY_5,
	EKeyCode::KEY_6,
	EKeyCode::KEY_7,
	EKeyCode::KEY_8,
	EKeyCode::KEY_9,
	EKeyCode::KEY_SEMICOLON,
	EKeyCode::KEY_EQUAL,
	EKeyCode::KEY_A,
	EKeyCode::KEY_B,
	EKeyCode::KEY_C,
	EKeyCode::KEY_D,
	EKeyCode::KEY_E,
	EKeyCode::KEY_F,
	EKeyCode::KEY_G,
	EKeyCode::KEY_H,
	EKeyCode::KEY_I,
	EKeyCode::KEY_J,
	EKeyCode::KEY_K,
	EKeyCode::KEY_L,
	EKeyCode::KEY_M,
	EKeyCode::KEY_N,
	EKeyCode::KEY_O,
	EKeyCode::KEY_P,
	EKeyCode::KEY_Q,
	EKeyCode::KEY_R,
	EKeyCode::KEY_S,
	EKeyCode::KEY_T,
	EKeyCode::KEY_U,
	EKeyCode::KEY_V,
	EKeyCode::KEY_W,
	EKeyCode::KEY_X,
	EKeyCode::KEY_Y,
	EKeyCode::KEY_Z,
	EKeyCode::KEY_LEFT_BRACKET,
	EKeyCode::KEY_BACKSLASH,
	EKeyCode::KEY_RIGHT_BRACKET,
	EKeyCode::KEY_GRAVE_ACCENT,
	EKeyCode::KEY_WORLD_1,
	EKeyCode::KEY_WORLD_2,
	EKeyCode::KEY_ESCAPE,
	EKeyCode::KEY_ENTER,
	EKeyCode::KEY_TAB,
	EKeyCode::KEY_BACKSPACE,
	EKeyCode::KEY_INSERT,
	EKeyCode::KEY_DELETE,
	EKeyCode::KEY_RIGHT,
	EKeyCode::KEY_LEFT,
	EKeyCode::KEY_DOWN,
	EKeyCode::KEY_UP,
	EKeyCode::KEY_PAGE_UP,
	EKeyCode::KEY_PAGE_DOWN,
	EKeyCode::KEY_HOME,
	EKeyCode::KEY_END,
	EKeyCode::KEY_CAPS_LOCK,
	EKeyCode::KEY_SCROLL_LOCK,
	EKeyCode::KEY_NUM_LOCK,
	EKeyCode::KEY_PRINT_SCREEN,
	EKeyCode::KEY_PAUSE,
	EKeyCode::KEY_F1,
	EKeyCode::KEY_F2,
	EKeyCode::KEY_F3,
	EKeyCode::KEY_F4,
	EKeyCode::KEY_F5,
	EKeyCode::KEY_F6,
	EKeyCode::KEY_F7,
	EKeyCode::KEY_F8,
	EKeyCode::KEY_F9,
	EKeyCode::KEY_F10,
	EKeyCode::KEY_F11,
	EKeyCode::KEY_F12,
	EKeyCode::KEY_F13,
	EKeyCode::KEY_F14,
	EKeyCode::KEY_F15,
	EKeyCode::KEY_F16,
	EKeyCode::KEY_F17,
	EKeyCode::KEY_F18,
	EKeyCode::KEY_F19,
	EKeyCode::KEY_F20,
	EKeyCode::KEY_F21,
	EKeyCode::KEY_F22,
	EKeyCode::KEY_F23,
	EKeyCode::KEY_F24,
	EKeyCode::KEY_F25,
	EKeyCode::KEY_KP_0,
	EKeyCode::KEY_KP_1,
	EKeyCode::KEY_KP_2,
	EKeyCode::KEY_KP_3,
	EKeyCode::KEY_KP_4,
	EKeyCode::KEY_KP_5,
	EKeyCode::KEY_KP_6,
	EKeyCode::KEY_KP_7,
	EKeyCode::KEY_KP_8,
	EKeyCode::KEY_KP_9,
	EKeyCode::KEY_KP_DECIMAL,
	EKeyCode::KEY_KP_DIVIDE,
	EKeyCode::KEY_KP_MULTIPLY,
	EKeyCode::KEY_KP_SUBTRACT,
	EKeyCode::KEY_KP_ADD,
	EKeyCode::KEY_KP_ENTER,
	EKeyCode::KEY_KP_EQUAL,
	EKeyCode::KEY_LEFT_SHIFT,
	EKeyCode::KEY_LEFT_CONTROL,
	EKeyCode::KEY_LEFT_ALT,
	EKeyCode::KEY_LEFT_SUPER,
	EKeyCode::KEY_RIGHT_SHIFT,
	EKeyCode::KEY_RIGHT_CONTROL,
	EKeyCode::KEY_RIGHT_ALT,
	EKeyCode::KEY_RIGHT_SUPER,
	EKeyCode::KEY_MENU,
};

/**
 * @brief 마우스 버튼의 배열입니다.
 */
const std::array<EMouseButton, NUM_OF_MOUSEBUTTON> MOUSE_BUTTONS = 
{
	EMouseButton::BUTTON_LEFT,
	EMouseButton::BUTTON_RIGHT,
};

void InputManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup input manager...");

	prevKeyStates_ = std::unordered_map<EKeyCode, int32_t>();
	currKeyStates_ = std::unordered_map<EKeyCode, int32_t>();

	for (const auto& keyCode : KEY_CODES)
	{
		prevKeyStates_.insert({ keyCode , 0 });
		currKeyStates_.insert({ keyCode , 0 });
	}

	prevMouseButtonStates_ = std::unordered_map<EMouseButton, int32_t>();
	currMouseButtonStates_ = std::unordered_map<EMouseButton, int32_t>();

	for (const auto& mouseButton : MOUSE_BUTTONS)
	{
		prevMouseButtonStates_.insert({ mouseButton, 0 });
		currMouseButtonStates_.insert({ mouseButton, 0 });
	}

	bIsStartup_ = true;
}

void InputManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");
	window_ = nullptr;
	bIsStartup_ = false;
}

void InputManager::PreStartup(Window* window)
{
	ASSERT(window != nullptr, "invalid window pointer...");
	window_ = window;
}

void InputManager::Tick()
{
	glfwPollEvents();

	GLFWwindow* window = window_->GetWindowPtr();
	for (const auto& keyCode : KEY_CODES)
	{
		prevKeyStates_[keyCode] = currKeyStates_[keyCode];
		currKeyStates_[keyCode] = glfwGetKey(window, static_cast<int32_t>(keyCode));
	}

	for (const auto& mouseButton : MOUSE_BUTTONS)
	{
		prevMouseButtonStates_[mouseButton] = currMouseButtonStates_[mouseButton];
		currMouseButtonStates_[mouseButton] = glfwGetMouseButton(window, static_cast<int32_t>(mouseButton));
	}
}

EPressState InputManager::GetKeyPressState(const EKeyCode& keyCode) const
{
	EPressState state = EPressState::None;

	if (prevKeyStates_.at(keyCode))
	{
		if (currKeyStates_.at(keyCode))
		{
			state = EPressState::Held;
		}
		else
		{
			state = EPressState::Released;
		}
	}
	else
	{
		if (currKeyStates_.at(keyCode))
		{
			state = EPressState::Pressed;
		}
		else
		{
			state = EPressState::None;
		}
	}

	return state;
}

EPressState InputManager::GetMouseButtonPressState(const EMouseButton& mouseButton) const
{
	EPressState state = EPressState::None;

	if (prevMouseButtonStates_.at(mouseButton))
	{
		if (currMouseButtonStates_.at(mouseButton))
		{
			state = EPressState::Held;
		}
		else
		{
			state = EPressState::Released;
		}
	}
	else
	{
		if (currMouseButtonStates_.at(mouseButton))
		{
			state = EPressState::Pressed;
		}
		else
		{
			state = EPressState::None;
		}
	}

	return state;
}

Vector2f InputManager::GetCurrentMousePosition() const
{
	double x = 0.0;
	double y = 0.0;
	glfwGetCursorPos(window_->GetWindowPtr(), &x, &y);

	return Vector2f(static_cast<float>(x), static_cast<float>(y));
}