cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project(WolfImporter)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
add_library(LibWolfImporter 
	wolf/filesystemutils.cpp
	wolf/import/_3dformats/_3dfileparser.cpp
	wolf/import/_3dformats/file.cpp
	wolf/import/_3dformats/mtlfileparser.cpp
	wolf/import/_3dformats/objfileparser.cpp
	wolf/import/wavefrontutils.cpp
	wolf/maputils.cpp
	wolf/stringutils.cpp
	wolf/vectorutils.cpp
)
target_include_directories(LibWolfImporter PRIVATE 
	../include/
)


