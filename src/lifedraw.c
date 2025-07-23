/*
    LifeLua WIP
    Draw library
*/

#include "lifeinit.h"

static int lua_swapbuff(lua_State *L) {
    oslEndDrawing();
    oslSwapBuffers();
    oslSyncFrame();
    oslStartDrawing();
    return 0;
}

static int lua_rect(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int w = luaL_checkinteger(L, 3);
    int h = luaL_checkinteger(L, 4);
    Color *color = lua_tocolor(L, 5);
    Color *outline; if(!lua_isnone(L, 6)) outline = lua_tocolor(L, 6);
    oslDrawFillRect(x, y, w, h, color->color);
    if(!lua_isnone(L, 6)) oslDrawRect(x, y, w, h, outline->color);
    return 0;
}

static int lua_line(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int w = luaL_checkinteger(L, 3);
    int h = luaL_checkinteger(L, 4);
    Color *color = lua_tocolor(L, 5);
    oslDrawLine(x, y, w, h, color->color);
    return 0;
}

static int lua_gradient(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int w = luaL_checkinteger(L, 3);
    int h = luaL_checkinteger(L, 4);
    Color *c1 = lua_tocolor(L, 5);
    Color *c2 = lua_tocolor(L, 6);
    Color *c3 = lua_tocolor(L, 7);
    Color *c4 = lua_tocolor(L, 8);
    oslDrawGradientRect(x, y, w, h, c1->color, c2->color, c3->color, c4->color);
    return 0;
}

static const luaL_Reg draw_lib[] = {
    //{"text", lua_text},
	//{"textwidth", lua_textwidth},
	//{"textheight", lua_textheight},
    {"rect", lua_rect},
    //{"circle", lua_circle},
	//{"triangle", lua_triangle},
	//{"radialcircle", lua_radialcircle},
    {"line", lua_line},
	//{"pixel", lua_pixel},
	{"gradientrect", lua_gradient},
	//{"hdoublegradientrect", lua_hdoublegradient},
	//{"vdoublegradientrect", lua_vdoublegradient},
	//{"enableclip", lua_enableclip},
	//{"cliprect", lua_cliprect},
	//{"clipcircle", lua_clipcircle},
    {"swapbuffers", lua_swapbuff},
    {NULL, NULL}
};

LUALIB_API int luaL_opendraw(lua_State *L) {
	luaL_register(L, "draw", draw_lib);
    return 1;
}