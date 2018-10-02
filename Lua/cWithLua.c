//Both libraries required to import Lua scripting
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int main()
{
	// To work with Lua
	//(1) loads the Lua interpreter to C
	lua_State *L = luaL_newstate();
	//(2) loads the Lua libraries to C
	luaL_openlibs(L);
	//(3) Loads the Lua code to C
	luaL_dofile(L, "luaToC.lua");

	//Access variables within the Lua file
	lua_getglobal(L, "foo");
	if (lua_isnil(L, -1))
	{
		printf("The number is nil\n");
	}
	else
	{
		int i = lua_tonumber(L, -1);
		printf("The number is %d\n", i);
	}

	//Access functions within the Lua file
	lua_getglobal(L, "func1");
	lua_pcall(L, 0, 0, 0);

	//Access functions within the Lua file and pass through C an argument to func2
	lua_getglobal(L, "func2");
	lua_pushnumber(L, 2);
	lua_pcall(L, 1, 1, 0);
	int result = lua_tonumber(L, -1);
	printf("Func2 returns %d\n", result);


	return 0;
}
