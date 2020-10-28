#pragma once
#include <core/constants.h>
#include <core/types.h>
#include <core/entity.h>

#include <libraries/std.hpp>
#include <libraries/sfml.hpp>

namespace cap
{
	// Base container class //
	class Container
	{
	protected:
		int type;
		string name;
		bool visible;
		int offset_x, offset_y;
		double opacity;

	public:
		Container(string name, int type);

		void setVisible(bool value);
		void setOffset(int x, int y);
		void setOpacity(double value);
		void setName(const string& name);

		double getOpacity();
		Point getOffset();
		const string& getName();

		virtual void draw() = 0;
		virtual void update() = 0;

		bool isVisible();
	};

	// Tile layer class //
	class TileLayer : public Container
	{
		using TileMatrix = map<int, map<int, Sprite>>;
		using ObjectMatrix = map<int, map<int, Entity*>>;

	private:
		TileMatrix tiles;
		ObjectMatrix objects;

	public:
		TileLayer(string name);

		void addTile(Sprite sprite, int x, int y);

		void draw();
		void update();

		// static functions
		static TileLayer* fromContainer(Container* container);
	};

	// Object layer class //
	class ObjectLayer : public Container
	{
	private:
		vector<Entity*> all_objects;
		vector<DrawableEntity*> drawable_objects;

	public:
		ObjectLayer(string name);

		void addObject(Entity* obj);

		void draw();
		void update();

		static ObjectLayer* fromContainer(Container* container);
	};

	// Group layer class //
	class GroupLayer : public Container
	{
	private:
		vector<Container*> containers;

	public:
		GroupLayer(string name);

		void addContainer(Container* container);

		void draw();
		void update();

		static GroupLayer* fromContainer(Container* container);
	};

	// Level class //
	class Level
	{
	private:
		string name;
		vector<Container*> containers;

	public:
		Level(string name = "");
		~Level();

		const string& getName();
		Container* getContainer(int index);
		Container* getContainer(string name);

		void addContainer(Container* container);

		void draw();
		void update();
	};
}