/*
    LifeLua WIP
    OS library extension
*/

#include "lifeinit.h"

static int lua_delay(lua_State *L) {
	float secs = luaL_optnumber(L, 1, 0);
    sceKernelDelayThread(secs * 1000*1000);
    return 0;
}

static int lua_delaycb(lua_State *L) {
	float secs = luaL_optnumber(L, 1, 0);
    sceKernelDelayThreadCB(secs * 1000*1000);
    return 0;
}

static int lua_osk(lua_State *L){
    const char *desc = luaL_checkstring(L, 1);
    const char *deft = luaL_optstring(L, 2, "");
    int tlim = luaL_optinteger(L, 3, 255);
    int ln = luaL_optinteger(L, 4, 1);
    oslInitOsk((char *)desc, (char *)deft, tlim, ln, -1);
    oslDialogDrawAndWait(OSL_DIALOG_OSK);
    if(oslOskGetResult() == PSP_UTILITY_OSK_RESULT_CANCELLED) lua_pushnil(L);
    else{
        char res[tlim];
        oslOskGetText(res);
        lua_pushstring(L, res);
    }
    oslEndOsk();
    return 1;
}

static int lua_message(lua_State *L){
    const char *msg = luaL_checkstring(L, 1);
    bool yn = lua_toboolean(L, 2);
    oslInitMessageDialog(msg, yn);
    oslDialogDrawAndWait(OSL_DIALOG_MESSAGE);
    if(yn){
        if(oslGetDialogButtonPressed() == PSP_UTILITY_MSGDIALOG_RESULT_NO) lua_pushboolean(L, false);
        else if(oslGetDialogButtonPressed() == PSP_UTILITY_MSGDIALOG_RESULT_YES) lua_pushboolean(L, true);
    }else{
        if(oslDialogGetResult() == OSL_DIALOG_OK){
            if(oslGetDialogButtonPressed() == PSP_UTILITY_MSGDIALOG_RESULT_NO) lua_pushboolean(L, false);
            else if(oslGetDialogButtonPressed() == PSP_UTILITY_MSGDIALOG_RESULT_YES) lua_pushboolean(L, true);
        }else if(oslDialogGetResult() == OSL_DIALOG_CANCEL){
            lua_pushboolean(L, false);
        }
    }
    return 1;
}

static int lua_errormessage(lua_State *L){
    const unsigned int error = luaL_checknumber(L, 1);
    oslInitErrorDialog(error);
    oslDialogDrawAndWait(OSL_DIALOG_ERROR);
    return 0;
}

static int lua_netconf(lua_State *L){
    oslInitNetDialog();
    oslDialogDrawAndWait(OSL_DIALOG_NETCONF);
    return 0;
}

static int lua_browser(lua_State *L){
    const char *url = luaL_checkstring(L, 1);
    const char *dpath = luaL_optstring(L, 2, "/PSP/PHOTO");
    int dmode = luaL_optinteger(L, 3, PSP_UTILITY_HTMLVIEWER_DISPLAYMODE_NORMAL);
    int opt = luaL_optinteger(L, 4, PSP_UTILITY_HTMLVIEWER_DISABLE_STARTUP_LIMITS);
    int imode = luaL_optinteger(L, 5, PSP_UTILITY_HTMLVIEWER_INTERFACEMODE_FULL);
    int cmode = luaL_optinteger(L, 6, PSP_UTILITY_HTMLVIEWER_CONNECTMODE_MANUAL_ALL);
    int res = oslBrowserInit((char *)url, (char *)dpath, 5*1024*1024, dmode, opt, imode, cmode);
    oslDialogDrawAndWait(OSL_DIALOG_BROWSER);
    return 0;
}

static int lua_language(lua_State *L){
    int l;
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &l);
    lua_pushinteger(L, l);
    return 1;
}

static int lua_nickname(lua_State *L){
    char n[2048];
    sceUtilityGetSystemParamString(PSP_SYSTEMPARAM_ID_STRING_NICKNAME, n, sizeof(n));
    lua_pushstring(L, n);
    return 1;
}

static int lua_splash1(lua_State *L){
    oslShowSplashScreen1();
    return 1;
}

static int lua_splash2(lua_State *L){
    oslShowSplashScreen2();
    return 1;
}

static const luaL_Reg os_lib[] = {
    {"delay", lua_delay},
    {"delaycb", lua_delaycb},
	{"keyboard", lua_osk}, {"osk", lua_osk},
	{"message", lua_message},
	{"errormessage", lua_errormessage},
    {"netconf", lua_netconf},
    {"browser", lua_browser},
    {"language", lua_language},
    {"nickname", lua_nickname},
    {"splash1", lua_splash1},
    {"splash2", lua_splash2},
    {NULL, NULL}
};

LUALIB_API int luaL_extendos(lua_State *L) {
	luaL_register(L, "os", os_lib);
    luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_DISPLAYMODE_NORMAL);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_DISPLAYMODE_FIT);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_DISPLAYMODE_SMART_FIT);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_OPEN_SCE_START_PAGE);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_DISABLE_STARTUP_LIMITS);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_DISABLE_EXIT_DIALOG);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_DISABLE_CURSOR);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_DISABLE_DOWNLOAD_COMPLETE_DIALOG);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_DISABLE_DOWNLOAD_START_DIALOG);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_DISABLE_DOWNLOAD_DESTINATION_DIALOG);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_LOCK_DOWNLOAD_DESTINATION_DIALOG);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_DISABLE_TAB_DISPLAY);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_ENABLE_ANALOG_HOLD);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_ENABLE_FLASH);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_DISABLE_LRTRIGGER);
    luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_INTERFACEMODE_FULL);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_INTERFACEMODE_LIMITED);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_INTERFACEMODE_NONE);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_CONNECTMODE_LAST);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_CONNECTMODE_MANUAL_ONCE);
	luaL_pushglobalint(L, PSP_UTILITY_HTMLVIEWER_CONNECTMODE_MANUAL_ALL);
    luaL_pushglobalint(L, PSP_SYSTEMPARAM_LANGUAGE_JAPANESE);
    luaL_pushglobalint(L, PSP_SYSTEMPARAM_LANGUAGE_ENGLISH);
    luaL_pushglobalint(L, PSP_SYSTEMPARAM_LANGUAGE_FRENCH);
    luaL_pushglobalint(L, PSP_SYSTEMPARAM_LANGUAGE_SPANISH);
    luaL_pushglobalint(L, PSP_SYSTEMPARAM_LANGUAGE_GERMAN);
    luaL_pushglobalint(L, PSP_SYSTEMPARAM_LANGUAGE_ITALIAN);
    luaL_pushglobalint(L, PSP_SYSTEMPARAM_LANGUAGE_DUTCH);
    luaL_pushglobalint(L, PSP_SYSTEMPARAM_LANGUAGE_PORTUGUESE);
    luaL_pushglobalint(L, PSP_SYSTEMPARAM_LANGUAGE_RUSSIAN);
    luaL_pushglobalint(L, PSP_SYSTEMPARAM_LANGUAGE_KOREAN);
    luaL_pushglobalint(L, PSP_SYSTEMPARAM_LANGUAGE_CHINESE_TRADITIONAL);
    luaL_pushglobalint(L, PSP_SYSTEMPARAM_LANGUAGE_CHINESE_SIMPLIFIED);
    return 1;
}