#include <common/Matrix.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <common/Vector.h>

#define M_PI            3.14159265358979323846

namespace Matrix
{

void setIdentityMatrix( float* mat, int size )
{
    // fill matrix with 0s
    for( int i = 0; i < size * size; ++i )
        mat[i] = 0.0f;

    // fill diagonal with 1s
    for( int i = 0; i < size; ++i )
        mat[i + i * size] = 1.0f;
}

void multMatrix( float *a, float *b)
{
    float res[16];

    for( int i = 0; i < 4; ++i )
    {
        for( int j = 0; j < 4; ++j )
        {
            res[j * 4 + i] = 0.0f;
            for( int k = 0; k < 4; ++k )
            {
                res[j * 4 + i] += a[k * 4 + i] * b[j * 4 + k];
            }
        }
    }
    memcpy( a, res, 16 * sizeof( float ));

}


void setTranslationMatrix( float* mat, float x, float y, float z )
{
    setIdentityMatrix( mat,4 );
    mat[12] = x;
    mat[13] = y;
    mat[14] = z;
}

void buildProjectionMatrix( float* projectionMatrix, float fov, float ratio, float nearP, float farP )
{
    float f = 1.0f / tan (fov * ( M_PI / 360.0 ));

    setIdentityMatrix( projectionMatrix, 4 );

    projectionMatrix[0] = f / ratio;
    projectionMatrix[1 * 4 + 1] = f;
    projectionMatrix[2 * 4 + 2] = ( farP + nearP ) / ( nearP - farP );
    projectionMatrix[3 * 4 + 2] = ( 2.0f * farP * nearP ) / ( nearP - farP );
    projectionMatrix[2 * 4 + 3] = -1.0f;
    projectionMatrix[3 * 4 + 3] = 0.0f;
}

void setCamera( float* viewMatrix, float posX, float posY, float posZ,
                float lookAtX, float lookAtY, float lookAtZ )
{

    float dir[3], right[3], up[3];

    up[0] = 0.0f;   up[1] = 1.0f;   up[2] = 0.0f;

    dir[0] =  ( lookAtX - posX );
    dir[1] =  ( lookAtY - posY );
    dir[2] =  ( lookAtZ - posZ );
    Vector::normalize( dir );

    Vector::crossProduct( dir, up, right );
    Vector::normalize( right );

    Vector::crossProduct( right, dir, up );
    Vector::normalize( up );

    float aux[16];

    viewMatrix[0]  = right[0];
    viewMatrix[4]  = right[1];
    viewMatrix[8]  = right[2];
    viewMatrix[12] = 0.0f;

    viewMatrix[1]  = up[0];
    viewMatrix[5]  = up[1];
    viewMatrix[9]  = up[2];
    viewMatrix[13] = 0.0f;

    viewMatrix[2]  = -dir[0];
    viewMatrix[6]  = -dir[1];
    viewMatrix[10] = -dir[2];
    viewMatrix[14] =  0.0f;

    viewMatrix[3]  = 0.0f;
    viewMatrix[7]  = 0.0f;
    viewMatrix[11] = 0.0f;
    viewMatrix[15] = 1.0f;

    setTranslationMatrix( aux, -posX, -posY, -posZ );

    multMatrix( viewMatrix, aux );
}

}

