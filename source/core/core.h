#pragma once
#include <core/Script.h>
#include <core/types.h>
#include <core/Level.h>
#include <core/entity.h>
#include <core/gui.h>

#include <libraries/std.hpp>
#include <libraries/sfml.hpp>
#include <libraries/lua.hpp>

#include <loaders\levelloader.h>
#include <loaders\TiledLoaderCSV.h>

namespace cap
{
    // Pseudotypes
	using LvlLoaders =	map<string, LevelLoader*>;
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
		static float deltaTime;
		static Event event;
        static GUIStack stack_gui;

        // Callbacks
        static LuaRef onSetup;
        static LuaRef onClose;

		// Data arrais
		static LvlLoaders lvl_loaders;
		static Tilesets tilesets;
		static Levels levels;
		static LuaMap properties;
        static Forms forms;

		// Init core
		static void init(int width, int height, const string& title);
		static void initScript(string file);
		static void startLoop();

		// Методы
		static void setProperty(string name, LuaRef value);
		static LuaRef getProperty(string name);
		static Tileset getTilesets(const vector<string>& list);

		// Загрузка ресурсов
		Level* loadLevel(string name, string loader_type);
		LuaRef loadTilesetForLevel(string name, string loader_type);

	private:
        static void initClasses();
		static void update();
		static void draw();
		static void eventProcessing();
	};
}

