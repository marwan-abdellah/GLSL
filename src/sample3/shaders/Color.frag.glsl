#version 150

in vec3 colorToFrag;
out vec4 outputF;

void main()
{
    outputF = vec4( colorToFrag, 1.0 );
}
