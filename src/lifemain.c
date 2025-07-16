// LifeLua for the PSP

#include "lifeinit.h"
#include "include/asprintf.h"

// PSP_MODULE_INFO(name, attrs, major version, minor version) - just in mind
PSP_MODULE_INFO("LifeLua PSP", 0, 0, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);

lua_State *L;
SceCtrlData pad, oldpad;

/*-- Compat - Lua 5.1 --------------------------------------------------------*/

#if (LUA_VERSION_NUM <= 501)
void *luaL_testudata(lua_State *L, int ud, const char *tname) {
  void *p = lua_touserdata(L, ud);
  if (p != NULL) {  /* value is a userdata? */
    if (lua_getmetatable(L, ud)) {  /* does it have a metatable? */
      luaL_getmetatable(L, tname);  /* get correct metatable */
      if (!lua_rawequal(L, -1, -2))  /* not the same? */
        p = NULL;  /* value is a userdata with wrong metatable */
      lua_pop(L, 2);  /* remove both metatables */
      return p;
    }
  }
  return NULL;  /* value is not a userdata with a metatable */
}
#endif

int exit_callback(int arg1, int arg2, void *common) {
    lua_getglobal(L, "LifeLuaExitCallback");
	if (lua_isfunction(L, -1)) lua_call(L, 0, 0);
	sceKernelExitGame();
    return 0;
}

int callback_thread(SceSize args, void *argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

int setup_callbacks() {
    SceUID thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xFA0, 0, 0);
    if(thid >= 0) sceKernelStartThread(thid, 0, 0);
    return thid;
}

void luaL_lifelua_dofile(lua_State *L) {
    char *error = NULL;

    while(true) {
        if(luaL_dofile(L, "main.lua") == LUA_OK) break; // Success, exit loop

        asprintf(&error, "LifeLua has encountered an error:\n%s\n\nDo you want to retry?", lua_tostring(L, -1));

        oslInitMessageDialog(error, 1);
        oslDialogDrawAndWait(OSL_DIALOG_MESSAGE);

        if(oslGetDialogButtonPressed() == PSP_UTILITY_MSGDIALOG_RESULT_NO) break;
        else if(oslGetDialogButtonPressed() == PSP_UTILITY_MSGDIALOG_RESULT_YES) continue; // Retry
    }
}

int main(){
    setup_callbacks();
    oslInit(0);
    oslInitGfx(OSL_PF_8888, 1);
    oslInitAudio();
    oslSetQuitOnLoadFailure(1);
    oslIntraFontInit(INTRAFONT_CACHE_ALL | INTRAFONT_STRING_UTF8);

    L = luaL_newstate();
    luaL_openlibs(L);
    luaL_opencolor(L);
    luaL_opendebugscreen(L);
    luaL_openutf8(L);

    luaL_lifelua_dofile(L);

    oslEndGfx();
    lua_close(L);
    
    sceKernelExitGame();
    return 0;
}
