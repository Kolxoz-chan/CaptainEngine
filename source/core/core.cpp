#include <core\core.h>
namespace cap
{
	RenderWindow*	Core::window;
	Clock			Core::clock;
	Time			Core::time;
	float			Core::deltaTime = 0.0;
	Camera*			Core::current_camera;
	Camera*			Core::default_camera;
	Event			Core::event;
	Level*			Core::current_level;

	LuaMap			Core::properties;
	Managers		Core::managers;
	TilesetMap		Core::tilesets;
	Levels			Core::levels;
	Forms           Core::forms;
	GUIStack        Core::stack_gui;

    LuaRef          Core::onSetup = 0;
    LuaRef          Core::onClose = 0;
	LuaRef			Core::onUpdate = 0;

	void Core::init(int width, int height, const string& title)
	{
        // Lua init //
        Script::init();

        // Data init //
		window = new RenderWindow(VideoMode(width, height), title);
		default_camera = new Camera();
		default_camera->resize(Point(width, height));
		current_camera = default_camera;

		current_level = nullptr;

		// Init events //
        onSetup = Script::newRef();
        onClose = Script::newRef();
		onUpdate = Script::newRef();

        // GUI init //
		ImGui::SFML::Init(*window);

		//////////////////////////////////////////////////////////////////////////////
        GUIForm* test = new GUIForm();
        test->setTitle("Test form");

		GUILabel* label = new GUILabel();
		label->setTitle("Everlasting Summer");
		test->addWidget(label);

        GUIButton* but1 = new GUIButton();
        but1->setTitle("New game");
        test->addWidget(but1);

        GUIButton* but2 = new GUIButton();
        but2->setTitle("Settings");
        test->addWidget(but2);

        GUIButton* but3 = new GUIButton();
        but3->setTitle("Exit");
		but3->onClick = Script::eval("function() Core.close() end");
        test->addWidget(but3);

        stack_gui.push_back(test);
		///////////////////////////////////////////////////////////////////////////

        // Reset log //
        Script::reset_log("Captain Engine log:");

        // Including plugins //
		managers["TILED_MANAGER"] = new TiledManager();
	}

	void Core::setProperty(const string& name, LuaRef value)
	{
		if (name == "fps")
		{
			window->setFramerateLimit(value);
		}
		else if(name == "window_size")
		{
			window->setSize(value.cast<Point>());
		}
		//properties.set(name, value);
	}

	LuaRef Core::getProperty(const string& name)
	{
		return properties.get(name);
	}

	void Core::setCurrentLevel(Level* level)
	{
		current_level = level;
	}

	void Core::initScript(string file)
    {
        // Class init
        initClasses();

        // Run script
        Script::include(CAP_SCRIPTS_DIR + file + ".lua");
		
        // Call onSetup
        if(onSetup.isFunction()) onSetup();
	}

	void Core::eventProcessing()
	{
		while (window->pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
            if (event.type == Event::Closed)
            {
				if (onClose.isFunction())
				{
					LuaRef result = onClose();
					if (result.isNil() || result == true) window->close();
				}
				else window->close();
            }
			else if (event.type == Event::Resized)
			{
				Point size = Point(window->getSize());
				size.x -= int(size.x) % 2;
				size.y -= int(size.y) % 2;
				window->setSize(size);
				
				if (current_camera)
				{
					default_camera->resize(size);
				}
			}
		}
	}

	void Core::startLoop()
	{
		while (window->isOpen())
		{
			// Time reset
			time = clock.restart();
			deltaTime = time.asSeconds();

			eventProcessing();
			update();
			draw();
		}
		ImGui::SFML::Shutdown();
	}

	void Core::update()
	{
		current_camera->move(0, 1);
		current_camera->update();
		window->setView(current_camera->getView());

		ImGui::SFML::Update(*window, time);
		if (onUpdate.isFunction()) onUpdate();
	}

	void Core::draw()
	{
		// Clear display
		window->clear();

		// Draw level
		if(current_level) current_level->draw();

        // Draw gui
        //for(GUIForm* form : stack_gui) form->draw();
		ImGui::SFML::Render(*window);

		window->display();
	}

	Level* Core::loadLevel(string name, string loader_type)
	{
		Level* level = nullptr;

		ResourceManager* loader = managers[loader_type];
		if (loader)
		{
			if (loader->getType() == CAP_MANAGER_LEVEL)
			{
				level = static_cast<LevelManager*>(loader)->loadLevel(name);
				if (level) levels[level->getName()] = level;
			}
			else Script::print_log("Error. Wrong loader '" + loader_type + "'! Tileset not loaded!");
		}
		else Script::print_log("Error. Loader '" + loader_type + "' not found! Tileset not loaded!");

		return level;
	}

	Tileset* Core::loadTileset(string name, string loader_type)
	{
		Tileset* tileset = nullptr;

		ResourceManager* loader = managers[loader_type];
		if (loader)
		{
			if (loader->getType() == CAP_MANAGER_LEVEL)
			{
				tileset = static_cast<LevelManager*>(loader)->loadTileset(name);
				if (tileset) tilesets[tileset->getName()] = tileset;
			}
			else Script::print_log("Error. Wrong loader '" + loader_type + "'! Tileset not loaded!");
		}
		else Script::print_log("Error. Loader '" + loader_type + "' not found! Tileset not loaded!");

		return tileset;
	}

	LuaRef Core::loadTilesetsForLevel(string name, string loader_type)
	{
		TilesetMap list;

		ResourceManager* loader = managers[loader_type];
		if (loader)
		{
			if (loader->getType() == CAP_MANAGER_LEVEL)
			{
				list = static_cast<LevelManager*>(loader)->loadTilesetsForLevel(name);
				tilesets.insert(list.begin(), list.end());
			}
			else Script::print_log("Error. Wrong loader '" + loader_type + "'! Tileset not loaded!");
		}
		else Script::print_log("Error. Loader '" + loader_type + "' not found! Tileset not loaded!");

		return Script::toTable(list);
	}

	void Core::close()
	{
		window->close();
	}

    void Core::initClasses()
    {
		Script::global()

			// ------- Class Core ----------------------------------------------- //
			.beginClass<Core>("Core")
			.addStaticFunction("setProperty", &Core::setProperty)
			.addStaticFunction("getProperty", &Core::getProperty)
			.addStaticFunction("setCurrentLevel", &Core::setCurrentLevel)

			.addStaticProperty("onSetup", &Core::onSetup)
			.addStaticProperty("onClose", &Core::onClose)
			.addStaticProperty("onUpdate", &Core::onUpdate)

			.addStaticFunction("loadLevel", &Core::loadLevel)
			.addStaticFunction("loadTileset", &Core::loadTileset)
			.addStaticFunction("loadTilesetsForLevel", &Core::loadTilesetsForLevel)

			.addStaticFunction("close", &Core::close)

			.addStaticProperty("deltaTime", &Core::deltaTime, false)
			.endClass()

			// ------- Class Entity ----------------------------------------------- //
			.beginClass<Entity>("Entity")

			.addFunction("update", &Entity::update)

			.addFunction("addChild", &Entity::addChild)

			.addFunction("setName", &Entity::setName)

			.addFunction("getName", &Entity::getName)
			.addFunction("getType", &Entity::getType)
			.addFunction("getParent", &Entity::getParent)
			.addFunction("getChild", &Entity::getChild)
			.endClass()

			// ------- Class PointEntity ----------------------------------------------- //
			.deriveClass<PointEntity, Entity>("PointEntity")
			.addConstructor<void(*)(const string&)>()
			.endClass()

			// ------- Class PointEntity ----------------------------------------------- //
			.deriveClass<RectEntity, Entity>("RectEntity")
			.addConstructor<void(*)(const string&)>()
			.endClass()

			// ------- Class PointEntity ----------------------------------------------- //
			.deriveClass<DrawableEntity, Entity>("DrawableEntity")
			.addConstructor<void(*)(const string&)>()
			.endClass()

			// ------- Class Tileset ----------------------------------------------- //
			.beginClass<Level>("Level")
			.endClass()

			// ------- Class Tileset ----------------------------------------------- //
			.beginClass<Tileset>("Tileset")
			.endClass()

			// ------- Class Point ----------------------------------------------- //
			.beginClass<Point>("Point")
			.addConstructor<void(*)(double, double)>()

			.addProperty("x", &Point::x)
			.addProperty("y", &Point::y)
			.endClass()

			// ------- Class Rect ----------------------------------------------- //
			.beginClass<Rect>("Rect")
			.addConstructor<void(*)(double, double, double, double)>()

			.addProperty("x", &Rect::x)
			.addProperty("y", &Rect::y)
			.addProperty("width", &Rect::width)
			.addProperty("height", &Rect::height)
			.endClass();
    }	
}
