#pragma once
#include <core/resource_manager.h>
#include <core/types.h>

#include <libraries/xml.hpp>
#include <libraries/std.hpp>

using namespace cap;

// --------------- Lever loader --------------------------- //
class TiledManager : public LevelManager
{
private:
	Tileset* required_tileset;
	int tilewidth, tileheight;
	
private:
	TileLayer* loadTileLayer(XMLElement* group);
	ObjectLayer* loadObjectLayer(XMLElement* group);
	GroupLayer* loadGroupLayer(XMLElement* group);

	void print_error(XMLDocument& elem, string path);

public:
	TiledManager() ;
	~TiledManager() = default;

	Level* loadLevel(const string& path);
	vector<Tileset*> loadTilesetsForLevel(const string& name);
	Tileset* loadTileset(const string& path);
};