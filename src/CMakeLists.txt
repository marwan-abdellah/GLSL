#####################################################################
# Copyright © 2016
# Marwan Abdellah: <abdellah.marwan@gmail.com>
#####################################################################

#########################################################
#! Add source files
#########################################################
set( COMMON_SOURCES_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/common/Shaders.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/Utilities.cpp
)

#########################################################
#! Add header files
#########################################################
SET( COMMON_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/common/Shaders.h
    ${CMAKE_CURRENT_SOURCE_DIR}/common/Utilities.h
)

add_subdirectory( sample1 )
add_subdirectory( sample2 )

