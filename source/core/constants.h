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
		CAP_GUI_LABEL
	};

	// Value type //
	enum
	{
		CAP_VALUE_RELATIVE,
		CAP_VALUE_ABSOLUTE
	};

	// Resource types //
	enum
	{
		CAP_RESOURCE_TILESET
	};

	// Managers type //
	enum
	{
		CAP_MANAGER_LEVEL,
		CAP_MANAGER_TILESET
	};
}