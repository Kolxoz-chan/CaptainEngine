#pragma once
#include <core\types.h>
#include <core\script.h>

#include <libraries\std.hpp>

namespace cap
{
	// Базовый класс для Lua-объектов
	class LuaObject
	{
	public:
		LuaRef self = 0;

		LuaObject();
		static Namespace& regLua(Namespace& global);
	};

	// Базовая сущность
	class Entity : public LuaObject
	{
	protected:
		Entity* parent;
		vector<Entity*> childs;
		string name;
		int type;

	public:
		// Конструктор
		Entity(string name, int type);

		// get-методы
		int getType();
		string getName();
		Entity* getChild(int index);
		Entity* getParent();

		// set-методы
		void setName(string name);

		void addChild(Entity* child);

		virtual void update();
	};

	// Точечная сущность
	class PointEntity : public Entity
	{
	protected:
		Point position;

	public:
		PointEntity(string name = "object");

		void setPosition(Point pos);

		Point getPosition();

		// Регистрация класса
		static void regLua(Namespace& global);
	};

	// Прямоугольная сущность
	class RectEntity : public PointEntity
	{
	protected:
		Point size;

	public:
		RectEntity(string name = "object");

		void setSize(Point size);
		void setRect(int x, int y, int width, int height);

		// Регистрация класса
		static void regLua(Namespace& global);
	};

	// Отображаемая сущность
	class DrawableEntity : public RectEntity
	{
	private:
		RenderStates states;
		Drawable* drawable;
		bool visible;

	public:
		DrawableEntity(string name = "object");
		~DrawableEntity();

		void setTexture(Sprite sprite);

		void setVisible(bool value);

		virtual void draw();

		// Регистрация класса
		static void regLua(Namespace& global);
	};
}