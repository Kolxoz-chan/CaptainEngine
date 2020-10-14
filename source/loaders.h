#pragma once
#include <core/resource_manager.h>
#include <core/types.h>

#include <libraries/xml.hpp>
#include <libraries/std.hpp>

using namespace cap;

// --------------- Lever loader --------------------------- //
class TiledLevelLoader : public LevelManager
{
private:
	int tilewidth, tileheight;
	
private:
	TileLayer* loadTileLayer(XMLElement* group);
	ObjectLayer* loadObjectLayer(XMLElement* group);
	GroupLayer* loadGroupLayer(XMLElement* group);

	void print_error(XMLDocument& elem, string path);

public:
	TiledLevelLoader() ;
	~TiledLevelLoader() = default;

	Level* loadLevel(const string& path);
	RequiredList getRequired(const string& path);
};

// --------------- Tileset loader --------------------------- //
class TiledTilesetLoader : public TilesetManager
{
public:
	TiledTilesetLoader();
	~TiledTilesetLoader() = default;

	Tileset* loadTileset(const string& path);
};