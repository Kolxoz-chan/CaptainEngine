#include "loaders.h"

TiledManager::TiledManager()
{
	this->name = "Tiled level loader [CSV]";
	this->autor = "Kolxoz";
	this->version = "1.0";
	this->description = "This parser is designed to load maps created in Tiled 1.3.2 in CSV mode";

	required_tileset = new Tileset();;
}

TileLayer* TiledManager::loadTileLayer(XMLElement* layer)
{
	// Имя слоя 
	string layerName = layer->Attribute("name");
	
	// Создаём слой
	TileLayer* currentLayer = new TileLayer(layerName);

	// Смещение слояя
	int offset_x, offset_y;
	offset_x = layer->IntAttribute("offsetx", 0);
	offset_y = layer->IntAttribute("offsety", 0);

	// Работа с чанками
	XMLElement *data = layer->FirstChildElement("data");
	XMLElement *chunk = data->FirstChildElement("chunk");

	while (chunk)
	{
		int chunk_w = chunk->IntAttribute("width");		// Длинна чанка
		int chunk_h = chunk->IntAttribute("height");	// Высота чанка
		int chunk_x = chunk->IntAttribute("x");			// Позиция чанка по X
		int chunk_y = chunk->IntAttribute("y");			// Позиция чанка по Y

		CSVParser parser;
		parser.loadFromString(chunk->GetText());
		CSVTable table = parser.getTable();


		for (int y = 0; y < chunk_h; y++)
		{
			for (int x = 0; x < chunk_w; x++)
			{
				int x_pos = (chunk_x + x) * tilewidth;
				int y_pos = (chunk_y + y) * tileheight;

				int index = atoi(table[y][x].c_str()) - 1;

				if (index >= 0)
				{
					if (required_tileset->length() > index) currentLayer->addTile(required_tileset->getTile(index), x_pos, y_pos);
					else Script::print_log("Error! Tile with index " + to_string(index) + " is not loaded!");
				}
			}
		}
		chunk = chunk->NextSiblingElement("chunk"); // Следующий чанк
	}
	return currentLayer;
}

ObjectLayer* TiledManager::loadObjectLayer(XMLElement* layer)
{
	// Имя слоя и группы-родителя
	string layerName = layer->Attribute("name");
	ObjectLayer* currentLayer = new ObjectLayer(layerName);

	XMLElement *object = layer->FirstChildElement("object");
	while (object)
	{
		Entity* obj = nullptr;

		const char* name = object->Attribute("name");
		const char* type = object->Attribute("type");

		// Если у объекта есть тип
		if (type)
		{
            LuaRef constr = Script::getVar(type);
			if (constr.isTable())
			{
				LuaRef lua_obj = constr();
				if (lua_obj.isUserdata())
				{
                    // NOT FINISHED
				}
				obj = lua_obj["__parent"].cast<Entity*>();
			}
			else
			{
				// Если тип не опознан
				Script::print_log("Error! Don't such class '" + string(type) + "', object is not loaded");
				continue;
			}
		}

		// Если у объекта есть текстура
		const char* gid = object->Attribute("gid");
		if (gid)
		{
			// Если объект не создан - создаём
			if (!obj) obj = new DrawableEntity();

			// Если объект отображаемый - присваиваем ему текстуру
			if (obj->getType() == CAP_DRAWABLE_ENTTY)
			{
				int index = atoi(gid) - 1;
				if (required_tileset->length() > index)
				{
					static_cast<DrawableEntity*>(obj)->setTexture(required_tileset->getTile(index));
				}
				else Script::print_log("Warning! Object type " + string(type) + " is not drawable, texture is not seted!");
			}
		}

		// Позиция объекта
		int x = atoi(object->Attribute("x"));
		int y = atoi(object->Attribute("y"));

		// Размеры объекта (могут отсутствовать)
		int w = 0, h = 0;
		if (object->Attribute("width") && object->Attribute("height"))
		{
			w = atoi(object->Attribute("width"));
			h = atoi(object->Attribute("height"));
			
			// Смещаем позицию если есть тектсура
			if (gid) y -= h;

			// Если объект не создан - создаём
			if (!obj) obj = new RectEntity();

			// Позиция и размер
			((RectEntity*)obj)->setSize(Point(w, h));
		}

		// Если объект не создан - создаём
		if (!obj) obj = new PointEntity();
		if (name) obj->setName(name);

		// Устанавливаем позицию
		((PointEntity*)obj)->setPosition(Point(x, y));

		// Загрузка свойств
		if (object->FirstChildElement("properties"))
		{
			XMLElement *prop = object->FirstChildElement("properties")->FirstChildElement("property");
			while (prop)
			{
				string name = prop->Attribute("name");
				string value = prop->Attribute("value");

                obj->self[name] = Script::eval(value);
				prop = prop->NextSiblingElement("property");
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Put object on layer
		currentLayer->addObject(obj);
		object = object->NextSiblingElement("object");
	}
	return currentLayer;
}

GroupLayer* TiledManager::loadGroupLayer(XMLElement* group)
{
	// Создаём группу
    GroupLayer* currentGroup = new GroupLayer(group->Attribute("name"));

    // Group offset
    int offset_x = group->Attribute("offsetx") ? atoi(group->Attribute("offsetx")) : 0;
    int offset_y = group->Attribute("offsety") ? atoi(group->Attribute("offsety")) : 0;
    currentGroup->setOffset(offset_x, offset_y);

	// Работа со слоями
	auto layer = group->FirstChildElement();
	while (layer)
	{
		string layerType = layer->Value();

		// Загрузка слоёв
		if (layerType == "group") currentGroup->addContainer(loadGroupLayer(layer));
		else if (layerType == "layer") currentGroup->addContainer(loadTileLayer(layer));
		else if (layerType == "objectgroup") currentGroup->addContainer(loadGroupLayer(layer));

		// Следующий слой
		layer = layer->NextSiblingElement(); 
	}

	return currentGroup;
}

Level* TiledManager::loadLevel(const string& path)
{
	// Loading level file
	string level_name;
	XMLDocument doc;
	int status = doc.LoadFile(path.c_str());
	if (status == XML_SUCCESS)
	{
		int begin = path.find_last_of("\/") + 1;
		int end = path.find_last_of(".");
		level_name = path.substr(begin, end - begin);
	}
	else
	{
		level_name = path;
		string new_path = CAP_LEVELS_DIR + path + ".tmx";	
		status = doc.LoadFile(new_path.c_str());
	}

	// Loading level data
	if (status == XML_SUCCESS)
	{
		XMLElement* map = doc.RootElement();
		if (map)
		{
			Level* lvl = new Level(level_name);

			tilewidth = map->IntAttribute("tilewidth");
			tileheight = map->IntAttribute("tileheight");

			// Считываем карту
			XMLElement* elem = map->FirstChildElement();
			while (elem)
			{
				string name = elem->Value();
				if (name == "group") lvl->addContainer(loadGroupLayer(elem));
				else if (name == "layer") lvl->addContainer(loadTileLayer(elem));
				else if (name == "objectgroup") lvl->addContainer(loadObjectLayer(elem));

				elem = elem->NextSiblingElement();
			}
			return lvl;
		}
	}
	else print_error(doc, path);

	return nullptr;
}

TilesetMap TiledManager::loadTilesetsForLevel(const string& name)
{
	TilesetMap list;

	// Loading level file
	string path = name + ".tmx";

	// Tileset paths loading
	XMLDocument doc, tsx;
	if (doc.LoadFile(path.c_str()) == XML_SUCCESS)
	{
		XMLElement* map = doc.RootElement();
		required_tileset->clear();

		if (map)
		{
			XMLElement* tileset = map->FirstChildElement("tileset");
			while (tileset)
			{
				string source = tileset->Attribute("source");
				source = CAP_GAMEDATA_DIR + source.substr(3);

				Tileset* tiles = loadTileset(source);
				list[tiles->getName()] = tiles;
				required_tileset->concat(*tiles);

				tileset = tileset->NextSiblingElement("tileset");
			}
		}
	}
	else print_error(doc, path);

	return list;
}

void TiledManager::print_error(XMLDocument& doc, string path)
{
	string error_name = doc.ErrorName();
	string error_line = to_string(doc.ErrorLineNum());

	Script::print_log("Error! File '" + path + "' is not loaded! ");
	Script::print_log("Reason: " + error_name);
	Script::print_log("Line: " + error_line);
}

Tileset* TiledManager::loadTileset(const string& path)
{
	Tileset* tileset = nullptr;
	XMLDocument doc;
	if (doc.LoadFile(path.c_str()) == XML_SUCCESS)
	{
		XMLElement* root = doc.RootElement();
		XMLElement* image = root->FirstChildElement("image");
		sf::Texture* texture = new sf::Texture();
		string source = image->Attribute("source");
		source = CAP_GAMEDATA_DIR + source.substr(3);
		
		// Image loading
		if (!texture->loadFromFile(source))
		{
			delete texture;
			Script::print_log("Error. File '" + source + "' not found! Tileset not loaded!");
			return nullptr;
		}
		Point tile_size = { root->FloatAttribute("tilewidth"), root->FloatAttribute("tilewidth")};
		int tilecount = root->IntAttribute("tilecount");
		int columns = root->IntAttribute("columns");
		int rows = tilecount / columns;

		// Create tileset
		tileset = new Tileset(root->Attribute("name"));
		tileset->subdivide(texture, Point(columns, rows), tile_size, root->IntAttribute("spacing", 0), root->IntAttribute("margin", 0));
	}
	else
	{
		string error_name = doc.ErrorName();
		string error_line = to_string(doc.ErrorLineNum());

		Script::print_log("Error! File '" + path + "' is not loaded! ");
		Script::print_log("Reason: " + error_name);
		Script::print_log("Line: " + error_line);
	}

	return tileset;
}