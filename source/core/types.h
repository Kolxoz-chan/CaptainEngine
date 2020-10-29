#pragma once
#include <libraries\std.hpp>
#include <libraries\sfml.hpp>
#include <libraries\lua.hpp>

namespace cap
{
	// Ассоциативнй массив для LuaRef
	class LuaMap
	{
	private:
		LuaRef* m_values;
		string* m_keys;
		size_t m_count;

	public:
		LuaMap();

		int find(string key);
		void set(string key, LuaRef values);
		LuaRef get(string key);
	};

	// Двумерный вектор
	class Point
	{
	public:
		double x, y;

		Point(double x = 0.0, double y = 0.0);
		Point(const Vector2f& point);
		Point(const Vector2i& point);
		Point(const Vector2u& point);

		inline Point round() const
		{
			return Point((int)x, (int)y);
		}

		friend Point operator+ (const Point& left, const Point& right);
		friend Point operator- (const Point& left, const Point& right);
		friend Point operator* (const Point& left, const Point& right);
		friend Point operator/ (const Point& left, const Point& right);
		friend Point operator* (const Point& left, float right);
		friend Point operator/ (const Point& left, float right);

		bool operator== (const Point& right) const;
		bool operator< (const Point& right) const;

		operator Vector2f();
		operator Vector2i();
		operator Vector2u();

		inline operator const char* ()
		{
			return toString();
		}

		const char* toString();
		bool isEqual(const Point* left, const Point* right);

		static double distance(const Point& left, const Point& right);
	};

	// Rect class
	class Rect
	{
	public:
		double x, y, width, height;

		Rect(double x = 0.0, double y = 0.0, double h = 0.0, double w = 0.0);
		Rect(Point pos , Point size);

		Rect round();

		Point getPosition();
		Point getSize();
		Point getCenter();
		Point getLeftTop();
		Point getLeftBottom();
		Point getRightTop();
		Point getRightBottom();

		friend Rect operator+ (const Rect& left, const Rect& right);
		friend Rect operator- (const Rect& left, const Rect& right);
		friend Rect operator* (const Rect& left, const Rect& right);
		friend Rect operator/ (const Rect& left, const Rect& right);
		friend Rect operator* (const Rect& left, float right);
		friend Rect operator/ (const Rect& left, float right);

		operator IntRect();
		operator FloatRect();

		operator const char* ();
	};

	// Tileset class
	class Tileset
	{
	private:
		string m_name;
		sf::Texture* m_texrture = nullptr;
		vector<sf::Sprite> m_tiles;
		Point m_tileset_size, m_tile_size, m_margin, m_spacing;

	public:
		Tileset(string name = string()) : m_name(name) {};

		string getName();
		Sprite getTile(int index);
		Sprite getTile(Point coords);
		inline Sprite getTile(int x, int y) { return getTile(Point(x, y)); };

		void subdivide(sf::Texture* texture, Point tileset_size, Point tile_size, int spacing = 0, int margin = 0);
		void concat(const Tileset& tileset);
		int length();
		void clear();
	};
	using TilesetList = vector<Tileset*>;
	using TilesetMap = map<string, Tileset*>;

	// Anmation class 
	class Animation : public Drawable
	{
		using Frame = pair<int, const Sprite>;

	private:
		bool started = true;
		Clock timer;
		int time = 0;
		int current_frame = 0;
		vector<Frame> frames;

		void draw(RenderTarget& target, RenderStates states) const;
		int getNextFrame();

	public:
		Animation() = default;

		void addFrame(int delay, const Sprite& texture);

		void setCurentFrame(int frame);

		void play();
		void pause();
		void stop();
		void restart();
		void update();

		int length();
	};
}