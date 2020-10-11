#include "levelloader.h"

LevelLoader::LevelLoader(string name, string description, string autor, string version) :
	name(name), description(description), autor(autor), version(version) 
{
}

string LevelLoader::getName()
{
	return name;
}

string LevelLoader::getDescription()
{
	return description;
}

string LevelLoader::getAutor()
{
	return autor;
}

string LevelLoader::getVersion()
{
	return version;
}
