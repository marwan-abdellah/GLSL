#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

namespace Utilities
{

/**
 * @brief printOglError
 * @param file
 * @param line
 * @return
 */
int printOglError( char *file, int line );

}


#define CHECK_GL_ERROR( ) Utilities::printOglError( __FILE__, __LINE__ )

#endif // UTILITIES_H
