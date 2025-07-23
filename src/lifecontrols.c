/*
    LifeLua WIP
    Controls library
*/

#include "lifeinit.h"

static int lua_updatecontrols(lua_State *L){
	oldpad = pad;
	sceCtrlPeekBufferPositive(&pad, 1);
	return 0;
}

static int lua_check(lua_State *L){
	int button = luaL_checkinteger(L, 1);
	lua_pushboolean(L, pad.Buttons & button);
	return 1;
}

static int lua_pressed(lua_State *L){
	int button = luaL_checkinteger(L, 1);
	lua_pushboolean(L, (pad.Buttons & button) && !(oldpad.Buttons & button));
	return 1;
}

static int lua_held(lua_State *L){
	int button = luaL_checkinteger(L, 1);
	lua_pushboolean(L, (pad.Buttons & button) && (oldpad.Buttons & button));
	return 1;
}

static int lua_released(lua_State *L){
	int button = luaL_checkinteger(L, 1);
	lua_pushboolean(L, !(pad.Buttons & button) && (oldpad.Buttons & button));
	return 1;
}
static int lua_analogl(lua_State *L){
	lua_pushinteger(L, pad.Lx - 128);
	lua_pushinteger(L, pad.Ly - 128);
	return 2;
}

static int lua_analogr(lua_State *L){
	lua_pushinteger(L, pad.Rx - 128);
	lua_pushinteger(L, pad.Ry - 128);
	return 2;
}

static const luaL_Reg controls_lib[] = {
	{"update", lua_updatecontrols},
	{"check", lua_check},
	{"pressed", lua_pressed},
	{"held", lua_held},
	{"released", lua_released},
	{"leftanalog", lua_analogl},
	{"rightanalog", lua_analogr},
    {NULL, NULL}
};

LUALIB_API int luaL_opencontrols(lua_State *L) {
	luaL_register(L, "controls", controls_lib);
	luaL_pushglobalint(L, PSP_CTRL_SELECT);
	luaL_pushglobalint(L, PSP_CTRL_START);
	luaL_pushglobalint(L, PSP_CTRL_UP);
	luaL_pushglobalint(L, PSP_CTRL_RIGHT);
	luaL_pushglobalint(L, PSP_CTRL_DOWN);
	luaL_pushglobalint(L, PSP_CTRL_LEFT);
	luaL_pushglobalint(L, PSP_CTRL_LTRIGGER);
	luaL_pushglobalint(L, PSP_CTRL_RTRIGGER);
	luaL_pushglobalint(L, PSP_CTRL_TRIANGLE);
	luaL_pushglobalint(L, PSP_CTRL_CIRCLE);
	luaL_pushglobalint(L, PSP_CTRL_CROSS);
	luaL_pushglobalint(L, PSP_CTRL_SQUARE);
	luaL_pushglobalint(L, PSP_CTRL_HOME);
	luaL_pushglobalint(L, PSP_CTRL_HOLD);
	luaL_pushglobalint(L, PSP_CTRL_NOTE);
	luaL_pushglobalint(L, PSP_CTRL_SCREEN);
	luaL_pushglobalint(L, PSP_CTRL_VOLUP);
	luaL_pushglobalint(L, PSP_CTRL_VOLDOWN);
	luaL_pushglobalint(L, PSP_CTRL_WLAN_UP);
	luaL_pushglobalint(L, PSP_CTRL_REMOTE);
	luaL_pushglobalint(L, PSP_CTRL_DISC);
	luaL_pushglobalint(L, PSP_CTRL_MS);
    return 1;
}