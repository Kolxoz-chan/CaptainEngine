#include <core\script.h>

lua_State*		Script::L;

void Script::init()
{
    L = luaL_newstate();
    luaL_openlibs(L);
    LuaException::enableExceptions(L);
}

void Script::free()
{
    lua_close(L);
}

bool Script::include(string file)
{
	if (luaL_dofile(L, file.c_str()))
	{	
		print_log(lua_tostring(L, -1));
		lua_pop(L, 1);
		return false;
	}
	else return true;
}

LuaRef Script::eval(string code)
{
	LuaRef loadstring = getVar("load");
	LuaRef value = loadstring("return " + code);
	return value();
}

Namespace Script::global()
{
	return getGlobalNamespace(L);
}

LuaRef Script::getVar(string name)
{
	return getGlobal(L, name.c_str());
}

LuaRef Script::newRef()
{
	return LuaRef(L);
}

LuaRef Script::newTable()
{
	return luabridge::newTable(L);
}

void Script::addRequirePath(string path)
{
	LuaRef package = getVar("package");
	package["path"] = package["path"].cast<string>() + ";" + path;
}

void Script::reset_log(string value)
{
	fstream file;
	file.open("log.txt", ios::out);
	if (file.is_open())
	{
		file << value << "\n";
	}
	file.close();
}

void Script::print_log(string value)
{
	cout << value << endl;
	fstream file;
	file.open("log.txt", ios::out|ios::app);
	if (file.is_open())
	{
		file << value << "\n";
	}
	file.close();
}
