#include <core\entity.h>

namespace cap
{
	/* -------------------- Base entity ---------------------- */
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
		if (self["onUpdate"]) self["onUpdate"](self);
	}

	/* -------------------- Point entity ---------------------- */
	PointEntity::PointEntity(const string& name) : Entity(name, CAP_POINT_ENTITY)
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

	void PointEntity::move(Point vec)
	{
		position.x += vec.x;
		position.y += vec.y;
	}

	/* -------------------- Rect entity ---------------------- */
	RectEntity::RectEntity(const string& name)
	{
		this->name = name;
		this->type = CAP_RECT_ENTITY;
	}

	void RectEntity::setSize(Point size)
	{
		this->size = size;
	}

	void RectEntity::setRect(Rect rect)
	{
		this->position = rect.getPosition();
		this->size = rect.getSize();
	}

	/* -------------------- Drawable entity ---------------------- */
	DrawableEntity::DrawableEntity(const string& name)
	{
		this->name = name;
		this->type = CAP_DRAWABLE_ENTTY;
		this->drawable = nullptr;
		this->visible = true;
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

	void DrawableEntity::draw(RenderTarget& target, RenderStates states) const
	{
		if (drawable && visible)
		{
			dynamic_cast<Transformable*>(drawable)->setPosition(position.round());
			target.draw(*drawable, states);
		}
	}

	/* -------------------- Camera entity ---------------------- */
	Camera::Camera(Rect rect)
	{
		m_view.reset(rect);
	}

	Camera::Camera(const View& view)
	{
		m_view = view;
	}

	void Camera::resize(const Point& size)
	{
		m_view.reset(FloatRect(0, 0, size.x, size.y));
	}

	void Camera::update()
	{
		m_view.setCenter((int)position.x, (int)position.y);
	}

	const View& Camera::getView()
	{
		return m_view;
	}
}
