#include "resource.h"

namespace cap
{
	Sprite Tileset::getTile(int index)
	{
		return m_tiles[index];
	}

	Sprite Tileset::getTile(Point coords)
	{
		return m_tiles[coords.y * m_tileset_size.x + coords.x - 1];;
	}

	void Tileset::subdivide(sf::Texture* texture, Point tileset_size, Point tile_size, int spacing, int margin)
	{
		m_texrture = texture;
		m_tileset_size = tileset_size;
		m_tile_size = tile_size;
		m_margin = margin;
		m_spacing = spacing;

		for (int y = 0; y < tileset_size.y; y++)
		{
			for (int x = 0; x < tileset_size.x; x++)
			{
				Point pos = Point(x, y) * (tile_size + margin) + spacing;
				m_tiles.push_back(Sprite(*m_texrture, Rect(pos, tile_size)));
			}
		}
	}

	void Tileset::concat(const Tileset& tileset)
	{
		m_tiles.insert(m_tiles.end(), tileset.m_tiles.begin(), tileset.m_tiles.end());
	}

	int Tileset::length()
	{
		return m_tiles.size();
	}

	void Tileset::clear()
	{
		m_tiles.clear();
	}
}