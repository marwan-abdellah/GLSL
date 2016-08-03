#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <common/Shaders.h>
#include <common/Utilities.h>
#include <common/Matrix.h>
#include <common/Vector.h>

#define WINDOW_WIDTH    512
#define WINDOW_HEIGHT   512
#define WINDOW_TITLE    "Shader Sample !"

/**
 * @brief vertexCode
 */
GLuint vertexCode;

/**
 * @brief geometryCode
 */
GLuint geometryCode;

/**
 * @brief fragmentCode
 */
GLuint fragmentCode;

/**
 * @brief shaderProgram
 */
GLuint shaderProgram;

/**
 * @brief shaderProjectionMatrix
 */
GLuint shaderProjectionMatrix;

/**
 * @brief shaderViewMatrix
 */
GLuint shaderViewMatrix;

/**
 * @brief shaderVertex
 */
GLuint shaderVertex;

/**
 * @brief shaderColor
 */
GLuint shaderColor;

/**
 * @brief vertexArray
 * Vertex Array Objects Identifiers
 */
GLuint vertexArray;

/**
 * @brief projectionMatrix
 */
float projectionMatrix[16];

/**
 * @brief viewMatrix
 */
float viewMatrix[16];

// Data for triangle
float vertices1[] = { -1.0f, -1.0f, -5.0f, 1.0f,
                       1.0f, -1.0f, -5.0f, 1.0f,
                       0.0f, 1.0f, -5.0f, 1.0f };

float colors1[] = { 0.0f, 0.0f, 1.0f, 1.0f,
                    0.0f, 0.0f, 1.0f, 1.0f,
                    0.0f,0.0f, 1.0f, 1.0f };


void reshape( int w, int h )
{
    float ratio;
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if( h == 0 )
        h = 1;

    // Set the viewport to be the entire window
    glViewport( 0, 0, w, h );

    ratio = ( 1.0f * w ) / h;
    Matrix::buildProjectionMatrix( projectionMatrix, 15, ratio, 1.0f, 100.0f );
}

void setUniforms()
{
    // Must be called after glUseProgram
    glUniformMatrix4fv( shaderProjectionMatrix,  1, false, projectionMatrix );
    glUniformMatrix4fv( shaderViewMatrix,  1, false, viewMatrix );
}

void renderScene( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Matrix::setCamera( viewMatrix, 0, 0, 10, 0, 0, 0 );

    glUseProgram( shaderProgram );
    setUniforms( );

    glBindVertexArray( vertexArray );
    glDrawArrays( GL_TRIANGLES, 0, 3) ;

    glutSwapBuffers( );
}

void processNormalKeys( unsigned char key, int, int )
{
    if( key == 27 )
    {
        glDeleteVertexArrays( 1, &vertexArray );
        glDeleteProgram( shaderProgram );
        glDeleteShader( vertexCode );
        glDeleteShader( fragmentCode );
        exit( EXIT_SUCCESS );
    }
}

void initBuffers()
{
    GLuint buffers[2];

    glGenVertexArrays( 1, &vertexArray );

    // VAO for first triangle
    glBindVertexArray( vertexArray );

    // Generate two slots for the vertex and color buffers
    glGenBuffers( 2, buffers );

    // Bind buffer for vertices and copy data into buffer
    glBindBuffer( GL_ARRAY_BUFFER, buffers[0] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices1 ), vertices1,
                  GL_STATIC_DRAW );
    glEnableVertexAttribArray( shaderVertex );
    glVertexAttribPointer( shaderVertex, 4, GL_FLOAT, 0, 0, 0 );

    // Bind buffer for colors and copy data into buffer
    glBindBuffer( GL_ARRAY_BUFFER, buffers[1] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( colors1 ), colors1, GL_STATIC_DRAW );
    glEnableVertexAttribArray( shaderColor );
    glVertexAttribPointer( shaderColor, 4, GL_FLOAT, 0, 0, 0 );
}

void initShaders( )
{
    char* vertexShader = NULL;
    char* geometryShader = NULL;
    char* fragmentShader = NULL;

    vertexCode = glCreateShader( GL_VERTEX_SHADER );
    geometryCode = glCreateShader( GL_GEOMETRY_SHADER );
    fragmentCode = glCreateShader( GL_FRAGMENT_SHADER );

    // Read the shaders !
    vertexShader = Shader::readTextFile("Color.vert.glsl");
    geometryShader = Shader::readTextFile("Color.geom.glsl");
    fragmentShader = Shader::readTextFile("Color.frag.glsl");

    // Update the globals
    const char* vv = vertexShader;
    const char* gg = geometryShader;
    const char* ff = fragmentShader;

    glShaderSource( vertexCode, 1, &vv, NULL );
    glShaderSource( geometryCode, 1, &gg, NULL );
    glShaderSource( fragmentCode, 1, &ff, NULL );

    free( vertexShader );
    free( geometryShader );
    free( fragmentShader );

    glCompileShader( vertexCode );
    glCompileShader( geometryCode );
    glCompileShader( fragmentCode );

    Shader::printShaderInfoLog( vertexCode );
    Shader::printShaderInfoLog( geometryCode );
    Shader::printShaderInfoLog( fragmentCode );

    shaderProgram = glCreateProgram( );
    glAttachShader( shaderProgram, vertexCode );
    glAttachShader( shaderProgram, geometryCode );
    glAttachShader( shaderProgram, fragmentCode );

    glBindFragDataLocation( shaderProgram, 0, "outputF" );

    glLinkProgram( shaderProgram );
    Shader::printProgramInfoLog( shaderProgram );

    shaderVertex = glGetAttribLocation( shaderProgram, "inPosition" );
    shaderColor = glGetAttribLocation( shaderProgram, "inColor" );

    shaderProjectionMatrix = glGetUniformLocation( shaderProgram, "projMatrix" );
    shaderViewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix" );
}

int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );
    glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow( WINDOW_TITLE );

    glutDisplayFunc( renderScene );
    glutIdleFunc( renderScene );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( processNormalKeys );

    glewInit( );
    if( glewIsSupported( "GL_VERSION_3_3" ))
        printf( "Ready for OpenGL 3.3 \n" );
    else
    {
        printf( "OpenGL 3.3 is NOT supported, EXITTING ... \n");
        exit( EXIT_FAILURE );
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0,1.0,1.0,1.0);

    // INITIALIZE SHADERS
    initShaders( );

    // INITIALIZE OPENGL BUFFERS
    initBuffers();

    // RENDERING
    glutMainLoop( );

    return EXIT_SUCCESS;
}
