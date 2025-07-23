/*
    LifeLua WIP
    Font library
*/

#include "lifeinit.h"

static int lua_loadfont(lua_State *L){
	const char *filename = luaL_checkstring(L, 1);
    Font *font = (Font *)lua_newuserdata(L, sizeof(Font));
	//memset(font, 0, sizeof(Font));
    font->font = oslLoadFontFile(filename);

	luaL_getmetatable(L, "font");
    lua_setmetatable(L, -2);
	return 1;
}

static int lua_defaultfont(lua_State *L){
	Font *font = (Font *)luaL_checkudata(L, 1, "font");
    oslSetFont(font->font);
	return 0;
}

static int lua_fontprops(lua_State *L){
	Font *font = (Font *)luaL_checkudata(L, 1, "font");
    luaL_checktype(L, 2, LUA_TTABLE);

    lua_getfield(L, 2, "size");
    float size = luaL_optnumber(L, -1, 1.0);
    lua_pop(L, 1);

    lua_getfield(L, 2, "color");
    Color *color = lua_tocolor(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, 2, "shadow");
    Color *s_color = lua_tocolor(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, 2, "angle");
    float angle = luaL_optnumber(L, -1, 0.f);
    lua_pop(L, 1);

    lua_getfield(L, 2, "options");
    int options = luaL_optnumber(L, -1, INTRAFONT_ALIGN_LEFT);
    lua_pop(L, 1);

    oslIntraFontSetStyle(font->font, size, color->color, s_color->color, angle, options);
	return 0;
}

static int lua_fontgc(lua_State *L){
	Font *font = (Font *)luaL_checkudata(L, 1, "font");
    oslDeleteFont(font->font);
	return 0;
}

static int lua_text(lua_State *L){
    Font *font = (Font *)luaL_checkudata(L, 1, "font");
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);
    const char *text = luaL_checkstring(L, 4);
    oslDrawString(x, y, text);
    return 0;
}

static int lua_textbox(lua_State *L){
    Font *font = (Font *)luaL_checkudata(L, 1, "font");
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);
    int w = luaL_checkinteger(L, 4);
    int h = luaL_checkinteger(L, 5);
    const char *text = luaL_checkstring(L, 6);
    oslDrawTextBox(x, y, w, h, text, 0);
    return 0;
}

static const luaL_Reg font_lib[] = {
    {"load", lua_loadfont},
	{"default", lua_defaultfont},
    {"properties", lua_fontprops},
    {"text", lua_text},
    {"textbox", lua_textbox},
    {NULL, NULL}
};

static const luaL_Reg font_methods[] = {
	{"default", lua_defaultfont},
    {"properties", lua_fontprops},
    {"text", lua_text},
    {"textbox", lua_textbox},
    {NULL, NULL}
};

LUALIB_API int luaL_openfont(lua_State *L){
	luaL_newmetatable(L, "font");
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);  /* pushes the metatable */
    lua_settable(L, -3);  /* metatable.__index = metatable */
    
    luaL_register(L, NULL, font_methods);

	luaL_register(L, "font", font_lib);
    return 1;
}