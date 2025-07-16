/*
    LifeLua WIP
    Debug screen library
*/

#include "lifeinit.h"

static int lua_dinit(lua_State *L){
    pspDebugScreenInit();
    return 0;
}

static int lua_d_bg_enable(lua_State *L){
    bool enable = lua_toboolean(L, 1);
    pspDebugScreenEnableBackColor(enable);
    return 0;
}

static int lua_dbg(lua_State *L){
    Color *color = lua_tocolor(L, 1);
    pspDebugScreenSetBackColor(color->color);
    return 0;
}

static int lua_dfg(lua_State *L){
    Color *color = lua_tocolor(L, 1);
    pspDebugScreenSetTextColor(color->color);
    return 0;
}

static int lua_drawtext(lua_State *L){
    const char *str = luaL_checkstring(L, 1);
    pspDebugScreenPuts(str);
    return 0;
}

static int lua_dclear(lua_State *L){
    pspDebugScreenClear();
    return 0;
}

static int lua_dxy(lua_State *L){
    if(lua_isnone(L, 1)){
        lua_newtable(L);
        lua_pushinteger(L, pspDebugScreenGetX());
        lua_setfield(L, -2, "x");
        lua_pushinteger(L, pspDebugScreenGetY());
        lua_setfield(L, -2, "y");
        return 1;
    }else{
        int x = luaL_checkinteger(L, 1);
        int y = luaL_checkinteger(L, 2);
        pspDebugScreenSetXY(x, y);
    }
    return 0;
}

static int lua_clearline(lua_State *L){
    bool clr = lua_toboolean(L, 1);
    if(clr) pspDebugScreenClearLineEnable();
    else pspDebugScreenClearLineDisable();
    return 0;
}

static const luaL_Reg debug_lib[] = {
    {"init", lua_dinit},
    {"backcolorenable", lua_d_bg_enable},
    {"textcolor", lua_dfg},
    {"backcolor", lua_dbg},
    {"text", lua_drawtext},
    {"coords", lua_dxy},
    {"clear", lua_dclear},
    {"clearline", lua_clearline},
    {NULL, NULL}
};

LUALIB_API int luaL_opendebugscreen(lua_State *L) {
    luaL_register(L, "debugscreen", debug_lib);
    return 1;
}