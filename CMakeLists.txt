cmake_minimum_required(VERSION 3.11)

project(LifeLua)

add_executable(${PROJECT_NAME} 
src/lifemain.c
src/lifecolor.c
src/lifedebug.c
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

target_link_libraries(${PROJECT_NAME}
    lua
    osl
    png
    z
    m
    psphprm 
    pspsdk 
    pspctrl
    pspumd
    psprtc
    psppower
    pspgu
    pspgum
    pspge
    pspdebug
    pspdisplay
    pspaudiolib
    pspaudio
    psphttp
    pspssl
    pspwlan
    pspnet_adhocmatching
    pspnet_adhoc
    pspnet_adhocctl
    jpeg
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
