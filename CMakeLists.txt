cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
project(WolfImporter)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
option(GLFW_BUILD_DOCS OFF)
get_filename_component(GLFW_FULLPATH Vendor/glfw ABSOLUTE)
add_subdirectory(${GLFW_FULLPATH})

include(FetchContent)


FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
    GIT_TAG v3.8.0
    )
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

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
    src/wolf/engine/resources/resourcemanager.cpp
    src/wolf/import/resourceloader.cpp
        include/wolf/import/resources/resourceloader_json.hpp
        src/wolf/import/resources/resourceloader_json.cpp
        src/wolf/engine/ecs/component.cpp
        include/wolf/engine/ecs/component.hpp
        src/wolf/engine/id.cpp include/wolf/engine/id.hpp
        src/wolf/engine/ecs/component/component_name.cpp
        include/wolf/engine/ecs/component/component_name.hpp
        src/wolf/engine/ecs/component/component_mesh.cpp
        include/wolf/engine/ecs/component/component_mesh.hpp
        src/wolf/engine/resources/resourcemesh.cpp
        include/wolf/engine/resources/resourcemesh.hpp
        src/wolf/engine/resources/resource.cpp
        include/wolf/engine/resources/resource.hpp
        src/wolf/engine/resources/resourcenameutils.cpp
        include/wolf/engine/resources/resourcenameutils.hpp
        )
target_link_libraries(  ${PROJECT_NAME} PRIVATE glfw
                        ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                        nlohmann_json::nlohmann_json)
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
