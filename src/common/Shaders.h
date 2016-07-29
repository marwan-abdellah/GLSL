#include <GL/gl.h>

namespace Shader
{

/**
 * @brief readTextFile
 * @param fn
 * @return
 */
char *readTextFile( const char *fn );

/**
 * @brief writeTextFile
 * @param fn
 * @param s
 * @return
 */
int writeTextFile( char *fn, char *s );

/**
 * @brief printShaderInfoLog
 * @param object
 */
void printShaderInfoLog( GLuint object );

/**
 * @brief printProgramInfoLog
 * @param object
 */
void printProgramInfoLog( GLuint object );

}
