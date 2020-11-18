#include <core/input.h>

namespace cap
{
	map<Mouse::Button, bool>	Input::m_mouse_clicked;
	map<Keyboard::Key, bool>	Input::m_keyboard_clicked;
	Window*						Input::window = nullptr;

	bool Input::isKeyboardPressed(int button)
	{
		return Keyboard::isKeyPressed(Keyboard::Key(button));
	}

	bool Input::isKeyboardReleased(int button)
	{
		return !isKeyboardPressed(button);
	}

	bool Input::isKeyboardClicked(int button)
	{
		Keyboard::Key key = Keyboard::Key(button);
		bool has_button = (m_keyboard_clicked.find(key) != m_keyboard_clicked.end());

		if (Keyboard::isKeyPressed(key) && !has_button)
		{
			return m_keyboard_clicked[key] = true;
		}
		else if (!Keyboard::isKeyPressed(key) && has_button)
		{
			m_keyboard_clicked.erase(key);
		}
		else if (has_button)
		{
			return m_keyboard_clicked[key];
		}
		return false;
	}

	Point Input::getMousePosition(bool absolute)
	{
		Point pos = Mouse::getPosition(*window);
		if (absolute)
		{
			View cam = static_cast<RenderWindow*>(window)->getView();
			Point cam_center = cam.getCenter();
			Point cam_size = cam.getSize();

			pos = pos + cam_center - cam_size / 2;
		}

		return pos;
	}

	bool Input::isMousePressed(int button)
	{
		return Mouse::isButtonPressed(Mouse::Button(button));
	}

	bool Input::isMouseReleased(int button)
	{
		return !isMousePressed(button);
	}

	bool Input::isMouseClicked(int button)
	{
		Mouse::Button key = Mouse::Button(button);
		bool has_button = (m_mouse_clicked.find(key) != m_mouse_clicked.end());

		if (Mouse::isButtonPressed(key) && !has_button)
		{
			return m_mouse_clicked[key] = true;
		}
		else if (!Mouse::isButtonPressed(key) && has_button)
		{
			m_mouse_clicked.erase(key);
		}
		else if (has_button)
		{
			return m_mouse_clicked[key];
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

	void Input::update()
	{
		for (auto p : m_mouse_clicked)
		{
			m_mouse_clicked[p.first] = false;
		}

		for (auto p : m_keyboard_clicked)
		{
			m_keyboard_clicked[p.first] = false;
		}
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