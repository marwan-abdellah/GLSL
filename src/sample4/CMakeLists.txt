#####################################################################
# Copyright © 2016
# Marwan Abdellah: <abdellah.marwan@gmail.com>
#####################################################################

get_filename_component( SAMPLE ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message( ${SAMPLE} )

#########################################################
#! Add source and header files
#########################################################
file( GLOB SAMPLE_SOURCE_FILES "*.cpp" )
file( GLOB SAMPLE_HEADER_FILES "*.h" )

#########################################################
#! Add shaders files
#########################################################
SET( SHADERS
    shaders/Color.vert.glsl
    shaders/Color.geom.glsl
    shaders/Color.frag.glsl
)

#########################################################
#! Generate executable(s)
#########################################################
# Voxy
add_executable( ${SAMPLE} ${SAMPLE_SOURCE_FILES}
    ${COMMON_FILES}
    ${SHADERS}
)

#! Copy all the shaders to the binary directory
configure_file( shaders/Color.vert.glsl ${CMAKE_CURRENT_BINARY_DIR}/Color.vert.glsl )
configure_file( shaders/Color.geom.glsl ${CMAKE_CURRENT_BINARY_DIR}/Color.geom.glsl )
configure_file( shaders/Color.frag.glsl ${CMAKE_CURRENT_BINARY_DIR}/Color.frag.glsl )
