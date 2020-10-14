#pragma once
#include <core/types.h>
#include <core/constants.h>

#include <libraries/std.hpp>
#include <libraries/sfml.hpp>

namespace cap
{
	// --------------- Base Reource --------------------------- //
	class Resource
	{
	protected:
		int m_type;
		string m_name;

	public:
		Resource(int type, string name) : m_name(name), m_type(type) {};

		int getType() { return m_type; }
		const string& getName() { return m_name; };
	};

	// --------------- Tileset Reource --------------------------- //
	class Tileset : public Resource
	{
	private:
		sf::Texture* m_texrture = nullptr;
		vector<sf::Sprite> m_tiles;
		Point m_tileset_size, m_tile_size, m_margin, m_spacing;

	public:
		Tileset(string name = string()) : Resource(CAP_RESOURCE_TILESET, name) {};

		Sprite getTile(int index);
		Sprite getTile(Point coords);
		inline Sprite getTile(int x, int y) { return getTile(Point(x, y)); };

		void subdivide(sf::Texture* texture, Point tileset_size, Point tile_size, int spacing = 0, int margin = 0);

		int length();
	};
	using TilesetList = vector<Tileset*>;
	using TilesetMap = map<string, Tileset*>;
}