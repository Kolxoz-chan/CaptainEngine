#include <core\level.h>

namespace cap
{
	// -------- Contaner Class -------------------------------------------------------------------- //
	Container::Container(string name, int type)
	{
		this->name = name;
		this->type = type;
		this->visible = true;
		this->offset_x = 0; 
		this->offset_y = 0;
		this->opacity = 1.0;
	}

	double Container::getOpacity()
	{
		return opacity;
	}

	Point Container::getOffset()
	{
		return Point(offset_x, offset_y);
	}

	const string& Container::getName()
	{
		return name;
	}

	bool Container::isVisible()
	{
		return visible;
	}

	void Container::setVisible(bool value)
	{
		this->visible = value;
	}

	void Container::setOffset(int x, int y)
	{
		this->offset_x = x;
		this->offset_y = y;
	}

	void Container::setOpacity(double value)
	{
		this->opacity = value;
	}

	void Container::setName(const string& name)
	{
		this->name = name;
	}

	// --------- Class TileLayer ------------------------------------------------------------------ //
	TileLayer::TileLayer(string name) : Container(name, CAP_TILE_CONTAINER)
	{

	}

	void TileLayer::addTile(Sprite tile, Point pos)
	{
		m_tiles[pos] = tile;
	}

	void TileLayer::draw(RenderTarget& target, RenderStates states) const
	{
		View view = target.getView();
		Point center = view.getCenter();
		Point size = view.getSize();
		Rect rect = Rect(center - size / 2, size) / Rect(m_tilesize, m_tilesize) + Rect(-1, -1, 1, 1);
		rect = rect.round();

		for (int x = rect.x; x < rect.width; x++)
		{
			for (int y = rect.y; y < rect.height; y++)
			{
				Point point = Point(x, y);
				if (m_tiles.find(point) != m_tiles.end())
				{
					target.draw(m_tiles.at(point), states);
				}
				else if (m_objects.find(point) != m_objects.end())
				{
					target.draw(*m_objects.at(point), states);
				}
			}
		}
	}

	void TileLayer::update()
	{

	}

	void TileLayer::setTilesize(Point size)
	{
		m_tilesize = size;
	}

	TileLayer* TileLayer::fromContainer(Container* container)
	{
		if (container)
		{
			/// ????????????? ////
		}
		return nullptr;
	}

	// --------- Class ObjectLayer ------------------------------------------------------------------ //
	ObjectLayer::ObjectLayer(string name) : Container(name, CAP_OBJECT_CONTAINER)
	{

	}

	void ObjectLayer::addObject(Entity* obj)
	{
		int type = obj->getType();
		all_objects.push_back(obj);
		if (type == CAP_DRAWABLE_ENTTY)
		{
			drawable_objects.push_back((DrawableEntity*)obj);
		}
			
	}

	void ObjectLayer::draw(RenderTarget& target, RenderStates states) const
	{
		for (auto obj : drawable_objects) target.draw(*obj, states);
	}

	void ObjectLayer::update()
	{
		for (auto obj : all_objects) obj->update();
	}

	// --------- Class GroupLayer ------------------------------------------------------------------ //
	GroupLayer::GroupLayer(string name) : Container(name, CAP_GROUP_CONTAINER)
	{

	}

	void GroupLayer::addContainer(Container* container)
	{
		containers.push_back(container);
	}

	void GroupLayer::draw(RenderTarget& target, RenderStates states) const
	{
		for (auto container : containers)
		{
			if (container->isVisible()) target.draw(*container);
		}
	}

	void GroupLayer::update()
	{
		for (auto cont : containers)
		{
			cont->update();
		}
	}

	// --------- Class Level ------------------------------------------------------------------ //

	Level::Level(string name)
	{
		this->name = name;
	}

	Level::~Level()
	{
	}

	const string& Level::getName()
	{
		return name;
	}

	Container* Level::getContainer(int index)
	{
		return containers[index];
	}

	Container* Level::getContainer(string name)
	{
		for (int i = 0; i < containers.size(); i++)
		{
			if (containers[i]->getName() == name)
				return containers[i];
		}
		return nullptr;
	}

	void Level::addContainer(Container* container)
	{
		containers.push_back(container);
	}

	void Level::draw(RenderTarget& target, RenderStates states) const
	{
		for (auto container : containers)
		{
			if (container->isVisible()) target.draw(*container);
		}
	}

	void Level::update()
	{
		for (auto cont : containers)
		{
			cont->update();
		}
	}
}