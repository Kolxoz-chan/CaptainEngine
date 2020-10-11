#pragma once
#include <loaders\levelloader.h>

#include <core\types.h>

#include <libraries\xml.hpp>
#include <libraries\std.hpp>

using namespace cap;

class TiledLoaderCSV : public LevelLoader
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

	Level* load(const string& name);
	Tilesets loadTilesets(const string& name);
};