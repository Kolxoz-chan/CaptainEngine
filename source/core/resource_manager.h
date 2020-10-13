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
		LuaMap properties;
		string name, description, autor, version, url;

	public:
		ResourceManager() = default;
		virtual ~ResourceManager() = default;

		// Setters //
		void setProperty(const string& key, LuaRef value);

		// Getters //
		const string& getName();
		const string& getDescription();
		const string& getAutor();
		const string& getVersion();
		const string& getUrl();
	};

	// -------------- Level Manager ------------------------------- //
	class LevelManager : public ResourceManager
	{
	protected:
		string m_level_name;
		RequiredResources m_required;

	public:
		LevelManager(string level_name = string()) : m_level_name(level_name) {};

		virtual RequiredList getRequired() = 0;
		void setRequired(const RequiredResources& resources);

		virtual Level* loadLevel(string name) = 0;
	};
}
