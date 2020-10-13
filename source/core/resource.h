#pragma once
#include <core/types.h>

#include <libraries/std.hpp>
#include <libraries/sfml.hpp>

namespace cap
{
	// --------------- Base Reource --------------------------- //
	class Resource
	{
	protected:
		int type;

	public:
		Resource();

		int getType();
	};

	// --------------- Tileset Reource --------------------------- //
	class Tileset : public Resource
	{
	private:
		sf::Texture* m_texrture = nullptr;
		Point texture_size, tileset_size, tile_size, margin, spacing;
		string name;

	public:
		Tileset() = default;

		Sprite getTile(int index);
		Sprite getTile(Point coords);
		inline Sprite getTile(int x, int y) { return getTile(Point(x, y)); };

		void setTexture(sf::Texture* texture);
		void setTileSize(Point size);
		void setTilesetSize(Point size);

		int length();
	};
	using TilesetList = vector<Tileset>;
}