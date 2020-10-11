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
	private:
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
	private:


	public:
		LevelManager() = default;

		Level* loadLevel(string name);
	};
}
