#pragma once
#include <libraries/std.hpp>

// Constants
namespace cap
{
	// Дирректории //
	const string CAP_GAMEDATA_DIR = "gamedata/";
	const string CAP_SCRIPTS_DIR = CAP_GAMEDATA_DIR + "scripts/";
	const string CAP_TEXTURES_DIR = CAP_GAMEDATA_DIR + "textures/";
	const string CAP_TILESETS_DIR = CAP_GAMEDATA_DIR + "tilesets/";
	const string CAP_LEVELS_DIR = CAP_GAMEDATA_DIR + "levels/";

	// Типы сущностей //
	enum
	{
		CAP_POINT_ENTITY = 1,
		CAP_RECT_ENTITY,
		CAP_DRAWABLE_ENTTY
	};

	// Типы контейнеров //
	enum
	{
		CAP_TILE_CONTAINER = 1,
		CAP_OBJECT_CONTAINER,
		CAP_GROUP_CONTAINER
	};

	// Widget types //
	enum
	{
		CAP_GUI_FORM = 1,
		CAP_GUI_BUTTON,
		CAP_GUI_LABEL,
		CAP_GUI_TEXT
	};

	// Position and size types //
	enum 
	{
		CAP_RELATIVE_X =			1 << 0,
		CAP_RELATIVE_Y =			1 << 1,
		CAP_INVERSED_X =			1 << 2,
		CAP_INVERSED_Y =			1 << 3,
		CAP_RELATIVE_WIDTH =		1 << 4,
		CAP_RELATIVE_HEIGHT =		1 << 5,
		CAP_CONTENT_WIDTH =			1 << 6,
		CAP_CONTENT_HEIGHT =		1 << 7,

		CAP_RELATIVE_POS =			CAP_RELATIVE_X | CAP_RELATIVE_Y,
		CAP_INVERSED_POS =			CAP_INVERSED_X | CAP_INVERSED_Y,
		CAP_RELATIVE_SIZE =			CAP_RELATIVE_WIDTH | CAP_RELATIVE_HEIGHT,
		CAP_CONTENT_SIZE =			CAP_CONTENT_WIDTH | CAP_CONTENT_HEIGHT
	};

	// Resource types //
	enum
	{
		CAP_RESOURCE_TILESET
	};

	// Managers types //
	enum
	{
		CAP_MANAGER_LEVEL,
	};

	// Devices types
	enum
	{
		CAP_DEVICE_MOUSE =			1 << 0,
		CAP_DEVICE_KEYBOARD =		1 << 1,
		CAP_DEVICE_JOYSTICK =		1 << 2,
		CAP_DEVICE_TOUCHSCREEN =	1 << 3
	};

	// GUI styles list
	enum
	{
		GUI_STYLE_BACKGROUND_COLOR
	};
}