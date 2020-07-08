cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
project(WolfImporter)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
option(GLFW_BUILD_DOCS OFF)
get_filename_component(GLFW_FULLPATH Vendor/glfw ABSOLUTE)
add_subdirectory(${GLFW_FULLPATH})


file(GLOB           VENDORS_SOURCES Vendor/glad/src/glad.c)
file(GLOB           GUIIMPL_SOURCES Vendor/gui/examples/imgui_impl_glfw.*
                                    Vendor/gui/examples/imgui_impl_opengl3.*
                                    Vendor/gui/*.h
                                    Vendor/gui/imgui.cpp
                                    Vendor/gui/imgui_draw.cpp
                                    Vendor/gui/imgui_widgets.cpp)


list(APPEND FULL_SOURCES_LIST 
    ${VENDORS_SOURCES} 
    ${GUIIMPL_SOURCES})


add_library(${PROJECT_NAME} 
    src/wolf/filesystemutils.cpp
    src/wolf/stringutils.cpp
    src/wolf/vectorutils.cpp
    src/wolf/file/file.cpp
    src/wolf/import/parser_obj.cpp
    src/wolf/glfw/glfw.cpp
    src/wolf/gui/gui.cpp
    src/wolf/engine/scene.cpp
    src/wolf/engine/engine.cpp
    src/wolf/engine/cliparser.cpp
    src/wolf/engine/sandboxmapper.cpp
    src/wolf/engine/resourcemanager.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
target_sources(${PROJECT_NAME} PRIVATE 
    ${FULL_SOURCES_LIST})
list(APPEND ENGINE_HEADERS 

    include/
    Vendor/glm
    Vendor/glad/include
    Vendor/gui
    Vendor/gui/examples
    Vendor/signalslot
    /usr/local/include

)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${ENGINE_HEADERS}
)

add_definitions(-DGLFW_INCLUDE_NONE)

get_filename_component(ENGINE_RESOURCES_FULLPATH Resources ABSOLUTE)
get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
    set(ENGINE_RESOURCES_FULLPATH ${ENGINE_RESOURCES_FULLPATH} PARENT_SCOPE)
endif()
