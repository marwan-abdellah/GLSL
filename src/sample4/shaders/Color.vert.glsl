#version 150

uniform mat4 viewMatrix, projMatrix;

in vec4 inPosition;

void main()
{
    gl_Position = inPosition;
}
