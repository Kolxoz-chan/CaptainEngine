#pragma once
#include <core/constants.h>
#include <core/types.h>

#include <libraries/std.hpp>
#include <libraries/sfml.hpp>

namespace cap
{
	class Input
	{
	private:
		static map<Mouse::Button, bool> m_mouse_clicked;
		static map<Keyboard::Key, bool> m_keyboard_clicked;
		static vector<string> m_mouse_buttons;
		static vector<string> m_keyboard_buttons;

	public:
		Input() = delete;
		~Input() = delete;

		// Keyboard
		static bool isKeyboardPressed(int button);
		static bool isKeyboardReleased(int button);
		static bool isKeyboardClicked(int button);

		// Mouse
		static Point getMousePosition(bool absolute = false);
		static bool isMousePressed(int button);
		static bool isMouseReleased(int button);
		static bool isMouseClicked(int button);

		// Getters
		static const vector<string>& getKeyboardButtons();
		static const vector<string>& getMouseButtons();

		// Other
		static void update();

		// Fields
		static Window* window;
	};
}
