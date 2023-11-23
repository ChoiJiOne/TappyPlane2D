#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>

#include "IManager.h"
#include "SingletonMacro.h"
#include "Vector2.h"

class Window; // ������ Ŭ������ ����ϱ� ���� ���� �����Դϴ�.


/**
 * @brief �Է� ���¸� ��Ÿ���ϴ�.
 *
 * @note �����ӿ� ���� �Է� �����Դϴ�.
 * ---------------------------------------
 * | ���� ������ | ���� ������ | �Է� ���� |
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
 * @brief Ű �ڵ� ���Դϴ�.
 * 
 * @note GLFW Ű �ڵ� ���� �ϴ��� �����մϴ�.
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
 * @brief ���콺 ��ư ���� �������Դϴ�.
 */
enum class EMouseButton : int32_t
{
	BUTTON_LEFT = 0x00,
	BUTTON_RIGHT = 0x01,
};


/**
 * @brief ������ �̺�Ʈ�� ���� �������Դϴ�.
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
 * @biref �Է� ó���� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class InputManager : public IManager
{
	SINGLETON(InputManager);


public:
	/**
	 * @brief �Է� ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief �Է� ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief �Է� ó���� �����ϴ� �Ŵ����� ��� �� ������ �����մϴ�.
	 * 
	 * @param window �Է� ó���� ������ ������ �������Դϴ�.
	 */
	void PreStartup(Window* window);


	/**
	 * @brief �Է� ���¸� ������Ʈ �մϴ�.
	 */
	void Tick();


	/**
	 * @brief Ű �Է� ���¸� ����ϴ�.
	 *
	 * @param keyCode �Է� ���¸� ���� Ű �ڵ� ���Դϴ�.
	 *
	 * @return Ű �Է� ���¸� ��ȯ�մϴ�.
	 */
	EPressState GetKeyPressState(const EKeyCode& keyCode) const;


	/**
	 * @brief ���콺 ��ư�� �Է� ���¸� ����ϴ�.
	 *
	 * @param mouseButton �Է� ���¸� ���� ���콺 ��ư�Դϴ�.
	 *
	 * @return ���콺 ��ư�� �Է� ���¸� ��ȯ�մϴ�.
	 */
	EPressState GetMouseButtonPressState(const EMouseButton& mouseButton) const;


	/**
	 * @brief ���콺�� ���� ��ġ�� ����ϴ�.
	 *
	 * @return ���콺�� ���� ��ġ�� ��ȯ�մϴ�.
	 */
	Vector2f GetCurrentMousePosition() const;


	/**
	 * @brief ������ �̺�Ʈ�� ������ �׼��� ���ε��մϴ�.
	 * 
	 * @note
	 * - �ñ״�ó ���ڿ��� ���� �Է� ó�� �Ŵ��� ������ �����ؾ� �մϴ�.
	 * - ������ �̺�Ʈ�� ���ε��� ��� �⺻������ Ȱ��ȭ�˴ϴ�. ��Ȱ��ȭ�ϱ� ���ؼ��� DisableWindowEventAction �޼��带 ȣ���ؾ� �մϴ�.
	 *
	 * @param signature ������ �̺�Ʈ�� �ñ״�ó ���ڿ��Դϴ�.
	 * @param windowEvent ������ �׼ǿ� �����ϴ� ������ �̺�Ʈ�Դϴ�.
	 * @param eventAction ������ �̺�Ʈ ������ ��� ������ �׼��Դϴ�.
	 */
	void BindWindowEventAction(const std::string& signature, const EWindowEvent& windowEvent, const std::function<void()>& eventAction);


	/**
	 * @brief ������ �̺�Ʈ�� ������ �׼��� ���ε��� �����մϴ�.
	 *
	 * @param signature ���ε� ������ ������ �̺�Ʈ�� �ñ״�ó ���Դϴ�.
	 */
	void UnbindWindowEventAction(const std::string& signature);


	/**
	 * @brief ������ �̺�Ʈ�� Ȱ��ȭ�մϴ�.
	 * 
	 * @param signature Ȱ��ȭ�� ������ �̺�Ʈ�� �ñ״�ó ���Դϴ�.
	 */
	void EnableWindowEventAction(const std::string& signature);


	/**
	 * @brief ������ �̺�Ʈ�� ��Ȱ��ȭ�մϴ�.
	 * 
	 * @param signature ��Ȱ��ȭ�� ������ �̺�Ʈ�� �ñ״�ó ���Դϴ�.
	 * 
	 */
	void DisableWindowEventAction(const std::string& signature);


	/**
	 * @brief ������ �̺�Ʈ�� ó���մϴ�.
	 *
	 * @note public �ʵ忡 �ִ� �޼���������, �ܺο��� ȣ���ϸ� �ȵ˴ϴ�.
	 *
	 * @param windowEvent ó���� ������ �̹�Ʈ�Դϴ�.
	 */
	void ProcessWindowEvent(const EWindowEvent& windowEvent);


private:
	/**
	 * @brief ������ �̺�Ʈ �׼��Դϴ�.
	 */
	struct WindowEventAction
	{
		/**
		 * @brief ������ �̺�Ʈ�� Ȱ��ȭ �����Դϴ�.
		 * 
		 * @note ��Ȱ��ȭ�Ǹ� �̺�Ʈ�� �����Ǿ �׼��� �������� �ʽ��ϴ�.
		 */
		bool bIsActive;


		/**
		 * @brief ������ �̺�Ʈ�� �������Դϴ�.
		 */
		EWindowEvent windowEvent;


		/**
		 * @brief ������ ������ �̺�Ʈ�Դϴ�.
		 */
		std::function<void()> windowEventAction;
	};


private:
	/**
	 * @brief �Է� ó���� ������ �������Դϴ�.
	 */
	Window* window_ = nullptr;

	
	/**
	 * @brief Tick ȣ�� ������ Ű �ڵ� ������ �����Դϴ�.
	 */
	std::unordered_map<EKeyCode, int32_t> prevKeyStates_;


	/**
	 * @brief Tick ȣ�� ������ Ű �ڵ�
	 */
	std::unordered_map<EKeyCode, int32_t> currKeyStates_;


	/**
	 * @brief Tick ȣ�� ������ ���콺 ��ư�� �����Դϴ�.
	 */
	std::unordered_map<EMouseButton, int32_t> prevMouseButtonStates_;


	/**
	 * @brief Tick ȣ�� ������ ���콺 ��ư�� �����Դϴ�.
	 */
	std::unordered_map<EMouseButton, int32_t> currMouseButtonStates_;


	/**
	 * @brief ������ �̺�Ʈ�� �����ϴ� �׼��Դϴ�.
	 */
	std::unordered_map<std::string, WindowEventAction> windowEventActions_;
};