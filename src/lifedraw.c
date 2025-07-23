/*
    LifeLua WIP
    Draw library
*/

#include "lifeinit.h"

static int lua_swapbuff(lua_State *L) {
    oslEndDrawing();          // finish current drawing
    oslEndFrame();            // show frame
    oslSyncFrame();           // wait for vertical blank
    oslStartDrawing();        // start new drawing phase
    oslClearScreen(RGBA(0, 0, 0, 255));  // clear to black (fully opaque)
    return 0;
}

static const luaL_Reg draw_lib[] = {
    //{"text", lua_text},
	//{"textwidth", lua_textwidth},
	//{"textheight", lua_textheight},
    //{"rect", lua_rect},
    //{"circle", lua_circle},
	//{"triangle", lua_triangle},
	//{"radialcircle", lua_radialcircle},
    //{"line", lua_line},
	//{"pixel", lua_pixel},
	//{"gradientrect", lua_gradient},
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