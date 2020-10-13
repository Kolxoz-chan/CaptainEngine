#include "resource.h"

namespace cap
{
	Sprite Tileset::getTile(int index)
	{
		
	}

	Sprite Tileset::getTile(Point coords)
	{
		Point pos = coords * tile_size + margin;
		return Sprite(m_texrture, Rect(, tile_size));
	}

	void Tileset::setTexture(sf::Texture* texture)
	{
		m_texrture = texture;
	}

	void Tileset::setTileSize(Point size)
	{
		tile_size = size;
	}

	void Tileset::setTilesetSize(Point size)
	{
		tileset_size = size;
	}

	int Tileset::length()
	{
		return tileset_size.x * tileset_size.y;
	}
}