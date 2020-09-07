cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
project(WolfImporter)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
option(GLFW_BUILD_DOCS OFF)
get_filename_component(GLFW_FULLPATH Vendor/glfw ABSOLUTE)
add_subdirectory(${GLFW_FULLPATH})
get_filename_component(SPDLOG_FULLPATH Vendor/log ABSOLUTE)
add_subdirectory(${SPDLOG_FULLPATH})


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
    src/wolf/glfw/glfw.cpp
    src/wolf/gui/gui.cpp
    src/wolf/engine/scene.cpp
    src/wolf/engine/engine.cpp
    src/wolf/engine/cliparser.cpp
    src/wolf/engine/sandboxmapper.cpp
    src/wolf/resources/resourcemanager.cpp
    src/wolf/import/resourceloader.cpp
        include/wolf/engine/gamemanager.hpp
        include/wolf/import/resources/resourceloader_json.hpp
        src/wolf/import/resources/resourceloader_json.cpp
        src/wolf/ecs/component/component.cpp
        include/wolf/ecs/component/component.hpp
        src/wolf/id.cpp include/wolf/id.hpp
        src/wolf/ecs/component/component_name.cpp
        include/wolf/ecs/component/component_name.hpp
        src/wolf/ecs/component/component_mesh.cpp
        include/wolf/ecs/component/component_mesh.hpp
        src/wolf/resources/resourcemesh.cpp
        include/wolf/resources/resourcemesh.hpp
        src/wolf/resources/resource.cpp
        include/wolf/resources/resource.hpp
        src/wolf/resources/resourcenameutils.cpp
        include/wolf/resources/resourcenameutils.hpp
        include/wolf/ecs/scenebuilder.cpp
        include/wolf/ecs/scenebuilder.hpp
        include/wolf/resources/json/resourcejson.hpp
        include/wolf/resources/resourcefactory.hpp
        src/wolf/resources/resourcefactory.cpp
        src/wolf/resources/json/resourcejson.cpp
        include/wolf/resources/json/resourcejsonvisitor.cpp
        include/wolf/resources/json/resourcejsonvisitor.hpp
        src/wolf/ecs/ecsnode.cpp include/wolf/ecs/ecsnode.hpp
        src/wolf/ecs/component/componentfactory.cpp
        include/wolf/ecs/component/componentfactory.hpp)

target_link_libraries(  ${PROJECT_NAME} PRIVATE glfw
                        ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                        nlohmann_json::nlohmann_json
                        spdlog)
target_sources(${PROJECT_NAME} PRIVATE ${FULL_SOURCES_LIST})

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
