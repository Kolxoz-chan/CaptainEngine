#pragma once
#include <core\types.h>
#include <core\script.h>

#include <libraries\std.hpp>

namespace cap
{
	// Базовая сущность
	class Entity
	{
	protected:
		Entity* parent;
		vector<Entity*> childs;
		string name;
		int type;

	public:
		LuaRef self = 0;

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

		virtual void update() {};
	};

	// Точечная сущность
	class PointEntity : public Entity
	{
	protected:
		Point position;

	public:
		PointEntity(const string& name = "object");

		void setPosition(Point pos);

		Point getPosition();

		void move(float x, float y);
		void move(Point vec);
	};

	// Прямоугольная сущность
	class RectEntity : public PointEntity
	{
	protected:
		Point size;

	public:
		RectEntity(const string& name = "object");

		void setSize(Point size);
		void setRect(Rect rect);
	};

	// Отображаемая сущность
	class DrawableEntity : public RectEntity
	{
	private:
		RenderStates states;
		Drawable* drawable;
		bool visible;

	public:
		DrawableEntity(const string& name = "object");
		~DrawableEntity();

		void setTexture(Sprite sprite);

		void setVisible(bool value);

		virtual void draw();
	};

	// ----------- Custom Entities ---------------------- //
	class Camera : public RectEntity
	{
	private:
		View m_view;

	public:
		Camera();
		Camera(Rect rect);

		void resize(const Point& size);
		void update();

		const View& getView();
	};
}