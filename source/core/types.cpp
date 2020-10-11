#include <core\types.h>

namespace cap
{
	// --------- LuaMap --------------------------------------------- //
	LuaMap::LuaMap()
	{
		m_values = nullptr;
		m_keys = nullptr;
		m_count = 0;
	}

	int LuaMap::find(string key)
	{
		for (int i = 0; i < m_count; i++)
			if (m_keys[i] == key)
				return i;
		return -1;
	}

	void LuaMap::set(string key, LuaRef value)
	{
		int index = find(key);
		if (index < 0)
		{
			index = ++m_count;
			m_values = (LuaRef*)realloc(m_values, m_count);
			m_keys = (string*)realloc(m_keys, m_count);
		}

		m_values[index] = value;
		m_keys[index] = key;
	}

	LuaRef LuaMap::get(string key)
	{
		int index = find(key);
		if (index > 0) return m_values[index];
		return 0;
	}

	// ------ Point Class -------------------------------------//
	Point::Point(double x, double y) 
		: x(x), y(y) {}

	// ------ Rect Class -------------------------------------//
	Rect::Rect(double x, double y, double h, double w)
		: x(x), y(y), width(w), height(h) {}

	Rect::operator IntRect()
	{
		return IntRect(x, y, width, height);
	}

	Rect::operator FloatRect()
	{
		return FloatRect(x, y, width, height);
	}

	// ------ Texture Class -------------------------------------//
	Texture::Texture()
	{
		m_image = nullptr;
		m_texture = nullptr;
	}

	Sprite Texture::toSprite()
	{
		return Sprite(*m_texture);
	}

	Sprite Texture::cutRect(Rect rect)
	{
		return Sprite(*m_texture, rect);
	}

	Texture::operator sf::Texture()
	{
		return *m_texture;
	}

	Texture::operator sf::Image()
	{
		return *m_image;
	}

	// ------ Animation Class -------------------------------------//
	void Animation::addFrame(int delay, const Sprite texture)
	{
		frames.push_back({ delay, texture });
	}

	void Animation::setCurentFrame(int frame)
	{
		int size = frames.size();
		if (frame < size) current_frame = frame;
		else current_frame = size ? size - 1 : 0;
	}
}