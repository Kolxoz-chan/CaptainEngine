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
		return author;
	}

	const string& ResourceManager::getVersion()
	{
		return version;
	}

	const string& ResourceManager::getUrl()
	{
		return url;
	}

	int ResourceManager::getType()
	{
		return m_type;
	}

	void ResourceManager::setProperty(const string& key, LuaRef value)
	{
		properties.set(key, value);
	}
}