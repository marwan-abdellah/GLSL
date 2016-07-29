#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <common/Shaders.h>
#include <common/Utilities.h>

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
 * @brief angle
 */
float angle = 0;


float lightPosition[4] = { 1, 0.5, 1, 0};

void reshape( int w, int h )
{
    // Prevent a divide by zero, when window is too short
    if( h == 0 )
        h = 1;

    float ratio = 1.0 * w / h;

    // Reset the coordinate system before modifying
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    // Set the viewport to be the entire window
    glViewport( 0, 0, w, h );

    // Set the correct perspective.
    gluPerspective( 45, ratio, 1, 1000 );
    glMatrixMode( GL_MODELVIEW );


}

void renderScene( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glLoadIdentity( );
    gluLookAt( 0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f );

    glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );
    glRotatef( angle, 0, 1, 1 );
    glutSolidTeapot( 1 );
    angle += 1;

    glutSwapBuffers( );
}

void processNormalKeys( unsigned char key, int, int )
{
    if( key == 27 )
        exit( EXIT_SUCCESS );
}

void initShaders( )
{
    char *vertexShader = NULL;
    char* fragmentShader = NULL;

    vertexCode = glCreateShader( GL_VERTEX_SHADER );
    fragmentCode = glCreateShader( GL_FRAGMENT_SHADER );

    // Read the shaders !
    vertexShader = Shader::readTextFile("Minimal.vert.glsl");
    fragmentShader = Shader::readTextFile("Minimal.frag.glsl");

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

    glLinkProgram( shaderProgram );
    Shader::printProgramInfoLog( shaderProgram );

    glUseProgram( shaderProgram );
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

    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0);
    glEnable( GL_CULL_FACE );

    glewInit( );
    if( glewIsSupported( "GL_VERSION_2_0" ))
        printf( "Ready for OpenGL 2.0 \n" );
    else
    {
        printf( "OpenGL 2.0 is NOT supported, EXITTING ... \n");
        exit( EXIT_FAILURE );
    }

    // INITIALIZE SHADERS
    initShaders( );

    // RENDERING
    glutMainLoop( );

    return EXIT_SUCCESS;
}

