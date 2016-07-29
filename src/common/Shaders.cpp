#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>

namespace Shader
{

char* readTextFile(const char *fn)
{
    FILE *fp;
    char *content = NULL;

    long count=0;

    if( fn != NULL )
    {
        fp = fopen( fn, "rt" );

        if( fp != NULL )
        {
            fseek( fp, 0, SEEK_END );
            count = ftell( fp );
            rewind( fp );

            if( count > 0 )
            {
                content = ( char * ) malloc( sizeof( char ) * ( count + 1 ));
                count = fread( content, sizeof(char), count, fp );
                content[count] = '\0';
            }
            fclose( fp );
        }
    }
    return content;
}

int writeTextFile( char* fn, char* s )
{
    FILE *fp;
    int status = 0;

    if( fn != NULL )
    {
        fp = fopen( fn, "w" );

        if( fp != NULL )
        {

            if( fwrite( s, sizeof( char ), strlen( s ), fp ) == strlen( s ))
                status = 1;
            fclose( fp );
        }
    }
    return( status );
}

void printShaderInfoLog( GLuint object )
{
    int infologLength = 0;
    int charsWritten  = 0;
    char* infoLog;

    glGetShaderiv( object, GL_INFO_LOG_LENGTH, &infologLength );

    if ( infologLength > 0 )
    {
        infoLog = ( char* ) malloc( infologLength );
        glGetShaderInfoLog( object, infologLength, &charsWritten, infoLog );
        printf( "%s \n", infoLog );
        free( infoLog );
    }
}

void printProgramInfoLog( GLuint object )
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv( object, GL_INFO_LOG_LENGTH,&infologLength );

    if( infologLength > 0 )
    {
        infoLog = ( char* ) malloc( infologLength );
        glGetProgramInfoLog( object, infologLength, &charsWritten, infoLog );
        printf( "%s \n", infoLog );
        free( infoLog );
    }
}

}





