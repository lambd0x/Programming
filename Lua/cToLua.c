//Both libraries required to import Lua scripting
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int l_bar(lua_State *L)
{
	const char *str = lua_tostring(L, -1);

	char c;
	int length = 0;
	do
	{
		c = str[length];
		length++;
	}
	while (c != '\0');

	lua_pushstring(L, str);
	lua_pushnumber(L, length);

	return 2;
}

int main()
{
	// To work with Lua
	//(1) loads the Lua interpreter to C
	lua_State *L = luaL_newstate();
	//(2) loads the Lua libraries to C
	luaL_openlibs(L);
	//(3) Loads the Lua code to C
	luaL_dofile(L, "luaWithC.lua");

	//push argument to function in Lua
	lua_pushcfunction(L, l_bar);
	lua_setglobal(L, "bar");
	lua_getglobal(L, "foo");
	lua_pushstring(L, "cheeseburguer");
	lua_pcall(L, 1, 1, 0);
	int result2 = lua_tonumber(L, -1);
	printf("result2 is %d\n", result2);

	return 0;
}
