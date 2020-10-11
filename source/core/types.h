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

	};

	// Прямоугольник
	class Rect
	{
	public:
		double x, y, width, height;

		Rect(double x = 0.0, double y = 0.0, double h = 0.0, double w = 0.0);

		operator IntRect();
		operator FloatRect();

	};

	// Обёртка текстуры
	class Texture
	{
	private:
		sf::Image* m_image;
		sf::Texture* m_texture;

	public:
		Texture();

		Sprite toSprite();
		Sprite cutRect(Rect rect);

		operator sf::Texture();
		operator sf::Image();

	};
	using Tileset = vector<cap::Texture*>;
	using Tilesets = map<string, Tileset>;

	// Анимация 
	class Animation : public Drawable
	{
		using Frame = pair<int, const Sprite>;

	private:
		bool started = false;
		int current_frame = 0;
		vector<Frame> frames;

	public:
		Animation() = default;

		void addFrame(int delay, const Sprite texture);

		void setCurentFrame(int frame);
		
	};
}