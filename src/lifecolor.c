/*
    LifeLua WIP
    Color library
*/

#include "lifeinit.h"

Color *lua_tocolor(lua_State *L, int n) {
    Color *color = (Color *)luaL_testudata(L, n, "color");
    if (color) return color;
    if (lua_isnumber(L, n)) {
        unsigned int col = luaL_checknumber(L, n);
        Color *newcolor = (Color *)lua_newuserdata(L, sizeof(Color));
        newcolor->color = RGBA(col & 0xFF, (col >> 8) & 0xFF, (col >> 16) & 0xFF, (col >> 24) & 0xFF); //ABGR to RGBA
        luaL_getmetatable(L, "color");
        lua_setmetatable(L, -2);
        return newcolor;
    }
    return (Color *)luaL_typerror(L, n, "color");
}

static int lua_tocolortype(lua_State *L){
	unsigned int col = luaL_checknumber(L, 1);
    Color *color = (Color *)lua_newuserdata(L, sizeof(Color));
    color->color = RGBA(col & 0xFF, (col >> 8) & 0xFF, (col >> 16) & 0xFF, (col >> 24) & 0xFF); //ABGR to RGBA
    luaL_getmetatable(L, "color");
    lua_setmetatable(L, -2);
	return 1;
}

static int lua_newcolor(lua_State *L) {
	unsigned int r = luaL_checkinteger(L, 1);
	unsigned int g = luaL_checkinteger(L, 2);
	unsigned int b = luaL_checkinteger(L, 3);
	unsigned int a = luaL_optinteger(L, 4, 255);
	Color *color = (Color *)lua_newuserdata(L, sizeof(Color));
	color->color = (a == 255) ? RGB(CLAMP(r, 0, 255), CLAMP(g, 0, 255), CLAMP(b, 0, 255)) : RGBA(CLAMP(r, 0, 255), CLAMP(g, 0, 255), CLAMP(b, 0, 255), CLAMP(a, 0, 255));
	luaL_getmetatable(L, "color");
    lua_setmetatable(L, -2);
	return 1;
}

static int lua_colorr(lua_State *L){
	Color *color = (Color *)luaL_checkudata(L, 1, "color");
    u8 red, green, blue, alpha;
    oslRgbaGet8888(color->color, red, green, blue, alpha);
	if(lua_isnone(L, 2)){
        lua_pushnumber(L, red);
	}else if(lua_isnumber(L, 2)){
		unsigned int r = luaL_checkinteger(L, 2);
		Color *res = (Color *)lua_newuserdata(L, sizeof(Color));
		res->color = RGBA(CLAMP(r, 0, 255), green, blue, alpha);
		luaL_getmetatable(L, "color");
    	lua_setmetatable(L, -2);
	}
	return 1;
}

static int lua_colorg(lua_State *L){
	Color *color = (Color *)luaL_checkudata(L, 1, "color");
    u8 red, green, blue, alpha;
    oslRgbaGet8888(color->color, red, green, blue, alpha);
	if(lua_isnone(L, 2)){
        lua_pushnumber(L, green);
	}else if(lua_isnumber(L, 2)){
		unsigned int g = luaL_checkinteger(L, 2);
		Color *res = (Color *)lua_newuserdata(L, sizeof(Color));
		res->color = RGBA(red, CLAMP(g, 0, 255), blue, alpha);
		luaL_getmetatable(L, "color");
    	lua_setmetatable(L, -2);
	}
	return 1;
}

static int lua_colorb(lua_State *L){
	Color *color = (Color *)luaL_checkudata(L, 1, "color");
    u8 red, green, blue, alpha;
    oslRgbaGet8888(color->color, red, green, blue, alpha);
	if(lua_isnone(L, 2)){
        lua_pushnumber(L, blue);
	}else if(lua_isnumber(L, 2)){
		unsigned int b = luaL_checkinteger(L, 2);
		Color *res = (Color *)lua_newuserdata(L, sizeof(Color));
		res->color = RGBA(red, green, CLAMP(b, 0, 255), alpha);
		luaL_getmetatable(L, "color");
    	lua_setmetatable(L, -2);
	}
	return 1;
}

static int lua_colora(lua_State *L){
	Color *color = (Color *)luaL_checkudata(L, 1, "color");
    u8 red, green, blue, alpha;
    oslRgbaGet8888(color->color, red, green, blue, alpha);
	if(lua_isnone(L, 2)){
        lua_pushnumber(L, alpha);
	}else if (lua_isnumber(L, 2)){
		unsigned int a = luaL_checkinteger(L, 2);
		Color *res = (Color *)lua_newuserdata(L, sizeof(Color));
		res->color = RGBA(red, green, blue, CLAMP(a, 0, 255));
		luaL_getmetatable(L, "color");
    	lua_setmetatable(L, -2);
	}
	return 1;
}

static int lua_coloradd(lua_State *L){
	Color *color1 = (Color *)luaL_checkudata(L, 1, "color");
	Color *color2 = (Color *)luaL_checkudata(L, 2, "color");
    u8 red, green, blue, alpha, red1, green1, blue1, alpha1;
    oslRgbaGet8888(color1->color, red, green, blue, alpha);
    oslRgbaGet8888(color2->color, red1, green1, blue1, alpha1);

	Color *color = (Color *)lua_newuserdata(L, sizeof(Color));
	color->color = RGBA(
		CLAMP(red+red1, 0, 255), //r
		CLAMP(green+green1, 0, 255), //g
		CLAMP(blue+blue1, 0, 255), //b
		CLAMP(alpha+alpha1, 0, 255));
	luaL_getmetatable(L, "color");
    lua_setmetatable(L, -2);
	return 1;
}

static int lua_colorsub(lua_State *L){
	Color *color1 = (Color *)luaL_checkudata(L, 1, "color");
	Color *color2 = (Color *)luaL_checkudata(L, 2, "color");
    u8 red, green, blue, alpha, red1, green1, blue1, alpha1;
    oslRgbaGet8888(color1->color, red, green, blue, alpha);
    oslRgbaGet8888(color2->color, red1, green1, blue1, alpha1);

	Color *color = (Color *)lua_newuserdata(L, sizeof(Color));
	color->color = RGBA(
		CLAMP(red-red1, 0, 255), //r
		CLAMP(green-green1, 0, 255), //g
		CLAMP(blue-blue1, 0, 255), //b
		CLAMP(alpha-alpha1, 0, 255));
	luaL_getmetatable(L, "color");
    lua_setmetatable(L, -2);
	return 1;
}

static int lua_coloreq(lua_State *L){
	Color *color1 = (Color *)luaL_checkudata(L, 1, "color");
	Color *color2 = (Color *)luaL_checkudata(L, 2, "color");
	lua_pushboolean(L, color1->color == color2->color);
	return 1;
}

static int lua_colorblend(lua_State *L) {
    Color *c1 = (Color *)luaL_checkudata(L, 1, "color");
    Color *c2 = (Color *)luaL_checkudata(L, 2, "color");

    Color *result = (Color *)lua_newuserdata(L, sizeof(Color));
    result->color = oslBlendColors(c1->color, c2->color);

    luaL_getmetatable(L, "color");
    lua_setmetatable(L, -2);
    return 1;
}

static int lua_colormix(lua_State *L) {
    Color *color1 = (Color *)luaL_checkudata(L, 1, "color");
    Color *color2 = (Color *)luaL_checkudata(L, 2, "color");
    u8 red, green, blue, alpha, red1, green1, blue1, alpha1;
    oslRgbaGet8888(color1->color, red, green, blue, alpha);
    oslRgbaGet8888(color2->color, red1, green1, blue1, alpha1);
    float p1 = luaL_checknumber(L, 3);
    float p2 = luaL_checknumber(L, 4);

    float sum = p1 + p2;
    if (sum <= 0.0f) sum = 1.0f; // avoid division by zero

    float f1 = p1 / sum;
    float f2 = p2 / sum;

    Color *result = (Color *)lua_newuserdata(L, sizeof(Color));
    result->color = RGBA(
        CLAMP((int)(red * f1 + red1 * f2), 0, 255),
        CLAMP((int)(green * f1 + green1 * f2), 0, 255),
        CLAMP((int)(blue * f1 + blue1 * f2), 0, 255),
        CLAMP((int)(alpha * f1 + alpha1 * f2), 0, 255)
    );

    luaL_getmetatable(L, "color");
    lua_setmetatable(L, -2);
    return 1;
}

static const luaL_Reg color_lib[] = {
    {"new", lua_newcolor},
	{"r", lua_colorr},
	{"g", lua_colorg},
	{"b", lua_colorb},
	{"a", lua_colora},
	{"add", lua_coloradd},
	{"sub", lua_colorsub},
	{"blend", lua_colorblend},
	{"mix", lua_colormix},
    {NULL, NULL}
};

static const luaL_Reg color_methods[] = {
	{"r", lua_colorr},
	{"g", lua_colorg},
	{"b", lua_colorb},
	{"a", lua_colora},
	{"add", lua_coloradd},
	{"sub", lua_colorsub},
	{"blend", lua_colorblend},
	{"mix", lua_colormix},
	{"__add", lua_coloradd},
	{"__sub", lua_colorsub},
	{"__eq", lua_coloreq},
    {NULL, NULL}
};

LUALIB_API int luaL_opencolor(lua_State *L) {
	luaL_newmetatable(L, "color");
	lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);  /* pushes the metatable */
    lua_settable(L, -3);  /* metatable.__index = metatable */
    
    luaL_register(L, NULL, color_methods);

	luaL_register(L, "color", color_lib);
	lua_register(L, "tocolor", lua_tocolortype);
    return 1;
}