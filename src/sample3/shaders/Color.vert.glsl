#version 150

uniform mat4 viewMatrix, projMatrix;

in vec4 inPosition;

in vec3 inColor;
out vec3 colorToGeom;

void main()
{
    colorToGeom = inColor;
    gl_Position = projMatrix * viewMatrix * inPosition ;
}
