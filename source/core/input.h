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
		static vector<bool> m_mouse_pressed;
		static vector<bool> m_keyboard_pressed;
		static vector<string> m_mouse_buttons;
		static vector<string> m_keyboard_buttons;

	public:
		Input() = delete;
		~Input() = delete;

		static void init();

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

		// Fields
		static Window* window;
	};
}
