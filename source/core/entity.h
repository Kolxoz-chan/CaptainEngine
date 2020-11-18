#pragma once
#include <core\types.h>
#include <core\script.h>
#include <core\constants.h>

#include <libraries\std.hpp>

namespace cap
{
	class Container;

	// Базовая сущность
	class Entity
	{
	protected:
		Container* m_container = nullptr;
		Entity* m_parent = nullptr;
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

		virtual void update();
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

		void move(Point vec);
		void move_to(Point vec, double step);
	};

	// Прямоугольная сущность
	class RectEntity : public PointEntity
	{
	protected:
		Point size;

	public:
		RectEntity(const string& name = "object");

		Point getCenter();
		Point getSize();
		Rect getRect();

		void setSize(Point size);
		void setRect(Rect rect);
	};

	// Отображаемая сущность
	class DrawableEntity : public RectEntity, public Drawable
	{
	protected:
		RenderStates states;
		Drawable* m_drawable = nullptr;
		bool visible = true;

		virtual void draw(RenderTarget& target, RenderStates states) const;

	public:
		DrawableEntity(const string& name = "object");
		~DrawableEntity();

		void setTexture(Sprite sprite);

		void setVisible(bool value);
	};

	// --------------- Camera entity ------------------- //
	class Camera : public RectEntity
	{
	private:
		View m_view;

	public:
		Camera(const string& name = "object") : RectEntity(name) {};
		Camera(const View& view);
		Camera(Rect rect);

		void zoom(double value);
		void resize(const Point& size);
		void update();

		const View& getView();
	};

	// ----------- Primitive Entity ---------------------- //
	class Primitive : public DrawableEntity
	{
	private:
		Color m_background_color, m_outline_color;
		double m_outline_thickness = 0;

		void draw(RenderTarget& target, RenderStates states) const;

	public:
		Primitive(const string& name = "object");

		void setBackgroundColor(const Color& color);
		void setOutlineColor(const Color& color);
		void setOutlineThikness(double value);

		void generatePrimitive(int primitive);

		void clear();
		void addPoint(Point point);
	};
}