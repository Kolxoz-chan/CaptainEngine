#pragma once
#include <libraries\lua.hpp>
#include <libraries\std.hpp>

class Script
{
private:
	static lua_State *L;

    Script() = delete;
    ~Script() = delete;

public:
    static void init();
    static void free();

	template <class T>
    static LuaRef toLua(T value)
	{
		return LuaRef(L, value);
	}

	template <class T>
    static void setVar(string name, T value)
	{
        setGlobal(L, value, name.c_str());
	}

	static LuaRef newRef();
	static LuaRef newTable();

    static LuaRef getVar(string name);

    static bool include(string file);
    static LuaRef eval(string code);
    static Namespace global();

	static void reset_log(string value);
	static void print_log(string value);
};
