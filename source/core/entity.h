#pragma once
#include <core\types.h>
#include <core\script.h>
#include <core\constants.h>

#include <libraries\std.hpp>

namespace cap
{
	// ������� ��������
	class Entity
	{
	protected:
		Entity* parent;
		vector<Entity*> childs;
		string name;
		int type;

	public:
		LuaRef self = 0;

		// �����������
		Entity(string name, int type);

		// get-������
		int getType();
		string getName();
		Entity* getChild(int index);
		Entity* getParent();

		// set-������
		void setName(string name);

		void addChild(Entity* child);

		virtual void update();
	};

	// �������� ��������
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

	// ������������� ��������
	class RectEntity : public PointEntity
	{
	protected:
		Point size;

	public:
		RectEntity(const string& name = "object");

		void setSize(Point size);
		void setRect(Rect rect);
	};

	// ������������ ��������
	class DrawableEntity : public RectEntity, public Drawable
	{
	private:
		RenderStates states;
		Drawable* drawable;
		bool visible;

		void draw(RenderTarget& target, RenderStates states) const;

	public:
		DrawableEntity(const string& name = "object");
		~DrawableEntity();

		void setTexture(Sprite sprite);

		void setVisible(bool value);
	};

	// ----------- Custom Entities ---------------------- //
	class Camera : public RectEntity
	{
	private:
		View m_view;

	public:
		Camera() = default;
		Camera(const View& view);
		Camera(Rect rect);

		void resize(const Point& size);
		void update();

		const View& getView();
	};
}