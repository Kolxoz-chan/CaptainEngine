#include <loaders\TiledLoaderCSV.h>

TiledLoaderCSV::TiledLoaderCSV(string level_name) : LevelManager(level_name)
{
	this->name = "Tiled CSV loader";
	this->autor = "Kolxoz";
	this->version = "1.0";
	this->description = "This parser is designed to load maps created in Tiled 1.3.2 in CSV mode";
}

TileLayer* TiledLoaderCSV::loadTileLayer(XMLElement* layer)
{
	// Имя слоя 
	string layerName = layer->Attribute("name");
	
	// Создаём слой
	TileLayer* currentLayer = new TileLayer(layerName);

	// Смещение слояя
	int offset_x = 0, offset_y = 0;
	if (layer->Attribute("offsetx") && layer->Attribute("offsety"))
	{
		offset_x = atoi(layer->Attribute("offsetx"));
		offset_y = atoi(layer->Attribute("offsety"));
	}
	currentLayer->setOffset(offset_x, offset_y);

	// Работа с чанками
	XMLElement *data = layer->FirstChildElement("data");
	XMLElement *chunk = data->FirstChildElement("chunk");

	while (chunk)
	{
		int chunk_w = atoi(chunk->Attribute("width"));		// Длинна чанка
		int chunk_h = atoi(chunk->Attribute("height"));		// Высота чанка
		int chunk_x = atoi(chunk->Attribute("x"));			// Позиция чанка по X
		int chunk_y = atoi(chunk->Attribute("y"));			// Позиция чанка по Y

		char* ch = (char*)chunk->GetText();

		/*for (int y = 0; y < chunk_h; y++)
		{
			for (int x = 0; x < chunk_w; x++)
			{
				int x_pos = (chunk_x + x) * tilewidth;
				int y_pos = (chunk_y + y) * tileheight;

				char* num = strtok(ch, " ,\n");
				int index = atoi(num) - 1;

				if (index >= 0)
				{
					cap::Texture* texture = getTexture(index);
					if (texture) currentLayer->addTile(textures[index]->toSprite(), x_pos, y_pos);
					else Script::print_log("Error! Tile with index " + to_string(index) + " is not loaded!");
				}
			}
		}*/
		chunk = chunk->NextSiblingElement("chunk"); // Следующий чанк
	}
	return currentLayer;
}

ObjectLayer* TiledLoaderCSV::loadObjectLayer(XMLElement* layer)
{
	// Имя слоя и группы-родителя
	string layerName = layer->Attribute("name");
	ObjectLayer* currentLayer = new ObjectLayer(layerName);

	XMLElement *object = layer->FirstChildElement("object");
	while (object)
	{
		Entity* obj = nullptr;

		string name = object->Attribute("name");
		string type = object->Attribute("type");

		// Если у объекта есть тип
		if (!type.empty())
		{
            LuaRef constr = Script::getVar(type);
			if (constr.isTable())
			{
				LuaRef lua_obj = constr(name);
				if (lua_obj.isUserdata())
				{
                    // NOT FINISHED
				}
				obj = lua_obj["__parent"].cast<Entity*>();
			}
			else
			{
				// Если тип не опознан
				Script::print_log("Error! Don't such class '" + type + "', object is not loaded");
				continue;
			}
		}

		// Если у объекта есть текстура
		const char* gid = object->Attribute("gid");
		if (gid)
		{
			// Если объект не создан - создаём
			if (!obj) obj = new DrawableEntity(name);

			// Если объект отображаемый - присваиваем ему текстуру
			if (obj->getType() == CAP_DRAWABLE_ENTTY)
			{
				int index = atoi(gid) - 1;
				cap::Texture* texture = getTexture(index);
				if(texture)((DrawableEntity*)obj)->setTexture(texture->toSprite());
				else Script::print_log("Warning! Object type " + type + " is not drawable, texture is not seted!");
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
			if (!obj) obj = new RectEntity(name);

			// Позиция и размер
			((RectEntity*)obj)->setSize(Point(w, h));
		}

		// Если объект не создан - создаём
		if (!obj) obj = new PointEntity(name);

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

GroupLayer* TiledLoaderCSV::loadGroupLayer(XMLElement* group)
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

vector<string> TiledLoaderCSV::getTitles(XMLElement* tileset)
{
	vector<string> titles;
	while (tileset)
	{
		string source = tileset->Attribute("source");
		titles.push_back(CAP_GAMEDATA_DIR + source.erase(0, 3));
		tileset = tileset->NextSiblingElement("tileset");
	}
	return titles;
}

Tileset TiledLoaderCSV::loadTileset(XMLElement* tileset)
{
	XMLElement* image = tileset->FirstChildElement("image");
	while (image)
	{

		tileset = tileset->NextSiblingElement("image");
	}

	return Tileset(); // Заглушка
}

Level* TiledLoaderCSV::loadLevel()
{
	// Loading level file
	string path = m_level_name + ".tmx";

	XMLDocument doc;
	if (doc.LoadFile(path.c_str()) == XML_SUCCESS)
	{
		XMLElement* map = doc.RootElement();
		if (map)
		{
			Level* lvl = new Level(name);

			tilewidth = atoi(map->Attribute("tilewidth"));
			tileheight = atoi(map->Attribute("tileheight"));

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

RequiredList TiledLoaderCSV::getRequired()
{
	RequiredList list;

	// Loading level file
	string path = m_level_name + ".tmx";

	// Tileset paths loading
	XMLDocument doc;
	if (doc.LoadFile(path.c_str()) == XML_SUCCESS)
	{
		XMLElement* map = doc.RootElement();
		if (map)
		{
			XMLElement* tileset = map->FirstChildElement("tileset");
			while (tileset)
			{
				list.push_back({CAP_RESOURCE_TILESET, tileset->Attribute("source")});
				tileset = tileset->NextSiblingElement("tileset");
			}
		}
	}
	else print_error(doc, path);

	return list;
}

void TiledLoaderCSV::print_error(XMLDocument& doc, string path)
{
	string error_name = doc.ErrorName();
	string error_line = to_string(doc.ErrorLineNum());

	Script::print_log("Error! File '" + path + "' is not loaded! ");
	Script::print_log("Reason: " + error_name);
	Script::print_log("Line: " + error_line);
}
