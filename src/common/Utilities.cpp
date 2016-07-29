#include <common/Utilities.h>

namespace Utilities
{

int printOglError( char *file, int line )
{
    GLenum glError;
    int returnCode = 0;

    glError = glGetError( );
    while( glError != GL_NO_ERROR )
    {
        printf("OpenGL ERROR in file [%s] @ line [%d]: %s\n",
               file, line, gluErrorString( glError ));
        returnCode = 1;
        glError = glGetError( );
    }
    return returnCode;
}

}


