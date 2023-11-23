#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>

#include "IManager.h"
#include "SingletonMacro.h"
#include "Vector2.h"

class Window; // 윈도우 클래스를 사용하기 위한 전방 선언입니다.


/**
 * @brief 입력 상태를 나타냅니다.
 *
 * @note 프레임에 따른 입력 상태입니다.
 * ---------------------------------------
 * | 이전 프레임 | 현재 프레임 | 입력 상태 |
 * ---------------------------------------
 * |     0      |     0      | None       |
 * |     0      |     1      | Pressed    |
 * |     1      |     0      | Released   |
 * |     1      |     1      | Held       |
 * ---------------------------------------
 */
enum class EPressState : int32_t
{
	None = 0x00,
	Pressed = 0x01,
	Released = 0x02,
	Held = 0x03
};


/**
 * @brief 키 코드 값입니다.
 * 
 * @note GLFW 키 코드 값과 일대일 대응합니다.
 */
enum class EKeyCode : int32_t
{
	KEY_UNKNOWN = -1,
	KEY_SPACE = 32,
	KEY_APOSTROPHE = 39,
	KEY_COMMA = 44,
	KEY_MINUS = 45,
	KEY_PERIOD = 46,
	KEY_SLASH = 47,
	KEY_0 = 48,
	KEY_1 = 49,
	KEY_2 = 50,
	KEY_3 = 51,
	KEY_4 = 52,
	KEY_5 = 53,
	KEY_6 = 54,
	KEY_7 = 55,
	KEY_8 = 56,
	KEY_9 = 57,
	KEY_SEMICOLON = 59,
	KEY_EQUAL = 61,
	KEY_A = 65,
	KEY_B = 66,
	KEY_C = 67,
	KEY_D = 68,
	KEY_E = 69,
	KEY_F = 70,
	KEY_G = 71,
	KEY_H = 72,
	KEY_I = 73,
	KEY_J = 74,
	KEY_K = 75,
	KEY_L = 76,
	KEY_M = 77,
	KEY_N = 78,
	KEY_O = 79,
	KEY_P = 80,
	KEY_Q = 81,
	KEY_R = 82,
	KEY_S = 83,
	KEY_T = 84,
	KEY_U = 85,
	KEY_V = 86,
	KEY_W = 87,
	KEY_X = 88,
	KEY_Y = 89,
	KEY_Z = 90,
	KEY_LEFT_BRACKET = 91,
	KEY_BACKSLASH = 92,
	KEY_RIGHT_BRACKET = 93,
	KEY_GRAVE_ACCENT = 96,
	KEY_WORLD_1 = 161,
	KEY_WORLD_2 = 162,
	KEY_ESCAPE = 256,
	KEY_ENTER = 257,
	KEY_TAB = 258,
	KEY_BACKSPACE = 259,
	KEY_INSERT = 260,
	KEY_DELETE = 261,
	KEY_RIGHT = 262,
	KEY_LEFT = 263,
	KEY_DOWN = 264,
	KEY_UP = 265,
	KEY_PAGE_UP = 266,
	KEY_PAGE_DOWN = 267,
	KEY_HOME = 268,
	KEY_END = 269,
	KEY_CAPS_LOCK = 280,
	KEY_SCROLL_LOCK = 281,
	KEY_NUM_LOCK = 282,
	KEY_PRINT_SCREEN = 283,
	KEY_PAUSE = 284,
	KEY_F1 = 290,
	KEY_F2 = 291,
	KEY_F3 = 292,
	KEY_F4 = 293,
	KEY_F5 = 294,
	KEY_F6 = 295,
	KEY_F7 = 296,
	KEY_F8 = 297,
	KEY_F9 = 298,
	KEY_F10 = 299,
	KEY_F11 = 300,
	KEY_F12 = 301,
	KEY_F13 = 302,
	KEY_F14 = 303,
	KEY_F15 = 304,
	KEY_F16 = 305,
	KEY_F17 = 306,
	KEY_F18 = 307,
	KEY_F19 = 308,
	KEY_F20 = 309,
	KEY_F21 = 310,
	KEY_F22 = 311,
	KEY_F23 = 312,
	KEY_F24 = 313,
	KEY_F25 = 314,
	KEY_KP_0 = 320,
	KEY_KP_1 = 321,
	KEY_KP_2 = 322,
	KEY_KP_3 = 323,
	KEY_KP_4 = 324,
	KEY_KP_5 = 325,
	KEY_KP_6 = 326,
	KEY_KP_7 = 327,
	KEY_KP_8 = 328,
	KEY_KP_9 = 329,
	KEY_KP_DECIMAL = 330,
	KEY_KP_DIVIDE = 331,
	KEY_KP_MULTIPLY = 332,
	KEY_KP_SUBTRACT = 333,
	KEY_KP_ADD = 334,
	KEY_KP_ENTER = 335,
	KEY_KP_EQUAL = 336,
	KEY_LEFT_SHIFT = 340,
	KEY_LEFT_CONTROL = 341,
	KEY_LEFT_ALT = 342,
	KEY_LEFT_SUPER = 343,
	KEY_RIGHT_SHIFT = 344,
	KEY_RIGHT_CONTROL = 345,
	KEY_RIGHT_ALT = 346,
	KEY_RIGHT_SUPER = 347,
	KEY_MENU = 348,
};


/**
 * @brief 마우스 버튼 종류 열거형입니다.
 */
enum class EMouseButton : int32_t
{
	BUTTON_LEFT = 0x00,
	BUTTON_RIGHT = 0x01,
};


/**
 * @brief 윈도우 이벤트에 대한 열거형입니다.
 */
enum class EWindowEvent : int32_t
{
	None = 0x00,
	Move = 0x01,
	ResizeWindow = 0x02,
	Close = 0x03,
	Refresh = 0x04,
	GainFocus = 0x05,
	LostFocus = 0x06,
	EnterMinimize = 0x07,
	ExitMinimize = 0x08,
	EnterMaximize = 0x09,
	ExitMaximize = 0x0A,
	ResizeFramebuffer = 0x0B,
	ChangeDisplay = 0x0C,
};


/**
 * @biref 입력 처리를 수행하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class InputManager : public IManager
{
	SINGLETON(InputManager);


public:
	/**
	 * @brief 입력 처리를 수행하는 매니저의 사용을 시작합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 입력 처리를 수행하는 매니저의 사용을 종료합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 입력 처리를 수행하는 매니저의 사용 전 설정을 수행합니다.
	 * 
	 * @param window 입력 처리를 수행할 윈도우 포인터입니다.
	 */
	void PreStartup(Window* window);


	/**
	 * @brief 입력 상태를 업데이트 합니다.
	 */
	void Tick();


	/**
	 * @brief 키 입력 상태를 얻습니다.
	 *
	 * @param keyCode 입력 상태를 얻을 키 코드 값입니다.
	 *
	 * @return 키 입력 상태를 반환합니다.
	 */
	EPressState GetKeyPressState(const EKeyCode& keyCode) const;


	/**
	 * @brief 마우스 버튼의 입력 상태를 얻습니다.
	 *
	 * @param mouseButton 입력 상태를 얻을 마우스 버튼입니다.
	 *
	 * @return 마우스 버튼의 입력 상태를 반환합니다.
	 */
	EPressState GetMouseButtonPressState(const EMouseButton& mouseButton) const;


	/**
	 * @brief 마우스의 현재 위치를 얻습니다.
	 *
	 * @return 마우스의 현재 위치를 반환합니다.
	 */
	Vector2f GetCurrentMousePosition() const;


	/**
	 * @brief 윈도우 이벤트에 동작할 액션을 바인딩합니다.
	 * 
	 * @note
	 * - 시그니처 문자열의 값은 입력 처리 매니저 내에서 유일해야 합니다.
	 * - 윈도우 이벤트는 바인딩할 경우 기본적으로 활성화됩니다. 비활성화하기 위해서는 DisableWindowEventAction 메서드를 호출해야 합니다.
	 *
	 * @param signature 윈도우 이벤트의 시그니처 문자열입니다.
	 * @param windowEvent 동작할 액션에 대응하는 윈도우 이벤트입니다.
	 * @param eventAction 윈도우 이벤트 감지될 경우 실행할 액션입니다.
	 */
	void BindWindowEventAction(const std::string& signature, const EWindowEvent& windowEvent, const std::function<void()>& eventAction);


	/**
	 * @brief 윈도우 이벤트에 동작할 액션의 바인딩을 해제합니다.
	 *
	 * @param signature 바인딩 해제할 윈도우 이벤트의 시그니처 값입니다.
	 */
	void UnbindWindowEventAction(const std::string& signature);


	/**
	 * @brief 윈도우 이벤트를 활성화합니다.
	 * 
	 * @param signature 활성화할 윈도우 이벤트의 시그니처 값입니다.
	 */
	void EnableWindowEventAction(const std::string& signature);


	/**
	 * @brief 윈도우 이벤트를 비활성화합니다.
	 * 
	 * @param signature 비활성화할 윈도우 이벤트의 시그니처 값입니다.
	 * 
	 */
	void DisableWindowEventAction(const std::string& signature);


	/**
	 * @brief 윈도우 이벤트를 처리합니다.
	 *
	 * @note public 필드에 있는 메서드이지만, 외부에서 호출하면 안됩니다.
	 *
	 * @param windowEvent 처리할 윈도우 이밴트입니다.
	 */
	void ProcessWindowEvent(const EWindowEvent& windowEvent);


private:
	/**
	 * @brief 윈도우 이벤트 액션입니다.
	 */
	struct WindowEventAction
	{
		/**
		 * @brief 윈도우 이벤트의 활성화 여부입니다.
		 * 
		 * @note 비활성화되면 이벤트가 감지되어도 액션을 실행하지 않습니다.
		 */
		bool bIsActive;


		/**
		 * @brief 윈도우 이벤트의 열거형입니다.
		 */
		EWindowEvent windowEvent;


		/**
		 * @brief 실행할 윈도우 이벤트입니다.
		 */
		std::function<void()> windowEventAction;
	};


private:
	/**
	 * @brief 입력 처리를 수행할 윈도우입니다.
	 */
	Window* window_ = nullptr;

	
	/**
	 * @brief Tick 호출 이전의 키 코드 값들의 상태입니다.
	 */
	std::unordered_map<EKeyCode, int32_t> prevKeyStates_;


	/**
	 * @brief Tick 호출 이후의 키 코드
	 */
	std::unordered_map<EKeyCode, int32_t> currKeyStates_;


	/**
	 * @brief Tick 호출 이전의 마우스 버튼의 상태입니다.
	 */
	std::unordered_map<EMouseButton, int32_t> prevMouseButtonStates_;


	/**
	 * @brief Tick 호출 이후의 마우스 버튼의 상태입니다.
	 */
	std::unordered_map<EMouseButton, int32_t> currMouseButtonStates_;


	/**
	 * @brief 윈도우 이벤트에 대응하는 액션입니다.
	 */
	std::unordered_map<std::string, WindowEventAction> windowEventActions_;
};