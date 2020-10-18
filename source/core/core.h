#pragma once
#include <core/script.h>
#include <core/types.h>
#include <core/level.h>
#include <core/entity.h>
#include <core/gui.h>
#include <core/resource_manager.h>

#include <libraries/std.hpp>
#include <libraries/sfml.hpp>
#include <libraries/lua.hpp>

#include "loaders.h"

namespace cap
{
    // Pseudotypes
	using Managers =	map<string, ResourceManager*>;
	using Levels =		map<string, Level*>;
    using Forms =       map<string, GUIForm*>;
    using GUIStack =    vector<GUIForm*>;

	class Core
	{
	public:
		Core() = default;

		// Objects
		static RenderWindow* window;
		static Camera* current_camera;
		static Camera* default_camera;
		static Level* current_level;
		static Clock clock;
		static Time time;
		static float deltaTime;
		static Event event;
		static GUIStack stack_gui;

		// Callbacks
		static LuaRef onSetup;
		static LuaRef onClose;
		static LuaRef onUpdate;

		// Data arrais
		static Managers managers;
		static TilesetMap tilesets;
		static Levels levels;
		static LuaMap properties;
		static Forms forms;

		// Init core
		static void init(int width, int height, const string& title);
		static void initScript(string file);
		static void startLoop();

		// Ìועמהû
		static void setProperty(const string& name, LuaRef value);
		static LuaRef getProperty(const string& name);
		static void setCurrentLevel(Level* level);

		// Resource load methods
		static Level* loadLevel(string name, string loader_type);
		static Tileset* loadTileset(string name, string loader_type);
		static LuaRef loadTilesetsForLevel(string name, string loader_type);

		// Portable core methods
		static void close();

	private:
		static void initClasses();
		static void update();
		static void draw();
		static void eventProcessing();
	};
}

