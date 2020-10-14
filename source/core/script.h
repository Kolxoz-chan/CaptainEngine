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

	// Convert to lua-value //
	template <class T>
    static LuaRef toLua(T value)
	{
		return LuaRef(L, value);
	}

	// Convert to table //
	template <class T>
	static LuaRef toTable(vector<T> arr)
	{
		LuaRef table = newTable();
		for (int i = 0; i < arr.size(); i++)
		{
			table[i] = arr[i];
		}
		return table;
	}

	// Convert to table //
	template <class T>
	static LuaRef toTable(map<string, T> arr)
	{
		LuaRef table = newTable();
		for (pair<string, T> p : arr)
		{
			table[p.first] = p.second;
		}
		return table;
	}

	// Set global varriable //
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
