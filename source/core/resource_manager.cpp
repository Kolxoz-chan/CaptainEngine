#include <core/resource_manager.h>

namespace cap
{
	// -------------- Base Manager ------------------------------- //
	const string& ResourceManager::getName()
	{
		return name;
	}

	const string& ResourceManager::getDescription()
	{
		return description;
	}

	const string& ResourceManager::getAutor()
	{
		return autor;
	}

	const string& ResourceManager::getVersion()
	{
		return version;
	}

	const string& ResourceManager::getUrl()
	{
		return url;
	}

	void ResourceManager::setProperty(const string& key, LuaRef value)
	{
		properties.set(key, value);
	}

	// -------------- Level Manager ------------------------------- //
	void LevelManager::setRequired(const RequiredResources& resources)
	{
		m_required = resources;
	}
}