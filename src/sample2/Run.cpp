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
GLuint vertexArray[3];

/**
 * @brief projectionMatrix
 */
float projectionMatrix[16];

/**
 * @brief viewMatrix
 */
float viewMatrix[16];

// Data for drawing Axis
float verticesAxis[] = { -20.0f, 0.0f, 0.0f, 1.0f,
                         20.0f, 0.0f, 0.0f, 1.0f,
                         0.0f, -20.0f, 0.0f, 1.0f,
                         0.0f,  20.0f, 0.0f, 1.0f,
                         0.0f, 0.0f, -20.0f, 1.0f,
                         0.0f, 0.0f,  20.0f, 1.0f };

float colorAxis[] = { 0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f };

// Data for triangle 1
float vertices1[] = { -3.0f, 0.0f, -5.0f, 1.0f,
                      -1.0f, 0.0f, -5.0f, 1.0f,
                      -2.0f, 2.0f, -5.0f, 1.0f };

float colors1[] = { 0.0f, 0.0f, 1.0f, 1.0f,
                    0.0f, 0.0f, 1.0f, 1.0f,
                    0.0f,0.0f, 1.0f, 1.0f };

// Data for triangle 2
float vertices2[] = { 1.0f, 0.0f, -5.0f, 1.0f,
                      3.0f, 0.0f, -5.0f, 1.0f,
                      2.0f, 2.0f, -5.0f, 1.0f };

float colors2[] = { 1.0f, 0.0f, 0.0f, 1.0f,
                    1.0f, 0.0f, 0.0f, 1.0f,
                    1.0f,0.0f, 0.0f, 1.0f };


/**
 * @brief angle
 */
float angle = 0;


float lightPosition[4] = { 1, 0.5, 1, 0};

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
    Matrix::buildProjectionMatrix( projectionMatrix, 53.13f, ratio, 1.0f, 30.0f );
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

    Matrix::setCamera( viewMatrix, 10, 2, 10, 0, 2, -5 );

    glUseProgram( shaderProgram );
    setUniforms( );

    glBindVertexArray( vertexArray[0]  );
    glDrawArrays( GL_TRIANGLES, 0, 3) ;

    glBindVertexArray( vertexArray[1] );
    glDrawArrays( GL_TRIANGLES, 0, 3) ;

    glBindVertexArray( vertexArray[2] );
    glDrawArrays( GL_LINES, 0, 6 );

    glutSwapBuffers( );
}

void processNormalKeys( unsigned char key, int, int )
{
    if( key == 27 )
    {
        glDeleteVertexArrays( 3, vertexArray );
        glDeleteProgram( shaderProgram );
        glDeleteShader( vertexCode );
        glDeleteShader( fragmentCode );
        exit( EXIT_SUCCESS );
    }
}

void initBuffers()
{
    GLuint buffers[2];

    glGenVertexArrays( 3, vertexArray );

    // VAO for first triangle
    glBindVertexArray( vertexArray[0] );

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

    // VAO for second triangle
    glBindVertexArray( vertexArray[1] );

    // Generate two slots for the vertex and color buffers
    glGenBuffers( 2, buffers );

    // Bind buffer for vertices and copy data into buffer
    glBindBuffer( GL_ARRAY_BUFFER, buffers[0] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices2 ), vertices2,
                  GL_STATIC_DRAW );
    glEnableVertexAttribArray( shaderVertex);
    glVertexAttribPointer( shaderVertex, 4, GL_FLOAT, 0, 0, 0 );

    // Bind buffer for colors and copy data into buffer
    glBindBuffer( GL_ARRAY_BUFFER, buffers[1]);
    glBufferData( GL_ARRAY_BUFFER, sizeof(colors2), colors2, GL_STATIC_DRAW );
    glEnableVertexAttribArray( shaderColor);
    glVertexAttribPointer( shaderColor, 4, GL_FLOAT, 0, 0, 0 );

    // This VAO is for the Axis
    glBindVertexArray( vertexArray[2] );

    // Generate two slots for the vertex and color buffers
    glGenBuffers( 2, buffers );

    // Bind buffer for vertices and copy data into buffer
    glBindBuffer( GL_ARRAY_BUFFER, buffers[0] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( verticesAxis ), verticesAxis,
                  GL_STATIC_DRAW );
    glEnableVertexAttribArray( shaderVertex );
    glVertexAttribPointer( shaderVertex, 4, GL_FLOAT, 0, 0, 0 );

    // bind buffer for colors and copy data into buffer
    glBindBuffer( GL_ARRAY_BUFFER, buffers[1] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( colorAxis ), colorAxis,
                  GL_STATIC_DRAW );
    glEnableVertexAttribArray( shaderColor );
    glVertexAttribPointer( shaderColor, 4, GL_FLOAT, 0, 0, 0 );

}

void initShaders( )
{
    char* vertexShader = NULL;
    char* geometryShader = NULL;
    char* fragmentShader = NULL;

    vertexCode = glCreateShader( GL_VERTEX_SHADER );
    fragmentCode = glCreateShader( GL_FRAGMENT_SHADER );

    // Read the shaders !
    vertexShader = Shader::readTextFile("Color.vert.glsl");
    fragmentShader = Shader::readTextFile("Color.frag.glsl");

    // Update the globals
    const char* vv = vertexShader;
    const char* ff = fragmentShader;

    glShaderSource( vertexCode, 1, &vv, NULL );
    glShaderSource( fragmentCode, 1, &ff, NULL );

    free( vertexShader );
    free( fragmentShader );

    glCompileShader( vertexCode );
    glCompileShader( fragmentCode );

    Shader::printShaderInfoLog( vertexCode );
    Shader::printShaderInfoLog( fragmentCode );

    shaderProgram = glCreateProgram( );
    glAttachShader( shaderProgram, vertexCode );
    glAttachShader( shaderProgram, fragmentCode );

    glBindFragDataLocation( shaderProgram, 0, "outputF" );

    glLinkProgram( shaderProgram );
    Shader::printProgramInfoLog( shaderProgram );

    shaderVertex = glGetAttribLocation( shaderProgram, "position" );
    shaderColor = glGetAttribLocation( shaderProgram, "color" );

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
