cmake_minimum_required(VERSION 3.11)

project(LifeLua)

add_executable(${PROJECT_NAME} 
    src/lifemain.c
    src/lifecolor.c
    src/lifedebug.c
    src/lifeos.c
    src/lifecontrols.c
    src/lifefont.c
    src/lifedraw.c
    src/ext/lutf8lib.c
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")

target_link_libraries(${PROJECT_NAME}
    lua
    osl
    png
    z
    psphprm
    pspsdk
    pspctrl
    psprtc
    psppower
    pspgu
    pspgum
    pspaudio
    psphttp
    pspssl
    pspwlan
    m
    jpeg
    pspdisplay
    pspnet_apctl
    pspnet_adhocmatching
    pspnet_adhoc
    pspnet_adhocctl
    pspdebug
    pspge
    pspnet
)

# Create an EBOOT.PBP file
create_pbp_file(
    TARGET ${PROJECT_NAME}
    ICON_PATH NULL
    BACKGROUND_PATH NULL
    PREVIEW_PATH NULL
    TITLE "LifeLua PSP"
    VERSION 01.00
)
