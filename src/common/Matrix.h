#ifndef MATRIX_H
#define MATRIX_H


namespace Matrix
{

/**
 * @brief setIdentityMatrix
 * Sets the square matrix mat to the identity matrix
 * size refers to the number of rows (or columns)
 * @param mat
 * @param size
 */
void setIdentityMatrix( float* mat, int size );

/**
 * @brief multMatrix
 * a = a * b;
 * @param a
 * @param b
 */
void multMatrix( float *a, float *b);

/**
 * @brief setTranslationMatrix
 * Defines a transformation matrix mat with a translation
 * @param mat
 * @param x
 * @param y
 * @param z
 */
void setTranslationMatrix( float* mat, float x, float y, float z );

/**
 * @brief buildProjectionMatrix
 * Projection Matrix
 * @param projectionMatrix
 * @param fov
 * @param ratio
 * @param nearP
 * @param farP
 */
void buildProjectionMatrix(float* projectionMatrix,
                           float fov, float ratio, float nearP, float farP );

/**
 * @brief setCamera
 * View Matrix
 * it assumes the camera is not tilted, i.e. a vertical up vector
 * @param viewMatrix
 * @param posX
 * @param posY
 * @param posZ
 * @param lookAtX
 * @param lookAtY
 * @param lookAtZ
 */
void setCamera(float* viewMatrix,
               float posX, float posY, float posZ,
               float lookAtX, float lookAtY, float lookAtZ );

}


#endif // MATRIX_H
