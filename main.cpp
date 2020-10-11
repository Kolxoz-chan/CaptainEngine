#include <core\script.h>
#include <core\core.h>

#include <libraries/lua.hpp>

using namespace cap;


int main(int argc, char **argv)
{
	try
    {
        Core::init(640, 480, "Captain Engine 0.1");
        Core::initScript("main");
        Core::startLoop();
	}
	catch (LuaException err)
	{
		Script::print_log(err.what());
		Core::window->close();
		system("pause");
    }

	return 0;
}
