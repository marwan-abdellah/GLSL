#####################################################################
# Copyright © 2016
# Marwan Abdellah: <abdellah.marwan@gmail.com>
#####################################################################

#########################################################
#! Add source and header files
#########################################################
file( GLOB COMMON_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/*.h"
)

add_subdirectory( sample1 )
add_subdirectory( sample2 )
add_subdirectory( sample3 )

