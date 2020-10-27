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
			index = m_count++;
			m_values = (LuaRef*)realloc(m_values, sizeof(LuaRef) * m_count);
			m_keys = (string*)realloc(m_keys, sizeof(string) * m_count);
		}
		
		m_keys[index] = key;
		m_values[index] = value;
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

	Point::Point(const Vector2f& point)
		: x(point.x), y(point.y) {};

	Point::Point(const Vector2i& point)
		: x(point.x), y(point.y) {};

	Point::Point(const Vector2u& point)
		: x(point.x), y(point.y) {};

	Point operator+ (const Point& left, const Point& right)
	{
		return Point(left.x + right.x, left.y + right.y);
	}

	Point operator- (const Point& left, const Point& right)
	{
		return Point(left.x - right.x, left.y - right.y);
	}

	Point operator* (const Point& left, const Point& right)
	{
		return Point(left.x * right.x, left.y * right.y);
	}

	Point operator* (const Point& left, float right)
	{
		return Point(left.x * right, left.y * right);
	}

	Point operator/ (const Point& left, const Point& right)
	{
		return Point(left.x / right.x, left.y / right.y);
	}

	Point operator/ (const Point& left, float right)
	{
		return Point(left.x / right, left.y / right);
	}

	Point::operator Vector2f()
	{
		return Vector2f(x, y);
	}

	Point::operator Vector2i()
	{
		return Vector2i(x, y);
	}

	Point::operator Vector2u()
	{
		return Vector2u(x, y);
	}

	Point::operator const char* ()
	{
		string str = "Point(" + to_string(x) + ", " + to_string(y) + ")";
		return str.c_str();
	}

	// ------ Tileset Class -------------------------------------//
	string Tileset::getName()
	{
		return m_name;
	}

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
				Point pos = Point(x, y) * (tile_size + Point(margin, margin)) + Point(spacing, spacing);
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

	// ------ Rect Class -------------------------------------//
	Rect::Rect(double x, double y, double h, double w)
		: x(x), y(y), width(w), height(h) {}

	Rect::Rect(Point pos, Point size) 
		: x(pos.x), y(pos.y), width(size.x), height(size.y){}

	Point Rect::getPosition()
	{
		return Point(x, y);
	}

	Point Rect::getSize()
	{
		return Point(width, height);
	}

	Point Rect::getCenter()
	{
		return Point(x + width / 2, y + height / 2);
	}

	Point Rect::getLeftTop()
	{
		return Point(x, y);
	}

	Point Rect::getLeftBottom()
	{
		return Point(x, y + height);
	}

	Point Rect::getRightTop()
	{
		return Point(x + width, y);
	}

	Point Rect::getRightBottom()
	{
		return Point(x + width, y + height);
	}

	Rect::operator IntRect()
	{
		return IntRect(x, y, width, height);
	}

	Rect::operator FloatRect()
	{
		return FloatRect(x, y, width, height);
	}

	Rect::operator const char* ()
	{
		string str = "Rect(" + to_string(x) + ", " + to_string(y) + ", " + to_string(width) + "x" + to_string(height) + ")";
		return str.c_str();
	}

	// ------ Animation Class -------------------------------------//
	void Animation::addFrame(int delay, const Sprite& texture)
	{
		frames.push_back(Frame(delay, texture));
	}

	void Animation::setCurentFrame(int frame)
	{
		int size = frames.size();

		if (frame < size) current_frame = frame;
		else current_frame = size ? size - 1 : 0;

		timer.restart();
		time = 0;
	}

	int Animation::getNextFrame()
	{
		if (current_frame == frames.size() - 1) return 0;
		return ++current_frame;
	}

	void Animation::update()
	{
		if (frames.size() > 1)
		{
			Frame frame = frames[current_frame];
			time += timer.restart().asMilliseconds();
			if (time > frame.first)
			{
				time -= frame.first;
				current_frame = getNextFrame();
			}
		}
	}

	void Animation::draw(RenderTarget& target, RenderStates states) const
	{
		if (frames.size())
		{
			Sprite sprite = frames[current_frame].second;
			target.draw(sprite);
		}
	}

	void Animation::play()
	{
		started = true;
	}

	void Animation::pause()
	{
		started = false;
	}

	void Animation::stop()
	{
		restart();
		pause();
	}

	void Animation::restart()
	{
		time = 0;
		started = true;
		current_frame = 0;
		timer.restart();
	}

	int Animation::length()
	{
		return frames.size();
	}
}