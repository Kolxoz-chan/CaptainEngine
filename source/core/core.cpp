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
	LuaRef          Core::onPreDraw = 0;
	LuaRef			Core::onPostDraw = 0;

	void Core::init(int width, int height, const string& title)
	{
		// Classes init //
		Script::init();

		// Init variables //
		onSetup = Script::newRef();
		onClose = Script::newRef();
		onUpdate = Script::newRef();
		onPreDraw = Script::newRef();
		onPostDraw = Script::newRef();

		// Window //
		window = new RenderWindow(VideoMode(width, height), title);
		window->setPosition(Point(50, 50));
		Input::window = window;

		// Camera init //
		default_camera = new Camera(window->getDefaultView());
		current_camera = default_camera;
		current_level = nullptr;

		// Init constants
		Core::initConstants();

        // Reset log //
        Script::reset_log("Captain Engine log:");

		// Create gui
		GUIForm* form = new GUIForm();
		stack_gui.push_back(form);

		form->setPosition(100, 100);
		form->setSize(300, 300);

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
		auto global = Script::global();
		initTypesClasses(global);
		initBaseClasses(global);
		initContainersClasses(global);
		initEntitiesClasses(global);

		// Add require paths
		Script::addRequirePath("gamedata\\scripts\\?.lua");

        // Run script
        Script::include(CAP_SCRIPTS_DIR + file + ".lua");
		
        // Call onSetup
        if(onSetup.isFunction()) onSetup();
	}

	void Core::eventProcessing()
	{
		while (window->pollEvent(event))
		{
			// Event on close window
			if (event.type == Event::Closed)
			{
				if (onClose.isFunction())
				{
					LuaRef result = onClose();
					if (result.isNil() || result == true) window->close();
				}
				else window->close();
			}

			// Event on resize window
			else if (event.type == Event::Resized)
			{
				Point size = Point(window->getSize());
				size.x += int(size.x) % 2;
				size.y += int(size.y) % 2;
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
	}

	void Core::update()
	{
		// Update camera
		current_camera->update();
		window->setView(current_camera->getView());

		// Update input
		Input::update();

		// Update level
		if (current_level) current_level->update();

		// Update GUI
		if (onUpdate.isFunction()) onUpdate();
	}

	void Core::draw()
	{
		// Clear display
		window->clear();

		// Pre draw event
		if (onPreDraw.isFunction()) onPreDraw();

		// Draw level
		if (current_level)
		{
			window->draw(*current_level);
		}

        // Draw gui
		for (GUIForm* form : stack_gui)
		{
			window->draw(*form);
		}

		// Post draw event
		if (onPostDraw.isFunction()) onPostDraw();

		// Display
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
			else Script::print_log("Error. Wrong loader '" + loader_type + "'! Level not loaded!");
		}
		else Script::print_log("Error. Loader '" + loader_type + "' not found! Level not loaded!");

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

	void Core::initConstants()
	{
		// Init keyboard buttons
		auto buttons = Input::getKeyboardButtons();
		for (int i = 0; i < buttons.size(); i++) Script::setVar(buttons[i], i);

		// Init mouse buttons
		buttons = Input::getMouseButtons();
		for (int i = 0; i < buttons.size(); i++) Script::setVar(buttons[i], i);
	}

	void Core::initBaseClasses(Namespace& global)
    {	
		global = global

			// ------- Class Core ----------------------------------------------- //
			.beginClass<Core>("Core")
			.addStaticFunction("setProperty", &Core::setProperty)
			.addStaticFunction("getProperty", &Core::getProperty)

			.addStaticProperty("onSetup", &Core::onSetup)
			.addStaticProperty("onClose", &Core::onClose)
			.addStaticProperty("onUpdate", &Core::onUpdate)
			.addStaticProperty("onPreDraw", &Core::onPreDraw)
			.addStaticProperty("onPostDraw", &Core::onPostDraw)

			.addStaticFunction("loadLevel", &Core::loadLevel)
			.addStaticFunction("loadTileset", &Core::loadTileset)
			.addStaticFunction("loadTilesetsForLevel", &Core::loadTilesetsForLevel)

			.addStaticFunction("close", &Core::close)

			.addStaticProperty("deltaTime", &Core::deltaTime, false)
			.addStaticProperty("default_camera", &Core::default_camera, false)
			.addStaticProperty("current_camera", &Core::current_camera)
			.addStaticProperty("current_level", &Core::current_level)
			.endClass()

			// ------- Class Input ----------------------------------------------- //
			.beginClass<Input>("Input")

			.addStaticFunction("isKeyboardClicked", &Input::isKeyboardClicked)
			.addStaticFunction("isKeyboardPressed", &Input::isKeyboardPressed)
			.addStaticFunction("isKeyboardReleased", &Input::isKeyboardReleased)
			.addStaticFunction("isMouseClicked", &Input::isMouseClicked)
			.addStaticFunction("isMousePressed", &Input::isMousePressed)
			.addStaticFunction("isMouseReleased", &Input::isMouseReleased)

			.addStaticFunction("getMousePosition", &Input::getMousePosition)

			.endClass();
    }

	void Core::initTypesClasses(Namespace& global)
	{
		global = global

			// ------- Class Tileset ----------------------------------------------- //
			.beginClass<Tileset>("Tileset")
			.endClass()

			// ------- Class Point ----------------------------------------------- //
			.beginClass<Point>("Point")
			.addConstructor<void(*)(double, double)>()

			.addProperty("x", &Point::x)
			.addProperty("y", &Point::y)

			.addFunction("round", &Point::round)
			.addFunction("toInteger", &Point::toInteger)
			.addFunction("__tostring", &Point::toString)
			.addFunction("__eq", &Point::isEqual)

			.addStaticFunction("distance", &Point::distance)
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

	void Core::initEntitiesClasses(Namespace& global)
	{
		global = global

			// ------- Class Entity ----------------------------------------------- //
			.beginClass<Entity>("Entity")

			.addProperty("self", &Entity::self)

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

			.addFunction("setPosition", &PointEntity::setPosition)

			.addFunction("getPosition", &PointEntity::getPosition)

			.addFunction("move", &PointEntity::move)
			.addFunction("move_to", &PointEntity::move_to)
			.endClass()

			// ------- Class RectEntity ----------------------------------------------- //
			.deriveClass<RectEntity, PointEntity>("RectEntity")
			.addConstructor<void(*)(const string&)>()

			.addFunction("getCenter", &RectEntity::getCenter)
			.addFunction("getRect", &RectEntity::getRect)

			.endClass()

			// ------- Class DrawableEntity ----------------------------------------------- //
			.deriveClass<DrawableEntity, RectEntity>("DrawableEntity")
			.addConstructor<void(*)(const string&)>()
			.endClass()

			// ------- Class Camera ----------------------------------------------- //
			.deriveClass<Camera, RectEntity>("Camera")
			.addConstructor<void(*)(Rect)>()

			.addFunction("zoom", &Camera::zoom)

			.endClass()

			// ------- Class Primitive ----------------------------------------------- //
			.deriveClass<Primitive, DrawableEntity>("Primitive")
			.addConstructor<void(*)(const string&)>()

			.addFunction("setOutlineColor", &Primitive::setOutlineColor)
			.addFunction("setBackgroundColor", &Primitive::setBackgroundColor)
			.addFunction("setOutlineThikness", &Primitive::setOutlineThikness)

			.addFunction("generatePrimitive", &Primitive::generatePrimitive)

			.addFunction("clear", &Primitive::clear)
			.addFunction("addPoint", &Primitive::addPoint)

			.endClass();
	}

	void Core::initContainersClasses(Namespace& global)
	{
		global = global

			// ------- Class Container ----------------------------------------------- //
			.beginClass<Container>("Container")
			.endClass()

			// ------- Class Container ----------------------------------------------- //
			.beginClass<ObjectLayer>("ObjectLayer")

			.addFunction("getFirstObject", &ObjectLayer::getFirstObject)
			.addFunction("getLastObject", &ObjectLayer::getLastObject)
			.addFunction("getObjects", &ObjectLayer::getObjects)

			.addStaticFunction("fromContainer", ObjectLayer::fromContainer)

			.endClass()

			// ------- Class Level ----------------------------------------------- //
			.beginClass<Level>("Level")

			.addFunction("getContainer", &Level::getContainer)

			.endClass();
	}
}
