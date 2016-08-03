#version 150

layout(triangles) in;
layout (triangle_strip, max_vertices=3) out;

in vec3 colorToGeom[3];
out vec3 colorToFrag;

void main()
{
    for(int i = 0; i < gl_in.length(); i++)
    {
        // Copy attributes
        gl_Position = gl_in[i].gl_Position;

        if( i == 0 )
        colorToFrag = vec3( 1, 0, 0); //colorToGeom[i];
        if( i == 1 )
        colorToFrag = vec3( 0, 1, 0); //colorToGeom[i];
        if( i == 2 )
        colorToFrag = vec3( 0, 0, 1); //colorToGeom[i];

        // Done with the vertex
        EmitVertex();
    }
}
