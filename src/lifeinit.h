/*
	LifeLua WIP, a PS Vita LuaJIT interpreter
	by Harommel OddSock
*/

#ifndef LJ_LIFEINIT_H
#define LJ_LIFEINIT_H

#include <oslib/oslib.h>
#include <stdbool.h>

#ifdef __cplusplus
#include <lua.hpp>
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

#define luaL_pushglobalint(L, value) lua_pushinteger(L, value); lua_setglobal(L, #value);
#define luaL_pushglobalint_as(L, value, var) lua_pushinteger(L, value); lua_setglobal(L, var);
#define luaL_pushglobalint_alsoas(L, value, var) luaL_pushglobalint(L, value); luaL_pushglobalint_as(L, value, var);
#define lerp(value, from_max, to_max) ((((value*10) * (to_max*10))/(from_max*10))/10)
#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

#if LUA_VERSION_NUM >= 502
#define luaL_register(L, name, reg) luaL_setfuncs(L, reg, 0); lua_setglobal(L, reg);
#endif

#ifndef LUA_OK
#define LUA_OK		0
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if (LUA_VERSION_NUM <= 501)
void *luaL_testudata(lua_State *L, int ud, const char *tname);
#endif

/*
extern char vita_ip[16];
extern unsigned short int vita_port;
*/
extern SceCtrlData pad, oldpad;
/*
extern bool unsafe;

extern vita2d_pgf *pgf;
extern vita2d_pvf *pvf;
*/
typedef struct {
    unsigned int color;
} Color;

typedef struct {
	OSL_FONT *font;
} Font;
/*
typedef struct {
    vita2d_texture *tex;
} Image;

int string_ends_with(const char * str, const char * suffix);

int file_exists(const char* path);

void makeHeadBin(const char *dir);

void utf2ascii(char* dst, uint16_t* src);

void ascii2utf(uint16_t* dst, char* src);
*/
Color *lua_tocolor(lua_State *L, int n);
/*
LUALIB_API int luaL_opentimer(lua_State *L);
LUALIB_API int luaL_extendio(lua_State *L);*/
LUALIB_API int luaL_extendos(lua_State *L);/*
LUALIB_API int luaL_opennetwork(lua_State *L);*/
LUALIB_API int luaL_opencontrols(lua_State *L);/*
LUALIB_API int luaL_opensqlite3(lua_State *L);*/
LUALIB_API int luaL_opendraw(lua_State *L);
LUALIB_API int luaL_opencolor(lua_State *L);
LUALIB_API int luaL_opendebugscreen(lua_State *L);/*
LUALIB_API int luaL_openimage(lua_State *L);*/
LUALIB_API int luaL_openfont(lua_State *L);/*
LUALIB_API int luaL_opencamera(lua_State *L);
LUALIB_API int luaL_openthread(lua_State *L);
//LUALIB_API int luaL_openimgui(lua_State *L);
LUALIB_API int luaL_openjson(lua_State *L);*/
LUALIB_API int luaL_openutf8(lua_State *L);/*
//LUALIB_API int luaL_openaudio(lua_State *L);
*/

#ifdef __cplusplus
}
#endif
#endif