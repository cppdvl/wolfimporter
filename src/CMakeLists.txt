cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
project(WolfImporter)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_library(WolfImporter 
    wolf/filesystemutils.cpp
    wolf/stringutils.cpp
    wolf/vectorutils.cpp
    wolf/file/file.cpp
    wolf/import/parser_obj.cpp
    wolf/glfw/glfw.cpp
)
target_include_directories(WolfImporter PRIVATE 

    ../include/
    ../Vendor/glm
    /usr/local/include
)


