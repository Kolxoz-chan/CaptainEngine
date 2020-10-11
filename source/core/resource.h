#pragma once

// --------------- Base Reource --------------------------- //
class Resource
{
protected:
	int type;

public:
	Resource();

	int getType();
};

// --------------- Tileset Reource --------------------------- //
class Tileset : public Resource
{
private:
	

public:
	Tileset();

};