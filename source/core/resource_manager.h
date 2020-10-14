#pragma once
#include <core/types.h>
#include <core/level.h>
#include <core/resource.h>

#include <libraries/std.hpp>
#include <libraries/lua.hpp>

namespace cap
{
	// -------------- Pseudotypes ------------------------------- //
	using RequiredResources = vector<pair<int, Resource*>>;
	using RequiredList = vector<pair<int, string>>;

	// -------------- Base Manager ------------------------------- //
	class ResourceManager
	{
	protected:
		int m_type;
		LuaMap properties;
		string name, description, autor, version, url;

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
	protected:
		RequiredResources m_required;

	public:
		LevelManager() : ResourceManager(CAP_MANAGER_LEVEL) {};

		virtual RequiredList getRequired(const string& name) = 0;
		void setRequired(const RequiredResources& resources);

		virtual Level* loadLevel(const string& name) = 0;
		virtual vector<Tileset*> loadTilesetsForLevel(const string& name) = 0;
		virtual Tileset* loadTileset(const string& name) = 0;
	};
}
