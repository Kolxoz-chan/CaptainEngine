#pragma once
#include <core\level.h>
#include <core\types.h>

#include <libraries\std.hpp>
#include <libraries\sfml.hpp>

using namespace cap;

class LevelLoader
{
protected:
	string name, description, autor, version;

public:
	LevelLoader() = default;
	LevelLoader(string name, string description, string autor, string version);
	virtual ~LevelLoader() = default;

	string getName();
	string getDescription();
	string getAutor();
	string getVersion();

	virtual Level* load(const string& name) = 0;
	virtual Tilesets loadTilesets(const string& name) = 0;
};

