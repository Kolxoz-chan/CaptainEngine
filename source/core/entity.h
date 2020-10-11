#pragma once
#include <core\types.h>
#include <core\script.h>

#include <libraries\std.hpp>

namespace cap
{
	// ������� ����� ��� Lua-��������
	class LuaObject
	{
	public:
		LuaRef self = 0;

		LuaObject();
		static Namespace& regLua(Namespace& global);
	};

	// ������� ��������
	class Entity : public LuaObject
	{
	protected:
		Entity* parent;
		vector<Entity*> childs;
		string name;
		int type;

	public:
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
		PointEntity(string name = "object");

		void setPosition(Point pos);

		Point getPosition();

		// ����������� ������
		static void regLua(Namespace& global);
	};

	// ������������� ��������
	class RectEntity : public PointEntity
	{
	protected:
		Point size;

	public:
		RectEntity(string name = "object");

		void setSize(Point size);
		void setRect(int x, int y, int width, int height);

		// ����������� ������
		static void regLua(Namespace& global);
	};

	// ������������ ��������
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

		// ����������� ������
		static void regLua(Namespace& global);
	};
}