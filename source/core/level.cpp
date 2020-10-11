#include <core\level.h>
#include <core\core.h>

namespace cap
{
	// -------- Contaner Class -------------------------------------------------------------------- //
	Container::Container(string name, int type)
	{
		this->name = name;
		this->type = type;
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

	void TileLayer::addTile(Sprite tile, int x, int y)
	{
		tile.setPosition(x, y);
		tiles[x][y] = tile;
	}

	void TileLayer::draw()
	{
		/*
		for (int i = 0; i < tiles.size(); i++)
		{
			Core::window->draw(tiles[i])
		}*/
	}

	void TileLayer::update()
	{

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

	void ObjectLayer::draw()
	{

	}

	void ObjectLayer::update()
	{

	}

	// --------- Class GroupLayer ------------------------------------------------------------------ //
	GroupLayer::GroupLayer(string name) : Container(name, CAP_GROUP_CONTAINER)
	{

	}

	void GroupLayer::addContainer(Container* container)
	{
		containers.push_back(container);
	}

	void GroupLayer::draw()
	{
		for (auto cont : containers)
		{
			if (cont->isVisible()) cont->draw();
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

	void Level::draw()
	{
		for (auto cont : containers)
		{
			if (cont->isVisible()) cont->draw();
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