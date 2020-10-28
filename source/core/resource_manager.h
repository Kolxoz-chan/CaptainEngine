#pragma once
#include <core/types.h>
#include <core/level.h>

#include <libraries/std.hpp>
#include <libraries/lua.hpp>

namespace cap
{
	// -------------- Base Manager ------------------------------- //
	class ResourceManager
	{
	protected:
		int m_type;
		LuaMap properties;
		string name, description, author, version, url;

	public:
		ResourceManager(int type) : m_type(type) {};
		virtual ~ResourceManager() = default;

		// Setters //
		void setProperty(const string& key, LuaRef value);

		// Getters //
		const string& getName();
		const string& getDescription();
		const string& getAutor();
		const string& getVersion();
		const string& getUrl();

		int getType();
	};

	// -------------- Level Manager ------------------------------- //
	class LevelManager : public ResourceManager
	{
	public:
		LevelManager() : ResourceManager(CAP_MANAGER_LEVEL) {};

		virtual Level* loadLevel(const string& name) = 0;
		virtual TilesetMap loadTilesetsForLevel(const string& name) = 0;
		virtual Tileset* loadTileset(const string& name) = 0;
	};
}
