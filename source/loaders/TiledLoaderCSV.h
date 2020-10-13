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

	cap::Texture* getTexture(int index);
	vector<string> getTitles(XMLElement* tileset);

	void print_error(XMLDocument& elem, string path);

public:
	TiledLoaderCSV();
	~TiledLoaderCSV() = default;

	Level* loadLevel(const string& name);
	TilesetList loadTilesets(const string& name);
};