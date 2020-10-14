#pragma once
#include <core/Script.h>
#include <core/types.h>
#include <core/Level.h>
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
		static View* camera;
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

		// Методы
		static void setProperty(const string& name, LuaRef value);
		static LuaRef getProperty(const string& name);

		// Загрузка ресурсов
		static Level* loadLevel(string name, string loader_type);
		static Tileset* loadTileset(string name, string loader_type);
		static vector<Tileset*> loadTilesetsForLevel(string name, string loader_type);

	private:
        static void initClasses();
		static void update();
		static void draw();
		static void eventProcessing();
	};
}

