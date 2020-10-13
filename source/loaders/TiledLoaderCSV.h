#pragma once
#include <core/resource_manager.h>
#include <core/types.h>

#include <libraries/xml.hpp>
#include <libraries/std.hpp>

using namespace cap;

class TiledLoaderCSV : public LevelManager
{
private:
	int tilewidth, tileheight;
	Tileset textures;

	TileLayer* loadTileLayer(XMLElement* group);
	ObjectLayer* loadObjectLayer(XMLElement* group);
	GroupLayer* loadGroupLayer(XMLElement* group);
	Tileset loadTileset(XMLElement* tileset);

	void print_error(XMLDocument& elem, string path);

public:
	TiledLoaderCSV(string level_name = string());
	~TiledLoaderCSV() = default;

	Level* loadLevel();
	RequiredList getRequired();
};