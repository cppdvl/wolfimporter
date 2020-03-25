cmake_minimum_required(VERSION 3.12)
project(wolfimportexample VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_executable(wolfimportexample example.cpp
    ../src/wolf/filesystemutils.cpp
    ../src/wolf/import/_3dformats/_3dfileparser.cpp
    ../src/wolf/import/_3dformats/file.cpp
    ../src/wolf/import/_3dformats/mtlfileparser.cpp
    ../src/wolf/import/_3dformats/objfileparser.cpp
    ../src/wolf/import/wavefrontutils.cpp
    ../src/wolf/maputils.cpp
    ../src/wolf/stringutils.cpp
    ../src/wolf/vectorutils.cpp
)
target_include_directories(wolfimportexample PRIVATE
	../include
    ../Vendor/glm)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/*.mtl $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_SHADERS})
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/*.obj $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_SHADERS})
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/*.png $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_SHADERS})
