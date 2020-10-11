#include <core\entity.h>
#include <core\core.h>

namespace cap
{
	// --------- LuaObject ------------------------------------------ //
	LuaObject::LuaObject()
	{
		self = Script::newRef();
	}

	Namespace& LuaObject::regLua(Namespace& global)
	{
		return global;
	}

	// Базовая сущность
	Entity::Entity(string name, int type) : name(name), type(type)
	{
		this->self = Script::newRef();
	}

	int Entity::getType()
	{
		return type;
	}

	string Entity::getName()
	{
		return name;
	}

	void Entity::setName(string name)
	{
		this->name = name;
	}

	Entity* Entity::getChild(int index)
	{
		return childs[index];
	}

	Entity* Entity::getParent()
	{
		return parent;
	}

	void Entity::addChild(Entity* child)
	{
		childs.push_back(child);
	}

	void Entity::update()
	{

	}

	// Точечная сущность
	PointEntity::PointEntity(string name) : Entity(name, CAP_POINT_ENTITY)
	{
	}

	void PointEntity::setPosition(Point pos)
	{
		this->position = pos;
	}

	Point PointEntity::getPosition()
	{
		return position;
	}

	void PointEntity::regLua(Namespace& global)
	{
		
	}

	// Пряогугольная сущность
	RectEntity::RectEntity(string name)
	{
		this->name = name;
		this->type = CAP_RECT_ENTITY;
	}

	void RectEntity::setSize(Point size)
	{
		this->size = size;
	}

	void RectEntity::setRect(int x, int y, int width, int height)
	{
		
	}

	void RectEntity::regLua(Namespace& global)
	{
		
	}

	// Текстурированая сущность
	DrawableEntity::DrawableEntity(string name)
	{
		this->name = name;
		this->type = CAP_DRAWABLE_ENTTY;
		this->drawable = nullptr;
	}

	DrawableEntity::~DrawableEntity()
	{
		if (drawable) delete drawable;
	}

	void DrawableEntity::setVisible(bool value)
	{
		this->visible = value;
	}

	void DrawableEntity::setTexture(Sprite sprite)
	{
		this->drawable = new Sprite(sprite);
	}

	void DrawableEntity::draw()
	{
		if (drawable && visible)
		{
			Core::window->draw(*drawable, states);
		}
	}

	void DrawableEntity::regLua(Namespace& global)
	{

	}
}
