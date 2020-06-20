cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
project(WolfImporter)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

file(GLOB           VENDORS_SOURCES ../Vendor/glad/src/glad.c)
file(GLOB           GUIIMPL_SOURCES ../Vendor/gui/examples/imgui_impl_glfw.*
                                    ../Vendor/gui/examples/imgui_impl_opengl3.*
                                    ../Vendor/gui/*.h
                                    ../Vendor/gui/imgui.cpp
                                    ../Vendor/gui/imgui_draw.cpp
                                    ../Vendor/gui/imgui_widgets.cpp)


list(APPEND FULL_SOURCES_LIST 
    ${VENDORS_SOURCES} 
    ${GUIIMPL_SOURCES})


add_library(${PROJECT_NAME} 
    wolf/filesystemutils.cpp
    wolf/stringutils.cpp
    wolf/vectorutils.cpp
    wolf/file/file.cpp
    wolf/import/parser_obj.cpp
    wolf/glfw/glfw.cpp
    wolf/gui/gui.cpp
    wolf/engine/engine.cpp
    wolf/engine/cliparser.cpp
    wolf/engine/sandboxmapper.cpp
)
target_sources(${PROJECT_NAME} PRIVATE 
    ${FULL_SOURCES_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE 

    ../include/
    ../Vendor/glm
    ../Vendor/glad/include
    ../Vendor/gui
    ../Vendor/gui/examples
    /usr/local/include
)


get_filename_component(ENGINE_RESOURCES_FULLPATH ../Resources ABSOLUTE)
set(ENGINE_RESOURCES_FULLPATH ${ENGINE_RESOURCES_FULLPATH} PARENT_SCOPE)