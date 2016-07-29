#####################################################################
# Copyright © 2016
# Marwan Abdellah: <abdellah.marwan@gmail.com>
#####################################################################

#########################################################
#! Minimum required CMake version
#########################################################
cmake_minimum_required( VERSION 2.8 )

#########################################################
#! Project name
#########################################################
project( GLSL )

#########################################################
#! Add CMake customized modules
#########################################################
set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )

#########################################################
#! Find packages
#########################################################
include( OpenGL )
include( GLEW )
include( OpenEXR )
include( GLUT )

#! Add the binary directory to the include and set off the mocs.
include_directories( ${PROJECT_BINARY_DIR} )
include_directories( src )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( libs )

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_subdirectory( src )
