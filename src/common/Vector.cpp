#include <common/Vector.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>

namespace Vector
{

void crossProduct( float *a, float *b, float *res )
{
    res[0] = a[1] * b[2]  -  b[1] * a[2];
    res[1] = a[2] * b[0]  -  b[2] * a[0];
    res[2] = a[0] * b[1]  -  b[0] * a[1];
}

void normalize( float* a )
{
    float mag = sqrt( a[0] * a[0]  +  a[1] * a[1]  +  a[2] * a[2] );

    a[0] /= mag;
    a[1] /= mag;
    a[2] /= mag;
}

}
