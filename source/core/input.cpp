#include <core/input.h>

namespace cap
{
	vector<bool>		Input::m_mouse_pressed;
	vector<bool>		Input::m_keyboard_pressed;

	void Input::init()
	{
		m_mouse_pressed = vector<bool>(Mouse::ButtonCount, false);
		m_keyboard_pressed = vector<bool>(Keyboard::KeyCount, false);
	}

	bool Input::isKeyboardPressed(int button)
	{
		return m_keyboard_pressed[button] = Keyboard::isKeyPressed(Keyboard::Key(button));
	}

	bool Input::isKeyboardReleased(int button)
	{
		return !isKeyboardPressed(button);
	}

	bool Input::isKeyboardClicked(int button)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key(button)) && !m_keyboard_pressed[button])
		{
			return m_keyboard_pressed[button] = true;
		}
		if (!Keyboard::isKeyPressed(Keyboard::Key(button)) && m_keyboard_pressed[button])
		{
			m_keyboard_pressed[button] = false;
		}
		return false;
	}

	bool Input::isMousePressed(int button)
	{
		return m_mouse_pressed[button] = Mouse::isButtonPressed(Mouse::Button(button));
	}

	bool Input::isMouseReleased(int button)
	{
		return !isMousePressed(button);
	}

	bool Input::isMouseClicked(int button)
	{
		if (Mouse::isButtonPressed(Mouse::Button(button)) && !m_mouse_pressed[button])
		{
			return m_mouse_pressed[button] = true;
		}
		if (!Mouse::isButtonPressed(Mouse::Button(button)) && m_mouse_pressed[button])
		{
			m_mouse_pressed[button] = false;
		}
		return false;
	}

	const vector<string>& Input::getKeyboardButtons()
	{
		return m_keyboard_buttons;
	}

	const vector<string>& Input::getMouseButtons()
	{
		return m_mouse_buttons;
	}

	vector<string> Input::m_mouse_buttons =
	{
		"MB_LEFT",
		"MB_RIGHT",
		"MB_MIDDLE",
		"MB_XBUTTON1",
		"MB_XBUTTON1"
	};

	vector<string> Input::m_keyboard_buttons =
	{
		"KB_A", 
		"KB_B", 
		"KB_C", 
		"KB_D", 
		"KB_E", 
		"KB_F", 
		"KB_G", 
		"KB_H", 
		"KB_I", 
		"KB_J", 
		"KB_K", 
		"KB_L", 
		"KB_M", 
		"KB_N", 
		"KB_O", 
		"KB_P", 
		"KB_Q", 
		"KB_R", 
		"KB_S", 
		"KB_T", 
		"KB_U", 
		"KB_V", 
		"KB_W", 
		"KB_X", 
		"KB_Y", 
		"KB_Z",
		"KB_NUM0",
		"KB_NUM1", 
		"KB_NUM2", 
		"KB_NUM3", 
		"KB_NUM4",
		"KB_NUM5", 
		"KB_NUM6", 
		"KB_NUM7", 
		"KB_NUM8",
		"KB_NUM9",
		"KB_ESCAPE", 
		"KB_LCONTROL", 
		"KB_LSHIFT",
		"KB_LALT", 
		"KB_LSYSTEM", 
		"KB_RCONTROL", 
		"KB_RSHIFT", 
		"KB_RALT", 
		"KB_RSYSTEM", 
		"KB_MENU", 
		"KB_LBRACKET",
		"KB_RBRACKET", 
		"KB_SEMICOLON", 
		"KB_COMMA", 
		"KB_PERIOD",
		"KB_QUOTE", 
		"KB_SLASH", 
		"KB_BACKSLASH", 
		"KB_TILDE", 
		"KB_EQUAL", 
		"KB_HYPEN", 
		"KB_SPACE",
		"KB_ENTER",
		"KB_BACKSPACE", 
		"KB_TAB", 
		"KB_PAGEUP", 
		"KB_PAGEDOWN",
		"KB_END", 
		"KB_HOME", 
		"KB_INSERT", 
		"KB_DELETE",	
		"KB_ADD", 
		"KB_SUBTRACT", 
		"KB_MULTIPLY", 
		"KB_DIVIDE",
		"KB_LEFT", 
		"KB_RIGHT", 
		"KB_UP", 
		"KB_DOWN",
		"KB_NUMPAD0",
		"KB_NUMPAD1", 
		"KB_NUMPAD2", 
		"KB_NUMPAD3", 
		"KB_NUMPAD4", 
		"KB_NUMPAD5", 
		"KB_NUMPAD6", 
		"KB_NUMPAD7",
		"KB_NUMPAD8", 
		"KB_NUMPAD9",
		"KB_F1", 
		"KB_F2",
		"KB_F3", 
		"KB_F4", 
		"KB_F5", 
		"KB_F6",
		"KB_F7", 
		"KB_F8", 
		"KB_F9", 
		"KB_F10",
		"KB_F11", 
		"KB_F12", 
		"KB_F13", 
		"KB_F14",
		"KB_F15",
		"KB_PAUSE"
	};
}