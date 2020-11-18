#include <core\entity.h>

namespace cap
{
	/* -------------------- Base entity ---------------------- */
	Entity::Entity(string name, int type) : name(name), type(type)
	{
		this->self = Script::newTable();
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
		return m_parent;
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

	void PointEntity::move_to(Point vec, double step)
	{
		Point pos = getPosition();
		if (Point::distance(vec, pos) > step)
		{
			vec = vec - pos;
			double sum = abs(vec.x) + abs(vec.y);
			move((vec / sum) * step);
		}
		else setPosition(vec);
	}


	/* -------------------- Rect entity ---------------------- */
	RectEntity::RectEntity(const string& name)
	{
		this->name = name;
		this->type = CAP_RECT_ENTITY;
	}

	Point RectEntity::getCenter()
	{
		return Rect(position, size).getCenter();
	}

	Point RectEntity::getSize()
	{
		return size;
	}

	Rect RectEntity::getRect()
	{
		return Rect(position, size);
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
	}

	DrawableEntity::~DrawableEntity()
	{
		if (m_drawable) delete m_drawable;
	}

	void DrawableEntity::setVisible(bool value)
	{
		this->visible = value;
	}

	void DrawableEntity::setTexture(Sprite sprite)
	{
		m_drawable = new Sprite(sprite);
	}

	void DrawableEntity::draw(RenderTarget& target, RenderStates states) const
	{
		if (m_drawable && visible)
		{
			dynamic_cast<Transformable*>(m_drawable)->setPosition(position.round());
			target.draw(*m_drawable, states);
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

	void Camera::zoom(double value)
	{
		m_view.zoom(value);
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

	/* -------------------- Primitive entity ---------------------- */
	Primitive::Primitive(const string& name) : DrawableEntity(name)
	{
		m_drawable = new ConvexShape();
	}

	void Primitive::setBackgroundColor(const Color& color)
	{
		m_background_color = color;
	}

	void Primitive::setOutlineColor(const Color& color)
	{
		m_outline_color = color;
	}

	void Primitive::setOutlineThikness(double value)
	{
		m_outline_thickness = value;
	}

	void Primitive::generatePrimitive(int primitive)
	{
		ConvexShape* shape = static_cast<ConvexShape*>(m_drawable);
		shape->setPointCount(0);

		switch (primitive)
		{
		case CAP_PRIMITIVE_RECT:
			shape->setPointCount(4);

			shape->setPoint(0, Point(0, 0));
			shape->setPoint(1, Point(1, 0));
			shape->setPoint(2, Point(1, 1));
			shape->setPoint(3, Point(0, 1));

			break;
		}
	}

	void Primitive::clear()
	{
		static_cast<ConvexShape*>(m_drawable)->setPointCount(0);
	}

	void Primitive::addPoint(Point point)
	{
		ConvexShape* shape = static_cast<ConvexShape*>(m_drawable);
		shape->setPoint(shape->getPointCount(), point);
	}

	void Primitive::draw(RenderTarget& target, RenderStates states) const
	{
		if (m_drawable && visible)
		{
			ConvexShape shape = *dynamic_cast<ConvexShape*>(m_drawable);
			shape.setPosition(position.round());
			
			for (int i = 0; i < shape.getPointCount(); i++)
			{
				Point point = shape.getPoint(i);
				shape.setPoint(i, point * size);
			}

			shape.setFillColor(m_background_color);
			shape.setOutlineColor(m_outline_color);
			shape.setOutlineThickness(m_outline_thickness);

			target.draw(shape, states);
		}
	}
}
